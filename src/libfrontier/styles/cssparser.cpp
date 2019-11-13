
#include <stdio.h>
#include "css3Lexer.h"
#include "css3Parser.h"
#include "css3BaseListener.h"

#include <string>
#include <vector>
#include <typeinfo>

#include <frontier/styles.h>
#include <frontier/utils.h>

#include "cssparser.h"

using namespace Frontier;
using namespace antlr4;
using namespace Geek;
using namespace std;

struct ShortcutProperty
{
    const char* name;
    bool copyToAll;
    const char* properties[4];
} g_shortcutProperties[] =
{
    { "border", true, {"border-top", "border-right", "border-bottom", "border-left"}},
    { "border-width", true, {"border-top-width", "border-right-width", "border-bottom-width", "border-left-width"}},
    { "border-style", true, {"border-top-style", "border-right-style", "border-bottom-style", "border-left-style"}},
    { "border-color", true, {"border-top-color", "border-right-color", "border-bottom-color", "border-left-color"}},
    { "border-top", false, {"border-top-width", "border-top-style", "border-top-color", NULL}},
    { "border-right", false, {"border-right-width", "border-right-style", "border-right-color", NULL}},
    { "border-bottom", false, {"border-bottom-width", "border-bottom-style", "border-bottom-color", NULL}},
    { "border-left", false, {"border-left-width", "border-left-style", "border-left-color", NULL}},

    { "margin", true, {"margin-top", "margin-right", "margin-bottom", "margin-left"}},
    { "padding", true, {"padding-top", "padding-right", "padding-bottom", "padding-left"}},
};

struct IdentValues
{
    const char* ident;
    int64_t value;
} g_identValues[] =
{
    {"true", 1},
    {"false", 0},

    {"black", 0x000000},
    {"white", 0xffffff},

    {"none", 0x0},
    {"solid", 0x1},

    {"disc", 0x1},
};

static std::string identString(css3Parser::IdentContext* identCtx)
{
    return identCtx->Ident()->getText().c_str();
}

class RuleSetListener : public css3BaseListener
{
 private:
    StyleEngine* m_styleEngine;

 public:
    RuleSetListener(StyleEngine* engine)
    {
        m_styleEngine = engine;
    }

    virtual void enterKnownRuleset(css3Parser::KnownRulesetContext * ctx) override;
    int64_t getTermValue(std::string property, css3Parser::TermContext* term0);

    int64_t getFontFamilyValue(std::string fontFamily);
};

void RuleSetListener::enterKnownRuleset(css3Parser::KnownRulesetContext * ctx)
{
    printf("RuleSetListener::enterKnownRuleset: Ruleset\n");

    css3Parser::SelectorGroupContext* selectorGroup = ctx->selectorGroup();
    if (selectorGroup == NULL)
    {
        return;
    }

    css3Parser::DeclarationListContext* declList = ctx->declarationList();
    if (declList == NULL)
    {
        return;
    }

    vector<StyleRule*> rules;

    for (css3Parser::SelectorContext* selector : selectorGroup->selector())
    {
        StyleRule* rule = new StyleRule();
        printf("RuleSetListener::enterKnownRuleset:  -> Selector:\n");
        for (css3Parser::SimpleSelectorSequenceContext* sss : selector->simpleSelectorSequence())
        {
            css3Parser::TypeSelectorContext* typeSelector = sss->typeSelector();
            if (typeSelector != NULL)
            {
                std::string elementName = typeSelector->elementName()->ident()->Ident()->getText();
                printf("RuleSetListener::enterKnownRuleset:     -> elementName=%s\n", elementName.c_str());
                rule->setWidgetType(Utils::string2wstring(elementName));
            }

            if (sss->universal() != NULL)
            {
                printf("RuleSetListener::enterKnownRuleset:     -> universal (*)\n");
                rule->setWidgetType(L"*");
            }

            for (tree::TerminalNode* hash : sss->Hash())
            {
                string hashStr = hash->getText();
                if (hashStr[0] == '#')
                {
                    hashStr = hashStr.substr(1);
                }
                printf("RuleSetListener::enterKnownRuleset:     -> hash=%s\n", hashStr.c_str());
                rule->setId(Utils::string2wstring(hashStr));
            }

            for (css3Parser::ClassNameContext* className : sss->className())
            {
                string classStr = identString(className->ident());
                printf("RuleSetListener::enterKnownRuleset:     -> className=%s\n", classStr.c_str());
                rule->setClassName(Utils::string2wstring(classStr.c_str()));
            }

            for (css3Parser::PseudoContext* pseudo : sss->pseudo())
            {
                string pseudoClass = identString(pseudo->ident());
                printf("RuleSetListener::enterKnownRuleset:     -> pseudo=%s\n", pseudoClass.c_str());
                rule->setState(pseudoClass);
            }
        }
        rules.push_back(rule);
    }

    printf("RuleSetListener::enterKnownRuleset:  -> Declarations:\n");
    for (css3Parser::DeclarationContext* decl0 : declList->declaration())
    {
        if (typeid(*decl0).hash_code() != typeid(css3Parser::KnownDeclarationContext).hash_code())
        {
            printf("RuleSetListener::enterKnownRuleset:   -> Declaration is not a KnownDeclarationContext\n");
            continue;
        }
        css3Parser::KnownDeclarationContext* decl = (css3Parser::KnownDeclarationContext*)decl0;

        css3Parser::PropertyContext* property0 = decl->property();
        if (typeid(*property0).hash_code() != typeid(css3Parser::GoodPropertyContext).hash_code())
        {
            printf("RuleSetListener::enterKnownRuleset:   -> Declaration: Not a GoodProperty! property=%s\n", typeid(*property0).name());
            continue;
        }

        css3Parser::GoodPropertyContext* propertyCtx = (css3Parser::GoodPropertyContext*)property0;
        string property = identString(propertyCtx->ident());

        printf("RuleSetListener::enterKnownRuleset:   -> property=%s\n", property.c_str());

        vector<int64_t> values;
        for (css3Parser::TermContext* term0 : decl->expr()->term())
        {
            int64_t value = getTermValue(property, term0);
            printf("RuleSetListener::enterKnownRuleset:     -> Term: value=%llx\n", value);
            values.push_back(value);
        }

        for (StyleRule* rule : rules)
        {
            rule->applyProperty(property, values);
        }
    }

    for (StyleRule* rule : rules)
    {
        m_styleEngine->addRule(rule);
    }
}


