#ifndef __test_Data_hpp__
#define __test_Data_hpp__

#include "cfl/Interp.hpp"
#include "cfl/Fit.hpp"
#include <vector>

namespace test
{
typedef cfl::Function (*t_interp)(const std::vector<double> &rTime, const std::vector<double> &rDF,
                                  double dInitialTime, const cfl::Interp &rInterp);
void discountYieldInterp(t_interp fMethod, double dInitialTime, double dMaturity,
                         const std::vector<cfl::Interp> &rMethod, const std::vector<std::string> &rName);
void discountLogInterp(t_interp fMethod, double dInitialTime, double dMaturity,
                       const std::vector<cfl::Interp> &rMethod, const std::vector<std::string> &rName);
void volatilityVarInterp(t_interp fInterp, double dInitialTime, double dMaturity,
                         const std::vector<cfl::Interp> &rMethod, const std::vector<std::string> &rName);

typedef cfl::Function (*t_fit)(const std::vector<double> &rTime, const std::vector<double> &rDF,
                               double dInitialTime, cfl::Fit &rFit, cfl::Function &rErr);
void discountYieldFit(t_fit fMethod, double dInitialTime, double dMaturity, cfl::Fit &rFit);
void discountLogFit(t_fit fMethod, double dInitialTime, double dMaturity, cfl::Fit &rFit);

typedef cfl::Function (*t_fit_lambda)(const std::vector<double> &rTime, const std::vector<double> &rDF,
                                      double dLambda, double dInitialTime, cfl::Function &rErr);
void discountNelsonSiegelFit(t_fit_lambda, double dInitialTime, double dMaturity);

typedef cfl::Function (*t_fit_lambda2)(const std::vector<double> &rTime, const std::vector<double> &rDF,
                                       double dLambda1, double dLambda2,
                                       double dInitialTime, cfl::Function &rErr);
void discountSvensonFit(t_fit_lambda2 fFit, double dInitialTime, double dMaturity);

void volatilityBlackFit(t_fit_lambda fFit, double dInitialTime, double dMaturity);

} // namespace test

#endif // of __test_Data_hpp__
