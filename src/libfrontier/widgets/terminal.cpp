/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2019 Ian Parker <ian@geekprojects.com>
 *
 * This file is part of Frontier.
 *
 * Frontier is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Frontier is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Frontier.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <frontier/frontier.h>
#include <frontier/widgets/terminal.h>

#include <unistd.h>
#include <signal.h>
#include <util.h>
#include <sys/time.h> 
#include <sys/types.h> 

#define DEBUG_TERMINAL

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

#ifdef DEBUG_TERMINAL
static void hexdump(const char* pos, int len);
#endif

Terminal::Terminal(FrontierApp* ui) : Widget(ui, L"Terminal")
{
    m_process = NULL;
    m_state = STATE_NORMAL;
}

Terminal::Terminal(FrontierWindow* window) : Widget(window, L"Terminal")
{
    m_state = STATE_NORMAL;
}

Terminal::~Terminal()
{
    if (m_process != NULL)
    {
        m_process->stop();
        delete m_process;
    }
}

void Terminal::calculateSize()
{
    FontHandle* font = m_app->getTheme()->getMonospaceFont(true);
    int fontHeight = m_app->getTheme()->getMonospaceHeight();

    FontManager* fm = m_app->getFontManager();
    int fontWidth = fm->width(font, L"M");

    m_minSize.width = fontWidth * 20;
    m_minSize.height = fontHeight * 2;

    m_maxSize.width = WIDGET_SIZE_UNLIMITED;
    m_maxSize.height = WIDGET_SIZE_UNLIMITED;
}

bool Terminal::draw(Surface* surface)
{
    surface->clear(0x0000ff);

    if (m_buffer.empty())
    {
        return true;
    }

    FontManager* fm = m_app->getFontManager();

    FontHandle* font = m_app->getTheme()->getMonospaceFont(true);
    int fontHeight = m_app->getTheme()->getMonospaceHeight();
    int fontWidth = fm->width(font, L"M");
    if (fontWidth == 0)
    {
        log(ERROR, "fontWidth is NULL?");
        return false;
    }

    unsigned int visibleRows = m_setSize.height / fontHeight;
    unsigned int visibleColumns = m_setSize.width / fontWidth;

    int offsetRow = (m_buffer.size() - 0) - visibleRows;
    if (offsetRow < 0)
    {
        offsetRow = 0;
    }

    int y = 0;
    unsigned int row;
    for (row = 0; row < visibleRows && (row + offsetRow) < m_buffer.size(); row++, y += fontHeight)
    {
        wstring line = m_buffer.at(row + offsetRow);
        unsigned int col;
        int x = 0;
        for (col = 0; col < visibleColumns && col < line.length(); col++, x += fontWidth)
        {
            fm->write(font, surface, x, y, wstring(L"") + line.at(col), 0xffffffff, true, NULL);
        }
    }

    return true;
}

Widget* Terminal::handleEvent(Event* event)
{
    // We just swallow events
    switch (event->eventType)
    {
        case FRONTIER_EVENT_KEY:
        {
            KeyEvent* keyEvent = (KeyEvent*)event;

            if (keyEvent->direction)
            {
                wchar_t c = L'?';
                //if (iswprint(keyEvent->chr))
                {
                    c = keyEvent->chr;
                }
                m_process->typeChar(c);
            }
        }
        default:
            break;
    }
    return this;
}

void Terminal::receiveChar(wchar_t c)
{
    if (m_buffer.empty())
    {
        m_buffer.push_back(L"");
    }
    int y = m_buffer.size() - 1;


    switch (m_state)
    {
        case STATE_NORMAL:
            if (c == 10)
            {
                m_buffer.push_back(L"");
            }
            else if (c == 0x1b)
            {
                m_state = STATE_CSI;
                m_command = L"";
            }
            else if (iswprint(c))
            {
                m_buffer.at(y) += c;
            }
            else
            {
                printf("Terminal::receiveChar: c: 0x%x\n", c);
            }
            break;

        case STATE_CSI:
            if (m_command.empty() && c == ']')
            {
                m_state = STATE_OSC;
            }
            else
            {
                m_command += c;

                if (iswalpha(c))
                {
                    printf("Terminal::receiveChar: Command: %ls\n", m_command.c_str());
                    m_state = STATE_NORMAL;
                }
            }
            break;

        case STATE_OSC:
            if (c == 0x07)
            {
                printf("Terminal::receiveChar: OSC: %ls\n", m_command.c_str());
                m_state = STATE_NORMAL;
            }
            else
            {
                m_command += c;
            }
            break;
    }

    setDirty(DIRTY_CONTENT);

}

