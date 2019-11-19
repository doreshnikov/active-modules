#ifndef ACTIVE_MODULES_UTILS_HPP
#define ACTIVE_MODULES_UTILS_HPP

#include <cstddef>
#include <cmath>
#include <random>
#include <chrono>

namespace utils {

    struct random {

        struct distribution {
            long double alpha_;
        } current_beta_;
        std::default_random_engine generator_;

        // TODO: create actual distribution
        random() : current_beta_{2}, generator_(std::chrono::system_clock::now().time_since_epoch().count()) {}

        std::size_t randint(std::size_t limit) {
            std::uniform_int_distribution<std::size_t> rnd(0, limit - 1);
            return rnd(generator_);
        };

        bool if_prob(long double prob) {
            std::uniform_real_distribution<long double> rnd(0, 1);
            return rnd(generator_) < prob;
        }

    };

    inline long double power(long double value, long double p) {
        return powl(value, p);
    }

    inline long double log_power(long double value, long double p) {
        return logl(value) * p;
    }

}

#endif //ACTIVE_MODULES_UTILS_HPP
