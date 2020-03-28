#ifndef __prb_Fit_hpp__
#define __prb_Fit_hpp__

#include "cfl/Fit.hpp"

/**
 * \file   prb/Fit.hpp
 * \author Dmitry Kramkov
 * \date   2020
 * 
 * \brief Fitting of one-dimensional functions.  
 * 
 * Contains classes and functions that deal with (least square) fitting of 
 * one-dimensional functions.
 */

namespace prb
{
  /**
   * @brief Implementations of one-dimensional (least square) fittings. 
   * 
   */
  namespace NFit
  {
    /**
     * @brief Classical least square fit of one-dimensional function. 
     * 
     * @param rBasisF The vector of basis functions. 
     * @return cfl::Fit 
     */
    cfl::Fit linear(const std::vector<cfl::Function> &rBasisF);

    /**
     * @brief Least square fitting with basis splines. 
     * 
     * @param iOrder The order of the fitting spline. 
     * @param rBreakpoints The number of breakpoints. 
     * @return cfl::Fit 
     */
    cfl::Fit bspline(unsigned iOrder, const std::vector<double> &rBreakpoints);

    /**
     * @brief Least square fitting with basis splines. 
     * 
     * @param iOrder The order of the fitting spline. 
     * @param dL The left point of the domain. 
     * @param dR The right point of the  domain. 
     * @param iBreakpoints The number of breakpoints. 
     * @return cfl::Fit 
     */
    cfl::Fit bspline(unsigned iOrder, double dL, double dR, unsigned iBreakpoints);
  } // namespace Fit
} // namespace prb

#endif // of __prb_Fit_hpp__
