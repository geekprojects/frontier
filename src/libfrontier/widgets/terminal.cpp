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
#include <sys/wait.h> 
#include <wchar.h>
#include <wctype.h>

// openpty
#if defined(__APPLE__) && defined(__MACH__)
#include <util.h>
#else
#include <pty.h>
#endif

#undef DEBUG_TERMINAL

#define ALIGN(V, SIZE) ((((V) + (SIZE) - 1) / (SIZE)) * (SIZE))

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

    reset();
    clear();
}

Terminal::Terminal(FrontierWindow* window) : Widget(window, L"Terminal")
{
    m_process = NULL;

    reset();
    clear();
}

Terminal::~Terminal()
{
    if (m_process != NULL)
    {
        m_process->stop();
        delete m_process;
        m_process = NULL;
    }
}

void Terminal::reset()
{
    m_fgColour = getColour8(9, true);
    m_bgColour = getColour8(9, false);
}

void Terminal::clear()
{
    m_col = 0;
    m_row = 0;
    m_offsetRow = 0;
    m_state = STATE_NORMAL;

    m_buffer.clear();
}

void Terminal::calculateSize()
{
    FontHandle* font = m_app->getTheme()->getMonospaceFont(true);
    int fontHeight = m_app->getTheme()->getMonospaceHeight();

    FontManager* fm = m_app->getFontManager();
    int fontWidth = fm->width(font, L"M");

    m_minSize.width = fontWidth * 20;
    m_minSize.height = fontHeight * 4;

    m_maxSize.width = WIDGET_SIZE_UNLIMITED;
    m_maxSize.height = WIDGET_SIZE_UNLIMITED;
}

bool Terminal::draw(Surface* surface)
{
    surface->clear(m_bgColour);

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

    // Make sure the current row is visible
    if (m_row > m_offsetRow + visibleRows)
    {
        m_offsetRow = (m_row - visibleRows) + 1;
    }
    else if (m_row < m_offsetRow)
    {
        m_offsetRow = m_row;
    }

    int y = 0;
    unsigned int row;
    for (row = 0; row < visibleRows && (row + m_offsetRow) < m_buffer.size(); row++, y += fontHeight)
    {
        TermLine& line = m_buffer.at(row + m_offsetRow);
        unsigned int col;
        int x = 0;
        for (col = 0; col < visibleColumns; col++, x += fontWidth)
        {
            uint32_t fg = m_fgColour;
            uint32_t bg = m_bgColour;
            TermChar c;
            if (col < line.chars.size())
            {
                c = line.chars.at(col);
                fg = c.fg;
                bg = c.bg;
            }
            else
            {
                if (row + m_offsetRow != m_row || col > m_col)
                {
                    // No more to draw on this line!
                    break;
                }
            }

            bool isCursor = (row + m_offsetRow == m_row && col == m_col);
            if (isCursor)
            {
                uint32_t tmp;
                tmp = bg;
                bg = fg;
                fg = tmp;
            }

            if (bg != m_bgColour)
            {
                if (isCursor && !isActive())
                {
                    surface->drawRect(x, y, fontWidth, fontHeight, bg);
                }
                else
                {
                    surface->drawRectFilled(x, y, fontWidth, fontHeight, bg);
                }
            }

            if (col < line.chars.size())
            {
                fm->write(font, surface, x, y, wstring(L"") + c.c, fg, true, NULL);
            }
        }
    }

    return true;
}

Widget* Terminal::handleEvent(Event* event)
{
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
                if (m_process != NULL)
                {
                    m_process->typeChar(c);
                }
            }
        }

        default:
            break;
    }
    return this;
}

void Terminal::setChar(unsigned int row, unsigned int col, wchar_t c)
{
    if (m_buffer.size() <= row)
    {
        m_buffer.resize(row + 1);
    }

    TermChar termChar;
    termChar.c = c;
    termChar.fg = m_fgColour;
    termChar.bg = m_bgColour;

    TermLine& line = m_buffer.at(row);
    if (col >= line.chars.size())
    {
        int pad = col - line.chars.size();
        int i;
        for (i = 0; i < pad; i++)
        {
            TermChar padchar;
            padchar.c = L' ';
            padchar.fg = m_fgColour;
            padchar.bg = m_bgColour;
            line.chars.push_back(padchar);
        }

        line.chars.push_back(termChar);
    }
    else
    {
        line.chars[col] = termChar;
    }
}

