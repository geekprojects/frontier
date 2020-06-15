
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

    m_currentId = 0;
}

StyleEngine::~StyleEngine()
{
}

bool StyleEngine::init()
{
#ifdef CSSDIR
    bool res;
    res = m_parser->parse(string(STRINGIFY(CSSDIR)) + "/frontier.css");
    if (!res)
    {
        return false;
    }
#endif

    timeval tv;
    gettimeofday(&tv, NULL);
    m_timestamp = tv.tv_sec * 1000l;
    m_timestamp += tv.tv_usec / 1000l;

    return true;
}

bool StyleEngine::parse(std::string path)
{
    bool res;
    res = m_parser->parse(path);
    if (!res)
    {
        return false;
    }

    timeval tv;
    gettimeofday(&tv, NULL);
    m_timestamp = tv.tv_sec * 1000l;
    m_timestamp += tv.tv_usec / 1000l;

    return true;
}

StyleRule* StyleEngine::findByKey(std::string key)
{
    return NULL;
}

void StyleEngine::addRule(StyleRule* rule)
{
    rule->setId(++m_currentId);

    int specificity = 0;

    // https://www.w3.org/TR/CSS2/cascade.html#specificity
    for (StyleSelector selector : rule->getSelectors())
    {
        if (selector.id.length() > 0)
        {
            specificity += 1000;
        }

        if (selector.state.length() > 0)
        {
            specificity += 100;
        }

        if (selector.className.length() > 0)
        {
            specificity += 10;
        }

        if (selector.widgetType.length() > 0)
        {
            if (selector.widgetType == L"*")
            {
                specificity += 1;
            }
            else
            {
                specificity += 2;
            }
        }
    }

    m_styleRules.push_back(make_pair(rule, specificity));

    StyleComparator compFunctor = [](std::pair<StyleRule*, int> elem1 ,std::pair<StyleRule*, int> elem2)
    {
        if (elem1.second == elem2.second)
        {
            return elem1.first->getId() < elem2.first->getId();
        }
        else
        {
            return elem1.second < elem2.second;
        }
    };

    std::sort(m_styleRules.begin(), m_styleRules.end(), compFunctor);
}

unordered_map<string, int64_t> StyleEngine::getProperties(Widget* widget)
{
    vector<StyleRule*> matchedRules;
    for (pair<StyleRule*, int> rulePair : m_styleRules)
    {
        StyleRule* rule = rulePair.first;
        if (rule->matches(widget))
        {
            matchedRules.push_back(rule);
        }
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

void StyleRule::addSelector(StyleSelector selector)
{
    m_selectors.push_back(selector);
}

bool StyleRule::matches(Widget* widget)
{
    Widget* currentWidget = widget;

    bool matches = true;
    bool first = true;
    for (auto it = m_selectors.rbegin(); matches && it != m_selectors.rend(); it++)
    {
        StyleSelector selector = *it;

        matches = false;
        while (!matches && currentWidget != NULL)
        {
            matches = selector.matches(currentWidget);
            if (selector.descendant && !matches)
            {
                break;
            }
            currentWidget = currentWidget->getParent();

            if (first)
            {
                // The first (last?) item must match the first (last?) selector
                break;
            }
        }
        first = false;
    }

    return matches;
}

wstring StyleRule::getKey()
{
    wstring key = L"";
    bool space = false;

    for (auto selector : m_selectors)
    {
        if (space)
        {
            key += L" ";
        }
        space = true;
        key += selector.getKey();
    }

    return key;
}

bool StyleSelector::matches(Widget* widget)
{
    bool hasId = (id.length() > 0);
    bool matchId = (hasId && id == widget->getWidgetId());
    if (hasId && !matchId)
    {
        return false;
    }

    bool hasType = (widgetType.length() > 0);
    bool matchType = (hasType && (widgetType == L"*" || widget->instanceOf(widgetType)));
    if (hasType && !matchType)
    {
        return false;
    }

    bool hasClass = (className.length() > 0);
    bool matchClass = (hasClass && widget->hasWidgetClass(className));
    if (hasClass && !matchClass)
    {
        return false;
    }

    bool matchState = false;
    if (state.length() > 0)
    {
        matchState = true;
        if (state == "active")
        {
            if (!widget->isActive())
            {
                return false;
            }
        }
        else if (state == "selected")
        {
            if (!widget->isSelected())
            {
                return false;
            }
        }
        else if (state == "hover")
        {
            if (!widget->isMouseOver())
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    return true;
}

wstring StyleSelector::getKey()
{
    wstring key = L"";

    if (widgetType.length() > 0)
    {
        key += widgetType;
    }
    if (className.length() > 0)
    {
        key += L"." + className;
    }
    if (id.length() > 0)
    {
        key += L"#" + id;
    }
    if (state.length() > 0)
    {
        key += L":" + Utils::string2wstring(state);
    }

    return key;
}


