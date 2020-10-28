#include "prb/Approx.hpp"
#include <gsl/gsl_chebyshev.h>

struct func_params {
    std::vector<double> rValues;
    std::vector<double> nodes;
};

double func(double x, void *p) {
    unsigned i=0;
    struct func_params *params = (struct func_params *)p;
    for(;(params->nodes)[i]<x-DBL_EPSILON&&i<(params->nodes.size());i++);
    return (params->rValues)[i];
}
    
class ChebApprox: public cfl::IApprox
{
public:

    ChebApprox(const std::function<unsigned(double)> &rSize)
    : rSize{rSize}
    {}

    cfl::IApprox *newApprox(double dLeft, double dRight) const
    {
        return new ChebApprox(dLeft,dRight,rSize);
    }

    const std::vector<double> &arg() const
    {
        return nodes;
    }

    cfl::Function approximate(const std::vector<double> &rValues) const
    {
        struct func_params params{rValues, nodes};
        const gsl_function F{&func, &params};
        gsl_cheb_init(p_cheb_series.get(), &F, dLeft, dRight);
        std::function<double(double)> approxFunc = [p_cs = p_cheb_series](double x) {
            return gsl_cheb_eval(p_cs.get(),x);
        };
        return cfl::Function(approxFunc);
    }

private:
    ChebApprox(double dLeft, double dRight, const std::function<unsigned(double)> &rSize)
    :dLeft{dLeft}, dRight{dRight}, rSize{rSize}
    {
        size = rSize(dRight-dLeft);
        p_cheb_series = std::shared_ptr<gsl_cheb_series>(gsl_cheb_alloc(size-1),&gsl_cheb_free);
        nodes = std::vector<double>(size);
        for(unsigned i=0;i<size;i++){
            nodes[i] = 0.5*(dRight-dLeft)*cos(M_PI*(size-i-0.5)/size)+0.5*(dLeft+dRight);
        }
    }

    double dLeft, dRight;
    const std::function<unsigned(double)> &rSize;
    std::shared_ptr<gsl_cheb_series> p_cheb_series;
    unsigned size;
    std::vector<double> nodes;
};


cfl::Approx prb::NApprox::chebyshev(const std::function<unsigned(double)> &rSize)
{
    return cfl::Approx(new ChebApprox(rSize));
}