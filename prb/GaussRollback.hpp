#ifndef __prbGaussRollback_hpp__
#define __prbGaussRollback_hpp__

#include "cfl/GaussRollback.hpp"

/**
 * \file   prb/GaussRollback.hpp
 * \author Dmitry Kramkov
 * \date   2020
 * 
 * \brief Conditional expectation with respect to gaussian distribution.
 *
 * Contains classes and functions that deal with numerical implementation of the operator of 
 * conditional expectation with respect to gaussian distribution. 
 */

namespace prb
{
  /**
   * @brief Implementations of the operator of conditional expectations 
   * with respect to gaussian distribution. 
   * 
   */
  namespace NGaussRollback
  {
    /**
     * @brief Explicit finite-difference scheme. 
     * 
     * @param dP Equals \f$ \tau/(2h^2)\f$, where \f$\tau\f$ is the time step and 
     * \f$h\f$ is the state step. 
     * @return cfl::GaussRollback 
     */
    cfl::GaussRollback explic(double dP = 1. / 3.);
    /**
     * @brief Fully implicit finite-difference scheme. 
     * 
     * @param dP Equals \f$ \tau/(2h^2)\f$, where \f$\tau\f$ is the time step and 
     * \f$h\f$ is the state step. 
     * @return cfl::GaussRollback 
     */
    cfl::GaussRollback implicit(double dP = 0.5);
    /**
     * @brief Fully implicit finite-difference scheme. 
     * 
     * @param dR Equals \f$ \tau/h\f$, where \f$\tau\f$ is the time step and 
     * \f$h\f$ is the state step. 
     * @return cfl::GaussRollback 
     */
    cfl::GaussRollback crankNicolson(double dR = 1.);
   
    /**
     * @brief A wrapper of "fast" scheme with explicit and implicit schemes 
     * to improve the performance. 
     * 
     * @param rFast The main (fast) finite-difference scheme.
     * @param iExplSteps The  number of time steps of explicit 
     * scheme used at the beginning  to smooth  boundary conditions. 
     * @param dExplP Equals \f$ \tau/(2h^2)\f$, where \f$\tau\f$ is the time step 
     * in the explicit scheme and \f$h\f$ is the state step. 
     * @param iImplSteps The number of time steps of fully implicit scheme used 
     * at the end to filter round-off errors. 
     * @param dImplP Equals \f$ \tau/(2h^2)\f$, where \f$\tau\f$ is the time step 
     * in the implicit scheme and \f$h\f$ is the state step. 
     * @return cfl::GaussRollback 
     */
    cfl::GaussRollback chain(const cfl::GaussRollback &rFast = crankNicolson(),
			    unsigned iExplSteps = 30, double dExplP = 1. / 3.,
			    unsigned iImplSteps = 10, double dImplP = 0.5);
  } // namespace NGaussRollback
} // namespace prb

#endif // of __prbGaussRollback_hpp__
