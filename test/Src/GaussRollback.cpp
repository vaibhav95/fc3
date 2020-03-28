#include <cmath>
#include <string>
#include <iomanip>
#include <chrono>
#include "test/Main.hpp"
#include "test/GaussRollback.hpp"

using namespace cfl;
using namespace std;
using namespace std::chrono;
using namespace test;

void test::testGaussRollback(const cfl::GaussRollback &rRollback,
                             const std::string &sMethod, bool bRes, bool bErr, bool bFull)
{
     std::cout << sMethod.c_str() << endl
               << endl;

     double dVar = 0.36;
     int iStandardDev = 8;
     double dInterval = iStandardDev * ::sqrt(dVar);

     unsigned iRuns = 3;
     double dHStep = 1. / ::sqrt(10.);
     double dH = 0.1;
     dH /= dHStep;

     for (unsigned i = 0; i < iRuns; i++)
     {
          auto start = std::chrono::system_clock::now();
          dH *= dHStep;
          unsigned iSize = unsigned(2 * ::ceil(dInterval / (dH)) + 1);
          std::cout << "size  = " << iSize << ", ";
          std::cout << "var = " << dVar << ", ";
          std::cout << "h = " << dH << endl
                    << endl;

          unsigned iNames = 8;
          std::vector<std::valarray<double>> uRes(iNames, std::valarray<double>(iSize));
          GaussRollback uRollback(rRollback);
          uRollback.assign(iSize, dH, dVar);

          std::valarray<double> uState(0., iSize);
          uState[0] = -dH * (iSize - 1) / 2;
          std::transform(begin(uState), end(uState) - 1, begin(uState) + 1,
                         [dH](double dX) { return dX + dH; });
          std::string sMes;

          if (bFull)
          {
               double dA = 2;
               sMes = "Rollback of constant function f(x) = ";
               sMes += std::to_string(dA);
               sMes += ". ";
               uRes[0] = dA;
               uRollback.rollback(uRes[0], uRes[1], uRes[2]);
               uRes[3] = uRes[2];
               uRollback.vega(uRes[3]);
               uRes[4] = dA;
               uRes[5] = 0.;
               uRes[6] = 0.;
               uRes[7] = 0.;
               printRollback(uRes, sMes, uState, bRes, bErr);

               sMes = "Rollback of linear function f(x) = x. ";
               uRes[0] = uState;
               uRollback.rollback(uRes[0], uRes[1], uRes[2]);
               uRes[3] = uRes[2];
               uRollback.vega(uRes[3]);
               uRes[4] = uState;
               uRes[5] = 1;
               uRes[6] = 0;
               uRes[7] = 0;
               printRollback(uRes, sMes, uState, bRes, bErr);

               sMes = "Rollback of quadratic function f(x) = x^2. ";
               uRes[0] = uState * uState;
               uRollback.rollback(uRes[0], uRes[1], uRes[2]);
               uRes[3] = uRes[2];
               uRollback.vega(uRes[3]);
               uRes[4] = uState * uState + dVar;
               uRes[5] = uState * 2.;
               uRes[6] = 2;
               uRes[7] = 2 * ::sqrt(dVar);
               printRollback(uRes, sMes, uState, bRes, bErr);

               sMes = "Rollback of exponential function f(x) = e^x. ";
               uRes[0] = exp(uState);
               uRollback.rollback(uRes[0], uRes[1], uRes[2]);
               uRes[3] = uRes[2];
               uRollback.vega(uRes[3]);
               uRes[4] = exp(uState + 0.5 * dVar);
               uRes[5] = uRes[4];
               uRes[6] = uRes[4];
               uRes[7] = uRes[4] * std::sqrt(dVar);
               printRollback(uRes, sMes, uState, bRes, bErr);
          }

          sMes = "Rollback of function f(x) = xe^x. ";
          uRes[0] = uState * exp(uState);
          uRollback.rollback(uRes[0], uRes[1], uRes[2]);
          uRes[3] = uRes[2];
          uRollback.vega(uRes[3]);
          uRes[4] = (uState + dVar) * exp(uState + 0.5 * dVar);
          uRes[5] = (uState + (1 + dVar)) * exp(uState + 0.5 * dVar);
          uRes[6] = (uState + (2 + dVar)) * exp(uState + 0.5 * dVar);
          uRes[7] = uRes[6] * std::sqrt(dVar);
          printRollback(uRes, sMes, uState, bRes, bErr);

          auto end = std::chrono::system_clock::now();
          std::chrono::duration<double> diff = end - start;
          cout << "Execution time = " << diff.count() << " seconds." << endl
               << endl;
     }
}

void test::printRollback(const std::vector<std::valarray<double>> &rRes,
                         const std::string &sMes, const std::valarray<double> &rState,
                         bool bRes, bool bErr)
{
     unsigned iNames = 8;
     ASSERT(rRes.size() == iNames);
     std::vector<std::string> uNames(iNames);
     uNames[0] = "num value";
     uNames[1] = "num delta";
     uNames[2] = "num gamma";
     uNames[3] = "num vega";
     uNames[4] = "true value";
     uNames[5] = "true delta";
     uNames[6] = "true gamma";
     uNames[7] = "true vega";

     uNames.insert(uNames.begin(), "state");
     auto uRes(rRes);
     uRes.insert(uRes.begin(), rState);

     unsigned iErr = iNames / 2;
     unsigned iSize = rRes.front().size();
     std::vector<std::valarray<double>> uErr(iErr, std::valarray<double>(iSize));
     std::vector<std::string> uErrNames(iErr);
     uErrNames[0] = "err value";
     uErrNames[1] = "err delta";
     uErrNames[2] = "err gamma";
     uErrNames[3] = "err vega";

     unsigned iPoints = 11; //points to print
     unsigned iColumns = 12;
     unsigned iSpace = 3;

     if (bRes)
     {
          test::print(uRes, uNames, sMes, iColumns, iSpace, iPoints);
     }
     if (bErr)
     {
          for (unsigned i = 0; i < iErr; i++)
          {
               uErr[i] = abs(rRes[i] - rRes[i + iErr]);
          }
          std::string sErr = sMes;
          sErr += "Errors:";
          test::print(uErr, uErrNames, sErr, iColumns, iSpace, iPoints);
     }
}