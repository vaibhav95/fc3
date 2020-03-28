#include <functional>
#include <vector>
#include "cfl/GaussRollback.hpp"
#include "cfl/Ind.hpp"
#include "prb/GaussRollback.hpp"
#include "prb/Ind.hpp"
#include "test/GaussRollback.hpp"
#include "test/Ind.hpp"
#include "test_prb/Main.hpp"

std::function<void()> test::ind()
{
  return []() {
    std::vector<cfl::Ind> uInd;
    std::vector<std::string> uMethod;

    uInd.push_back(prb::NInd::naive());
    uMethod.push_back("naive");

    uInd.push_back(prb::NInd::linear());
    uMethod.push_back("linear");

    uInd.push_back(prb::NInd::quadratic());
    uMethod.push_back("quadratic");

    printInd(uInd, uMethod);
    std::vector<cfl::GaussRollback> uGaussRollback;
    std::vector<std::string> uNames;
    uGaussRollback.push_back(prb::NGaussRollback::explic());
    uNames.push_back("Explicit scheme");
    uGaussRollback.push_back(prb::NGaussRollback::implicit());
    uNames.push_back("Fully implicit scheme");
    uGaussRollback.push_back(prb::NGaussRollback::crankNicolson());
    uNames.push_back("Crank-Nicolson scheme");
    uGaussRollback.push_back(prb::NGaussRollback::chain());
    uNames.push_back("3 layer scheme");

    bool bResults = false;
    bool bErr = true;

    rollbackInd(uInd, uMethod, uGaussRollback, uNames, bResults, bErr);
  };
};
 