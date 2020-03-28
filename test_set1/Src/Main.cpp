#include "test/Main.hpp"
#include "test/Interp.hpp"
#include "prb/Interp.hpp"
#include "test_set1/Output.hpp"

std::function<void()> test_set1()
{
  return []() {
    test::testInterp(prb::NInterp::linear(), "LINEAR INTERPOLATION");
    test::testInterp(prb::NInterp::cspline(), "CSPLINE INTERPOLATION");
  };
};

int main()
{
  try
  {
    test::project(test_set1(), PROJECT_NAME, "test_set1", "TESTING OF SET 1");
    return 0;
  }
  catch (const std::exception &rError)
  {
    std::cerr << rError.what() << std::endl;
  }
}
