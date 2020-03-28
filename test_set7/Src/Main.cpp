#include "test/Main.hpp"
#include "test_set7/Output.hpp"
#include <string>
#include <vector>
#include "prb/GaussRollback.hpp"
#include "test/GaussRollback.hpp"
#include "test_prb/Main.hpp"

std::function<void()> test_set7()
{
     using namespace prb::NGaussRollback;
     using namespace test;
     return []() {
          bool bErr = true;
          bool bRes = false;
          bool bFull = false;
          std::string sMethod = "Explicit scheme with default parameters";
          testGaussRollback(explic(), sMethod, bRes, bErr, bFull);

          sMethod = "Implicit scheme with default parameters";
          testGaussRollback(implicit(), sMethod, bRes, bErr, bFull);
     };
};
 

int main()
{
  try
  {
   test::project(test_set7(), PROJECT_NAME, "test_set7", "TESTING OF SET 7"); 
    return 0;
  }
  catch (const std::exception &rError)
  {
    std::cerr << rError.what() << std::endl;
  }
}
 
