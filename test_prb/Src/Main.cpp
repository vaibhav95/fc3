#include "test_prb/Main.hpp"
#include "test_prb/Output.hpp"
#include "test/Output.hpp"
#include "test/Main.hpp"

using namespace test;
using namespace std;

int main()
{
  try
  {
    test::project(approx(), PROJECT_NAME, "test_approx", "TESTING OF APPROXIMATION");
    test::project(data(), PROJECT_NAME, "test_data", "TESTING OF DATA CURVES");
    test::project(fit(), PROJECT_NAME, "test_fit", "TESTING OF FIT");
    test::project(gaussRollback(), PROJECT_NAME, "test_gaussRollback", "TESTING OF GAUSS ROLLBACK");
    test::project(ind(),  PROJECT_NAME, "test_ind", "TESTING OF INDICATOR FUNCTION");
    test::project(interp(), PROJECT_NAME, "test_interp", "TESTING OF INTERPOLATION");
        
    return 0;
  }
  catch (const exception &rError)
  {
    cerr << rError.what() << endl;
  }
}
