#include "prb/Fit.hpp"
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_bspline.h>
#include <iostream>
class LinearFit: public cfl::IFit
{
public:
    LinearFit(size_t P, const std::function<gsl_vector*(double)> basisFunc)
    :P(P),basisFunc(basisFunc),
     p_work(nullptr, &gsl_multifit_linear_free),
     p_X(nullptr,&gsl_matrix_free),
     p_y(nullptr,&gsl_vector_free),
     p_c(nullptr,&gsl_vector_free),
     p_cov(nullptr,&gsl_matrix_free),
     p_w(nullptr,&gsl_vector_free)
    {}

    virtual cfl::IFit *newObject(const std::vector<double> &rArg,
                          const std::vector<double> &rVal) const
    {
        return new LinearFit(P,basisFunc,rArg, rVal);
    }

    virtual cfl::IFit *newObject(const std::vector<double> &rArg,
                          const std::vector<double> &rVal,
                          const std::vector<double> &rW) const
    {
        return new LinearFit(P,basisFunc,rArg, rVal, rW);
    }

    virtual cfl::Function fit() const
    {
        std::function<double(double)> fitFunc = [basisFunc=basisFunc,p_c=p_c,p_cov=p_cov]
        (double dX) {
            gsl_vector * x = basisFunc(dX);
            double y = 0;
            double y_err = 0;
            gsl_multifit_linear_est(x, p_c.get(), p_cov.get(), &y, &y_err);
            gsl_vector_free(x);
            return y;
        };
        return cfl::Function(fitFunc);
    }

    virtual cfl::Function err() const
    {
        std::function<double(double)> errFunc = [basisFunc=basisFunc,p_c=p_c,p_cov=p_cov]
        (double dX) {
            gsl_vector * x = basisFunc(dX);
            double y = 0;
            double y_err = 0;
            gsl_multifit_linear_est(x, p_c.get(), p_cov.get(), &y, &y_err);
            gsl_vector_free(x);
            return y_err;
        };
        return cfl::Function(errFunc);
    }
    
private:
    LinearFit(size_t P,const std::function<gsl_vector*(double)> basisFunc,const std::vector<double> &rArg,
                const std::vector<double> &rVal,const std::vector<double> &rW = std::vector<double>())
    :N(rArg.size()),P(P),basisFunc(basisFunc),
     p_work(gsl_multifit_linear_alloc(N,P), &gsl_multifit_linear_free),
     p_X(gsl_matrix_alloc(N,P),&gsl_matrix_free),
     p_y(gsl_vector_alloc(N),&gsl_vector_free),
     p_c(gsl_vector_alloc(P),&gsl_vector_free),
     p_cov(gsl_matrix_alloc(P,P),&gsl_matrix_free),
     p_w(gsl_vector_alloc(N),&gsl_vector_free)
    {
        for(size_t i=0;i<N;i++)
        {
            gsl_vector_set(p_y.get(),i,rVal[i]);
            gsl_vector* row = basisFunc(rArg[i]);
            gsl_matrix_set_row(p_X.get(),i,row);
            if(rW.size()>0)
                gsl_vector_set(p_w.get(),i,rW[i]);
        }
        if(rW.size()>0)
            gsl_multifit_wlinear(p_X.get(),p_w.get(),p_y.get(),p_c.get(),
                                    p_cov.get(),&chisq,p_work.get());
        else
            gsl_multifit_linear(p_X.get(),p_y.get(),p_c.get(),
                                        p_cov.get(),&chisq,p_work.get());
        
    }

    size_t N,P;
    const std::function<gsl_vector*(double)> basisFunc;
    std::unique_ptr<gsl_multifit_linear_workspace, decltype(&gsl_multifit_linear_free)> p_work;
    std::unique_ptr<gsl_matrix, decltype(&gsl_matrix_free)> p_X;
    std::unique_ptr<gsl_vector, decltype(&gsl_vector_free)> p_y;
    std::shared_ptr<gsl_vector> p_c;
    std::shared_ptr<gsl_matrix> p_cov;
    std::unique_ptr<gsl_vector, decltype(&gsl_vector_free)> p_w;
    double chisq;

};

cfl::Fit prb::NFit::linear(const std::vector<cfl::Function> &rBasisF)
{
    const std::function<gsl_vector*(double)> basisFunc = [rBasisF](double dX) {
        gsl_vector * vec = gsl_vector_alloc(rBasisF.size());
        for(size_t i=0;i<rBasisF.size();i++)
        {
            gsl_vector_set(vec,i,rBasisF[i](dX));
        }
        return vec;
    };
    return cfl::Fit(new LinearFit(rBasisF.size(),basisFunc));
}


cfl::Fit prb::NFit::bspline(unsigned iOrder, const std::vector<double> &rBreakpoints)
{
    size_t nbreak = rBreakpoints.size();
    std::shared_ptr<gsl_bspline_workspace> p_wspace(
            gsl_bspline_alloc(iOrder,nbreak), &gsl_bspline_free);
    gsl_vector * breakpts = gsl_vector_alloc(nbreak);
    for(size_t i=0;i<nbreak;i++)
        gsl_vector_set(breakpts,i,rBreakpoints[i]);
    gsl_bspline_knots(breakpts, p_wspace.get());
    gsl_vector_free(breakpts);
    std::function<gsl_vector*(double)> basisFunc = [nbreak,iOrder,p_wspace](double dX) {
        gsl_vector *vec = gsl_vector_alloc(nbreak+iOrder-2);
        gsl_bspline_eval(dX,vec, p_wspace.get());
        return vec;
    };
    return cfl::Fit(new LinearFit(nbreak+iOrder-2,basisFunc));
}

cfl::Fit prb::NFit::bspline(unsigned iOrder, double dL, double dR, unsigned iBreakpoints)
{
    std::shared_ptr<gsl_bspline_workspace> p_wspace(
            gsl_bspline_alloc(iOrder,iBreakpoints), &gsl_bspline_free);
    gsl_bspline_knots_uniform(dL,dR, p_wspace.get());
    std::function<gsl_vector*(double)> basisFunc = [iBreakpoints,iOrder,p_wspace](double dX) {
        gsl_vector *vec = gsl_vector_alloc(iBreakpoints+iOrder-2);
        gsl_bspline_eval(dX,vec, p_wspace.get());
        return vec;
    };
    return cfl::Fit(new LinearFit(iBreakpoints+iOrder-2,basisFunc));
}