#ifndef __FRONTIER_TESTS_TEST_COMMON_H_
#define __FRONTIER_TESTS_TEST_COMMON_H_

#include <frontier/frontier.h>
#include "engines/test/test_engine.h"

#include <gtest/gtest.h>

class TestApp : public Frontier::FrontierApp
{
 public:
    TestApp();
    virtual ~TestApp();
};


#endif