int64_t RuleSetListener::getTermValue(string property, css3Parser::TermContext* term0)
{
    if (typeid(*term0).hash_code() != typeid(css3Parser::KnownTermContext).hash_code())
    {
        printf("RuleSetListener::getTermValue:   -> Term is not a KnownTerm: %s\n", typeid(*term0).name());
        return 0;
    }

    css3Parser::KnownTermContext* term = (css3Parser::KnownTermContext*)term0;
    if (term->number() != NULL)
    {
        string numberStr = term->number()->Number()->getText();
        printf("RuleSetListener::getTermValue:   -> Term: number=%s\n", numberStr.c_str());
        return atoi(numberStr.c_str());
    }
    if (term->dimension() != NULL)
    {
        std::string dimStr = term->dimension()->Dimension()->getText();
        printf("RuleSetListener::getTermValue:   -> Term: dimension=%s\n", dimStr.c_str());
        return atoi(dimStr.c_str());
    }
    if (term->hexcolor() != NULL)
    {
        string hex = term->hexcolor()->Hash()->getText();
        printf("RuleSetListener::getTermValue:   -> Term: hexcolor=%s\n", hex.c_str());
        hex = hex.substr(1);

        if (hex.length() == 3)
        {
            string expandedHex = "";
            expandedHex += hex[0];
            expandedHex += hex[0];
            expandedHex += hex[1];
            expandedHex += hex[1];
            expandedHex += hex[2];
            expandedHex += hex[2];;
            hex = expandedHex.c_str();
        }

        uint64_t rgb = strtol(hex.c_str(), NULL, 16);
        rgb |= 0xff000000; // Set alpha
        return rgb;
    }
    if (term->String() != NULL)
    {
        string str = term->String()->getText();
        printf("RuleSetListener::getTermValue:   -> Term: String=%s\n", str.c_str());
        if (property == "font-family")
        {
            return getFontFamilyValue(str);
        }
        return 0;
    }
    if (term->ident() != NULL)
    {
        string identStr = identString(term->ident());
        printf("RuleSetListener::getTermValue:   -> Term: ident=%s\n", identStr.c_str());

        if (property == "font-family")
        {
            return getFontFamilyValue(identStr);
        }

        for (auto val : g_identValues)
        {
            if (!strcmp(val.ident, identStr.c_str()))
            {
                printf("RuleSetListener::getTermValue:   -> Term: ident MAPPED to %lld\n", val.value);
                return val.value;
            }
        }
        printf("RuleSetListener::getTermValue:     -> Term: %s is UNKNOWN\n", identStr.c_str());
    }
    if (term->function())
    {
        const char* functionName = term->function()->Function()->getText().c_str();
        printf("RuleSetListener::getTermValue:   -> function: Function=%s\n", functionName);
        vector<uint32_t> funcValues;
        for (css3Parser::TermContext* funcTerm0 : term->function()->expr()->term())
        {
            int64_t funcValue = getTermValue(property, funcTerm0);
            printf("RuleSetListener::getTermValue:   -> function: funcValue=%lld\n", funcValue);
            funcValues.push_back(funcValue);
        }

        if (!strcmp("rgb(", functionName))
        {
            uint64_t rgb = 0;
            unsigned int i;
            for (i = 0; i < 3 && i < funcValues.size(); i++)
            {
                rgb <<= 8;
                rgb |= funcValues.at(i);
            }
            rgb |= 0xff000000; // Set alpha
            printf("RuleSetListener::getTermValue:   -> function: RGB: 0x%llx\n", rgb);
            return rgb;
        }
        else
        {
            printf("RuleSetListener::getTermValue:   -> function: Unknown function: %s\n", functionName);
        }
        return 0;
    }

    return 0;
}

