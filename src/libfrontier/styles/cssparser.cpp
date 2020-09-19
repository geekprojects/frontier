/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2020 Ian Parker <ian@geekprojects.com>
 *
 * This file is part of Frontier.
 *
 * Frontier is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Frontier is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Frontier.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "css3Lexer.h"
#include "css3Parser.h"
#include "css3BaseListener.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <string>
#include <vector>
#include <typeinfo>

#include <frontier/styles.h>
#include <frontier/utils.h>

#include "cssparser.h"

#undef DEBUG_CSS_PARSER

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
    uint64_t value;
} g_identValues[] =
{
    {"true", 1},
    {"false", 0},

    {"black", 0x000000},
    {"white", 0xffffff},
    {"red",   0xff0000},
    {"yellow", 0xffff00},

    {"none", 0x0},
    {"solid", 0x1},

    {"disc", 0x1},

    {"transparent", FRONTIER_COLOUR_TRANSPARENT},

    // Alignment
    {"left", 0},
    {"center", 1},
    {"right", 2},
    {"top", 0},
    {"middle", 1},
    {"bottom", 2},
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
    Value getTermValue(std::string property, css3Parser::TermContext* term0);

    Value getFontFamilyValue(std::string fontFamily);
};

void RuleSetListener::enterKnownRuleset(css3Parser::KnownRulesetContext * ctx)
{
#ifdef DEBUG_CSS_PARSER
    printf("RuleSetListener::enterKnownRuleset: Ruleset\n");
#endif

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
#ifdef DEBUG_CSS_PARSER
        printf("RuleSetListener::enterKnownRuleset:  -> Selector:\n");
#endif

        bool descendant = false;
        for (css3Parser::CombinatorContext* combinator : selector->combinator())
        {
            printf("RuleSetListener::enterKnownRuleset:  -> Selector: combinator: %p\n", combinator);
            if (combinator->Greater() != NULL)
            {
                printf("RuleSetListener::enterKnownRuleset:  -> Selector: combinator: Greater than!!\n");
                descendant = true;
            }
            else
            {
                printf("RuleSetListener::enterKnownRuleset:  -> Selector: combinator: Unknown type!\n");
            }
        }

        for (css3Parser::SimpleSelectorSequenceContext* sss : selector->simpleSelectorSequence())
        {
            StyleSelector selector;
            selector.descendant = descendant;

            css3Parser::TypeSelectorContext* typeSelector = sss->typeSelector();
            if (typeSelector != NULL)
            {
                std::string elementName = typeSelector->elementName()->ident()->Ident()->getText();
#ifdef DEBUG_CSS_PARSER
                printf("RuleSetListener::enterKnownRuleset:     -> elementName=%s\n", elementName.c_str());
#endif
                selector.widgetType = Utils::string2wstring(elementName);
            }

            if (sss->universal() != NULL)
            {
#ifdef DEBUG_CSS_PARSER
                printf("RuleSetListener::enterKnownRuleset:     -> universal (*)\n");
#endif
                selector.widgetType = L"*";
            }

            for (tree::TerminalNode* hash : sss->Hash())
            {
                string hashStr = hash->getText();
                if (hashStr[0] == '#')
                {
                    hashStr = hashStr.substr(1);
                }
#ifdef DEBUG_CSS_PARSER
                printf("RuleSetListener::enterKnownRuleset:     -> hash=%s\n", hashStr.c_str());
#endif
                selector.id = Utils::string2wstring(hashStr);
            }

            for (css3Parser::ClassNameContext* className : sss->className())
            {
                string classStr = identString(className->ident());
#ifdef DEBUG_CSS_PARSER
                printf("RuleSetListener::enterKnownRuleset:     -> className=%s\n", classStr.c_str());
#endif
                selector.className = Utils::string2wstring(classStr.c_str());
            }

            for (css3Parser::PseudoContext* pseudo : sss->pseudo())
            {
                string pseudoClass = identString(pseudo->ident());
#ifdef DEBUG_CSS_PARSER
                printf("RuleSetListener::enterKnownRuleset:     -> pseudo=%s\n", pseudoClass.c_str());
#endif
                selector.state = pseudoClass;
            }

            rule->addSelector(selector);
        }
        rules.push_back(rule);
    }

#ifdef DEBUG_CSS_PARSER
    printf("RuleSetListener::enterKnownRuleset:  -> Declarations:\n");
