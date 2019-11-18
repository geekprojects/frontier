
#include <string.h>
#include <wchar.h>
#include <time.h>
#include <sys/time.h>

#include <frontier/styles.h>
#include <frontier/widgets.h>
#include "cssparser.h"

#include <algorithm>

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

    timeval tv;
    gettimeofday(&tv, NULL);
    m_timestamp = tv.tv_sec * 1000l;
    m_timestamp += tv.tv_usec / 1000l;

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
    int specificity = 0;

    if (rule->getId().length() > 0)
    {
        specificity += 1000;
    }

    if (rule->getState().length() > 0)
    {
        specificity += 100;
    }

    if (rule->getClassName().length() > 0)
    {
        specificity += 10;
    }

    if (rule->getWidgetType().length() > 0)
    {
        if (rule->getWidgetType() == L"*")
        {
            specificity += 1;
        }
        else
        {
            specificity += 2;
        }
    }

    m_styleRules.push_back(make_pair(rule, specificity));

    StyleComparator compFunctor = [](std::pair<StyleRule*, int> elem1 ,std::pair<StyleRule*, int> elem2)
    {
        return elem1.second < elem2.second;
    };

    std::sort(m_styleRules.begin(), m_styleRules.end(), compFunctor);

    //m_styleRules = orderedRules;
}

unordered_map<string, int64_t> StyleEngine::getProperties(Widget* widget)
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

    vector<StyleRule*> matchedRules;
    for (pair<StyleRule*, int> rulePair : m_styleRules)
    {
        StyleRule* rule = rulePair.first;

        bool hasId = (rule->getId().length() > 0);
        bool matchId = (hasId && rule->getId() == widget->getWidgetId());
        if (hasId && !matchId)
        {
            continue;
        }

        bool hasType = (rule->getWidgetType().length() > 0);
        bool matchType = (hasType && (rule->getWidgetType() == L"*" || rule->getWidgetType() == widget->getWidgetName()));
        if (hasType && !matchType)
        {
            continue;
        }

        bool hasClass = (rule->getClassName().length() > 0);
        bool matchClass = (hasClass && widget->hasWidgetClass(rule->getClassName()));
        if (hasClass && !matchClass)
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

        matchedRules.push_back(rule);
    }

    matchedRules.push_back(widget->getWidgetStyle());

    unordered_map<string, int64_t> results;
    for (auto rule : matchedRules)
    {
#ifdef DEBUG_STYLE_PROPERTIES
        //int specificity = matchedRule.second;
        //log(DEBUG, "getProperties: %d: %ls", specificity, rule->getKey().c_str());
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
        log(DEBUG, "getProperties:     %s -> %lld (0x%llx)", prop.first.c_str(), prop.second, prop.second);
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


