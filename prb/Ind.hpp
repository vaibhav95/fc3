#ifndef __prbInd_hpp__
#define __prbInd_hpp__

#include "cfl/Ind.hpp"

/**
 * \file   prb/Ind.hpp
 * \author Dmitry Kramkov
 * \date   2020
 * 
 * \brief One-dimensional indicator functions.  
 * 
 * Contains classes and functions that deal with numerically efficient construction of
 * one-dimensional indicator functions.
 */

namespace prb
{
  /**
   * @brief Implementations of one-dimensional indicator functions. 
   * 
   */
  namespace NInd
  {
    /**
     * @brief Naive indicator functions with values 0 and 1. 
     * 
     * @return cfl::Ind 
     */
    cfl::Ind naive();
    /**
     * @brief Indicator function that depends linearly on the point of discontinuity. 
     * 
     * @return cfl::Ind 
     */
    cfl::Ind linear();

    /**
     * @brief Indicator function that has a quadratic dependence on the point of discontinuity. 
     * 
     * @return cfl::Ind 
     */
    cfl::Ind quadratic();

    //add for delta
  } // namespace NInd
} // namespace prb

#endif // of __prbInd_hpp__
