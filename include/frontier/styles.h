#ifndef __FRONTIER_STYLES_H_
#define __FRONTIER_STYLES_H_

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>

#include <geek/core-logger.h>

#define FRONTIER_COLOUR_TRANSPARENT 0xffffffff00000000ull

namespace Frontier {

class Widget;

union StyleValue
{
    uint64_t value;
    const char* str;
    union
    {
        uint32_t value1;
        uint32_t value2;
    };
};

/**
 * \defgroup styles CSS Engine
 */

struct StyleSelector
{
    std::wstring widgetType;
    std::wstring className;
    std::wstring id;
    std::string state;

    bool matches(Frontier::Widget* widget);
    std::wstring getKey();
};

/**
 * \brief An individual CSS rule
 *
 * \ingroup styles
 */
class StyleRule
{
 private:
    uint64_t m_id;
    std::vector<StyleSelector> m_selectors;
    std::unordered_map<std::string, int64_t> m_properties;

 public:
    StyleRule() { m_id = 0; }
    virtual ~StyleRule() {}

    const std::vector<StyleSelector>& getSelectors() { return  m_selectors; }
    void addSelector(StyleSelector selector);

    bool matches(Frontier::Widget* widget);

    void setId(uint64_t id) { m_id = id; }
    uint64_t getId() { return m_id; }
    std::wstring getKey();

    void setProperty(std::string property, int64_t value);
    void applyProperty(std::string property, int64_t value);
    void applyProperty(std::string property, std::vector<int64_t> values);
    void applyProperty(std::string property, int count, const int64_t* values);
    std::unordered_map<std::string, int64_t> getProperties() { return m_properties; }
};

class CssParser;

typedef std::function<bool(std::pair<StyleRule*, int>, std::pair<StyleRule*, int>)> StyleComparator;

/**
 * \brief A CSS rules engine
 *
 * \ingroup styles
 */
class StyleEngine : public Geek::Logger
{
 private:
    CssParser* m_parser;
    std::vector<std::pair<StyleRule*, int>> m_styleRules;
    uint64_t m_timestamp;
    uint64_t m_currentId;

 public:
    StyleEngine();
    ~StyleEngine();

    bool init();

    bool parse(std::string path);

    void addRule(StyleRule* rule);
    StyleRule* findByKey(std::string key);

    std::unordered_map<std::string, int64_t> getProperties(Widget* widget);
    uint64_t getTimestamp() { return m_timestamp; }
};

};

#endif
