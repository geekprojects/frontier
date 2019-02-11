#ifndef __FRONTIER_WIDGETS_TERMINAL_H_
#define __FRONTIER_WIDGETS_TERMINAL_H_

#include <frontier/widgets.h>
#include <geek/core-thread.h>

#include <vector>
#include <string>

#include <unistd.h>

namespace Frontier
{

enum TerminalState
{
    STATE_NORMAL,
    STATE_CSI,
    STATE_OSC
};

class Terminal;

class TerminalProcess : public Geek::Thread
{
 private:
    Terminal* m_terminal;
    pid_t m_childPid;
    int m_childIn;
    int m_childOut;

 public:
    TerminalProcess(Terminal* terminal);
    ~TerminalProcess();

    bool main();

    void typeChar(wchar_t c);

    void stop();
};

class Terminal : public Widget
{
 private:
    std::vector<std::wstring> m_buffer;
    std::wstring m_command;
    TerminalState m_state;

    TerminalProcess* m_process;

 public:
    Terminal(FrontierApp* ui);
    Terminal(FrontierWindow* ui);
    virtual ~Terminal();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    void receiveChar(wchar_t c);
    void receiveChars(char* c, int length);

    bool run(const char* command);
};

};

#endif
