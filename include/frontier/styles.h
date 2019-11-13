#ifndef __FRONTIER_STYLES_H_
#define __FRONTIER_STYLES_H_

#include <string>
#include <vector>
#include <map>

#include <geek/core-logger.h>

namespace Frontier {

class Widget;

class StyleRule
{
 private:
    std::wstring m_widgetType;
    std::wstring m_className;
    std::wstring m_id;
    std::string m_state;

    std::map<std::string, int64_t> m_properties;

 public:
    StyleRule() {}
    virtual ~StyleRule() {}

    void setWidgetType(std::wstring type) { m_widgetType = type; }
    std::wstring getWidgetType() { return m_widgetType; }
    void setClassName(std::wstring name) { m_className = name; }
    std::wstring getClassName() { return m_className; }
    void setId(std::wstring id) { m_id = id; }
    std::wstring getId() { return m_id; }
    void setState(std::string state) { m_state = state; }
    std::string getState() { return m_state; }

    std::wstring getKey();

    void setProperty(std::string property, int64_t value);
    void applyProperty(std::string property, int64_t value);
    void applyProperty(std::string property, std::vector<int64_t> values);
    void applyProperty(std::string property, int count, const int64_t* values);
    std::map<std::string, int64_t> getProperties() { return m_properties; }
};

class CssParser;

typedef std::function<bool(std::pair<StyleRule*, int>, std::pair<StyleRule*, int>)> StyleComparator;

class StyleEngine : public Geek::Logger
{
 private:
    CssParser* m_parser;
    //std::map<std::string, StyleRule*> m_styleRules;
    std::vector<std::pair<StyleRule*, int>> m_styleRules;
    uint64_t m_timestamp;

 public:
    StyleEngine();
    ~StyleEngine();

    bool init();

    bool parse(std::string path);

    void addRule(StyleRule* rule);
    StyleRule* findByKey(std::string key);

    std::map<std::string, int64_t> getProperties(Widget* widget);
    uint64_t getTimestamp() { return m_timestamp; }
};

};

#endif
