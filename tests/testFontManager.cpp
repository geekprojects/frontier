
#include "testCommon.h"

using namespace Frontier;

TEST(FontManagerTest, multipleOpens)
{
    FrontierApp* app = new TestApp();
    bool res = app->init();
    EXPECT_EQ(true, res);

    FontManager* fm = app->getFontManager();

    FontHandle* handle1 = fm->openFont(
        "Hack",
        "Regular",
        10);
    EXPECT_TRUE(handle1 != NULL);

    FontHandle* handle2 = fm->openFont(
        "Hack",
        "Regular",
        12);
    EXPECT_TRUE(handle2 != NULL);

    int width1 = fm->width(handle1, L"hello");
    int width2 = fm->width(handle2, L"hello");

    EXPECT_EQ(30, width1);
    EXPECT_EQ(35, width2);

    
}

