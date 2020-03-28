#include "test/Main.hpp"
#include "test/Data.hpp"
#include "prb/Data.hpp"
#include "prb/Fit.hpp"
#include "test_set6/Output.hpp"

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


std::function<void()> test_set6()
{
  return []() {
    double dInitialTime = 2;
    double dMaturity = dInitialTime + 3.;
    cfl::Fit uFit = getBSpline(dInitialTime, dMaturity);
    test::discountYieldFit(prb::NData::discountYieldFit, dInitialTime, dMaturity,uFit);
    test::discountLogFit(prb::NData::discountLogFit, dInitialTime, dMaturity, uFit);
    test::volatilityBlackFit(prb::NData::volatilityBlackFit, dInitialTime, dMaturity);
    test::discountNelsonSiegelFit(prb::NData::discountNelsonSiegelFit, dInitialTime, dMaturity);
    test::discountSvensonFit(prb::NData::discountSvensonFit, dInitialTime, dMaturity);
  };
};

int main()
{
  try
  {
    test::project(test_set6(), PROJECT_NAME, "test_set6", "TESTING OF SET 6");
    return 0;
  }
  catch (const std::exception &rError)
  {
    std::cerr << rError.what() << std::endl;
  }
}