#ifndef __test_GaussRollback_hpp__
#define __test_GaussRollback_hpp__

#include "cfl/GaussRollback.hpp"

namespace test
{
/**
     * @brief Tests the implementation of GaussRollback. 
     * 
     * @param rRollback The method. 
     * @param sMethod The name of the method. 
     * @param bRes If \p true, then the results are printed. 
     * @param bErr if \p true, then the errors are printed. 
     * @param bFull If \p true, then the complete set of testing routines will be used. 
     */
void testGaussRollback(const cfl::GaussRollback &rRollback,
                       const std::string &sMethod,
                       bool bRes = true, bool bErr = true, bool bFull = true);

/**
 * @brief Prints the results of the rollback operator. 
 * 
 * @param rRes Vector of arrays of results. There are 8 columns: 
 * 1. numerical values, 
 * 2. numerical delta, 
 * 3. numerical gamma, 
 * 4. numerical gamma, 
 * 5. true value, 
 * 6. true delta, 
 * 7. true gamma, 
 * 8. true vega. 
 * 
 * @param sMes The printed message. 
 * @param rState Array of state values. 
 * @param bRes If \p true, then we print the results. 
 * @param bErr If \p true, then we print the errors. 
 */
void printRollback(const std::vector<std::valarray<double>> &rRes,
                   const std::string &sMes, const std::valarray<double> &rState,
                   bool bRes, bool bErr);
} // namespace test

#endif // of __test_GaussRollback_hpp__
