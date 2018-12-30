
#include <frontier/object.h>

#include <stdio.h>

using namespace Frontier;
//using namespace std;

FrontierObject::FrontierObject()
{
    m_referenceCount = 0;
}

FrontierObject::~FrontierObject()
{
    if (m_referenceCount > 0)
    {
        printf("FrontierObject::~FrontierObject: WARN: m_referenceCount=%d\n", getRefCount());
    }
}


