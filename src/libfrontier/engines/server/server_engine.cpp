//
// Created by Ian Parker on 22/10/2020.
//

#include <frontier/engines/server.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <cstdio>
#include <unistd.h>

using namespace Frontier;
using namespace Geek;

ServerEngine::ServerEngine(FrontierApp* app) : FrontierEngine(app)
{
    m_messageSignal = Thread::createCondVar();
}

ServerEngine::~ServerEngine()
{
    if (m_serverSocket != -1)
    {
        close(m_serverSocket);
    }

    delete m_nativeEngine;
}

bool ServerEngine::init()
{
    log(DEBUG, "init: Here!");
    m_nativeEngine = m_app->createNativeEngine();
    if (m_nativeEngine == nullptr)
    {
        return false;
    }

    m_serverSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    log(DEBUG, "init: serverSocket=%d", m_serverSocket);

    sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, "frontier.socket", sizeof(addr.sun_path)-1);
    bind(m_serverSocket, (struct sockaddr*)&addr, sizeof(addr));

    listen(m_serverSocket, 5);

    log(DEBUG, "init: Starting ServerThread");
    m_serverThread = new ServerThread(this);
    m_serverThread->start();

    m_messageSignal->signal();

    return true;
}

bool ServerEngine::checkEvents()
{
    log(DEBUG, "checkEvents: Waiting for message...");
    m_messageSignal->wait();

    return true;
}

