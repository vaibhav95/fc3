#ifndef __cflInd_hpp__
#define __cflInd_hpp__

/**
 * @file Ind.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief One-dimensional indicator function. 
 * @version 0.1
 * @date 2020-03-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <memory>
#include <valarray>

namespace cfl
{
/**
   * \ingroup cflNumeric
   * \defgroup cflInd	Indicators of one-dimensional functions. 
   * This module is dealing with with numerically efficient 
   * implementations of one-dimensional indicator functions.  
   */
// @{

//! Interface class for one-dimensional indicator function.
/**
   * This is the abstract class for one-dimensional indicator function. Its implementation 
   * is used to construct concrete class Ind. The goal is to accelerate the 
   * numerical integration of discontinuous functions. 
   * \see Ind
   */
class IInd
{
public:
   /**
     * Virtual destructor. 
     */
   virtual ~IInd() {}

   /**
     * Constructs the indicator function of the event: "the function is greater then 
     * the barrier". The goal is to accelerate the numerical integration of discountinuous functions.
     * 
     * \param rValues Before the operation, \a rValues represents the values of 
     * the input function f=f(x) on a grid. After the operation, \a rValues represents the indicator of the event
     * "f(x) >= dBarrier". 
     * \param dBarrier The barrier. 
     */
   virtual void indicator(std::valarray<double> &rValues, double dBarrier) const = 0;
};

//! Standard concrete class for indicator functions.
/** 
   * This is the standard class for indicator functions. It is implemented by a	
   *  new instance of the interface class \p IInd. The class \p Ind is used to define 
   * discontinuous functions on a grid with the goal to accelerate the 
   *  numerical integration. 
   * \see IInd
   */
class Ind
{
public:
   /** 
     * @brief A constructor. 
     * \param pNewInd Pointer to new  implementation of the interface 
     * class \p IInd. 
     */
   explicit Ind(IInd *pNewInd = 0);

   /**
     * \copydoc IInd::indicator()
     */
   void indicator(std::valarray<double> &rValues,
                  double dBarrier) const;

private:
   std::shared_ptr<IInd> m_pInd;
};
// @}
} // namespace cfl

#include "cfl/Inline/iInd.hpp"
#endif // of __cflInd_hpp__
