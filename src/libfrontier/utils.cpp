
#include <frontier/utils.h>

using namespace Frontier;
using namespace std;

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

