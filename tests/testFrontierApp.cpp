
#include <frontier/frontier.h>
#include "engines/test/test_engine.h"

#include <gtest/gtest.h>

using namespace Frontier;

class TestApp : public FrontierApp
{
 public:
    TestApp();
    virtual ~TestApp();
};

TestApp::TestApp() : FrontierApp(L"Test App")
{
    TestEngine* testEngine = new TestEngine(this);
    setEngine(testEngine);
}

TestApp::~TestApp()
{
}

TEST(FrontierAppTest, initTest)
{
    FrontierApp* app = new TestApp();
    bool res = app->init();

    EXPECT_EQ(true, res);
}

#define GC_OBJECTS 100u
TEST(FrontierAppTest, gc)
{
    FrontierApp* app = new TestApp();

    FrontierObject* objects[GC_OBJECTS];

    unsigned int i;
    for (i = 0; i < GC_OBJECTS; i++)
    {
        FrontierObject* obj = new FrontierObject();
        obj->incRefCount();
        app->registerObject(obj);
        objects[i] = obj;
    }

    EXPECT_EQ(GC_OBJECTS, app->getObjectCount());

    app->gc();

    // Nothing should have been garbage collected
    EXPECT_EQ(GC_OBJECTS, app->getObjectCount());

    unsigned int n = GC_OBJECTS / 4;
    for (i = 0; i < n; i++)
    {
         objects[i]->decRefCount();
         objects[i + n]->incRefCount();
    }

    app->gc();
    EXPECT_EQ(GC_OBJECTS - n, app->getObjectCount());

    for (i = 0; i < n; i++)
    {
         objects[i + n]->decRefCount();
    }
    app->gc();
    EXPECT_EQ(GC_OBJECTS - n, app->getObjectCount());

    for (i = 0; i < n; i++)
    {
         objects[i + n]->decRefCount();
    }
    app->gc();
    EXPECT_EQ(GC_OBJECTS - (n * 2), app->getObjectCount());

    for (i = 0; i < n; i++)
    {
         objects[i + (n * 2)]->decRefCount();
         objects[i + (n * 3)]->decRefCount();
    }
    app->gc();
    EXPECT_EQ(0u, app->getObjectCount());
}


