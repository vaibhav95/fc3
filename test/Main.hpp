#ifndef __testMain_hpp__
#define __testMain_hpp__

/**
 * @file test/Main.hpp
 * @author Dmitry Kramkov (kramkov@andrew.cmu.edu)
 * @brief Collections of testing functions. 
 * @version 0.1
 * @date 2020-03-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <valarray>
#include "cfl/Function.hpp"
#include "test/Output.hpp"
#include "test/Index.hpp"

/**
   * \defgroup test_all Test. 
   * 
   * A collection of useful testing functions. 
   */
//@{
/**
 * @brief Namespace for testing functions. 
 * 
 */
namespace test
{
/**
     * @brief Returns uniform partition of an interval. 
     * 
     * @param dL The left point of the interval. 
     * @param dR The right point of the interval. 
     * @param iN The number of points in the partition. 
     * @return std::valarray<double> The uniform partion 
     * of the interval <em> [L,U] </em> on \a iN points. 
     */
std::valarray<double> getArg(double dL, double dR, unsigned iN);

/**
 * @brief Returns uniformly distributed random points.
 *  
 * @param dL The left point of the interval. 
 * @param dR The right point of the interval. 
 * @param iN The number of random points. 
 * @return std::valarray<double> The partion of the interval 
 * <em> [L,U] </em> on \a iN points having the uniform distribution. 
 */
std::valarray<double> getRandArg(double dL, double dR, unsigned iN);

/**
 * @brief Get array of values of a function. 
 * 
 * @param rF The function. 
 * @param rArg The vector of arguments. 
 * @return std::valarray<double> The array of the values of 
 * the function \a rF at the arguments \a rArg. 
 */
std::valarray<double> getValues(const cfl::Function &rF,
                                const std::valarray<double> &rArg);

/**
 * @brief Prints the values of an array. 
 * 
 * @tparam T The type of an iterator. 
 * @param start The iterator to the first element. 
 * @param end The iterator to the last plus one element. 
 */
template <class T>
void print(T start, T end);

/**
 * @brief Prints the subset of the table of the results. 
 * 
 * @param rValues The vector of columns of the results. 
 * @param rNames The vector of titles of the columns. 
 * @param sMessage The title of the table. 
 * @param iColumnSize The width of the column.
 * @param iSpaceSize The space between the columns. 
 * @param iRows The maximal number of rows in the middle of total table 
 * to be printed. 
 */
void print(const std::vector<std::valarray<double>> &rValues,
           const std::vector<std::string> &rNames,
           const std::string &sMessage, unsigned iColumnSize,
           unsigned iSpaceSize, unsigned iRows);

/**
 * @brief Prints the table of the results. 
 * 
 * @param rF The vector of functions. 
 * @param rNames The vector of titles of the columns. 
 * @param rArg The vector of arguments for the functions. 
 * @param sMessage The title of the table. 
 * @param iColumnSize The width of the column.
 * @param iSpaceSize The space between the columns. 
 */
void print(const std::vector<cfl::Function> &rF, const std::vector<std::string> &rNames,
           const std::valarray<double> &rArg, const std::string &sMessage,
           unsigned iColumnSize, unsigned iSpaceSize);

/**
 * @brief Prints displayed message. 
 * 
 * @param sMessage The message. 
 */
void print(const std::string &sMessage);

/**
 * @brief Prints the sum of estimated and actual errors. 
 * 
 * @param rEstErr Estimated error function. 
 * @param rActErr Actual error function. 
 * @param rArg The vector of arguments. 
 */
void printTotalErr(const cfl::Function &rEstErr, const cfl::Function &rActErr,
                   const std::valarray<double> &rArg);

/**
 * @brief Prints the values of the function at given arguments.  
 * 
 * @param rF The function. 
 * @param rArg The vector of arguments. 
 */
void printValues(const cfl::Function &rF, const std::valarray<double> &rArg);

/**
 * @brief The top program for running a test. 
 * 
 * @param rF The function that runs the test.
 * @param sProjectDir The name of the project directory relative to the output directory. 
 * @param sFile The name of the output file. 
 * @param sTitle The name of the project. It is printed at the top of the output file.  
 */
void project(const std::function<void()> &rF, const std::string &sProjectDir, 
const std::string & sFile, const std::string &sTitle);
} // namespace test
//@}

#include "test/Inline/iMain.hpp"
#endif // of __testMain_hpp__
