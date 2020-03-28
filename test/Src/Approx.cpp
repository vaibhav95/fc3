#include <cmath>
#include <iomanip>
#include <algorithm>
#include <exception>
#include <numeric>
#include "cfl/Function.hpp"
#include "test/Main.hpp"
#include "test/Approx.hpp"

using namespace cfl;
using namespace std;
using namespace test;

void testApprox(Approx &rApprox, const std::string &sApprox)
{
     cout << sApprox.c_str() << endl
          << endl;
     std::string sApproxNodes("Comparison at the nodes of approximation. Should get zero errors.");
     std::string sRandNodes("Comparison at the random arguments");
     double dL = -1;
     double dR = 2;
     cout << "Interval of approximation is [" << dL << "," << dR << "]" << endl
          << endl;
     rApprox.assign(dL, dR);
     std::valarray<double> uX(rApprox.arg().size());
     std::copy(begin(rApprox.arg()), end(rApprox.arg()), begin(uX));
     unsigned iColumn = 10;
     unsigned iWidth = 8;
     unsigned iN = 8;
     std::valarray<double> uY = getRandArg(dL, dR, iN);
     Function uArg([](double dX) { return dX; });
     double dC = 1;
     double dT = 2;
     double dP = 3;
     std::vector<std::string> uNames(1, "exact");
     uNames.push_back("numeric");
     uNames.push_back("error");
     std::vector<Function> uF(3);

     cout << "Approximation of const function: f(x) = " << dC << endl
          << endl;
     std::valarray<double> uV(dC, uX.size());
     uF[0] = dC;
     uF[1] = rApprox.approximate(begin(uV), end(uV));
     uF[2] = cfl::abs((uF[1] - uF[0]) / uF[0]);
     print(uF, uNames, uX, sApproxNodes, iColumn, iWidth);
     print(uF, uNames, uY, sRandNodes, iColumn, iWidth);

     cout << "Approximation  of linear function: f(x) = "
          << dC << " + " << dT << "x" << endl
          << endl;
     uV = dC + dT * uX;
     uF[0] = dC + dT * uArg;
     uF[1] = rApprox.approximate(begin(uV), end(uV));
     uF[2] = cfl::abs((uF[1] - uF[0]) / uF[0]);
     print(uF, uNames, uX, sApproxNodes, iColumn, iWidth);
     print(uF, uNames, uY, sRandNodes, iColumn, iWidth);

     cout << "Approximation  of quadratic function: f(x) = "
          << dC << " + " << dT << "x + " << dP << "x^2"
          << endl
          << endl;
     uV = dC + dT * uX + dP * uX * uX;
     uF[0] = dC + dT * uArg + dP * uArg * uArg;
     uF[1] = rApprox.approximate(begin(uV), end(uV));
     uF[2] = cfl::abs((uF[1] - uF[0]) / uF[0]);
     print(uF, uNames, uX, sApproxNodes, iColumn, iWidth);
     print(uF, uNames, uY, sRandNodes, iColumn, iWidth);

     cout << "Approximation  of cubic function: f(x) = "
          << dC << " + 0.5 + x^2 + " << dT << "x^3" << endl
          << endl;
     uV = dC + 0.5 + uX * uX + dT * uX * uX * uX;
     uF[0] = dC + 0.5 + uArg * uArg + dT * uArg * uArg * uArg;
     uF[1] = rApprox.approximate(begin(uV), end(uV));
     uF[2] = cfl::abs((uF[1] - uF[0]) / uF[0]);
     print(uF, uNames, uX, sApproxNodes, iColumn, iWidth);
     print(uF, uNames, uY, sRandNodes, iColumn, iWidth);

     cout << "Approximation of exponential function: f(x) = exp(x)" << endl
          << endl;
     uV = exp(uX);
     uF[0] = exp(uArg);
     uF[1] = rApprox.approximate(begin(uV), end(uV));
     uF[2] = cfl::abs((uF[1] - uF[0]) / uF[0]);
     print(uF, uNames, uX, sApproxNodes, iColumn, iWidth);
     print(uF, uNames, uY, sRandNodes, iColumn, iWidth);

     cout << "Approximation of itself. Should get zero errors everywhere." << endl
          << endl;
     uV = getValues(uF.front(), uX);
     uF[0] = uF[1];
     uF[1] = rApprox.approximate(begin(uV), end(uV));
     uF[2] = cfl::abs((uF[1] - uF[0]));
     print(uF, uNames, uX, sApproxNodes, iColumn, iWidth);
     print(uF, uNames, uY, sRandNodes, iColumn, iWidth);
}

void test::testChebyshevApprox(test::t_chebyshev rChebyshev)
{
     unsigned iNodes = 3;
     std::function<unsigned(double)> uSize = [iNodes](double dX) {
          unsigned iR = std::max<unsigned>(static_cast<unsigned>(std::sqrt(dX) * iNodes), 3);
          return iR;
     };
     cfl::Approx uApprox = rChebyshev(uSize);
     testApprox(uApprox, "CHEBYSHEV APPROXIMATION");
}