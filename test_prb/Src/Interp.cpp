#include "prb/Interp.hpp"
#include "test/Interp.hpp"
#include "test_prb/Main.hpp"

std::function<void()> test::interp()
{
     return []() {
           testInterp(prb::NInterp::linear(),"LINEAR INTERPOLATION");
           testInterp(prb::NInterp::cspline(), "CSPLINE INTERPOLATION");
           testInterp(prb::NInterp::polynomial(), "POLYNOMIAL INTERPOLATION");
           testInterp(prb::NInterp::steffen(), "STEFFEN INTERPOLATION");
           testInterp(prb::NInterp::akima(), "AKIMA INTERPOLATION");
     };
};