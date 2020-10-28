#include "prb/GaussRollback.hpp"
#include <cmath>
#include <gsl/gsl_linalg.h>

class GaussRollbackExplic: public cfl::IGaussRollback
{
public:

    GaussRollbackExplic(double dP)
    :p{dP}
    {}

    cfl::IGaussRollback *newObject(unsigned iSize,double dH,double dVar) const
    {
        return new GaussRollbackExplic(p,iSize, dH, dVar);
    }

    void rollback(std::valarray<double> &rValues) const
    {
        std::valarray<double> rValsCopy{rValues};
        for(int i=0;i<M;i++)
        {
            for(unsigned j=0;j<N;j++)
            {   
                double k = (j==0)?1:((j==N-1)?(N-2):j);
                double delta = rValues[k-1]-2*rValues[k]+rValues[k+1];
                rValsCopy[j]+=q*delta;
            }
            rValues = rValsCopy;
        }
    }

private:
    GaussRollbackExplic(double dP,unsigned iSize,double dH,double dVar)
    :p{dP},N{iSize},h{dH},var{dVar}
    {
        double m = var/(2*pow(h,2)*p);
        M = ceil(m);
        q = var/(2*pow(h,2)*M);
    }
    double p;
    unsigned N;
    double h;
    double var;
    int M;
    double q;
};

cfl::GaussRollback prb::NGaussRollback::explic(double dP)
{
    return cfl::GaussRollback(new GaussRollbackExplic(dP));
}

class GaussRollbackImplicit: public cfl::IGaussRollback
{
public:

    GaussRollbackImplicit(double dP)
    :p{dP}
    {}

    cfl::IGaussRollback *newObject(unsigned iSize,double dH,double dVar) const
    {
        return new GaussRollbackImplicit(p,iSize, dH, dVar);
    }

    void rollback(std::valarray<double> &rValues) const
    {
        gsl_vector *x = gsl_vector_alloc(N);
        gsl_vector *b = gsl_vector_alloc(N);
        for(unsigned i=0;i<N;i++)
            gsl_vector_set(b,i,rValues[i]);
        for(int i=0;i<M;i++)
        {
            gsl_linalg_solve_tridiag(diag.get(),e.get(),f.get(),b,x);
            gsl_vector_memcpy(b,x);
        }
        for(unsigned i=0;i<N;i++)
            rValues[i] = gsl_vector_get(b,i);
        gsl_vector_free(x);
        gsl_vector_free(b);
    }

private:
    GaussRollbackImplicit(double dP,unsigned iSize,double dH,double dVar)
    :p{dP},N{iSize},h{dH},var{dVar},diag(gsl_vector_alloc(iSize),&gsl_vector_free),
    e(gsl_vector_alloc(iSize-1),&gsl_vector_free),f(gsl_vector_alloc(iSize-1),&gsl_vector_free)
    {
        double m = var/(2*pow(h,2)*p);
        M = ceil(m);
        double q = var/(2*pow(h,2)*M);
        if(N>0)
        {
            gsl_vector_set(diag.get(),0,1);
            gsl_vector_set(diag.get(),N-1,1);
            for(unsigned i=1;i<N-1;i++)
                gsl_vector_set(diag.get(),i,(1+2*q));
        }
        if(N>1) 
        {
            gsl_vector_set(e.get(),0,0);
            for(unsigned i=1;i<N-1;i++)
                gsl_vector_set(e.get(),i,-q);
            gsl_vector_set(f.get(),N-2,0);
            for(unsigned i=0;i<N-2;i++)
                gsl_vector_set(f.get(),i,-q);
        }
        
    }
    double p;
    unsigned N;
    double h;
    double var;
    int M;
    std::shared_ptr<gsl_vector> diag;
    std::shared_ptr<gsl_vector> e;
    std::shared_ptr<gsl_vector> f;
};

cfl::GaussRollback prb::NGaussRollback::implicit(double dP)
{
    return cfl::GaussRollback(new GaussRollbackImplicit(dP));
}


class GaussRollbackCrank: public cfl::IGaussRollback
{
public:

    GaussRollbackCrank(double dR)
    :r{dR}
    {}

    cfl::IGaussRollback *newObject(unsigned iSize,double dH,double dVar) const
    {
        return new GaussRollbackCrank(r,iSize, dH, dVar);
    }

