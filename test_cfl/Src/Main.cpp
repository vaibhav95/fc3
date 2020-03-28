#include "test_cfl/Main.hpp"
#include "test_cfl/Output.hpp"
#include "test/Output.hpp"
#include "test/Main.hpp"

using namespace test;
using namespace std;

int main()
{
  try
  {
    test::project(test_function(), PROJECT_NAME, "test_function", "TEST OF cfl::Function");
    return 0;
  }
  catch (const exception &rError)
  {
    cerr << rError.what() << endl;
  }
}
