#include "prb/Data.hpp"
#include "prb/Fit.hpp"
#include<cmath>

class DiscountYieldInterpFunction: public cfl::IFunction
{
public:
    DiscountYieldInterpFunction(const std::vector<double> &rTime, const std::vector<double> &rDF,
                                double dInitialTime, const cfl::Interp &rInterp)
    :t0(dInitialTime),t_left(rTime.front()),t_right(rTime.back())
    {
        std::vector<double> yields;
        for(size_t i=0;i<rTime.size();i++) {
            yields.push_back(-log(rDF[i])/(rTime[i]-dInitialTime));
        }
        yieldInterpFunc = rInterp.interpolate(rTime.begin(),rTime.end(),yields.begin());
    }

    virtual double operator()(double dt) const
    {
        double y = yieldInterpFunc(dt);
        return exp(-y*(dt-t0));
    }

    virtual bool belongs(double dt) const
    {
        return dt>=t_left && dt<=t_right;
    }

private:
    cfl::Function yieldInterpFunc;
    double t0;
    double t_left, t_right;
};

cfl::Function prb::NData::discountYieldInterp(const std::vector<double> &rTime, const std::vector<double> &rDF,
                                  double dInitialTime, const cfl::Interp &rInterp)
{
    return cfl::Function(new DiscountYieldInterpFunction(rTime,rDF,dInitialTime,rInterp));
}


class DiscountLogInterpFunction: public cfl::IFunction
{
public:
    DiscountLogInterpFunction(const std::vector<double> &rTime, const std::vector<double> &rDF,
                              double dInitialTime, const cfl::Interp &rInterp)
    :t_left(dInitialTime),t_right(rTime.back())
    {
        std::vector<double> logDF;
        logDF.push_back(0);
        for(size_t i=0;i<rTime.size();i++) {
            logDF.push_back(log(rDF[i]));
        }
        std::vector<double> newTime;
        newTime.push_back(dInitialTime);
        newTime.insert(newTime.end(),rTime.begin(),rTime.end());
        logDFInterpFunc = rInterp.interpolate(newTime.begin(),newTime.end(),logDF.begin());
    }

    virtual double operator()(double dt) const
    {
        double ld = logDFInterpFunc(dt);
        return exp(ld);
    }

    virtual bool belongs(double dt) const
    {
        return dt>=t_left && dt<=t_right;
    }

private:
    cfl::Function logDFInterpFunc;
    double t_left, t_right;
};


cfl::Function prb::NData::discountLogInterp(const std::vector<double> &rTime, const std::vector<double> &rDF,
                  double dInitialTime, const cfl::Interp &rInterp)
{
    return cfl::Function(new DiscountLogInterpFunction(rTime,rDF,dInitialTime,rInterp));
}


class VolatilityVarInterpFunction: public cfl::IFunction
{
public:
    VolatilityVarInterpFunction(const std::vector<double> &rTime, const std::vector<double> &rVol,
                              double dInitialTime, const cfl::Interp &rInterp)
    :t0(dInitialTime),t_left(dInitialTime),t_right(rTime.back())
    {
        std::vector<double> marketVars;
        marketVars.push_back(0);
        for(size_t i=0;i<rTime.size();i++) {
            marketVars.push_back(pow(rVol[i],2)*(rTime[i]-t0));
        }
        std::vector<double> newTime;
        newTime.push_back(dInitialTime);
        newTime.insert(newTime.end(),rTime.begin(),rTime.end());
        marketVarsInterpFunc = rInterp.interpolate(newTime.begin(),newTime.end(),marketVars.begin());
    }

    virtual double operator()(double dt) const
    {
        double v = marketVarsInterpFunc(dt);
        return sqrt(v/(dt-t0));
    }

    virtual bool belongs(double dt) const
    {
        return dt>=t_left && dt<=t_right;
    }

private:
    cfl::Function marketVarsInterpFunc;
    double t0;
    double t_left, t_right;
};

cfl::Function prb::NData::volatilityVarInterp(const std::vector<double> &rTime, const std::vector<double> &rVol,
                    double dInitialTime, const cfl::Interp &rInterp)
{
    return cfl::Function(new VolatilityVarInterpFunction(rTime,rVol,dInitialTime,rInterp));
}

