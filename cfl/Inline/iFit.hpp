//do not include this file

template <class InIt1, class InIt2>
void cfl::Fit::assign(InIt1 itArgBegin, InIt1 itArgEnd, InIt2 itValBegin)
{
    std::vector<double> uArg(itArgBegin, itArgEnd);
    std::vector<double> uVal(itValBegin, itValBegin + uArg.size()); 
    m_uP = std::shared_ptr<IFit>(m_uP->newObject(uArg, uVal));
}

template <class InIt1, class InIt2, class InIt3>
void cfl::Fit::assign(InIt1 itArgBegin, InIt1 itArgEnd, InIt2 itValBegin,
                      InIt3 itWtBegin)
{
    std::vector<double> uArg(itArgBegin, itArgEnd);
    std::vector<double> uVal(itValBegin, itValBegin + uArg.size());
    std::vector<double> uWt(itWtBegin, itWtBegin + uArg.size());
    m_uP = std::shared_ptr<IFit>(m_uP->newObject(uArg, uVal, uWt));
}

inline cfl::Function cfl::Fit::fit() const
{
    return m_uP->fit();
}

inline cfl::Function cfl::Fit::err() const
{
    return m_uP->err();
}
