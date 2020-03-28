#ifndef __prbData_hpp__
#define __prbData_hpp__

#include "cfl/Interp.hpp"
#include "cfl/Fit.hpp"
/**
 * \file   prb/Data.hpp
 * \author Dmitry Kramkov
 * \date   2020
 * 
 * \brief  One-dimensional data curves. 
 * 
 */

namespace prb
{
/**
   * @brief One-dimensional data curves. 
   * 
   */
namespace NData
{
/**
    * Computes a discount curve by interpolation of market yields. 
    * The construction of the discount curve is accomplished in 3 steps: 
    * 1. Compute market yields from the discount factors \a rDF.
    * 2. Obtain market yield curve by interplation with  \a rInterp. 
    * 3. Compute the discount curve from the yield curve. 
      * 
    * @param rTime The maturities of known discount factors.
    * @param rDF The known discount factors. 
    * @param dInitialTime The initial time.
    * @param rInterp The interpolation method for yields.  
    * @return cfl::Function The interpolated discount curve. 
    */
cfl::Function discountYieldInterp(const std::vector<double> &rTime, const std::vector<double> &rDF,
                                  double dInitialTime, const cfl::Interp &rInterp);

/**
    * Computes a discount curve by interpolation of logs of market discount factors. 
    * The construction of the discount curve is accomplished in 3 steps: 
    * 1. Compute the logarithms of  the discount factors \a rDF.
    * 2. Interpolate the logarithms of the discount factors with   \a rInterp. 
    * 3. Recover the discount curve from its logarithmic interpolation. 
    * 
    * @param rTime The maturities of known discount factors.
    * @param rDF The known discount factors. 
    * @param dInitialTime The initial time.
    * @param rInterp The interpolation method for yields.  
    * @return cfl::Function The interpolated discount curve. 
    */
cfl::Function
discountLogInterp(const std::vector<double> &rTime, const std::vector<double> &rDF,
                  double dInitialTime, const cfl::Interp &rInterp);

/**
 * Computes the discount curve by least square fitting of market yields. 
 * 
 * @param rTime The maturities of known discount factors.
 * @param rDF The known discount factors. 
 * @param dInitialTime The initial time.
 * @param rFit The fitting method. 
 * @param rErr The error function of the fit. 
 * @return cfl::Function The fitted discount curve. 
 */
cfl::Function
discountYieldFit(const std::vector<double> &rTime, const std::vector<double> &rDF,
                 double dInitialTime, cfl::Fit &rFit, cfl::Function &rErr);

/**
 * Computes the discount curve by least square fitting of the logs of discount factors. 
 * 
 * @param rTime The maturities of known discount factors.
 * @param rDF The known discount factors. 
 * @param dInitialTime The initial time.
 * @param rFit The fitting method. 
 * @param rErr The error function of the fit. 
 * @return cfl::Function The fitted discount curve. 
 */
cfl::Function
discountLogFit(const std::vector<double> &rTime, const std::vector<double> &rDF,
               double dInitialTime, cfl::Fit &rFit, cfl::Function &rErr);

/**
 * Computes the discount curve by least square fitting of the Nelson-Siegel yield cureve. 
 * 
 * @param rTime The maturities of known discount factors.
 * @param rDF The known discount factors. 
 * @param dLambda The mean-reversion rate. 
 * @param dInitialTime The initial time.
 * @param rErr The error function of the fit. 
 * @return cfl::Function 
 */
cfl::Function
discountNelsonSiegelFit(const std::vector<double> &rTime, const std::vector<double> &rDF,
                        double dLambda, double dInitialTime, cfl::Function &rErr);

/**
 * Computes the discount curve by the least square fitting of the Svenson yield cureve. 
 * 
 * @param rTime The maturities of known discount factors.
 * @param rDF The known discount factors. 
 * @param dLambda1 The first mean-reversion rate. 
 * @param dLambda2 The second mean-reversion rate. 
 * @param dInitialTime The initial time.
 * @param rErr The error function of the fit. 
 * @return cfl::Function The fitted discount curve. 
 */
cfl::Function
discountSvensonFit(const std::vector<double> &rTime, const std::vector<double> &rDF,
                   double dLambda1, double dLambda2, double dInitialTime, cfl::Function &rErr);

/**
 * 
 * Computes the implied volatility curve by interpolation of the variance curve. 
 * 
 * @param rTime The maturities for known implied volatilities. 
 * @param rVol The market implied volatilities. 
 * @param dInitialTime The initial time.
 * @param rInterp A monotone interpolation method such as linear or Steffen interpolations. 
 * @return cfl::Function The implied volatility curve obtained by the interplation of the market variances. 
 */
cfl::Function
volatilityVarInterp(const std::vector<double> &rTime, const std::vector<double> &rVol,
                    double dInitialTime, const cfl::Interp &rInterp);

/**
 * Computes the stationary volatility curve in Black model by the least square 
 * fitting of market volatilities.
 * 
  * @param rTime The maturities for known implied volatilities. 
 * @param rVol The market implied volatilities. 
 * @param dLambda The mean-reversion rate. 
 * @param dInitialTime The initial time.
 * @param rErr The error function of the fit. 
 * @return cfl::Function The fitted volatility curve. 
 */
cfl::Function
volatilityBlackFit(const std::vector<double> &rTime, const std::vector<double> &rVol,
                   double dLambda, double dInitialTime, cfl::Function &rErr);
} // namespace NData
} // namespace prb

#endif // of __prbData_hpp__