cfl::Function prb::NData::discountYieldFit(const std::vector<double> &rTime, const std::vector<double> &rDF,
                 double dInitialTime, cfl::Fit &rFit, cfl::Function &rErr)
{
    std::vector<double> yields;
    for(size_t i=0;i<rTime.size();i++) {
        yields.push_back(-log(rDF[i])/(rTime[i]-dInitialTime));
    }
    rFit.assign(rTime.begin(),rTime.end(),yields.begin());
    cfl::Function yieldFitFunc = rFit.fit();
    std::function<double(double)> fnTime = [dInitialTime](double dt) {
        return dt-dInitialTime;
    };
    std::function<double(double)> fn = [yieldFitFunc, t0=dInitialTime](double dt) {
        double y = yieldFitFunc(dt);
        return exp(-y*(dt-t0));
    };
    rErr = rFit.err()*cfl::Function(fn)*cfl::Function(fnTime);
    return cfl::Function(fn);
}

cfl::Function prb::NData::discountLogFit(const std::vector<double> &rTime, const std::vector<double> &rDF,
               double dInitialTime, cfl::Fit &rFit, cfl::Function &rErr)
{
    std::vector<double> logDF;
    for(size_t i=0;i<rTime.size();i++) {
        logDF.push_back(log(rDF[i]));
    }
    rFit.assign(rTime.begin(),rTime.end(),logDF.begin());
    cfl::Function fitFunc = rFit.fit();
    std::function<double(double)> fn = [fitFunc](double dt) {
        double ld = fitFunc(dt);
        return exp(ld);
    };
    rErr = rFit.err()*cfl::Function(fn);
    return cfl::Function(fn);
}

cfl::Function prb::NData::discountNelsonSiegelFit(const std::vector<double> &rTime, const std::vector<double> &rDF,
                        double dLambda, double dInitialTime, cfl::Function &rErr)
{
    std::function<double(double)> fn_exp = [dLambda,dInitialTime](double dt) { 
        return exp(-dLambda*(dt-dInitialTime));
    };
    std::function<double(double)> fn_lin = [dLambda,dInitialTime](double dt) {
        return dLambda*(dt-dInitialTime);
    };
    cfl::Function func1{1};
    cfl::Function func2 = (func1-cfl::Function(fn_exp))/cfl::Function(fn_lin);
    cfl::Function func3 = func2-cfl::Function(fn_exp);
    std::vector<cfl::Function> basisFuncs{func1,func2,func3};
    cfl::Fit rFit = prb::NFit::linear(basisFuncs);
    return discountYieldFit(rTime,rDF,dInitialTime,rFit,rErr);
}

cfl::Function prb::NData::discountSvensonFit(const std::vector<double> &rTime, const std::vector<double> &rDF,
                   double dLambda1, double dLambda2, double dInitialTime, cfl::Function &rErr)
{
    std::function<std::function<double(double)>(double, double)> fn_exp = 
    [](double dLambda, double dInitialTime) { 
        return [dLambda, dInitialTime](double dt) {return exp(-dLambda*(dt-dInitialTime));};
    };
    std::function<std::function<double(double)>(double, double)> fn_lin = 
    [](double dLambda, double dInitialTime) { 
        return [dLambda, dInitialTime](double dt) {return dLambda*(dt-dInitialTime);};
    };
    cfl::Function func1{1};
    cfl::Function func2 = (func1-cfl::Function(fn_exp(dLambda1,dInitialTime)))/cfl::Function(fn_lin(dLambda1, dInitialTime));
    cfl::Function func3 = func2-cfl::Function(fn_exp(dLambda1,dInitialTime));
    cfl::Function func4 = (func1-cfl::Function(fn_exp(dLambda2,dInitialTime)))/cfl::Function(fn_lin(dLambda2, dInitialTime))-cfl::Function(fn_exp(dLambda2,dInitialTime));
    std::vector<cfl::Function> basisFuncs{func1,func2,func3,func4};
    cfl::Fit rFit = prb::NFit::linear(basisFuncs);
    return discountYieldFit(rTime,rDF,dInitialTime,rFit,rErr);
}

cfl::Function prb::NData::volatilityBlackFit(const std::vector<double> &rTime, const std::vector<double> &rVol,
                   double dLambda, double dInitialTime, cfl::Function &rErr)
{
    std::function<double(double)> fn_exp = [dLambda,dInitialTime](double dt) { 
        return exp(-2*dLambda*(dt-dInitialTime));
    };
    std::function<double(double)> fn_lin = [dLambda,dInitialTime](double dt) {
        return dLambda*(dt-dInitialTime);
    };
    cfl::Function func = cfl::sqrt((1-cfl::Function(fn_exp))/cfl::Function(fn_lin));
    std::vector<cfl::Function> basisFuncs{func};
    cfl::Fit rFit = prb::NFit::linear(basisFuncs);
    rFit.assign(rTime.begin(),rTime.end(),rVol.begin());
    rErr = rFit.err();
    return rFit.fit();
}