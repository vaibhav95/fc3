#include <cmath>
#include <chrono>
#include <string>
#include <vector>
#include <gsl/gsl_math.h>
#include "cfl/Function.hpp"
#include "cfl/GaussRollback.hpp"
#include "cfl/Ind.hpp"
#include "test/Main.hpp"
#include "test/GaussRollback.hpp"
#include "test/Ind.hpp"


using namespace cfl;
using namespace std;
using namespace test;

void test::printInd(const std::vector<cfl::Ind> &rInd, const std::vector<std::string> &sMethod)
{
  unsigned iColumn = 10;
  unsigned iSpace = 4;

  double dH = 1;
  unsigned iSize = 9;
  double dInitialValue = -(iSize - 1.) * 0.5 * dH;

  std::valarray<double> uState(dInitialValue, iSize);
  std::transform(begin(uState), end(uState) - 1, begin(uState) + 1, [dH](double dX) { return dX + dH; });

  std::vector<std::valarray<double>> uRes(1 + rInd.size(), uState);
  std::vector<string> sMes(sMethod);
  sMes.insert(sMes.begin(), "state");

  double dL = dInitialValue + (iSize - 1) * dH * 0.5;
  double dR = dL + dH;
  unsigned iN = 5;
  std::valarray<double> uBarrier = getArg(dL, dR, iN);

  for (unsigned i = 1; i < uBarrier.size() - 1; i++)
  {
    string sBarrier = "Indicator of the event: state is greater than the barrier ";
    sBarrier += std::to_string(uBarrier[i]);

    for (unsigned j = 0; j < rInd.size(); j++)
    {
      uRes[j + 1] = uState;
      rInd[j].indicator(uRes[j + 1], uBarrier[i]);
    }
    print(uRes, sMes, sBarrier, iColumn, iSpace, iSize);
  }
}

void test::rollbackInd(const std::vector<cfl::Ind> &rInd, const std::vector<std::string> &sMethod,
                 std::vector<cfl::GaussRollback> &rRollback,
                 const std::vector<string> &rNames, bool bRes, bool bErr)
{
  double dVar = 0.36;
  int iStandardDev = 5;
  double dInterval = iStandardDev * ::sqrt(dVar);
  double dH = 0.01;
  unsigned iSize = unsigned(2 * ::ceil(dInterval / (dH)) + 1);
  std::cout << "size  = " << iSize << ", ";
  std::cout << "var = " << dVar << ", ";
  std::cout << "h = " << dH << endl
            << endl;

  const double c_dPi = M_PI;

  for (unsigned j = 0; j < rRollback.size(); j++)
  {
    auto start = std::chrono::system_clock::now();
    std::cout << rNames[j].c_str() << endl
              << endl;

    unsigned iNames = 8;
    std::vector<std::valarray<double>> uRes(iNames, std::valarray<double>(iSize));
    GaussRollback uRollback(rRollback[j]);
    uRollback.assign(iSize, dH, dVar);

    std::valarray<double> uState(0., iSize);
    uState[0] = -dH * (iSize - 1) / 2;
    std::transform(begin(uState), end(uState) - 1, begin(uState) + 1,
                   [dH](double dX) { return dX + dH; });
    double dBarrier = dH * 1.001;
    string sMes = "Rollback of function f(x) = exp(x) * I(x>b), with b=";
    sMes += to_string(dBarrier);
    sMes += ". ";

    for (unsigned i = 0; i < rInd.size(); i++)
    {
      cout << "Type of the indicator function = " << sMethod[i] << endl
           << endl;
      uRes[0] = uState;
      rInd[i].indicator(uRes[0], dBarrier);
      uRes[0] *= exp(uState);
      uRollback.rollback(uRes[0], uRes[1], uRes[2]);
      uRes[3] = uRes[2];
      uRollback.vega(uRes[3]);
      //value
      std::valarray<double> uX(iSize);
      std::valarray<double> uY(iSize);
      std::valarray<double> uZ(iSize);
      uX = exp(uState + (0.5 * dVar));
      uY = ((dBarrier - dVar) - uState) / sqrt(dVar);
      uZ = uX * std::exp(-0.5 * (uY * uY)) / sqrt(2 * dVar * c_dPi);
      std::transform(begin(uY), end(uY), begin(uRes[4]), [](double dY) {
        return 0.5 * erfc(dY / sqrt(2.));
      });
      uRes[4] *= uX;
      uRes[5] = uZ + uRes[4];
      uRes[6] = uRes[5] + uZ * (1. + uY / sqrt(dVar));
      uRes[7] = uRes[6] * std::sqrt(dVar);
      printRollback(uRes, sMes, uState, bRes, bErr);
    }

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    cout << "Execution time = " << diff.count() << " seconds." << endl
         << endl;
  }
}
