#ifndef __FRONTIER_STYLES_CSS_PARSER_H_
#define __FRONTIER_STYLES_CSS_PARSER_H_

#include <string>
#include <vector>
#include <map>

#include <geek/core-logger.h>
#include <frontier/styles.h>

namespace Frontier {

class CssParser : public Geek::Logger
{
 private:
    StyleEngine* m_styleEngine;

 public:
    CssParser(StyleEngine* styleEngine);
    virtual ~CssParser();

    void parse(std::string path);
};

};

#endif

