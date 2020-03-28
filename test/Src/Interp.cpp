#include <iomanip>
#include "test/Main.hpp"
#include "test/Interp.hpp"

using namespace cfl;
using namespace std;
using namespace test;

void test::testInterp(const cfl::Interp &rInterp, const std::string &sInterp)
{
     cout << sInterp.c_str() << endl
          << endl;
     std::string sInterpNodes("Comparison at the nodes of interpolation");
     std::string sRandNodes("Comparison at the random arguments");
     double dL = 0;
     double dR = 1;
     unsigned iN = 8;
     unsigned iColumn = 10;
     unsigned iWidth = 8;
     std::valarray<double> uX = getArg(dL, dR, iN);
     std::valarray<double> uY = getRandArg(dL, dR, iN);
     Function uArg([](double dX) { return dX; });
     double dC = 1;
     double dT = 2;
     double dP = 3;
     std::vector<std::string> uNames(1, "exact");
     uNames.push_back("numeric");
     uNames.push_back("error");
     std::vector<Function> uF(3);

     cout << "Interpolation of const function: f(x) = " << dC << endl
          << endl;
     std::valarray<double> uV(dC, uX.size());
     uF[0] = dC;
     uF[1] = rInterp.interpolate(begin(uX), end(uX), begin(uV));
     uF[2] = cfl::abs(uF[1] - uF[0]);
     print(uF, uNames, uX, sInterpNodes, iColumn, iWidth);
     print(uF, uNames, uY, sRandNodes, iColumn, iWidth);

     cout << "Interpolation  of linear function: f(x) = "
          << dC << " + " << dT << "x" << endl
          << endl;
     uV = dC + dT * uX;
     uF[0] = dC + dT * uArg;
     uF[1] = rInterp.interpolate(begin(uX), end(uX), begin(uV));
     uF[2] = cfl::abs(uF[1] - uF[0]);
     print(uF, uNames, uX, sInterpNodes, iColumn, iWidth);
     print(uF, uNames, uY, sRandNodes, iColumn, iWidth);

     cout << "Interpolation  of quadratic function: f(x) = "
          << dC << " + " << dT << "x + " << dP << "x^2"
          << endl
          << endl;
     uV = dC + dT * uX + dP * uX * uX;
     uF[0] = dC + dT * uArg + dP * uArg * uArg;
     uF[1] = rInterp.interpolate(begin(uX), end(uX), begin(uV));
     uF[2] = cfl::abs(uF[1] - uF[0]);
     print(uF, uNames, uX, sInterpNodes, iColumn, iWidth);
     print(uF, uNames, uY, sRandNodes, iColumn, iWidth);

     cout << "Interpolation  of cubic function: f(x) = "
          << dC << " + 0.5 + x^2 + " << dT << "x^3" << endl
          << endl;
     uV = dC + 0.5 + uX * uX + dT * uX * uX * uX;
     uF[0] = dC + 0.5 + uArg * uArg + dT * uArg * uArg * uArg;
     uF[1] = rInterp.interpolate(begin(uX), end(uX), begin(uV));
     uF[2] = cfl::abs(uF[1] - uF[0]);
     print(uF, uNames, uX, sInterpNodes, iColumn, iWidth);
     print(uF, uNames, uY, sRandNodes, iColumn, iWidth);

     cout << "Interpolation of exponential function: f(x) = exp(x)" << endl
          << endl;
     uV = exp(uX);
     uF[0] = exp(uArg);
     uF[1] = rInterp.interpolate(begin(uX), end(uX), begin(uV));
     uF[2] = cfl::abs(uF[1] - uF[0]);
     print(uF, uNames, uX, sInterpNodes, iColumn, iWidth);
     print(uF, uNames, uY, sRandNodes, iColumn, iWidth);

     cout << "Interpolation of itself. Should get zero errors everywhere." << endl
          << endl;
     uV = getValues(uF.front(), uX);
     uF[0] = uF[1];
     uF[1] = rInterp.interpolate(begin(uX), end(uX), begin(uV));
     uF[2] = cfl::abs(uF[1] - uF[0]);
     print(uF, uNames, uX, sInterpNodes, iColumn, iWidth);
     print(uF, uNames, uY, sRandNodes, iColumn, iWidth);
};