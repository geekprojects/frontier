#ifndef FRONTIER_SERVER_H
#define FRONTIER_SERVER_H

#include <frontier/engine.h>
#include <geek/core-thread.h>

namespace Frontier
{

class ServerEngine;

class ServerThread : public Geek::Thread, public Geek::Logger
{
 private:
    ServerEngine* m_engine;

 public:
    ServerThread(ServerEngine* engine);
    ~ServerThread();

    bool main() override;
};

class ServerEngine : public FrontierEngine
{
 private:
    FrontierEngine* m_nativeEngine = nullptr;
    int m_serverSocket = -1;

    ServerThread* m_serverThread;
    Geek::CondVar* m_messageSignal;

 public:
    explicit ServerEngine(FrontierApp* app);
    ~ServerEngine() override;

    bool init() override;

    bool checkEvents() override;

    FrontierEngine* getNativeEngine() const
    {
        return m_nativeEngine;
    }

    int getServerSocket() const
    {
        return m_serverSocket;
    }

};

}

#endif //FRONTIER_SERVER_H
