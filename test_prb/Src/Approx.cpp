#include "test/Approx.hpp"
#include "test_prb/Main.hpp"
#include "prb/Approx.hpp"

std::function<void()> test::approx()
{
     return []() {
          testChebyshevApprox(prb::NApprox::chebyshev);
     };
};
