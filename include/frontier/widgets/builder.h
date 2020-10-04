#ifndef __FRONTIER_WIDGETS_BUILDER_H_
#define __FRONTIER_WIDGETS_BUILDER_H_

#include <geek/core-logger.h>
#include <frontier/widgets.h>

#include <libxml/parser.h>

namespace Frontier {

class WidgetBuilder : public Geek::Logger
{
 private:
    FrontierApp* m_app;

    Widget* walk(xmlDoc* doc, xmlNode* node, Widget* parent);

 public:
    explicit WidgetBuilder(FrontierApp* app);
    ~WidgetBuilder();

    Widget* loadWidget(const char* file);
};

}

#endif

