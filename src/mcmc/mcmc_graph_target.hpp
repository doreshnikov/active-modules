#ifndef ACTIVE_MODULES_MCMC_GRAPH_TARGET_HPP
#define ACTIVE_MODULES_MCMC_GRAPH_TARGET_HPP

#include <vector>
#include <set>
#include "../objects/graph.hpp"
#include "mcmc.hpp"

namespace mcmc {

    using namespace objects;

    class mcmc_graph_target {

        std::size_t const module_size_;
        subgraph target_;
    public:

        typedef subgraph::state state;

        mcmc_graph_target(subgraph const &initial_state, std::size_t module_size);
        ~mcmc_graph_target();

        void sample_me();

        struct proposal {

            std::size_t const old_id_;
            std::size_t const new_id_;

            proposal(std::size_t old_id, std::size_t new_id) : old_id_(old_id), new_id_(new_id) {};
            ~proposal() = default;

        };

        proposal propose_change() const;
        subgraph simulate(proposal const &suggestion);
        bool try_accept(proposal const &suggestion);

        utils::random const &get_target_rng();
        state const &get_state() const;

    };

}

#endif //ACTIVE_MODULES_MCMC_GRAPH_TARGET_HPP
