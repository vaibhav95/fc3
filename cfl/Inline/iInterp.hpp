//do not include this file

template <class InIt1, class InIt2>
cfl::Function cfl::Interp::interpolate(InIt1 itArgBegin, InIt1 itArgEnd,
                                       InIt2 itValBegin) const
{
  std::vector<double> uArg(itArgBegin, itArgEnd);
  std::vector<double> uVal(itValBegin, itValBegin + (itArgEnd - itArgBegin));
  return m_uP->interpolate(uArg, uVal);
}
