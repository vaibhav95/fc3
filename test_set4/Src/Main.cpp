#include "test/Main.hpp"
#include "test/Fit.hpp"
#include "prb/Fit.hpp"
#include "test_set4/Output.hpp"

std::function<void()> test_set4()
{
  return []() {
    test::testLinearFit(prb::NFit::linear);
  };
};

int main()
{
  try
  {
    test::project(test_set4(), PROJECT_NAME, "test_set4", "TESTING OF SET 4");
    return 0;
  }
  catch (const std::exception &rError)
  {
    std::cerr << rError.what() << std::endl;
  }
}
