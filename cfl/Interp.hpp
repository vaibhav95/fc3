#ifndef __cflInterp_hpp__
#define __cflInterp_hpp__

/**
 * @file Interp.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Interpolation of one-dimensional functions. 
 * @version 0.1
 * @date 2020-03-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <vector>
#include "cfl/Function.hpp"

namespace cfl
{
/**
   * \ingroup cflNumeric 
   * 
   * \defgroup cflInterp Interpolation of one-dimensional functions. 
   * This module deals with one-dimensional interpolation.  
   */
//@{

//! Interface class for numerical interpolation.
/** 
   * This is the interface class for one-dimensional interpolation. Its implementation 
   * is used to construct concrete class Interp.
   * \see Interp
   */
class IInterp
{
public:
   /**
     * Virtual destructor. 
     */
   virtual ~IInterp() {}

   /**
     * Interpolation of the data supplied by the vectors of arguments \a rArg and values \a rVal.
     * \param rArg The strictly increasing vector of arguments.
     * \param rVal The vector of values. 
     * \return Interpolating function. 
     */
   virtual Function interpolate(const std::vector<double> &rArg,
                                const std::vector<double> &rVal) const = 0;
};

//! Standard concrete class for interpolation of one-dimensional functions.
/** 
   * This is the standard class for one-dimensional interpolation. It is implemented by a
   * dynamically allocated object derived from the interface class IInterp. 
   * \see IInterp
   */
class Interp
{
public:
   /**
     * A constructor. 
     * \param pNewP A dynamically allocated implementation of IInterp. 
     */
   explicit Interp(IInterp *pNewP = 0);

   /**
     * Returns interpolated function for given arguments and values. 
     * \param itArgBegin The iterator to the start of the container of arguments.
     * \param itArgEnd The iterator to the end of the container of arguments.
     * \param itValBegin The iterator to the start of the container of values.
     * \return Interpolated function.
     */
   template <class InIt1, class InIt2>
   cfl::Function interpolate(InIt1 itArgBegin, InIt1 itArgEnd,
                             InIt2 itValBegin) const;

private:
   std::shared_ptr<IInterp> m_uP;
};
// @}
} // namespace cfl

#include "cfl/Inline/iInterp.hpp"
#endif // of __cflInterp_hpp__
