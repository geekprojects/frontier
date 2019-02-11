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
#include <sys/time.h> 
#include <sys/types.h> 

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

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

Terminal::Terminal(FrontierApp* ui) : Widget(ui, L"Terminal")
{
    //run("/usr/bin/uname -a");
    run("CLICOLOR_FORCE=1 /bin/ls -lG");
    //run("/usr/bin/make");
    //run("/usr/local/bin/bash");

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
    }
}

void Terminal::calculateSize()
{
    m_minSize.width = 8;
    m_minSize.height = 8;

    m_maxSize.width = WIDGET_SIZE_UNLIMITED;
    m_maxSize.height = WIDGET_SIZE_UNLIMITED;
}

bool Terminal::draw(Surface* surface)
{
    surface->clear(0x0000ff);

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
receiveChar(c);
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
            if (c == 10 || c == 0x0d)
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
hexdump(c, length);
    int i;
    for (i = 0; i < length; i++)
    {
        // TODO: Handle UTF-8
        receiveChar(c[i]);
    }
}

bool Terminal::run(const char* command)
{

//m_process = new TerminalProcess(this);
//m_process->start();

/*
    FILE *fp;

    log(DEBUG, "run: cmd: %s\n", command);
    fp = popen(command, "r");
    if (fp == NULL)
    {
        return;
    }

    char buffer[1024];
    string result = "";
    while (!feof(fp))
    {
        int res;
        res = fread(buffer, 1, 1024, fp);
        if (res <= 0)
        {
            break;
        }

        receiveChars(buffer, res);
    }

    pclose(fp);

    return;
*/
return true;
}

TerminalProcess::TerminalProcess(Terminal* terminal)
{
    m_terminal = terminal;
}

TerminalProcess::~TerminalProcess()
{
}

bool TerminalProcess::main()
{
    int read_pipe[2];
    int write_pipe[2];

    pipe(read_pipe);
    pipe(write_pipe);

    pid_t pid = fork();
    printf("TerminalProcess::main: pid=%d\n", pid);
    if (pid > 0)
    {
        // Parent
        m_childPid = pid;
        m_childOut = read_pipe[0];
        m_childIn = write_pipe[1];

        close(read_pipe[1]);
        close(write_pipe[0]);

/*
            struct timeval tv;
            fd_set readfds;
            tv.tv_sec = 10;
            tv.tv_usec = 0;
            FD_ZERO(&readfds);
            FD_SET(m_childOut, &readfds);
            select(m_childOut + 1, &readfds, NULL, NULL, &tv);
*/

        char buffer[4097];
        while (true)
        {
            int res;
            printf("TerminalProcess::main: (Parent) Waiting for data...\n");
            res = read(m_childOut, buffer, 4096);
            printf("TerminalProcess::main: (Parent) Read %d bytes\n", res);
            if (res <= 0)
            {
                break;
            }

            buffer[res] = 0;
            m_terminal->receiveChars(buffer, res);
        }
        printf("TerminalProcess::main: (Parent) Child exited\n");
    }
    else if (pid == 0)
    {
        printf("TerminalProcess::main: (Child) Setting up pipes...\n");
        close(read_pipe[0]);
        close(write_pipe[1]);

        dup2(read_pipe[1], STDOUT_FILENO);
        dup2(write_pipe[0], STDIN_FILENO);

        close(write_pipe[0]);
        close(read_pipe[1]);

        //printf("TerminalProcess::main: (Child) Calling watch!\n");
        //execl("/usr/local/bin/watch", "watch", "/bin/ls", "-l", NULL);
        //execl("/bin/ls", "/bin/ls", "-l", NULL);
        //execl("/bin/bash", "-l", NULL);
        //printf("TerminalProcess::main: (Child) Starting command...\n");
        //execl("/usr/local/bin/bash", "bash", "-i", NULL);
        //execl("/usr/bin/make", "make", NULL);
//char* const[] env = {
//"TERM
//};
        //execl("/usr/bin/top", "top", "-n", "5", NULL);

        execl("/usr/bin/uname", "uname", "-a", NULL);
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
    kill(m_childPid, SIGHUP);
}

