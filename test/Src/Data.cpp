#include <functional>
#include "test/Data.hpp"
#include "test/Main.hpp"

using namespace test;
using namespace cfl;
using namespace std;

typedef Function (*type_interp)(const std::vector<double> &, const std::vector<double> &, double, const cfl::Interp &);
void testInterp(const type_interp &rInterp, double dInitialTime, double dMaturity, 
const std::vector<cfl::Interp> & rMethod, const std::vector<std::string> & rName)
{
  std::string sInterpNodes("Comparison at the nodes of interpolation");
  std::string sRandNodes("Comparison at the random arguments");
  double dL = dInitialTime + 0.1 * (dMaturity - dInitialTime);
  double dR = dMaturity;
  unsigned iN = 8;
  unsigned iColumn = 10;
  unsigned iWidth = 8;
  std::valarray<double> uX = getArg(dL, dR, iN);
  std::valarray<double> uY = getRandArg(dL, dR, iN);
  Function uArg([](double dX) { return dX; });
  std::vector<std::string> uNames(1, "exact");
  uNames.push_back("numeric");
  uNames.push_back("error");
  std::vector<Function> uF(uNames.size());

  double dA = 0.1;
  double dB = 0.05;
  cout << "yield = b*exp(-a*t), where t=(arg-t0) is the time to maturity," << endl
       << "a = " << dA << ", b= " << dB << ", t0 = " << dInitialTime << endl
       << endl;
  std::valarray<double> uDF(uX.size());
  uDF = std::exp(-dB * std::exp(-dA * (uX - dInitialTime)) * (uX - dInitialTime));
  uF[0] = cfl::exp(-dB * cfl::exp(-dA * (uArg - dInitialTime)) * (uArg - dInitialTime));

  for (unsigned i = 0; i < rMethod.size(); i++)
  {
    print(rName[i].c_str());
    uF[1] = rInterp(std::vector<double>(begin(uX), end(uX)),
                    std::vector<double>(begin(uDF), end(uDF)),
                    dInitialTime, rMethod[i]);
    uF[2] = cfl::abs(uF[1] - uF[0]);
    print(uF, uNames, uX, sInterpNodes, iColumn, iWidth);
    print(uF, uNames, uY, sRandNodes, iColumn, iWidth);
  }
}

void test::discountYieldInterp(test::t_interp fMethod, double dInitialTime, double dMaturity, 
const std::vector<cfl::Interp> & rMethod, const std::vector<std::string> & rName)
{
  print("Discount curve obtained by interpolation of an yield curve");
  testInterp(fMethod, dInitialTime, dMaturity, rMethod, rName);
}

void test::discountLogInterp(test::t_interp fMethod, double dInitialTime, double dMaturity, 
const std::vector<cfl::Interp> & rMethod, const std::vector<std::string> & rName)
{
  print("Discount curve obtained by interpolation of its log");
  testInterp(fMethod, dInitialTime, dMaturity, rMethod, rName);
}

typedef std::function<Function(const std::valarray<double> &,
                               const std::valarray<double> &,
                               Function &)>
    tFit;

