#ifndef __cflFunction_hpp__
#define __cflFunction_hpp__

/**
 * @file Function.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief One-dimensional function object. 
 * @version 0.1
 * @date 2020-03-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <functional>
#include <limits>
#include <memory>

namespace cfl
{
/**
   * \defgroup cflFunction One-dimensional function object.
   * 
   * This module deals with one-dimensional function object.
   */
//@{

//! Interface for a one-dimensional function.
/**
   * Abstract class for one-dimensional function. Its  
   * implementation  is used to construct the concrete
   * class Function.  
   */
class IFunction
{
public:
   /** 
     * Virtual destructor. 
     */
   virtual ~IFunction() {}

   /** 
     * Standard functional operator. 
     * \param dX The argument.
     * \return  The value of the function at \a dX. 
     */
   virtual double operator()(double dX) const = 0;

   /**
     * Tests whether an argument belongs to the domain of the function. 
     * \param dX The argument.
     * \return The function returns \p true if the argument \a dX belongs to the domain 
     * of the function. Returns \p false otherwise.  
     */
   virtual bool belongs(double dX) const = 0;
};

//! Concrete class for a one-dimensional function.
/**
   * The standard class for a one-dimensional function. 
   * It is implemented by a dynamically allocated object derived 
   * from the interface class IFunction.
   * \see IFunction
   */
class Function
{
public:
   /**
     * Constructs constant function with the value 
     * \a dV on the interval [\a dLeft, \a dRight].
     * 
     * \param dV The value of the function.
     * \param dLeft The left point of the domain.
     * \param dRight The right point of the domain.
     */
   explicit Function(double dV = 0.,
                     double dLeft = -std::numeric_limits<double>::max(),
                     double dRight = std::numeric_limits<double>::max());

   /**
     * Constructs \p *this from a dynamically allocated implementation
     * of IFunction.
     * 
     * \param pNewP The pointer to a dynamically allocated
     * implementation of IFunction.
     */
   explicit Function(IFunction *pNewP);

   /**
     * Constructs \p Function from a standard function object of STL. 
     * 
     * @param rF The constant reference to the function object. 
     * A deep copy of \a rF will be created inside of \p *this. 
     * @param dLeft The left point of the domain. 
     * @param dRight The right point of the domain. 
     */
   explicit Function(const std::function<double(double)> &rF,
                     double dLeft = -std::numeric_limits<double>::max(),
                     double dRight = std::numeric_limits<double>::max());

   /**
     * Constructs \p Function from a pair of  standard function objects of STL. 
     * 
     * @param rF The constant reference to the function object. 
     * A deep copy of \a rF will be created inside of \p *this. 
     * @param rBelongs The constant reference to the domain descriptor. 
     * A deep copy of \a rBelongs will be created inside of \p *this. 
     */
   Function(const std::function<double(double)> &rF,
            const std::function<bool(double)> &rBelongs);

   /**
     * Assigns to \p *this the constant function with the value \a dV.
     * The domain becomes equal the real line.
     * 
     * \param dV The value of the function.
     * \return Reference to \p *this.
     */
   Function &operator=(double dV);

   /** 
     * Standard functional operator.
     *  
     * \param dX The argument.
     * \return The value of the function at \a dX.
     */
   double operator()(double dX) const;

   /**
     * \copydoc IFunction::belongs
     */
   bool belongs(double dX) const;

   /** 
     * Replaces \p *this with the sum of \p *this and \a rF.  The new
     * domain of \p *this equals the intersection of its old domain
     * with the domain of \a rF. A deep copy of \a rF is created
     * inside of \p *this.
     * 
     * \param rF Constant reference to the function that will be added. 
     * \return Reference to \p *this.
     */
   Function &operator+=(const Function &rF);

   /** 
     * Replaces \p *this with the product of \p *this and \a rF.  The
     * new domain of \p *this equals the intersection of its old
     * domain with the domain of \a rF. A deep copy of \a rF is
     * created inside of \p *this.
     * 
     * \param rF Constant reference to the multiplier. 
     * \return Reference to \p *this.
     */
   Function &operator*=(const Function &rF);

   /** 
     * Replaces \p *this with the difference between \p *this and \a
     * rF.  The new domain of \p *this equals the intersection of its
     * old domain with the domain of \a rF. A deep copy of \a rF is
     * created inside of \p *this.
     * 
     * \param rF Constant reference to the function that will be subtracted. 
     * \return Reference to \p *this.
     */
   Function &operator-=(const Function &rF);

   /** 
     * Replaces \p *this with the ratio between \p *this and \a rF.
     * The new domain of \p *this equals the intersection of its old
     * domain with the domain of \a rF. A deep copy of \a rF is
     * created inside of \p *this.
     * 
     * \param rF The divisor function. 
     *
     * \return Reference to \p *this.
     */
   Function &operator/=(const Function &rF);

