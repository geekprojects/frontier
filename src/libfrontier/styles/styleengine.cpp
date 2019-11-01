
#include <string.h>
#include <wchar.h>
#include <time.h>

#include <frontier/styles.h>
#include <frontier/widgets.h>
#include "cssparser.h"

using namespace std;
using namespace Frontier;
using namespace Geek;

#undef DEBUG_STYLE_PROPERTIES

#define STRINGIFY(x) XSTRINGIFY(x)
#define XSTRINGIFY(x) #x

StyleEngine::StyleEngine() : Logger("StyleEngine")
{
    m_parser = new CssParser(this);
}

StyleEngine::~StyleEngine()
{
}

bool StyleEngine::init()
{
#ifdef CSSDIR
    m_parser->parse(string(STRINGIFY(CSSDIR)) + "/frontier.css");
#endif

    return true;
}

bool StyleEngine::parse(std::string path)
{
    m_parser->parse(path);

    m_timestamp = time(NULL);
    return true;
}

StyleRule* StyleEngine::findByKey(std::string key)
{
    return NULL;
}

void StyleEngine::addRule(StyleRule* rule)
{
    m_styleRules.push_back(rule);
}

map<string, int64_t> StyleEngine::getProperties(Widget* widget)
{

#if 0
    wstring classes = L"";
    bool comma = false;
    for (wstring clazz : widget->getWidgetClasses())
    {
        if (comma)
        {
            classes += L",";
        }
        comma = true;

        classes += clazz;

    }

    log(DEBUG, "getProperties: Widget: type=%ls, classes=%ls, id=%ls", widget->getWidgetName().c_str(), classes.c_str(), widget->getWidgetId().c_str());
#endif

    map<StyleRule*, int> matchedRules;
    for (StyleRule* rule : m_styleRules)
    {

        bool matchId = (rule->getId().length() > 0 && rule->getId() == widget->getWidgetId());
        if (rule->getId().length() > 0 && !matchId)
        {
            continue;
        }

        bool matchType = (rule->getWidgetType().length() > 0 && (rule->getWidgetType() == L"Widget" || rule->getWidgetType() == widget->getWidgetName()));
        if (rule->getWidgetType().length() > 0 && !matchType)
        {
            continue;
        }

        bool matchClass = (rule->getClassName().length() > 0 && widget->hasWidgetClass(rule->getClassName()));
        if (rule->getClassName().length() > 0 && !matchClass)
        {
            continue;
        }

        bool matchState = false;
        if (rule->getState().length() > 0)
        {
            matchState = true;
            if (rule->getState() == "active")
            {
                if (!widget->isActive())
                {
                    continue;
                }
            }
            else if (rule->getState() == "selected")
            {
                if (!widget->isSelected())
                {
                    continue;
                }
            }
            else if (rule->getState() == "hover")
            {
                if (!widget->isMouseOver())
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
        }

        int specificity = 0;
        if (matchId)
        {
            specificity += 1000;
        }
        if (matchState)
        {
            specificity += 100;
        }
        if (matchClass)
        {
            specificity += 10;
        }
        if (matchType)
        {
            if (rule->getWidgetType() == L"Widget")
            {
                specificity += 1;
            }
            else
            {
                specificity += 2;
            }
        }
        matchedRules.insert(make_pair(rule, specificity));
    }

    matchedRules.insert(make_pair(widget->getWidgetStyle(), 10000));

    typedef std::function<bool(std::pair<StyleRule*, int>, std::pair<StyleRule*, int>)> Comparator;
    Comparator compFunctor = [](std::pair<StyleRule*, int> elem1 ,std::pair<StyleRule*, int> elem2)
    {
        return elem1.second < elem2.second;
    };

    std::set<std::pair<StyleRule*, int>, Comparator> orderedRules(matchedRules.begin(), matchedRules.end(), compFunctor);

    map<string, int64_t> results;
    for (auto matchedRule : orderedRules)
    {
        StyleRule* rule = matchedRule.first;
#ifdef DEBUG_STYLE_PROPERTIES
        int specificity = matchedRule.second;
        log(DEBUG, "getProperties: %d: %ls", specificity, rule->getKey().c_str());
#endif

        for (auto prop : rule->getProperties())
        {
            auto it = results.find(prop.first);
            if (it != results.end())
            {
                results.erase(it);
            }
            results.insert(make_pair(prop.first, prop.second));
        }

    }

#ifdef DEBUG_STYLE_PROPERTIES
    for (auto prop : results)
    {
        log(DEBUG, "getProperties: %s -> %lld (0x%llx)", prop.first.c_str(), prop.second, prop.second);
    }
#endif

    return results;
}

wstring StyleRule::getKey()
{
    wstring key = L"";
    if (m_widgetType.length() > 0)
    {
        key += m_widgetType;
    }
    if (m_className.length() > 0)
    {
        key += L"." + m_className;
    }
    if (m_id.length() > 0)
    {
        key += L"#" + m_id;
    }

    return key;
}