#endif
    for (css3Parser::DeclarationContext* decl0 : declList->declaration())
    {
        if (typeid(*decl0).hash_code() != typeid(css3Parser::KnownDeclarationContext).hash_code())
        {
#ifdef DEBUG_CSS_PARSER
            printf("RuleSetListener::enterKnownRuleset:   -> Declaration is not a KnownDeclarationContext\n");
#endif
            continue;
        }
        css3Parser::KnownDeclarationContext* decl = (css3Parser::KnownDeclarationContext*)decl0;

        css3Parser::PropertyContext* property0 = decl->property();
        if (typeid(*property0).hash_code() != typeid(css3Parser::GoodPropertyContext).hash_code())
        {
#ifdef DEBUG_CSS_PARSER
            printf("RuleSetListener::enterKnownRuleset:   -> Declaration: Not a GoodProperty! property=%s\n", typeid(*property0).name());
#endif
            continue;
        }

        css3Parser::GoodPropertyContext* propertyCtx = (css3Parser::GoodPropertyContext*)property0;
        string property = identString(propertyCtx->ident());

#ifdef DEBUG_CSS_PARSER
        printf("RuleSetListener::enterKnownRuleset:   -> property=%s\n", property.c_str());
#endif

        vector<Value> values;
        for (css3Parser::TermContext* term0 : decl->expr()->term())
        {
            Value value = getTermValue(property, term0);
#ifdef DEBUG_CSS_PARSER
            printf("RuleSetListener::enterKnownRuleset:     -> Term: value=%llx\n", value);
#endif
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


Value RuleSetListener::getTermValue(string property, css3Parser::TermContext* term0)
{
    if (typeid(*term0).hash_code() != typeid(css3Parser::KnownTermContext).hash_code())
    {
#ifdef DEBUG_CSS_PARSER
        printf("RuleSetListener::getTermValue:   -> Term is not a KnownTerm: %s\n", typeid(*term0).name());
#endif
        return 0;
    }

    css3Parser::KnownTermContext* term = (css3Parser::KnownTermContext*)term0;
    if (term->number() != NULL)
    {
        string numberStr = term->number()->Number()->getText();
#ifdef DEBUG_CSS_PARSER
        printf("RuleSetListener::getTermValue:   -> Term: number=%s\n", numberStr.c_str());
#endif
        return atoi(numberStr.c_str());
    }
    if (term->dimension() != NULL)
    {
        std::string dimStr = term->dimension()->Dimension()->getText();
#ifdef DEBUG_CSS_PARSER
        printf("RuleSetListener::getTermValue:   -> Term: dimension=%s\n", dimStr.c_str());
#endif
        return atoi(dimStr.c_str());
    }
    if (term->hexcolor() != NULL)
    {
        string hex = term->hexcolor()->Hash()->getText();
#ifdef DEBUG_CSS_PARSER
        printf("RuleSetListener::getTermValue:   -> Term: hexcolor=%s\n", hex.c_str());
#endif
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

        uint64_t rgb = strtol(hex.c_str(), NULL, 16) & 0xffffff;
        rgb |= 0xff000000; // Set alpha
        return rgb;
    }
    if (term->String() != NULL)
    {
        string str = term->String()->getText();
#ifdef DEBUG_CSS_PARSER
        printf("RuleSetListener::getTermValue:   -> Term: String=%s\n", str.c_str());
#endif
        if (property == "font-family")
        {
            return getFontFamilyValue(str);
        }
        else if (property == "font-style")
        {
            return getFontFamilyValue(str);
        }
        return 0;
    }
    if (term->ident() != NULL)
    {
        string identStr = identString(term->ident());
#ifdef DEBUG_CSS_PARSER
        printf("RuleSetListener::getTermValue:   -> Term: ident=%s\n", identStr.c_str());
#endif

        if (property == "font-family")
        {
            return getFontFamilyValue(identStr);
        }
        else if (property == "font-style")
        {
            return getFontFamilyValue(identStr);
        }

        for (auto val : g_identValues)
        {
            if (!strcmp(val.ident, identStr.c_str()))
            {
#ifdef DEBUG_CSS_PARSER
                printf("RuleSetListener::getTermValue:   -> Term: ident: %s MAPPED to %llx\n", val.ident, val.value);
#endif
                return val.value;
            }
        }
#ifdef DEBUG_CSS_PARSER
        printf("RuleSetListener::getTermValue:     -> Term: %s is UNKNOWN\n", identStr.c_str());
#endif
    }
    if (term->function())
    {
        string functionName = term->function()->Function()->getText();
#ifdef DEBUG_CSS_PARSER
        printf("RuleSetListener::getTermValue:   -> function: Function=%s\n", functionName.c_str());
#endif
        vector<Value> funcValues;
        for (css3Parser::TermContext* funcTerm0 : term->function()->expr()->term())
        {
            Value funcValue = getTermValue(property, funcTerm0);
#ifdef DEBUG_CSS_PARSER
            printf("RuleSetListener::getTermValue:   -> function: funcValue=%lld\n", funcValue);
#endif
            funcValues.push_back(funcValue);
        }

        if (!strcmp("rgb(", functionName.c_str()))
        {
            uint64_t rgb = 0;
            unsigned int i;
            for (i = 0; i < 3 && i < funcValues.size(); i++)
            {
                rgb <<= 8;
                rgb |= funcValues.at(i).asInt();
            }
            rgb |= 0xff000000; // Set alpha
#ifdef DEBUG_CSS_PARSER
            printf("RuleSetListener::getTermValue:   -> function: RGB: 0x%llx\n", rgb);
#endif
            return rgb;
        }
        else if (!strcmp("linear-gradient(", functionName.c_str()))
        {
            uint64_t gradient = 0;
            unsigned int i;
            for (i = 0; i < 2 && i < funcValues.size(); i++)
            {
                uint32_t v = funcValues.at(i).asInt();
                v |= 0xff000000;
                gradient <<= 32;
                gradient |= v;
            }
            return gradient;
        }
        else
        {
#ifdef DEBUG_CSS_PARSER
            printf("RuleSetListener::getTermValue:   -> function: Unknown function: %s\n", functionName.c_str());
            for (int value : funcValues)
            {
                printf("RuleSetListener::getTermValue:     -> function: parameter: %d (0x%x)\n", value, value);
            }
#endif
        }
        return 0;
    }

    return 0;
}

Value RuleSetListener::getFontFamilyValue(std::string fontFamily)
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

#ifdef DEBUG_CSS_PARSER
    printf("RuleSetListener::getFontFamilyValue: fontFamily=%s\n", fontFamily.c_str());
#endif
    return Value(Utils::string2wstring(fontFamily));
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

void StyleRule::setProperty(string property, Value value)
{
    ShortcutProperty* shortcutProperty = findShortcutProperty(property);
    if (shortcutProperty != NULL)
    {
        printf("StyleRule::setProperty: ERROR: property \"%s\" is a shortcut!\n", property.c_str());
        return;
    }

#if 0
    printf("setProperty: %s -> %llu (0x%llx)\n", property.c_str(), value, value);
#endif

    auto it = m_properties.find(property);
    if (it != m_properties.end())
    {
        m_properties.erase(it);
    }

    m_properties.insert(make_pair(property, value));
}

void StyleRule::applyProperty(string property, Value value)
{
    vector<Value> values;
    values.push_back(value);
    applyProperty(property, values);
}

void StyleRule::applyProperty(string property, vector<Value> values)
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

#if 0
    string valuesStr = "";
    bool space = false;
    for (Value v : values)
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
#endif

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

            vector<Value> childValues;
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

bool CssParser::parse(std::string path)
{
    log(DEBUG, "Parsing file: %s", path.c_str());

    int res = access(path.c_str(), R_OK);
    if (res != 0)
    {
        log(ERROR, "parse: Failed to find CSS file: %s", path.c_str());
        return false;
    }

    ANTLRFileStream* stream = new ANTLRFileStream(path.c_str());

    css3Lexer lexer(stream);
    CommonTokenStream tokens(&lexer);
    css3Parser parser(&tokens);

    tree::ParseTree *tree = parser.stylesheet();
    RuleSetListener listener(m_styleEngine);
    tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

    return true;
}

bool CssParser::parseString(std::string str)
{
    log(DEBUG, "Parsing string");

    ANTLRInputStream* stream = new ANTLRInputStream(str);

    css3Lexer lexer(stream);
    CommonTokenStream tokens(&lexer);
    css3Parser parser(&tokens);

    tree::ParseTree *tree = parser.stylesheet();
    RuleSetListener listener(m_styleEngine);
    tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

    return true;
}

