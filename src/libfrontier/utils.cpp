
#include <frontier/utils.h>

#include <execinfo.h>


using namespace Frontier;
using namespace std;

#define BT_BUF_SIZE 100

wstring Utils::string2wstring(string str)
{
    wstring out;
    unsigned int i;
    for (i = 0; i < str.length(); i++)
    {
        out += (char)str[i];
    }
    return out;
}

string Utils::wstring2string(wstring str)
{
    string out;
    unsigned int i;
    for (i = 0; i < str.length(); i++)
    {
        out += str[i];
    }
    return out;
}

void Utils::stacktrace()
{
    char **strings;
    void *buffer[BT_BUF_SIZE];
    int j;
    int nptrs;

    nptrs = backtrace(buffer, BT_BUF_SIZE);
    strings = backtrace_symbols(buffer, nptrs);
    if (strings != NULL)
    {
        for (j = 0; j < nptrs; j++)
        {
            printf("%s\n", strings[j]);
        }
        free(strings);
    }
}

