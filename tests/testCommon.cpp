
#include "testCommon.h"

using namespace std;
using namespace Frontier;

TestApp::TestApp() : FrontierApp(L"Test App")
{
    TestEngine* testEngine = new TestEngine(this);
    setEngine(testEngine);
}

TestApp::~TestApp()
{
}
