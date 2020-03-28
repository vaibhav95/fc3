#ifndef __prbApprox_hpp__
#define __prbApprox_hpp__

#include "cfl/Approx.hpp"

/**
 * \file   prb/Approx.hpp
 * \author Dmitry Kramkov
 * \date   2020
 * 
 * \brief  Approximation of one-dimensional functions.
 * 
 * Contains classes and functions related to one-dimensional approximation. 
 */

/**
 * @brief Namespace for exercises. 
 * 
 */
namespace prb
{
  /**
   * @brief Implementations of one-dimensional approximations. 
   * 
   */
  namespace NApprox
  {
    /**
     * @brief Constructs approximation scheme based on Chebyshev polynomials.
     * 
     * @param rSize Returns the number of arguments for given length of the 
     * domain of the appproximated function. 
     * @return cfl::Approx The approximation scheme based on Chebyshev polynomials. 
     */
    cfl::Approx chebyshev(const std::function<unsigned(double)> &rSize);
  } // namespace NApprox
} // namespace prb

#endif // of __prbApprox_hpp__
