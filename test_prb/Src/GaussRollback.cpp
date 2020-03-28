
#include <string>
#include <vector>
#include "prb/GaussRollback.hpp"
#include "test/GaussRollback.hpp"
#include "test_prb/Main.hpp"

std::function<void()> test::gaussRollback()
{
     using namespace prb::NGaussRollback;
     return []() {
          bool bErr = true;
          bool bRes = false;
          bool bFull = false;
          std::string sMethod = "Explicit scheme with default parameters";
          testGaussRollback(explic(), sMethod, bRes, bErr, bFull);

          sMethod = "Implicit scheme with default parameters";
          testGaussRollback(implicit(), sMethod, bRes, bErr, bFull);

          sMethod = "Crank-Nicolson scheme with default parameters";
          testGaussRollback(crankNicolson(), sMethod, bRes, bErr, bFull);

          sMethod = "3-layer scheme with default parameters";
          testGaussRollback(chain(), sMethod, bRes, bErr, bFull);
     };
};
 