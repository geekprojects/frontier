
#include "testCommon.h"

#include <frontier/styles.h>
#include <frontier/widgets.h>

using namespace Frontier;
using namespace Geek;
using namespace std;

TEST(StyleEngineTest, simple)
{
    bool res;
    StyleEngine* se = new StyleEngine();
    res = se->parse("../tests/test.css");
    EXPECT_EQ(true, res);

    FrontierApp* app = new TestApp();

    Widget* a = new Widget(app, L"WidgetA");
    unordered_map<string, int64_t> props = se->getProperties(a);
    EXPECT_EQ(2, props.size());

    {
        auto it = props.find("expand-horizontal");
        EXPECT_NE(props.end(), it);
        EXPECT_EQ(1, it->second);
    }
    {
        auto it = props.find("expand-vertical");
        EXPECT_NE(props.end(), it);
        EXPECT_EQ(0, it->second);
    }
}

TEST(StyleEngineTest, nested1)
{
    bool res;
    StyleEngine* se = new StyleEngine();
    res = se->parse("../tests/test.css");
    EXPECT_EQ(true, res);

    FrontierApp* app = new TestApp();

    Widget* group1 = new Widget(app, L"Widget");
    group1->setWidgetClass(L"group1");

    Widget* a = new Widget(app, L"WidgetA");
    a->setParent(group1);
    unordered_map<string, int64_t> props = se->getProperties(a);
    EXPECT_EQ(2, props.size());

    {
        auto it = props.find("expand-horizontal");
        EXPECT_NE(props.end(), it);
        EXPECT_EQ(0, it->second);
    }
    {
        auto it = props.find("expand-vertical");
        EXPECT_NE(props.end(), it);
        EXPECT_EQ(1, it->second);
    }
}

TEST(StyleEngineTest, nested2)
{
    bool res;
    StyleEngine* se = new StyleEngine();
    res = se->parse("../tests/test.css");
    EXPECT_EQ(true, res);

    FrontierApp* app = new TestApp();

    // Widget.group1 > Widget.middle WidgetA
    Widget* group1 = new Widget(app, L"Widget");
    group1->setWidgetClass(L"group1");

    Widget* middle = new Widget(app, L"Widget");
    middle->setWidgetClass(L"middle");
    middle->setParent(group1);

    Widget* a = new Widget(app, L"WidgetA");
    a->setParent(middle);
    unordered_map<string, int64_t> props = se->getProperties(a);
    EXPECT_EQ(2, props.size());

    {
        auto it = props.find("expand-horizontal");
        EXPECT_NE(props.end(), it);
        EXPECT_EQ(0, it->second);
    }
    {
        auto it = props.find("expand-vertical");
        EXPECT_NE(props.end(), it);
        EXPECT_EQ(1, it->second);
    }
}

TEST(StyleEngineTest, nested3)
{
    bool res;
    StyleEngine* se = new StyleEngine();
    res = se->parse("../tests/test.css");
    EXPECT_EQ(true, res);

    FrontierApp* app = new TestApp();

    // Widget.group1 > Widget.middle WidgetA WidgetA

    Widget* group1 = new Widget(app, L"Widget");
    group1->setWidgetClass(L"group1");

    Widget* middle = new Widget(app, L"Widget");
    middle->setWidgetClass(L"middle");
    middle->setParent(group1);

    Widget* a = new Widget(app, L"WidgetA");
    a->setParent(middle);

    Widget* b = new Widget(app, L"WidgetA");
    b->setParent(a);

    unordered_map<string, int64_t> props = se->getProperties(b);
    EXPECT_EQ(2, props.size());

    {
        auto it = props.find("expand-horizontal");
        EXPECT_NE(props.end(), it);
        EXPECT_EQ(0, it->second);
    }
    {
        auto it = props.find("expand-vertical");
        EXPECT_NE(props.end(), it);
        EXPECT_EQ(1, it->second);
    }
}

TEST(StyleEngineTest, nested4)
{
    bool res;
    StyleEngine* se = new StyleEngine();
    res = se->parse("../tests/test.css");
    EXPECT_EQ(true, res);

    FrontierApp* app = new TestApp();

    // Widget.group1 > Widget.middle WidgetA WidgetA

    Widget* group1 = new Widget(app, L"Widget");
    group1->setWidgetClass(L"group1");

    Widget* middle = new Widget(app, L"Widget");
    middle->setWidgetClass(L"middle");
    middle->setParent(group1);

    Widget* a = new Widget(app, L"WidgetA");
    a->setParent(middle);

    Widget* b = new Widget(app, L"WidgetB");
    b->setParent(a);

    unordered_map<string, int64_t> props = se->getProperties(b);
    EXPECT_EQ(0, props.size());
}

