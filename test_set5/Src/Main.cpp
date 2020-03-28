#include "test/Main.hpp"
#include "test/Fit.hpp"
#include "prb/Fit.hpp"
#include "test_set5/Output.hpp"

std::function<void()> test_set5()
{
  return []() {
    test::testBSplineFit(prb::NFit::bspline);
  };
};

int main()
{
  try
  {
     test::project(test_set5(), PROJECT_NAME, "test_set5", "TESTING OF SET 5");
    return 0;
  }
  catch (const std::exception &rError)
  {
    std::cerr << rError.what() << std::endl;
  }
}