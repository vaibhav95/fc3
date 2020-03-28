#include "test/Data.hpp"
#include "test_prb/Main.hpp"
#include "prb/Data.hpp"
#include "prb/Fit.hpp"
#include "prb/Interp.hpp"
#include <iomanip>

using namespace std;

cfl::Fit getBSpline(double dInitialTime, double dMaturity)
{
  unsigned iOrder = 4;
  unsigned iBreakpoints = 2;
  cout << "Fitting with basis splines: interval = [" << dInitialTime << ", "
       << dMaturity << "], order = " << iOrder << ", number of breakpoints = "
       << iBreakpoints << endl
       << endl;

  return prb::NFit::bspline(iOrder, dInitialTime, dMaturity, iBreakpoints);
}

std::function<void()> test::data()
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

    cfl::Fit uFit = getBSpline(dInitialTime, dMaturity);
    test::discountYieldFit(prb::NData::discountYieldFit, dInitialTime, dMaturity, uFit);
    test::discountLogFit(prb::NData::discountLogFit, dInitialTime, dMaturity, uFit);
    test::discountNelsonSiegelFit(prb::NData::discountNelsonSiegelFit, dInitialTime, dMaturity);
    test::discountSvensonFit(prb::NData::discountSvensonFit, dInitialTime, dMaturity);

    test::volatilityBlackFit(prb::NData::volatilityBlackFit, dInitialTime, dMaturity);
  };
};