void Terminal::receiveChar(wchar_t c)
{
    if (m_buffer.empty())
    {
        TermLine line;
        m_buffer.push_back(line);
    }

    switch (m_state)
    {
        case STATE_NORMAL:
            if (c == 0x8)
            {
                // Backspace
                setChar(m_row, m_col, ' ');
                m_col--;
            }
            else if (c == 0x9)
            {
                // TAB
                m_col = ALIGN(m_col + 1, 8);
            }
            else if (c == 0xa)
            {
                // Line Feed
                m_row++;
            }
            else if (c == 0xd)
            {
                // Carriage Return
                m_col = 0;
            }
            else if (c == 0x1b)
            {
                // Escape
                m_state = STATE_ESC;
                m_command = L"";
            }
            else if (iswprint(c))
            {
                setChar(m_row, m_col, c);
                m_col++;
            }
            else
            {
                printf("Terminal::receiveChar: c: 0x%x\n", c);
            }
            break;

        case STATE_ESC:
            if (c == '[')
            {
                m_state = STATE_CSI;
            }
            else if (c == ']')
            {
                m_state = STATE_OSC;
            }
            else
            {
                printf("Terminal::receiveChar: STATE_ESC: Unhandled char: %c (0x%x)\n", c, c);
                m_state = STATE_NORMAL;
            }
            break;

        case STATE_CSI:

            if (iswalpha(c))
            {
                handleCSI(c);
            }
            else
            {
                m_command += c;
            }
            break;

        case STATE_OSC:
            if (c == 0x07)
            {
                printf("Terminal::receiveChar: STATE_OSC: %ls\n", m_command.c_str());
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

void Terminal::handleCSI(wchar_t c)
{
    std::vector<long> params;
    if (m_command.length() > 0)
    {
        unsigned long pos = 0;
        while (pos != wstring::npos)
        {
            unsigned long idx = m_command.find(';', pos);
            wstring part;
            if (idx != wstring::npos)
            {
                part = m_command.substr(pos, idx);
            }
            else
            {
                part = m_command.substr(pos);
            }
            long param = wcstol(part.c_str(), NULL, 10);
            params.push_back(param);
            if (idx == wstring::npos)
            {
                break;
            }

            pos = idx + 1;
        }
    }

    long param1 = -1;
    long param2 = -1;
    if (params.size() > 0)
    {
        param1 = params.at(0);
        if (params.size() > 1)
        {
            param2 = params.at(1);
        }
    }

    switch (c)
    {
        case 'A':
            if (param1 == -1)
            {
                param1 = 1;
            }
            m_row -= param1;
            break;

        case 'B':
            if (param1 == -1)
            {
                param1 = 1;
            }
            m_row += param1;
            break;
        case 'C':
            if (param1 == -1)
            {
                param1 = 1;
            }
            m_col += param1;
            break;
        case 'D':
            if (param1 == -1)
            {
                param1 = 1;
            }
            m_col -= param1;
            break;
        case 'H':
        {
            if (param1 == -1)
            {
                param1 = 1;
            }
            if (param2 == -1)
            {
                param2 = 1;
            }
            printf("Terminal::receiveChar: : STATE_CSI: Cursor Position: row=%ld, col=%ld\n", param1, param2);

            m_row = param1 - 1;
            m_col = param2 - 1;
        } break;

        case 'G':
            if (param1 == -1)
            {
                param1 = 1;
            }
            m_col = param1 - 1;
            printf("Terminal::receiveChar: : STATE_CSI: Cursor Position: col=%ld\n", param1);
            break;

        case 'J':
            if (param1 == -1)
            {
                param1 = 0;
            }
            switch (param1)
            {
                case 2:
                    printf("Terminal::receiveChar: STATE_CSI: Erase in Display: ALL!\n");
                    clear();
                    break;
                default:
                    printf("Terminal::receiveChar: STATE_CSI: Erase in Display: Unhandled: %ld\n", param1);
                    break;
            }
            break;

        case 'K':
            if (param1 == -1)
            {
                param1 = 0;
            }
            switch (param1)
            {
                case 0:
                    printf("Terminal::receiveChar: STATE_CSI: Erase to Right\n");
                    if (m_row < m_buffer.size() && m_col >= 0)
                    {
                        TermLine& line = m_buffer.at(m_row);
                        if (m_col < line.chars.size())
                        {
                            line.chars.erase(line.chars.begin() + m_col);
                        }
                    }
                    break;

                default:
                    printf("Terminal::receiveChar: STATE_CSI: Erase in Line: Unhandled: %ld\n", param1);
                    break;
            }
            break;

        case 'P':
        {
            if (param1 == -1)
            {
                param1 = 1;
            }

            int count = param1;
            printf("Terminal::receiveChar: : STATE_CSI: Delete Characters: count=%d\n", count);
            if (m_row < m_buffer.size())
            {
                TermLine& line = m_buffer.at(m_row);
                if (m_col < line.chars.size())
                {
                    //line.erase(m_col, count);
                    int i;
                    for (i = 0; i < count; i++)
                    {
                        line.chars.erase(line.chars.begin() + m_col);
                    }
                }
            }
        } break;

        case 'd':
            if (param1 == -1)
            {
                param1 = 1;
            }

            m_row = param1 - 1;
            break;

        case 'm':
            printf("Terminal::receiveChar: : STATE_CSI: Character Attributes: %ld\n", param1);
            if (param1 == 0)
            {
                m_fgColour = getColour8(9, true);
                m_bgColour = getColour8(9, false);
            }
            else if (param1 >= 30 && param1 <= 39)
            {
                m_fgColour = getColour8(param1 - 30, true);
            }
            else if (param1 >= 40 && param1 <= 49)
            {
                m_bgColour = getColour8(param1 - 40, false);
            }
            else
            {
                printf("Terminal::receiveChar: : STATE_CSI: UNHANDLED Character Attributes: %ld\n", param1);
            }
            break;

        default:
            printf("Terminal::receiveChar: : STATE_CSI: UNHANDLED command: %c, params: %ls -> %ld, %ld\n", c, m_command.c_str(), param1, param2);
            break;
    }

    m_state = STATE_NORMAL;
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

uint32_t Terminal::getColour8(int code, bool fg)
{
    switch (code)
    {
        case 0: return 0x000000; // Black
        case 1: return 0xc91b00; // Red
        case 2: return 0x00c200; // Green
        case 3: return 0xc7c400; // Yellow
        case 4: return 0x0225c7; // Blue
        case 5: return 0xc930c7; // Magenta
        case 6: return 0x00c5c7; // Cyan
        case 7: return 0xc7c7c7; // White

        case 9:
        default:
            if (fg)
            {
                return 0xc7c7c7;
            }
            else
            {
                return 0x000000;
            }
    }
}

bool Terminal::run(const char* command)
{
    return run(command, vector<const char*>());
}

bool Terminal::run(const char* command, vector<const char*> args)
{
    return run(command, args, vector<const char*>());
}

bool Terminal::run(const char* command, vector<const char*> args, vector<const char*> env)
{
    m_process = new TerminalProcess(this, command, args, env);
    m_process->start();

    return true;
}

TerminalProcess::TerminalProcess(Terminal* terminal, const char* command, std::vector<const char*> args, std::vector<const char*> env) : Logger("TerminalProcess")
{
    m_terminal = terminal;
    m_command = strdup(command);

    for (const char* arg : args)
    {
        m_args.push_back(strdup(arg));
    }
    for (const char* e : env)
    {
        m_env.push_back(strdup(e));
    }
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
#if 0
    log(INFO, "main: master=%d, slave=%d, name=%s", master, slave, name);
#endif

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
            res = read(m_childOut, buffer, 4096);
            if (res <= 0)
            {
                break;
            }
#if 0
            log(DEBUG, "main: (Parent) Read %d bytes", res);
#endif

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

        char* argv[m_args.size() + 2];
        unsigned int i = 0;
        argv[0] = m_command;
        for (i = 0; i < m_args.size(); i++)
        {
            argv[i + 1] = m_args[i];
        }
        argv[i + 1] = 0;

        char* envp[m_env.size() + 3];
        for (i = 0; i < m_env.size(); i++)
        {
            envp[i] = m_env[i];
        }
        envp[i++] = strdup((string("HOME=") + getenv("HOME")).c_str());
        envp[i++] = strdup("TERM=xterm-256color");
        envp[i] = 0;

        execve(m_command, argv, envp);

        perror("execl() failed");
        _exit(errno);
    }

    return true;
}

void TerminalProcess::typeChar(wchar_t c)
{
    int res;
    printf("TerminalProcess::typeChar: c=0x%x\n", c);

    char buf[2];
    buf[0] = c;
    buf[1] = 0;

    res = write(m_childIn, buf, 1);
    if (res < 0)
    {
        int err = errno;
        log(ERROR, "Failed to write char: errno=%d", err);
    }
}

void TerminalProcess::stop()
{
    log(DEBUG, "stop: Killing child...");
    kill(m_childPid, SIGHUP);

    log(DEBUG, "stop: waiting...");
    int stat_loc;
    waitpid(m_childPid, &stat_loc, 0);

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

