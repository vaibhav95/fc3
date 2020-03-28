#ifndef __cflMacros_hpp__
#define __cflMacros_hpp__

/**
 * @file Macros.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Macros for cfl library. 
 * @version 0.1
 * @date 2020-03-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <assert.h>
#include <algorithm>

namespace cfl
{
  /**
   * \ingroup cflMisc
   * \defgroup cflMacros Macros and constants. 
   * This module contains macros and constants for cfl library. 
   */
  //@{

  /// Check conditions at the beginning of a function. 
  /**
   * The term \a ASSERT is used instead of \a std::asset to verify the
   * validity of input parameters.
   * 
   */
#define PRECONDITION assert

  /// Check conditions everywhere. 
  /**
   * The term \a ASSERT is used instead of \a std::asset to verify the
   * validity of variables everywhere in the program.
   * 
   */
#define ASSERT assert

  /// Check conditions at the end of a function. 
  /**
   * The term \a POSTCONDITION is used instead of \a std::asset to
   * verify the validity of output parameters.
   * 
   */
#define POSTCONDITION assert
  //@}
}

#endif//__cflMacros_hpp__
