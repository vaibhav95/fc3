#include <cmath>
#include <functional>
#include "cfl/Function.hpp"
#include "test_cfl/Main.hpp"
#include "test/Main.hpp"

using namespace cfl;
using namespace std;
using namespace test;

std::function<void()> test::test_function()
{
  return []() {
    test::print("TEST OF FUNCTION");

    unsigned iS = 5;
    double dL = 2;
    double dR = dL + 1.0;
    double dX = 2.;

    Function uF([](double x) { return std::sin(x); }, dL, dR);
    Function uG([](double x) { return std::exp(x); }, dL, dR);
    uF += Function([](double x) { return std::exp(x); }, dL, dR);
    uF += Function([](double x) { return std::cos(x); });
    uG = Function([](double dY) { return std::pow(dY, 3.); },
                  [](double dY) { return (dY > 0); });
    uF *= uG;

    cout << "function f:" << endl;
    printValues(uF, getArg(dL, dR, iS));

    uF += uG;
    uF -= uG;
    uF *= uG;
    uF /= uG;
    uF += dX;
    uF -= dX;
    uF *= dX;
    uF /= dX;
    uF = -uF;
    uF = -uF;
    uF = (uF * uG) / uG;
    uF = (uF / uG) * uG;
    uF = (uF - uG) + uG;
    uF = (uF + uG) - uG;
    uF = (uF + dX) - dX;
    uF = (dX + uF) - dX;
    uF = (uF * dX) / dX;
    uF = (uF / dX) * dX;
    uF = (uF + dX) - dX;
    uF = (uF - dX) + dX;
    uF = (dX + uF) - dX;
    uF = (dX - uF) * (-1) + dX;
    uF = (-1) * (dX - uF) + dX;

    uF = exp(log(uF));
    uF = log(exp(uF));
    uF = pow(sqrt(uF), 2);

    cout << "again function f after manipulations:" << endl;
    printValues(uF, getArg(dL, dR, iS));

    cout << "testing max and min and fabs" << endl;
    uF = Function([](double x) { return std::exp(x); });
    cout << "function f" << endl;
    printValues(uF, getArg(dL, dR, iS));
    uG = Function([](double x) { return std::sin(x); }) + 1.5;
    cout << "function g" << endl;
    printValues(uG, getArg(dL, dR, iS));
    Function uM = max(uF, uG);
    cout << "maximum of f and g" << endl;
    printValues(uM, getArg(dL, dR, iS));
    uM = min(uF, uG);
    cout << "minimum of f and g" << endl;
    printValues(uM, getArg(dL, dR, iS));
    cout << "should have zeros if correct" << endl;
    printValues(max(uF, uG) - min(uF, uG) - abs(uF - uG),
                getArg(dL, dR, iS));

    dX = 2.;
    cout << "constant X= " << dX << endl;
    uM = max(uF, dX);
    cout << "maximum of f and X" << endl;
    printValues(uM, getArg(dL, dR, iS));
    uM = min(uF, dX);
    cout << "minimum of f and g" << endl;
    printValues(uM, getArg(dL, dR, iS));

    cout << "should have zeros if correct: " << endl;
    uM = max(uF, uG) + min(uF, uG) - uF - uG;
    uM = max(uF, dX) + min(uF, dX) - uF - dX;
    printValues(uM, getArg(dL, dR, iS));
  };
};
