#ifndef __cfl_Fit_hpp__
#define __cfl_Fit_hpp__

/**
 * @file Fit.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Fitting of one-dimensional functions.  
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
   * \defgroup cflFit Fitting of one-dimensional functions. 
   * This module deals with fitting of one-dimensional functions.
   */
//@{
/**
   * @brief The interface class for one-dimensional fitting. 
   * 
   * This is the abstract class for one-dimensional fitting. Its
   * implementations are used to construct concrete class Fit.  
   * \see Fit
   */
class IFit
{
public:
  /**
     * Virtual destructor. 
     */
  virtual ~IFit() {}

  /**
     * Returns a pointer to a new implementation of IFit given the
     * vectors of arguments and values of fitted function. 
     * @param rArg The strictly increasing vector of arguments of fitted function.  
     * @param rVal The vector of values of fitted function. 
     * @return The pointer to a new implementation of IFit. 
     */

  virtual IFit *newObject(const std::vector<double> &rArg,
                          const std::vector<double> &rVal) const = 0;

  /**
     * Returns a pointer to a new implementation of IFit given the 
     * the  vectors of arguments, values, and weights. 
     * @param rArg The strictly increasing vector of arguments of fitted function. 
     * @param rVal The vector of values of fitted function. 
     * @param rW The vector of fitting weights. 
     * @return The pointer to a new implementation of IFit.
     */
  virtual IFit *newObject(const std::vector<double> &rArg,
                          const std::vector<double> &rVal,
                          const std::vector<double> &rW) const = 0;

  /**
     * Returns the result of the fit. 
     * 
     * @return The result of the fit. 
     */
  virtual Function fit() const = 0;

  /**
     * Returns the error of the fit. 
     * 
     * @return The error of the fit. 
     */
  virtual Function err() const = 0;
};

/**
   * @brief Standard concrete class for one-dimensional fitting.  
   * 
   * This is the standard class for one-dimensional fitting. It is
   * implemented by a new instance of IFit. 
   *
   * \see IFit
   */
class Fit
{
public:
  /**
     * Constructs a least square fitting scheme from the implementation of IFit. 
     * @param pNewP Pointer to a new instance of IFit. 
     */
  explicit Fit(IFit *pNewP = 0);

  /**
     * Constructs the fitted one-dimensional function given the arrays of arguments and values. 
     * The container of arguments is strictly increasing. The vectors have identical sizes. 
     * 
     * @param itArgBegin An iterator to the start of the container of arguments. 
     * @param itArgEnd An iterator to the end of the container of arguments. 
     * @param itValBegin An iterator to the start of the container of values. 
     */
  template <class InIt1, class InIt2>
  void assign(InIt1 itArgBegin, InIt1 itArgEnd, InIt2 itValBegin);

  /**
     * Constructs the fitted one-dimensional function given the vectors of arguments, values, 
     * and weights. The vector of arguments is strictly increasing. All containers have 
     * same sizes. 
     * 
     * @param itArgBegin An iterator to the start of the container of arguments. 
     * @param itArgEnd An iterator to the end of the container of arguments. 
     * @param itValBegin An iterator to the start of the container of values. 
     * @param itWtBegin An iterator to the start of the container of weights. 
     */
  template <class InIt1, class InIt2, class InIt3>
  void assign(InIt1 itArgBegin, InIt1 itArgEnd,
              InIt2 itValBegin, InIt3 itWtBegin);

  /**
     * \copydoc IFit::fit()
     */
  Function fit() const;

  /**
     * \copydoc IFit::err()
     */
  Function err() const;

private:
  std::shared_ptr<IFit> m_uP;
};
// @}
} // namespace cfl

#include "cfl/Inline/iFit.hpp"
#endif // of __cfl_Fit_hpp__
