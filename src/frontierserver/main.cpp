//
// Created by Ian Parker on 22/10/2020.
//

#include <frontier/app.h>
#include <frontier/engines/server.h>

 class FrontierServer : public Frontier::FrontierApp
{
 private:
 public:
    FrontierServer();
    ~FrontierServer() override;
};

using namespace Frontier;

FrontierServer::FrontierServer() : FrontierApp(L"FrontierServer")
{
    ServerEngine* engine = new ServerEngine(this);
    setEngine(engine);
}

FrontierServer::~FrontierServer()
{

}

int main(int argc, char** argv)
{
    FrontierServer* server = new FrontierServer();

    bool res;
    res = server->init();
    if (!res)
    {
        return 1;
    }

    server->main();

    delete server;

    return 0;
}