#include "test/Main.hpp"
#include "test/Data.hpp"
#include "prb/Data.hpp"
#include "prb/Interp.hpp"
#include "test_set3/Output.hpp"

std::function<void()> test_set3()
{
  return []() {
    double dInitialTime = 2;
    double dMaturity = dInitialTime + 3.;

    std::vector<cfl::Interp> uInterp(1, prb::NInterp::linear());
    std::vector<std::string> uMethod(1, "Linear interpolation: ");
    uInterp.push_back(prb::NInterp::cspline());
    uMethod.push_back("Cubic spline interpolation: ");
    uInterp.push_back(prb::NInterp::steffen());
    uMethod.push_back("Steffen interpolation: ");

    test::discountYieldInterp(prb::NData::discountYieldInterp, dInitialTime,
                              dMaturity, uInterp, uMethod);
    test::discountLogInterp(prb::NData::discountLogInterp, dInitialTime,
                            dMaturity, uInterp, uMethod);
    test::volatilityVarInterp(prb::NData::volatilityVarInterp, dInitialTime, dMaturity,
                              uInterp, uMethod);
  };
};

int main()
{
  try
  {
    test::project(test_set3(), PROJECT_NAME, "test_set3", "TESTING OF SET 3");
    return 0;
  }
  catch (const std::exception &rError)
  {
    std::cerr << rError.what() << std::endl;
  }
}