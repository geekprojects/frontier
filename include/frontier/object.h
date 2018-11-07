#ifndef __FRONTIER_OBJECT_H_
#define __FRONTIER_OBJECT_H_

namespace Frontier
{

class FrontierObject
{
 private:
    int m_referenceCount;

 public:
    FrontierObject();
    virtual ~FrontierObject();

    virtual void incRefCount() { m_referenceCount++; }
    virtual void decRefCount() { m_referenceCount--; }
    int getRefCount() { return m_referenceCount; }
};

};

#endif
