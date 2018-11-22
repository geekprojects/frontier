
#include "test_engine.h"

using namespace std;
using namespace Frontier;

TestEngine::TestEngine(FrontierApp* app) : FrontierEngine(app)
{
}

TestEngine::~TestEngine()
{
}


bool TestEngine::init()
{
    return true;
}


bool TestEngine::initWindow(FrontierWindow* window)
{
    return true;
}


bool TestEngine::checkEvents()
{
    return true;
}


std::string TestEngine::getConfigDir()
{
    return string("/tmp");
}


void TestEngine::message(std::string title, std::string message)
{
}

bool TestEngine::confirmBox(std::string title, std::string message)
{
    return true;
}

std::string TestEngine::chooseFile(int flags, std::string path, std::string pattern)
{
    return string("/tmp/test.txt");
}

