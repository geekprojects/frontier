#ifndef __FRONTIER_EMBEDDED_H_
#define __FRONTIER_EMBEDDED_H_

#include <frontier/engine.h>

namespace Frontier
{

class EmbeddedWindow : public Frontier::FrontierEngineWindow
{
 private:
    Geek::Vector2D m_position;

 public:
    EmbeddedWindow(Frontier::FrontierEngine* engine, Frontier::FrontierWindow* window);
    virtual ~EmbeddedWindow();

    virtual bool init();
    virtual void show();
    virtual void hide();
    virtual bool update();

    virtual void setPosition(unsigned int x, unsigned int y) { m_position.x = x; m_position.y = y; }
    virtual Geek::Vector2D getPosition() { return m_position; }

    virtual float getScaleFactor();
};

/**
 * \brief An Engine designed for embedding Frontier UIs in to other applications
 *
 * \ingroup engines
 */
class EmbeddedEngine : public FrontierEngine
{
 protected:
    float m_scaleFactor;
    Frontier::Size m_screenSize;

 public:
    EmbeddedEngine(FrontierApp* app);
    virtual ~EmbeddedEngine();

    virtual bool init();

    virtual bool initWindow(FrontierWindow* window);

    virtual bool checkEvents();

    virtual std::string getConfigDir();

    // Dialogs
    virtual void message(std::string title, std::string message);
    virtual bool confirmBox(std::string title, std::string message);
    virtual std::string chooseFile(int flags, std::string path, std::string pattern);

    void setScreenSize(Frontier::Size size) { m_screenSize = size; }
    Frontier::Size getScreenSize() { return m_screenSize; }

    void setScaleFactor(float factor) { m_scaleFactor = factor; }
    float getScaleFactor() { return m_scaleFactor; }
};

};

#endif