int64_t RuleSetListener::getFontFamilyValue(std::string fontFamily)
{
    if (fontFamily.at(0) == '"')
    {
        fontFamily = fontFamily.substr(1);
        int len = fontFamily.length();
        if (len <= 0)
        {
            return 0;
        }

        if (fontFamily.at(len - 1) == '"')
        {
            fontFamily = fontFamily.substr(0, len - 1);
        }
    }

    printf("RuleSetListener::getFontFamilyValue: fontFamily=%s\n", fontFamily.c_str());
    return (int64_t)strdup(fontFamily.c_str());
}

ShortcutProperty* findShortcutProperty(string property)
{
    unsigned int i;
    for (i = 0; i < sizeof(g_shortcutProperties) / sizeof(ShortcutProperty); i++)
    {
        if (!strcmp(g_shortcutProperties[i].name, property.c_str()))
        {
            return &(g_shortcutProperties[i]);
        }
    }
    return NULL;
}

void StyleRule::setProperty(string property, int64_t value)
{
    ShortcutProperty* shortcutProperty = findShortcutProperty(property);
    if (shortcutProperty != NULL)
    {
        printf("StyleRule::setProperty: ERROR: property \"%s\" is a shortcut!\n", property.c_str());
        return;
    }

    printf("setProperty: %s -> %llu (0x%llx)\n", property.c_str(), value, value);

    auto it = m_properties.find(property);
    if (it != m_properties.end())
    {
        m_properties.erase(it);
    }

    m_properties.insert(make_pair(property, value));
}

void StyleRule::applyProperty(string property, int64_t value)
{
    vector<int64_t> values;
    values.push_back(value);
    applyProperty(property, values);
}

void StyleRule::applyProperty(string property, vector<int64_t> values)
{
    ShortcutProperty* shortcutProperty = findShortcutProperty(property);

    if (shortcutProperty == NULL)
    {
        if (values.size() != 1)
        {
            printf("StyleRule::applyProperty: ERROR: Property should only have 1 value\n");
            return;
        }
        setProperty(property, values.at(0));
        return;
    }

    string valuesStr = "";
    bool space = false;
    for (int64_t v : values)
    {
        if (space)
        {
            valuesStr += " ";
        }
        space = true;
        char buf[64];
        snprintf(buf, 64, "%lld", v);
        valuesStr += string(buf);
    }

    if (shortcutProperty->copyToAll)
    {
        for (auto childProperty : shortcutProperty->properties)
        {
            if (childProperty == NULL)
            {
                break;
            }
            //printf("applyMultiProperty: Copying values to: %s\n", childProperty);
            applyProperty(childProperty, values);
        }
    }
    else
    {
        unsigned int idx = 0;
        for (auto childProperty : shortcutProperty->properties)
        {
            if (childProperty == NULL)
            {
                break;
            }

            //printf("applyMultiProperty: Copying value %d to: %s\n", idx, childProperty);
            if (idx >= values.size())
            {
                //printf("applyMultiProperty:  NOT ENOUGH VALUES!\n");
                break;
            }

            vector<int64_t> childValues;
            childValues.push_back(values.at(idx));
            applyProperty(childProperty, childValues);

            idx++;
        }
    }
}


CssParser::CssParser(StyleEngine* styleEngine) : Logger("CssParser")
{
    m_styleEngine = styleEngine;
}

CssParser::~CssParser()
{
}

void CssParser::parse(std::string path)
{
    log(DEBUG, "Parsing file: %s", path.c_str());

    ANTLRFileStream* stream = new ANTLRFileStream(path.c_str());

    css3Lexer lexer(stream);
    CommonTokenStream tokens(&lexer);
    css3Parser parser(&tokens);

    tree::ParseTree *tree = parser.stylesheet();
    RuleSetListener listener(m_styleEngine);
    tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
}

