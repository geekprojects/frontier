#ifndef FRONTIER_ENGINE_AWESOME_H
#define FRONTIER_ENGINE_AWESOME_H

#include <frontier/engine.h>

#include <awesome/connection.h>

namespace Frontier
{

class AwesomeEngine;

class AwesomeWindow;

class AwesomeEngine : public FrontierEngine
{
 private:
    Awesome::ClientConnection* m_connection = nullptr;
    std::map<int, AwesomeWindow*> m_windows;
    float m_scale = 1.0f;

 public:
    explicit AwesomeEngine(FrontierApp* app);
    ~AwesomeEngine() override;

    bool init() override;

    bool checkEvents() override;

    bool initWindow(FrontierWindow* window) override;

    Awesome::ClientConnection* getConnection() const
    {
        return m_connection;
    }

    bool providesMenus() override
    {
        return true;
    }

    float getScale() const
    {
        return m_scale;
    }
};

class AwesomeWindow : public FrontierEngineWindow
{
 private:
    int m_windowId = -1;
    Awesome::ClientSharedMemory* m_sharedMemory = nullptr;
    Size m_currentSize;
    float m_scale = 1.0;

 public:
    AwesomeWindow(FrontierEngine* engine, FrontierWindow* window);
    ~AwesomeWindow() override;

    bool init() override;
    bool update() override;

    void show() override;
    void hide() override;

    int getWindowId() const
    {
        return m_windowId;
    }

    float getScaleFactor() override
    {
        return m_scale;
    }

    void requestUpdate() override;
};

}

#endif //FRONTIER_CLIENT_H
