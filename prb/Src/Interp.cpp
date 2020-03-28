#include "prb/Interp.hpp"
#include <gsl/gsl_spline.h>

using namespace cfl;
using namespace prb;


class GslInterpFunction: public IFunction
{
public:
    GslInterpFunction(const std::vector<double> &rArg, const std::vector<double> &rVal,
                        const gsl_interp_type *p_gsl_interp_type)
        : p_gsl_spline(gsl_spline_alloc(p_gsl_interp_type,rArg.size()), &gsl_spline_free),
          p_gsl_interp_accel(gsl_interp_accel_alloc(), &gsl_interp_accel_free)
    {
        gsl_spline_init(p_gsl_spline.get(), rArg.data(), rVal.data(), rArg.size());
        x_left = rArg.front();
        x_right = rArg.back();
    }

    virtual double operator()(double dX) const 
    {
        return gsl_spline_eval(p_gsl_spline.get(), dX, p_gsl_interp_accel.get());
    }

    virtual bool belongs(double dX) const
    {
        return dX>=x_left && dX<=x_right;
    }

private:
    std::unique_ptr<gsl_spline, decltype(&gsl_spline_free)> p_gsl_spline;
    std::unique_ptr<gsl_interp_accel, decltype(&gsl_interp_accel_free)> p_gsl_interp_accel;
    double x_left, x_right;
};  


class LinearInterpFunction: public GslInterpFunction
{
public:
    LinearInterpFunction(const std::vector<double> &rArg, const std::vector<double> &rVal)
        : GslInterpFunction(rArg,rVal,gsl_interp_linear) {}
};

class LinearInterp: public IInterp 
{
public:
    Function interpolate(const std::vector<double> &rArg,
                                const std::vector<double> &rVal) const
    {
        return Function(new LinearInterpFunction(rArg, rVal));
    }
};

Interp NInterp::linear() 
{
    return Interp(new LinearInterp());
}

class CsplineInterpFunction: public GslInterpFunction
{
public:
    CsplineInterpFunction(const std::vector<double> &rArg, const std::vector<double> &rVal)
        : GslInterpFunction(rArg,rVal,gsl_interp_cspline) {}
};

class CsplineInterp: public IInterp 
{
public:
    Function interpolate(const std::vector<double> &rArg,
                                const std::vector<double> &rVal) const
    {
        return Function(new CsplineInterpFunction(rArg, rVal));
    }
};

Interp NInterp::cspline() 
{
    return Interp(new CsplineInterp());
}
