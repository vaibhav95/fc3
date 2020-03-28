#include "test_set10/Output.hpp"
#include "test/Approx.hpp"
#include "test/Main.hpp"
#include "prb/Approx.hpp"
#include <functional>

using namespace std;

std::function<void()> test_set10()
{
  using namespace test;
  return []() {
    testChebyshevApprox(prb::NApprox::chebyshev);
  };
};

int main()
{
  try
  {
    test::project(test_set10(), PROJECT_NAME, "test_set10", "TESTING OF SET 10");
    return 0;
  }
  catch (const std::exception &rError)
  {
    std::cerr << rError.what() << std::endl;
  }
}
