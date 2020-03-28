#include <cmath>
#include <numeric>
#include "cfl/Fit.hpp"
#include "cfl/Error.hpp"
#include "test/Main.hpp"
#include "test/Fit.hpp"

using namespace cfl;
using namespace std;
using namespace test;

void testFit(Fit &rFit, const std::valarray<double> &rFitNodes,
             const std::valarray<double> &rRandNodes)
{
  std::vector<Function> uF;
  std::vector<string> uNames;
  uF.push_back(Function([](double dX) { return std::exp(dX); }));
  uNames.push_back("exact");

  cout << "We fit the function f(x) = exp(x)" << endl
       << endl;
  std::valarray<double> uFitValues = getValues(uF.front(), rFitNodes);
  rFit.assign(begin(rFitNodes), end(rFitNodes), begin(uFitValues));

  uF.push_back(rFit.fit());
  uNames.push_back("numeric");
  uF.push_back(rFit.err());
  uNames.push_back("est err");
  uF.push_back(abs(uF[0] - uF[1]));
  uNames.push_back("act err");

  unsigned iColumn = 12;
  unsigned iSpace = 6;

  test::print(uF, uNames, rFitNodes, "Fit at the nodes of fitting", iColumn, iSpace);
  printTotalErr(rFit.err(), uF[uF.size() - 1], rFitNodes);

  test::print(uF, uNames, rRandNodes, "Fit at random nodes", iColumn, iSpace);
  printTotalErr(rFit.err(), uF[uF.size() - 1], rRandNodes);
}

void test::testLinearFit(test::tLinear fFit)
{
  cout << "TEST OF LINEAR LEAST SQUARE FITTING" << endl
       << endl;
  double dL = -1.;
  double dR = 2.;
  unsigned iPoints = 18;
  std::valarray<double> uFitNodes = getArg(dL, dR, iPoints);
  std::valarray<double> uRandNodes = getRandArg(dL, dR, iPoints);
  unsigned iOrder = iPoints / 3;
  Function uLinFunc([](double dX) { return dX; });

  std::vector<Function> uBase(iOrder);
  uBase.front() = Function(1.);
  for (unsigned i = 0; i + 1 < iOrder; i++)
  {
    uBase[i + 1] = uBase[i] * uLinFunc;
  }
  cout << "Fitting with polynomials of order " << (iOrder - 1) << endl
       << endl;

  Fit uFit = fFit(uBase);
  testFit(uFit, uFitNodes, uRandNodes);
}

void test::testBSplineFit(test::tBSpline fFit)
{
  cout << "TEST OF LINEAR LEAST SQUARE FITTING WITH BASIS SPLINES" << endl
       << endl;
  double dL = -1.;
  double dR = 2.;
  unsigned iPoints = 18;
  std::valarray<double> uFitNodes = getArg(dL, dR, iPoints);
  std::valarray<double> uRandNodes = getRandArg(dL, dR, iPoints);
  unsigned iBreakpoints = 4;
  unsigned iOrder = 4;
  ASSERT(iBreakpoints + iOrder - 2 <= uFitNodes.size());
  Fit uFit = fFit(iOrder, dL, dR, iBreakpoints);
  cout << "Fitting with basic splines of order " << iOrder
       << " with " << iBreakpoints << " uniform breakpoints on [" << dL
       << "," << dR << "]" << endl
       << endl;
  testFit(uFit, uFitNodes, uRandNodes);
}
