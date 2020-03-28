#include "test/Fit.hpp"
#include "prb/Fit.hpp"
#include "test_prb/Main.hpp"

std::function<void()> test::fit()
{
  return []() {
    testLinearFit(prb::NFit::linear);
    testBSplineFit(prb::NFit::bspline);
  };
};