void testFit(const tFit &rDataFit, double dInitialTime, double dMaturity)
{
  std::string sInterpNodes("Comparison at the nodes of fitting");
  std::string sRandNodes("Comparison at the random arguments");
  double dL = dInitialTime + 0.001 * (dMaturity - dInitialTime);
  double dR = dMaturity;
  unsigned iN = 8;
  unsigned iColumn = 10;
  unsigned iWidth = 8;
  std::valarray<double> uX = getArg(dL, dR, iN);
  std::valarray<double> uY = getRandArg(dL, dR, iN);
  std::valarray<double> uT(uX.size());
  uT = uX - dInitialTime;
  Function uArg([dInitialTime](double dX) { return dX - dInitialTime; });
  std::vector<std::string> uNames(1, "exact");
  uNames.push_back("numeric");
  uNames.push_back("est err");
  uNames.push_back("act err");
  std::vector<Function> uF(uNames.size());

  double dA0 = 0.1;
  double dA1 = 0.5;
  double dB0 = 0.3;
  double dB1 = 0.4;
  double dB2 = 0.5;
  double dB3 = 0.6;

  cout << "yield = b0 + (b1 + b2*t) * exp(-a0*t) + b3*t*exp(-a1*t)" << endl
       << "t = arg - t0 is the time to maturity," << endl
       << "a0 = " << dA0 << ", a1 = " << dA1 << ", b0 = " << dB0 << ", b1 = " << dB1 << ", b2 = " << dB2 << ", b3 = "
       << dB3 << ", t0 = " << dInitialTime << endl
       << endl;
  std::valarray<double> uDF(uX.size());
  uDF = dB0 + (dB1 + dB2 * uT) * exp(-dA0 * uT) + dB3 * uT * exp(-dA1 * uT);
  uDF = std::exp(-uDF * uT);
  uF[0] = dB0 + (dB1 + dB2 * uArg) * exp(-dA0 * uArg) + dB3 * uArg * exp(-dA1 * uArg);
  uF[0] = exp(-uF[0] * uArg);

  uF[1] = rDataFit(uX, uDF, uF[2]);
  uF[3] = abs(uF[0] - uF[1]);
  print(uF, uNames, uX, sInterpNodes, iColumn, iWidth);
  printTotalErr(uF[2], uF[3], uX);
  print(uF, uNames, uY, sRandNodes, iColumn, iWidth);
  printTotalErr(uF[2], uF[3], uY);
}

typedef Function (*type_fit)(const std::vector<double> &, const std::vector<double> &,
                             double, cfl::Fit &, cfl::Function &);

void testFit(const type_fit &rDataFit, double dInitialTime, double dMaturity,
             cfl::Fit &rFit)
{
  tFit uFit = [dInitialTime, &rFit, rDataFit](const std::valarray<double> &rX,
                                              const std::valarray<double> &rY, Function &rErr) {
    return rDataFit(std::vector<double>(begin(rX), end(rX)),
                    std::vector<double>(begin(rY), end(rY)),
                    dInitialTime, rFit, rErr);
  };
  testFit(uFit, dInitialTime, dMaturity);
}

void test::discountYieldFit(test::t_fit fFit, double dInitialTime, double dMaturity, cfl::Fit & rFit)
{
  print("Discount curve obtained by least square fitting of  yield curve");
  testFit(fFit, dInitialTime, dMaturity, rFit);
}

void test::discountLogFit(test::t_fit fFit, double dInitialTime, double dMaturity, cfl::Fit & rFit)
{
  print("Discount curve obtained by least square fitting of its log");
  testFit(fFit, dInitialTime, dMaturity, rFit);
}

void test::discountNelsonSiegelFit(test::t_fit_lambda fFit, double dInitialTime, double dMaturity)
{
  print("Discount curve obtained by the Nelson-Siegel fit");
  double dLambda = 0.1;
  cout << "mean-reversion = " << dLambda << endl
       << endl;
  tFit uFit = [dInitialTime, dLambda, fFit](const std::valarray<double> &rX,
                                            const std::valarray<double> &rY,
                                            Function &rErr) {
    return fFit(std::vector<double>(begin(rX), end(rX)),
                std::vector<double>(begin(rY), end(rY)),
                dLambda, dInitialTime, rErr);
  };
  testFit(uFit, dInitialTime, dMaturity);
}

void test::discountSvensonFit(test::t_fit_lambda2 fFit, double dInitialTime, double dMaturity)
{
  print("Discount curve obtained by the Svenson fit");
  double dLambda1 = 0.1;
  double dLambda2 = 0.5;
  cout << "mean-reversion 1 = " << dLambda1 << "; mean-reversion 2 = " << dLambda2 << endl
       << endl;
  tFit uFit = [dInitialTime, dLambda1, dLambda2, fFit](const std::valarray<double> &rX,
                                                       const std::valarray<double> &rY, Function &rErr) {
    return fFit(std::vector<double>(begin(rX), end(rX)),
               std::vector<double>(begin(rY), end(rY)),
               dLambda1, dLambda2, dInitialTime, rErr);
  };
  testFit(uFit, dInitialTime, dMaturity);
}

