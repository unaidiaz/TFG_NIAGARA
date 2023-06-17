#pragma once
#include <random>
// For:
//   std::mt19937
//   std::random_device
//   std::uniform_int_distribution
//   std::uniform_real_distribution
//   std::bernoulli_distribution
#include <type_traits>
// For:
//   std::common_type
#include <limits>

class grand {
public:
	typedef std::mt19937 rng_type;

    double d(double d = 1.0)
    {
        _rng.seed(rng_type::result_type(std::random_device()()));
        if (d > 0.0)
            return std::uniform_real_distribution<double>(0.0, d)(_rng);
        if (d < 0.0)
            return
            -std::uniform_real_distribution<double>(0.0, -d)(_rng);
        return 0.0;
    }

    bool b(double p = 0.5)
    {
        _rng.seed(rng_type::result_type(std::random_device()()));
        if (p <= 0.0) return false;
        if (p >= 1.0) return true;
        return std::bernoulli_distribution(p)(_rng);
    }


	rng_type _rng;
};
