#ifndef __prb_Interp_hpp__
#define __prb_Interp_hpp__

#include "cfl/Interp.hpp"

/**
 * \file   prb/Interp.hpp
 * \author Dmitry Kramkov
 * \date   2020
 * 
 * \brief  Interpolation of one-dimensional functions.
 * 
 * Contains functions and classes related to one-dimensional interpolation. 
 */

namespace prb
{
  /**
   * @brief Implementations of one-dimensional interpolations. 
   * 
   */
  namespace NInterp
  {
    /**
     * @brief Linear interpolation. 
     * 
     * @return cfl::Interp The engine for linear interpolation. 
     */
    cfl::Interp linear();

    /**
     * @brief Cubic spline interpolation. 
     * 
     * @return cfl::Interp The engine for cubic spline interpolation. 
     */
    cfl::Interp cspline();

    /**
     * @brief Steffen interpolation. 
     * Produces monotone function between interplation nodes. 
     * 
     * @return cfl::Interp The engine for Steffen interpolation. 
     */
    cfl::Interp steffen();

    /**
     * @brief Akima interpolation. 
     * Variation of cubic spline with more tolerance to outliers. 
     * 
     * @return cfl::Interp The engine for Akima interpolation. 
     */
    cfl::Interp akima();

    /**
     * @brief Polynomial interpoloation. 
     * 
     * @return cfl::Interp The engine for polynomial interpolation. 
     */
    cfl::Interp polynomial();
  } // namespace NInterp
} // namespace prb

#endif // of __prb_Interp_hpp__