   /**
     * Replaces \p *this with the sum of \p *this and \a dV. 
     * 
     * \param dV The number to be added to the function. 
     * 
     * \return Reference to \p *this.
     */
   Function &operator+=(double dV);

   /**
     * Replaces \p *this with the difference between \p *this and \a dV.
     * 
     * \param dV The number to be subtracted from the function. 
     * 
     * \return Reference to \p *this.
     */
   Function &operator-=(double dV);

   /**
     * Replaces \p *this with the product of \p *this and \a dV. 
     * 
     * \param dV The number to be multiplied by the function. 
     * 
     * \return Reference to \p *this.
     */
   Function &operator*=(double dV);

   /**
     * Replaces \p *this with the ratio of \p *this and \a dV. 
     *
     * \param dV The divisor number. 
     * 
     * \return Reference to \p *this.
     */
   Function &operator/=(double dV);

private:
   /**
     * The \p shared_ptr to an implementation of IFunction
     */
   std::shared_ptr<IFunction> m_pF;
};

/** 
   * Returns minus \a rF. The result contains a deep copy of \a rF.
   * The domain of the result equals the domain of \a rF.
   * 
   * \param rF A function object which minus is computed. 
   * 
   * \return The function given by <code>-rF</code>
   */
Function operator-(const Function &rF);

/** 
   * Returns the product of \a rF and \a rG.  The result contains
   * deep copies of \a rF and \a rG.  The domain of the result equals
   * the intersection of the domains of \a rF and \a rG.
   * 
   * \param rF First function multiplier.
   * \param rG Second function multiplier. 
   * 
   * \return The function given by <code>rF*rG</code>
   */
Function
operator*(const Function &rF, const Function &rG);

/** 
   * Returns the sum of \a rF and \a rG.  The result contains
   * deep copies of \a rF and \a rG.  The domain of the result equals
   * the intersection of the domains of \a rF and \a rG.
   * 
   * \param rF First element of the sum.
   * \param rG Second element of the sum. 
   * 
   * \return The function given by <code>rF+rG</code>
   */
Function
operator+(const Function &rF, const Function &rG);

/** 
   * Returns the difference between \a rF and \a rG.  The result
   * contains deep copies of \a rF and \a rG.  The domain of the
   * result equals the intersection of the domains of \a rF and \a rG.
   * 
   * \param rF The function from which we subtract. 
   * \param rG The function which is subtracted. 
   * 
   * \return The function given by <code>rF-rG</code>
   */
Function
operator-(const Function &rF, const Function &rG);

/** 
   * Returns the ratio of \a rF and \a rG.  The result contains deep
   * copies of \a rF and \a rG.  The domain of the result equals the
   * intersection of the domains of \a rF and \a rG.
   * 
   * \param rF The function which is divided.
   * \param rG The divisor function. 
   * 
   * \return The function given by <code>rF/rG</code>
   */
Function
operator/(const Function &rF, const Function &rG);

/** 
   * Returns the product of \a dV and \a rF. The result
   * contains a deep copy of \a rF.  The domain of the
   * result equals that of \a rF.
   * 
   * \param dV The multiplier number.
   * \param rF The multiplier function. 
   * 
   * \return The function given by <code>dV*rF</code>
   */
Function
operator*(double dV, const Function &rF);

/** 
   * Returns the  difference between \a dV and \a rF. The result
   * contains a deep copy of \a rF.  The domain of the
   * result equals that of \a rF.
   * 
   * \param dV The number from which we subtract.
   * \param rF The function which is subtracted. 
   * 
   * \return The function given by <code>dV-rF</code>
   */
Function
operator-(double dV, const Function &rF);

/** 
   * Returns the  ratio of \a dV and \a rF. The result
   * contains a deep copy of \a rF.  The domain of the
   * result equals that of \a rF.
   * 
   * \param dV The number which is divided. 
   * \param rF The divisor function. 
   * 
   * \return The function given by <code>dV/rF</code>
   */
Function
operator/(double dV, const Function &rF);

/** 
   * Returns the  sum of \a dV and \a rF. The result
   * contains a deep copy of \a rF.  The domain of the
   * result equals that of \a rF.
   * 
   * \param dV The number-term of the sum. 
   * \param rF The function-term of the sum. 
   * 
   * \return The function given by <code>dV+rF</code>
   */
Function
operator+(double dV, const Function &rF);

/** 
   * Returns the ratio of \a rF and \a dV. The result
   * contains a deep copy of \a rF.  The domain of the
   * result equals that of \a rF.
   * 
   * \param rF The function which is divided. 
   * \param dV The divisor number. 
   * 
   * \return The function given by <code>rF/dV</code>
   */
Function
operator/(const Function &rF, double dV);

/** 
   * Returns the sum of \a rF and \a dV. The result
   * contains a deep copy of \a rF.  The domain of the
   * result equals that of \a rF.
   * 
   * \param rF The function-term of the sum.
   * \param dV The number-term of the sum. 
   * 
   * \return The function given by <code>rF+dV</code>
   */
