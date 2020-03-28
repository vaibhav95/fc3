#include "test/Main.hpp"
#include "test/Interp.hpp"
#include "prb/Interp.hpp"
#include "test_set2/Output.hpp"

std::function<void()> test_set2()
{
  using namespace test;
  return []() {
    testInterp(prb::NInterp::polynomial(), "POLYNOMIAL INTERPOLATION");
    testInterp(prb::NInterp::steffen(), "STEFFEN INTERPOLATION");
    testInterp(prb::NInterp::akima(), "AKIMA INTERPOLATION");
  };
};

int main()
{
  try
  {
    test::project(test_set2(), PROJECT_NAME, "test_set2", "TESTING OF SET 2");
    return 0;
  }
  catch (const std::exception &rError)
  {
    std::cerr << rError.what() << std::endl;
  }
}
