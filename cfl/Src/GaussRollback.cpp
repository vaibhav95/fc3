#include "cfl/GaussRollback.hpp"
#include "cfl/Error.hpp"

using namespace cfl;

// class GaussRollback

cfl::GaussRollback::GaussRollback(IGaussRollback *pNewP,
                                  unsigned iSize, double dH, double dVar)
                                  :m_uP(pNewP)
{
    assign(iSize, dH, dVar);
}

std::valarray<double> state(unsigned iSize, double dH)
{
    std::valarray<double> uState(iSize);
    uState[0] = -((iSize - 1) * dH) / 2.;
    std::transform(begin(uState), end(uState) - 1, begin(uState) + 1,
                   [dH](double dX) { return dX + dH; });
    return uState;
}

void delta(const std::valarray<double> & rValues, const std::valarray<double> & rState, 
double dVar, std::valarray<double> & rDelta)
{
    rDelta -= (rValues * rState);
    rDelta /= dVar;
}

void cfl::GaussRollback::rollback(std::valarray<double> &rValues,
                                  std::valarray<double> &rDelta) const
{
    PRECONDITION(m_dVar > std::numeric_limits<double>::epsilon());
    std::valarray<double> uState = state(m_iSize, m_dH);
    rDelta = rValues * uState;
    rollback(rValues);
    rollback(rDelta);
    delta(rValues, uState, m_dVar, rDelta);
}

void cfl::GaussRollback::rollback(std::valarray<double> &rValues,
                                  std::valarray<double> &rDelta,
                                  std::valarray<double> &rGamma) const
{
    PRECONDITION(m_dVar > std::numeric_limits<double>::epsilon());
    std::valarray<double> uState = state(m_iSize, m_dH);
    std::valarray<double> uState2 = uState * uState;
    rDelta = rValues * uState;
    rGamma = rValues * uState2;
    rollback(rValues);
    rollback(rDelta);
    rollback(rGamma);
    rGamma += (-2. * uState * rDelta + uState2 * rValues);
    rGamma /= m_dVar;
    rGamma -= rValues;
    rGamma /= m_dVar;
    delta(rValues, uState, m_dVar, rDelta);
}

void cfl::GaussRollback::assign(unsigned iSize, double dH, double dVar)
{
    m_uP.reset(m_uP->newObject(iSize, dH, dVar));
    m_dH = dH;
    m_iSize = iSize;
    m_dVar = dVar;
}

void cfl::GaussRollback::vega(std::valarray<double> & rGamma) const {
    rGamma *= std::sqrt(m_dVar);
}
