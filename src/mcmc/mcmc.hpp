#ifndef ACTIVE_MODULES_MCMC_HPP
#define ACTIVE_MODULES_MCMC_HPP

#include <iostream>

namespace mcmc {

    template<class mcmc_target>
    class mcmc_worker {

        mcmc_target target_;
        std::vector<class mcmc_target::state> history_;
        std::size_t step_amount_;
        utils::random const &rng_;

        void step() {
            auto suggestion = target_.propose_change();
            bool acceptance = target_.try_accept(suggestion);
            history_.push_back(target_.get_state());
        };

    public:

        mcmc_worker(mcmc_target const &target, std::size_t step_amount) :
            target_(target), step_amount_(step_amount), rng_(target_.get_target_rng()) {};

        void run() {
            target_.sample_me();
            history_.push_back(target_.get_state());
            for (std::size_t step_number = 0; step_number < step_amount_; step_number++) {
                step();
            }
        }

        void status() const {
            for (std::size_t i = 0; i < history_.size(); i++) {
                std::cout << i << ": ";
                for (std::size_t node : history_[i]) {
                    std::cout << node << ' ';
                }
                std::cout << '\n';
            }
        }

    };

}

#endif //ACTIVE_MODULES_MCMC_HPP
