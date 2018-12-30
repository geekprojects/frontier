#ifndef __FRONTIER_OBJECT_H_
#define __FRONTIER_OBJECT_H_

#include <atomic>

namespace Frontier
{

class FrontierObject
{
 private:
    std::atomic<int> m_referenceCount;

 public:
    FrontierObject();
    virtual ~FrontierObject();

    void incRefCount() { m_referenceCount++; }
    void decRefCount() { m_referenceCount--; }
    int getRefCount() { return m_referenceCount.load(); }
};

};

#endif
