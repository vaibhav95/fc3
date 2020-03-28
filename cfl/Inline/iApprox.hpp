//do not include this file directly

inline void cfl::Approx::assign(double dL, double dR) 
{
  PRECONDITION(dL <= dR);
  m_uP.reset(m_uP->newApprox(dL,dR));
}

inline const std::vector<double> & cfl::Approx::arg() const 
{
  return m_uP->arg();
}

template <class InIt>
cfl::Function 
cfl::Approx::approximate(InIt itValBegin, InIt itValEnd) const 
{
  PRECONDITION(itValEnd - itValBegin == static_cast<int>(arg().size()));
  return m_uP->approximate(std::vector<double>(itValBegin, itValEnd)); 
}
