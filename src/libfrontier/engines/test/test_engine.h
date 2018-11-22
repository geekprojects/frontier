#ifndef __FRONTIER_ENGINES_TEST_H_
#define __FRONTIER_ENGINES_TEST_H_

#include <frontier/engine.h>

namespace Frontier
{

class TestEngine : public FrontierEngine
{
 protected:

 public:
    TestEngine(FrontierApp* app);
    virtual ~TestEngine();

    virtual bool init();

    virtual bool initWindow(FrontierWindow* window);

    virtual bool checkEvents();

    virtual std::string getConfigDir();

    // Dialogs
    virtual void message(std::string title, std::string message);
    virtual bool confirmBox(std::string title, std::string message);
    virtual std::string chooseFile(int flags, std::string path, std::string pattern);
};

};

#endif