void Terminal::receiveChars(char* c, int length)
{
#ifdef DEBUG_TERMINAL
    hexdump(c, length);
#endif
    int i;
    for (i = 0; i < length; i++)
    {
        // TODO: Handle UTF-8
        receiveChar(c[i]);
    }

    /*
    FrontierWindow* window = getWindow();
    if (window != NULL)
    {
        window->update();
    }
    */
}

bool Terminal::run(const char* command)
{
    m_process = new TerminalProcess(this);
    m_process->start();

    return true;
}

TerminalProcess::TerminalProcess(Terminal* terminal) : Logger("TerminalProcess")
{
    m_terminal = terminal;
}

TerminalProcess::~TerminalProcess()
{
}

bool TerminalProcess::main()
{
    int res;

    int master;
    int slave;
    char name[1024];

    res = openpty(&master, &slave, name, NULL, NULL);
    if (res != 0)
    {
        int err = errno;
        log(ERROR, "main: Failed to open PTY: %d", err);
        return false;
    }
    log(INFO, "main: master=%d, slave=%d, name=%s", master, slave, name);

    pid_t pid = fork();
    printf("TerminalProcess::main: pid=%d\n", pid);
    if (pid > 0)
    {
        // Parent
        close(slave);

        m_childPid = pid;
        m_childOut = master;
        m_childIn = master;

        char buffer[4097];
        while (true)
        {
            int res;
            log(DEBUG, "main: (Parent) Waiting for data...");
            res = read(m_childOut, buffer, 4096);
            log(DEBUG, "main: (Parent) Read %d bytes", res);
            if (res <= 0)
            {
                break;
            }

            buffer[res] = 0;
            m_terminal->receiveChars(buffer, res);
        }
        log(DEBUG, "main: (Parent) Child exited");
    }
    else if (pid == 0)
    {
        dup2(slave, STDOUT_FILENO);
        dup2(slave, STDIN_FILENO);
        dup2(slave, STDERR_FILENO);

        //printf("TerminalProcess::main: (Child) Calling watch!\n");
        //execl("/usr/local/bin/watch", "watch", "/bin/ls", "-l", NULL);
        //execl("/bin/ls", "/bin/ls", "-l", NULL);
        //execl("/bin/bash", "-l", NULL);
        //printf("TerminalProcess::main: (Child) Starting command...\n");
        execl("/usr/local/bin/bash", "bash", "-i", NULL);
        //execl("/usr/bin/make", "make", NULL);
//char* const[] env = {
//"TERM
//};
        //execl("/usr/bin/top", "top", "-n", "5", NULL);

//        execl("/usr/bin/uname", "uname", "-a", NULL);
        perror("execl() failed");
        _exit(errno);
    }

    return true;
}

void TerminalProcess::typeChar(wchar_t c)
{
    printf("TerminalProcess::typeChar: c=0x%x\n", c);

    char buf[2];
    buf[0] = c;
    buf[1] = 0;
    write(m_childIn, buf, 1);
}

void TerminalProcess::stop()
{
    log(DEBUG, "stop: Killing child...");
    kill(m_childPid, SIGHUP);

    if (m_childIn != 0)
    {
        log(DEBUG, "stop: Closing PTY");
        close(m_childIn);
    }
    log(DEBUG, "stop: done");
}

#ifdef DEBUG_TERMINAL
static void hexdump(const char* pos, int len)
{
    int i;
    for (i = 0; i < len; i += 16)
    {
        int j;
        printf("%08llx: ", (uint64_t)(pos + i));
        for (j = 0; j < 16 && (i + j) < len; j++)
        {
            printf("%02x ", (uint8_t)pos[i + j]);
        }
        for (j = 0; j < 16 && (i + j) < len; j++)
        {
            char c = pos[i + j];
            if (!isprint(c))
            {
                c = '.';
            }
            printf("%c", c);
        }
        printf("\n");
    }
}
#endif