void test::volatilityVarInterp(test::t_interp fInterp, double dInitialTime, double dMaturity, 
const std::vector<cfl::Interp> & rMethod, const std::vector<std::string> & rName)
{
  print("Volatility curve obtained by least square fitting of the variance curve");
  std::string sInterpNodes("Comparison at the nodes of interpolation");
  std::string sRandNodes("Comparison at the random arguments");
  double dL = dInitialTime + 0.1 * (dMaturity - dInitialTime);
  double dR = dMaturity;
  unsigned iN = 8;
  unsigned iColumn = 10;
  unsigned iWidth = 8;
  std::valarray<double> uX = getArg(dL, dR, iN);
  std::valarray<double> uY = getRandArg(dL, dR, iN);
  Function uArg([](double dX) { return dX; });
  std::vector<std::string> uNames(1, "exact");
  uNames.push_back("numeric");
  uNames.push_back("error");
  std::vector<Function> uF(uNames.size());

  double dA = 0.2;
  double dB = 0.35;
  cout << "volatility = b*sqrt((1-exp(-a*t))/(a*t))," << endl
       << "t=(arg-t0) is the time to maturity, a = " << dA << ", b= " << dB
       << ", t0 = " << dInitialTime << endl
       << endl;
  std::valarray<double> uVol(uX.size());
  uVol = dB * sqrt((1. - exp(-dA * (uX - dInitialTime))) / (dA * (uX - dInitialTime)));
  uF[0] = dB * sqrt((1. - exp(-dA * (uArg - dInitialTime))) / (dA * (uArg - dInitialTime)));

  for (unsigned i = 0; i < rMethod.size(); i++)
  {
    print(rName[i].c_str());
    uF[1] = fInterp(std::vector<double>(begin(uX), end(uX)),
                    std::vector<double>(begin(uVol), end(uVol)),
                    dInitialTime, rMethod[i]);
    uF[2] = cfl::abs(uF[1] - uF[0]);
    print(uF, uNames, uX, sInterpNodes, iColumn, iWidth);
    print(uF, uNames, uY, sRandNodes, iColumn, iWidth);
  }
}

void test::volatilityBlackFit(test::t_fit_lambda fFit, double dInitialTime, double dMaturity)
{
  print("Stationary volatility curve in Black model fitted to market data");
  double dLambda = 0.1;
  cout << "mean-reversion rate = " << dLambda << endl
       << endl;
  std::string sInterpNodes("Comparison at the nodes of fitting");
  std::string sRandNodes("Comparison at the random arguments");
  double dL = dInitialTime + 0.001 * (dMaturity - dInitialTime);
  double dR = dMaturity;
  unsigned iN = 8;
  unsigned iColumn = 10;
  unsigned iWidth = 8;
  std::valarray<double> uX = getArg(dL, dR, iN);
  std::valarray<double> uY = getRandArg(dL, dR, iN);
  Function uArg([](double dX) { return dX; });
  std::vector<std::string> uNames(1, "exact");
  uNames.push_back("numeric");
  uNames.push_back("est err");
  uNames.push_back("act err");
  std::vector<Function> uF(uNames.size());

  double dA = 2 * dLambda;
  double dB = 0.35;
  double dC = 0.1;
  cout << "volatility = c + b*sqrt((1-exp(-a*t))/(a*t))," << endl
       << "t=(arg-t0) is the time to maturity, a = " << dA
       << ", b= " << dB << ", c = " << dC << ", t0 = " << dInitialTime << endl
       << endl;
  std::valarray<double> uVol(uX.size());
  uVol = dC + dB * sqrt((1. - exp(-dA * (uX - dInitialTime))) / (dA * (uX - dInitialTime)));
  uF[0] = dC + dB * sqrt((1. - exp(-dA * (uArg - dInitialTime))) / (dA * (uArg - dInitialTime)));
  uF[1] = fFit(std::vector<double>(begin(uX), end(uX)),
               std::vector<double>(begin(uVol), end(uVol)),
               dLambda, dInitialTime, uF[2]);
  uF[3] = abs(uF[0] - uF[1]);
  print(uF, uNames, uX, sInterpNodes, iColumn, iWidth);
  printTotalErr(uF[2], uF[3], uX);
  print(uF, uNames, uY, sRandNodes, iColumn, iWidth);
  printTotalErr(uF[2], uF[3], uY);
}