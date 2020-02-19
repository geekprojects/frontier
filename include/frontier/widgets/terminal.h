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
    STATE_ESC,
    STATE_CSI,
    STATE_OSC
};

class Terminal;

class TerminalProcess : public Geek::Thread, Geek::Logger
{
 private:
    Terminal* m_terminal;
    char* m_command;
    std::vector<char*> m_args;
    std::vector<char*> m_env;

    pid_t m_childPid;
    int m_childIn;
    int m_childOut;

 public:
    TerminalProcess(Terminal* terminal, const char* command, std::vector<const char*> args, std::vector<const char*> env);
    ~TerminalProcess();

    bool main();

    void typeChar(wchar_t c);

    void stop();
};

struct TermChar
{
    wchar_t c;
    uint32_t fg;
    uint32_t bg;
};

struct TermLine
{
    std::vector<TermChar> chars;
};

/**
 * \inbrief A very simple terminal emulator Widget
 *
 * \ingroup widgets
 */
class Terminal : public Widget
{
 private:
    std::vector<TermLine> m_buffer;
    unsigned int m_col;
    unsigned int m_row;
    unsigned int m_offsetRow;
    uint32_t m_fgColour;
    uint32_t m_bgColour;

    std::wstring m_command;
    TerminalState m_state;

    TerminalProcess* m_process;

    void reset();
    void clear();
    void setChar(unsigned int row, unsigned int col, wchar_t c);

    void handleCSI(wchar_t c);

    uint32_t getColour8(int code, bool fg);

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
    bool run(const char* command, std::vector<const char*> args);
    bool run(const char* command, std::vector<const char*> args, std::vector<const char*> env);
};

};

#endif
