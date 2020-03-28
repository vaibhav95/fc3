#ifndef __test_Fit_hpp__
#define __test_Fit_hpp__

#include "cfl/Fit.hpp"

namespace test
{
typedef cfl::Fit (*tLinear)(const std::vector<cfl::Function> &rBasisF);
void testLinearFit(tLinear fFit);

typedef cfl::Fit (*tBSpline)(unsigned iOrder, double dL, double dR, unsigned iBreakpoints);
void testBSplineFit(tBSpline);
} // namespace test

#endif // of __test_Fit_hpp__
