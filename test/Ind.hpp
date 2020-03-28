#ifndef __test_Ind_hpp__
#define __test_Ind_hpp__

#include "cfl/Ind.hpp"

namespace test
{
void printInd(const std::vector<cfl::Ind> &rInd, const std::vector<std::string> &sMethod);
void rollbackInd(const std::vector<cfl::Ind> &rInd, const std::vector<std::string> &sMethod,
                 std::vector<cfl::GaussRollback> &rRollback,
                 const std::vector<std::string> &rNames, bool bRes, bool bErr);

} // namespace test

#endif // of __test_Ind_hpp__
