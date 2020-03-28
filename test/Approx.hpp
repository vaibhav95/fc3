#ifndef __test_Approx_hpp__
#define __test_Approx_hpp__

#include "cfl/Approx.hpp"

namespace test
{
typedef cfl::Approx (*t_chebyshev)(const std::function<unsigned(double)> &);
void testChebyshevApprox(t_chebyshev);
} // namespace test

#endif // of __test_Approx_hpp__