Function
operator+(const Function &rF, double dV);

/** 
   * Returns the product of \a rF and \a dV. The result
   * contains a deep copy of \a rF.  The domain of the
   * result equals that of \a rF.
   * 
   * \param rF The function multiplier. 
   * \param dV The number multiplier. 
   * 
   * \return The function given by <code>rF*dV</code>
   */
Function
operator*(const Function &rF, double dV);

/** 
   * Returns the difference between \a rF and \a dV. The result
   * contains a deep copy of \a rF.  The domain of the result equals
   * that of \a rF.
   * 
   * \param rF The function from which we subtract. 
   * \param dV The number which is subtracted. 
   * 
   * \return The function given by <code>rF-dV</code>
   */
Function
operator-(const Function &rF, double dV);

/** 
   * Returns the maximum \a rF and \a rG.  The result contains deep
   * copies of \a rF and \a rG.  The domain of the result equals the
   * intersection of the domains of \a rF and \a rG.
   * 
   * \param rF First function in the maximum. 
   * \param rG Second function in the maximum. 
   * 
   * \return The function given by <code>max(rF,rG)</code>
   */
Function max(const Function &rF, const Function &rG);

/** 
   * Returns the maximum of \a dV and \a rF. The result
   * contains a deep copy of \a rF.  The domain of the result equals
   * that of \a rF.
   * 
   * \param dV The number-term of the maximum. 
   * \param rF The function-term of the maximum. 
   * 
   * \return The function given by <code>max(dV,rF)</code>
   */
Function max(double dV, const Function &rF);

/** 
   * Returns the maximum of \a rF and \a dV. The result
   * contains a deep copy of \a rF.  The domain of the result equals
   * that of \a rF.
   * 
   * \param rF The function-term of the maximum. 
   * \param dV The number-term of the maximum. 
   * 
   * \return The function given by <code>max(rF,dV)</code>
   */
Function max(const Function &rF, double dV);

/** 
   * Returns the minimum of \a rF and \a rG.  The result contains deep
   * copies of \a rF and \a rG.  The domain of the result equals the
   * intersection of the domains of \a rF and \a rG.
   * 
   * \param rF The first function in the minimum. 
   * \param rG The second term in the minimum. 
   * 
   * \return The function given by <code>min(rF,rG)</code>
   */
Function min(const Function &rF, const Function &rG);

/** 
   * Returns the minimum of \a dV and \a rF. The result contains a
   * deep copy of \a rF.  The domain of the result equals that of \a
   * rF.
   * 
   * \param dV The number-term of the minimum. 
   * \param rF The function-term of the minimum. 
   * 
   * \return The function given by <code>min(dV,rF)</code>
   */
Function min(double dV, const Function &rF);

/** 
   * Returns the minimum of \a rF and \a dV. The result contains a
   * deep copy of \a rF.  The domain of the result equals that of \a
   * rF.
   * 
   * \param rF The function-term of the maximum. 
   * \param dV The number-term of the maximum. 
   * 
   * \return The function given by <code>min(rF,dV)</code>
   */
Function min(const Function &rF, double dV);

/** 
   * Returns \a rF in the power \a dV. The result contains a deep copy
   * of \a rF.  The domain of the result equals that of \a rF.
   * 
   * \param rF The function-base. 
   * \param dV The number-exponent. 
   * 
   * \return The function \a rF in the power \a dV. 
   */
Function pow(const Function &rF, double dV);

/** 
   * Returns the absolute value of \a rF.  The result contains a deep
   * copy of \a rF.  The domain of the result equals the domain of \a
   * rF.
   * 
   * \param rF The function which absolute value is computed. 
   *
   * \return The absolute value of \a rF. 
   */
Function abs(const Function &rF);

/**
   *  Returns the exponent of \a rF.  The result contains a deep
   * copy of \a rF.  The domain of the result equals the domain of \a
   * rF.
   * 
   * \param rF The function which exponent is computed. 
   *
   * \return The exponent of  \a rF. 
   */
Function exp(const Function &rF);

/**
   *  Returns the logarithm of \a rF. 
   * The result contains a deep copy of \a rF.
   * The domain of the result equals the domain of \a rF.
   * 
   * \param rF The function which logarithm is computed. 
   *
   * \return The logarithm of  \a rF.
   */
Function log(const Function &rF);

/** 
   * Returns the squire root of \a rF. 
   * The result contains the a deep copy of \a rF.
   * The domain of the result equals the domain of \a rF.
   * 
   * \param rF The function which square root is computed. 
   *
   * \return The square root of  \a rF.
   */
Function sqrt(const Function &rF);

//@}
} // namespace cfl

#include "cfl/Inline/iFunction.hpp"
#endif // of __cflFunction_hpp__
