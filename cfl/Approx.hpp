#ifndef __cflApprox_hpp__
#define __cflApprox_hpp__

/**
 * @file Approx.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Approximation of one-dimensional functions. 
 * @version 0.1
 * @date 2020-03-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <vector>
#include "cfl/Function.hpp"
#include "cfl/Macros.hpp"


//!Main namespace for cfl library.
/**
 * Contains everything in cfl library.
 */
namespace cfl
{
/**
   * \defgroup cflNumeric Numerical methods.
   * This module contains numerical routines used in implementations
   * of financial models. 
   */

/**
   * \ingroup cflNumeric
   * \defgroup cflApprox Approximation of one-dimensional functions.
   * This module deals with approximation of one-dimensional functions.
   */
//@{

//! Interface class for numerical approximation.
/**
   * This is the interface class for numerical approximation. Its implementation
   * is used to construct concrete class Approx.
   * \see Approx
   */
class IApprox
{
public:
  /** 
     * Virtual destructor. 
     */
  virtual ~IApprox(){};

  /**
     * Constructs approximation scheme on the interval [\a dLeft, \a dRight ]. 
     * \param dLeft The left point of the interval.
     * \param dRight The right point of the interval.
     * \return A dynamically allocated implementation of IApprox. 
     */
  virtual IApprox *newApprox(double dLeft, double dRight) const = 0;

  /**
     * Returns the nodes of the approximation scheme. It is a strictly increasing array. 
     * 
     * \return The nodes of the approximation scheme. 
     */
  virtual const std::vector<double> &arg() const = 0;

  /**
     * Computes approximation of a one-dimensional function,  using its values at the nodes of the
     * approximation scheme. 
     * 
     * \param rValues Values of the function at the nodes of the approximation scheme. 
     * \returns The result of numerical approximation of the function.
     */
  virtual Function approximate(const std::vector<double> &rValues) const = 0;
};

//!Standard concrete class for numerical approximation.
/** 
   * This is the standard class for different approximation schemes. 
   * It is implemented by a dynamically allocated object derived from 
   * the interface class IApprox. 
   * \see IApprox
   */
class Approx
{
public:
  /**
     * A constructor.
     * \param pNewP Pointer to new implementation of IApprox.
     */
  explicit Approx(IApprox *pNewP = 0);

  /**
     * Constructs an approximation scheme on the interval [\a dLeft, \a dRight]. 
     * \param dLeft The left point of the interval.
     * \param dRight The right point of the interval.
     */
  void assign(double dLeft, double dRight);

  /**
     * \copydoc IApprox::arg() 
     */
  const std::vector<double> &arg() const;

  /**
     * Computes approximation of a function given its values at the nodes of the approximation scheme. 
     * 
     * \param itValBegin The begin iterator of the 
     * sequence of values.
     * \param itValEnd The end iterator of the 
     * sequence of values. 
     * \return The result of numerical approximation of the function.
     */
  template <class InIt>
  cfl::Function approximate(InIt itValBegin, InIt itValEnd) const;

private:
  std::shared_ptr<IApprox> m_uP;
};
//@}
} // namespace cfl

#include "cfl/Inline/iApprox.hpp"
#endif // of __cflApprox_hpp__
