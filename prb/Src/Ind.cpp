#include "prb/Ind.hpp"

class NaiveInd: public cfl::IInd
{
public:
    void indicator(std::valarray<double> &rValues, double dBarrier) const
    {
        for(unsigned i=0;i<rValues.size();i++){
            rValues[i] = rValues[i]>=dBarrier;
        }
    }
};

cfl::Ind prb::NInd::naive()
{
    return cfl::Ind(new NaiveInd());
}

class LinearInd: public cfl::IInd
{
public:
    void indicator(std::valarray<double> &rValues, double dBarrier) const
    {
        std::valarray<double> rValues_L(rValues.size());
        for(unsigned i=0;i<rValues.size();i++) {
            rValues_L[i] = rValues[i]-dBarrier;
        }
        for(unsigned i=0;i<rValues.size();i++) {
            unsigned j = i>0?i-1:i;
            unsigned k = i<rValues.size()-1?i+1:i;
            rValues[i] = 0.5*(alpha(rValues_L[j],rValues_L[i])+alpha(rValues_L[i],rValues_L[k]));
        }
    }

    double alpha(double x, double y) const
    {
        return x<=0&&y<=0?0:(x!=y? ((x>0?x:0)-(y>0?y:0))/(x-y) : x>=0);
    }
};

cfl::Ind prb::NInd::linear()
{
    return cfl::Ind(new LinearInd());
}

class QuadraticInd: public cfl::IInd
{
public:
    void indicator(std::valarray<double> &rValues, double dBarrier) const
    {
        std::valarray<double> rValues_L(rValues.size());
        for(unsigned i=0;i<rValues.size();i++) {
            rValues_L[i] = rValues[i]-dBarrier;
        }
        for(unsigned i=0;i<rValues.size();i++) {
            unsigned j = i>0?i-1:i;
            unsigned k = i<rValues.size()-1?i+1:i;
            rValues[i] = 0.5*(alpha(rValues_L[j],rValues_L[i])+beta(rValues_L[i],rValues_L[k]));
        }
    }

    double alpha(double x, double y) const
    {
        return x<0&&y>=0?(1-pow(x/(x-y),2)):(y<0&&x>=0?pow(x/(x-y),2):x>=0&&y>=0);
    }

    double beta(double x, double y) const
    {
        return x<0&&y>=0?pow(y/(y-x),2):(y<0&&x>=0?1-pow(y/(y-x),2):x>=0&&y>=0);
    }
};

cfl::Ind prb::NInd::quadratic()
{
    return cfl::Ind(new QuadraticInd());
}
