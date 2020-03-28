//do not include this file

inline double cfl::Function::operator()(double dX) const 
{
  return m_pF->operator()(dX);
}
		
inline bool cfl::Function::belongs(double dX) const 
{
  return m_pF->belongs(dX);
}