    void rollback(std::valarray<double> &rValues) const
    {
        gsl_vector *x = gsl_vector_alloc(N);
        gsl_vector *b = gsl_vector_alloc(N);
        for(int i=0;i<M;i++)
        {
            for(unsigned j=0;j<N;j++)
            {   
                double k = (j==0)?1:((j==N-1)?(N-2):j);
                double delta = rValues[k-1]-2*rValues[k]+rValues[k+1];
                gsl_vector_set(b,j,rValues[j]+(q/2)*delta);
            }
            gsl_linalg_solve_tridiag(diag.get(),e.get(),f.get(),b,x);
            for(unsigned j=0;j<N;j++)
                rValues[j] = gsl_vector_get(x,j);
        }
        gsl_vector_free(x);
        gsl_vector_free(b);
    }

private:
    GaussRollbackCrank(double dR,unsigned iSize,double dH,double dVar)
    :r{dR},N{iSize},h{dH},var{dVar},diag(gsl_vector_alloc(iSize),&gsl_vector_free),
    e(gsl_vector_alloc(iSize-1),&gsl_vector_free),f(gsl_vector_alloc(iSize-1),&gsl_vector_free)
    {
        double m = var/(h*r);
        M = ceil(m);
        q = var/(2*pow(h,2)*M);
        if(N>0)
        {
            gsl_vector_set(diag.get(),0,1);
            gsl_vector_set(diag.get(),N-1,1);
            for(unsigned i=1;i<N-1;i++)
                gsl_vector_set(diag.get(),i,(1+q));
        }
        if(N>1) 
        {
            gsl_vector_set(e.get(),0,0);
            for(unsigned i=1;i<N-1;i++)
                gsl_vector_set(e.get(),i,-q/2);
            gsl_vector_set(f.get(),N-2,0);
            for(unsigned i=0;i<N-2;i++)
                gsl_vector_set(f.get(),i,-q/2);
        }
        
    }
    double r;
    unsigned N;
    double h;
    double var;
    int M;
    double q;
    std::shared_ptr<gsl_vector> diag;
    std::shared_ptr<gsl_vector> e;
    std::shared_ptr<gsl_vector> f;
};

cfl::GaussRollback prb::NGaussRollback::crankNicolson(double dR)
{
    return cfl::GaussRollback(new GaussRollbackCrank(dR));
}


class GaussRollbackChain: public cfl::IGaussRollback
{
public:
    GaussRollbackChain(const cfl::GaussRollback &rFast, unsigned iExplSteps, double dExplP,
			    unsigned iImplSteps, double dImplP)
    :rFast{rFast},iExplSteps{iExplSteps},dExplP{dExplP},iImplSteps{iImplSteps},dImplP{dImplP}
    {}

    cfl::IGaussRollback *newObject(unsigned iSize,double dH,double dVar) const
    {
        return new GaussRollbackChain(rFast,iExplSteps,dExplP,iImplSteps,dImplP,iSize, dH, dVar);
    }

    void rollback(std::valarray<double> &rValues) const
    {
        if(var>Te+Ti)
        {
            cfl::GaussRollback grExp = prb::NGaussRollback::explic(dExplP);
            grExp.assign(rValues.size(),h,Te);
            grExp.rollback(rValues);
            cfl::GaussRollback grFast = prb::NGaussRollback::crankNicolson();
            grFast.assign(rValues.size(),h,var-(Te+Ti));
            grFast.rollback(rValues);
            cfl::GaussRollback grImp = prb::NGaussRollback::implicit(dImplP);
            grImp.assign(rValues.size(),h,Ti);
            grImp.rollback(rValues);
        } else
        {
            cfl::GaussRollback grExp = prb::NGaussRollback::explic(dExplP);
            grExp.assign(rValues.size(),h,var);
            grExp.rollback(rValues);
        }
    }

private:
    GaussRollbackChain(const cfl::GaussRollback &rFast, unsigned iExplSteps, double dExplP,
			    unsigned iImplSteps, double dImplP, unsigned iSize, double dH, double dVar)
    :rFast{rFast},iExplSteps{iExplSteps},dExplP{dExplP},iImplSteps{iImplSteps},dImplP{dImplP},
    N{iSize},h{dH},var{dVar}
    {
        Te = 2*pow(h,2)*dExplP*iExplSteps;
        Ti = 2*pow(h,2)*dImplP*iImplSteps;
    }

    const cfl::GaussRollback &rFast;
    unsigned iExplSteps;
    double dExplP;
    unsigned iImplSteps;
    double dImplP;
    unsigned N;
    double h;
    double var;
    double Te,Ti;
};

cfl::GaussRollback prb::NGaussRollback::chain(const cfl::GaussRollback &rFast,
			    unsigned iExplSteps, double dExplP,
			    unsigned iImplSteps, double dImplP)
{
    return cfl::GaussRollback(new GaussRollbackChain(rFast,iExplSteps,dExplP,iImplSteps,dImplP));
}