#ifndef __FRONTIER_VALUE_H_
#define __FRONTIER_VALUE_H_

#include <wchar.h>
#include <variant>

namespace Frontier
{

enum ValueType
{
    VOID,
    INT,
    STRING
};

struct Value
{
    ValueType type;
    std::variant<int, std::wstring> v;

    Value()
    {
        type = VOID;
        v = 0;
    }

    Value(const Value& o)
    {
        type = o.type;
        v = o.v;
    }

    Value(int64_t i)
    {
        type = INT;
        v = i;
    }

    Value(std::wstring str)
    {
        type = STRING;
        v = str;
    }

    ~Value()
    {
    }

    std::wstring asString()
    {
        switch (type)
        {
            case VOID:
                return L"(void)";

            case INT:
            {
                wchar_t buf[256];
                swprintf(buf, 256, L"%lld", std::get<int>(v));
                return std::wstring(buf);
            } break;

            case STRING:
                return std::get<std::wstring>(v);
        }
    }

    int64_t asInt()
    {
        switch (type)
        {
            case VOID:
                return 0;

            case INT:
                return std::get<int>(v);

            case STRING:
                return wcstoul(std::get<std::wstring>(v).c_str(), NULL, 10);
        }
    }

    bool asBool()
    {
        switch (type)
        {
            case VOID:
                return false;

            case INT:
                return !!(std::get<int>(v));

            case STRING:
                std::wstring str = std::get<std::wstring>(v);
                if (str == L"true")
                {
                    return true;
                }
                else if (str == L"false")
                {
                    return false;
                }
                else
                {
                    return asInt() > 0;
                }
                break;
        }
    }
};

};

#endif
