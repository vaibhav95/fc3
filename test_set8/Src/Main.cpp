#include "test/Main.hpp"
#include "test_set8/Output.hpp"
#include <string>
#include <vector>
#include "prb/GaussRollback.hpp"
#include "test/GaussRollback.hpp"
#include "test_prb/Main.hpp"

std::function<void()> test_set8()
{
     using namespace prb::NGaussRollback;
     using namespace test;
     return []() {
          bool bErr = true;
          bool bRes = false;
          bool bFull = false;
          
          std::string sMethod = "Crank-Nicolson scheme with default parameters";
          testGaussRollback(crankNicolson(), sMethod, bRes, bErr, bFull);

          sMethod = "3-layer scheme with default parameters";
          testGaussRollback(chain(), sMethod, bRes, bErr, bFull);
     };
};
 
int main()
{
  try
  {
   test::project(test_set8(), PROJECT_NAME, "test_set8", "TESTING OF SET 8"); 
    return 0;
  }
  catch (const std::exception &rError)
  {
    std::cerr << rError.what() << std::endl;
  }
}
