
#include <frontier/engines/server.h>
#include <netinet/in.h>

using namespace Frontier;
using namespace Geek;

ServerThread::ServerThread(ServerEngine* engine) : Logger("ServerThread")
{
    m_engine = engine;
}

ServerThread::~ServerThread()
{

}

bool ServerThread::main()
{
    int fd = m_engine->getServerSocket();

    sockaddr_in cliAddr;
    int clientFd;
    socklen_t cliAddrLen = sizeof(cliAddr);

    log(DEBUG, "main: Waiting for connection...");
    clientFd = accept(fd, (sockaddr*)&cliAddr, &cliAddrLen);
    log(DEBUG, "main: clientFd=%d", clientFd);

    return true;
}
