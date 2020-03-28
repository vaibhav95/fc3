#ifndef __test_prb_Main_hpp__
#define __test_prb_Main_hpp__

#include <functional>
#include "test/Main.hpp"

namespace test
{
std::function<void()> interp();
std::function<void()> fit();
std::function<void()> approx();
std::function<void()> gaussRollback();
std::function<void()> ind();
std::function<void()> data();
} // namespace test

#endif // of __test_prb_Main_hpp__
