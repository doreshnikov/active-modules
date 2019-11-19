#include "mcmc_graph_target.hpp"

mcmc::mcmc_graph_target::mcmc_graph_target(const objects::subgraph &initial_state, std::size_t module_size)
    : target_(initial_state), module_size_(module_size) {}
mcmc::mcmc_graph_target::~mcmc_graph_target() = default;

void mcmc::mcmc_graph_target::sample_me() {
    for (std::size_t i = 0; i < module_size_; i++) {
        target_.add_node(target_.take_neighbour());
    }
}

mcmc::mcmc_graph_target::proposal mcmc::mcmc_graph_target::propose_change() const {
    return mcmc::mcmc_graph_target::proposal(
        target_.take_node(),
        target_.take_neighbour()
    );
}
objects::subgraph mcmc::mcmc_graph_target::simulate(const mcmc::mcmc_graph_target::proposal &suggestion) {
    subgraph result(target_);
    result.add_node(suggestion.new_id_);
    result.remove_node(suggestion.old_id_);
    return result;
}
bool mcmc::mcmc_graph_target::try_accept(const mcmc::mcmc_graph_target::proposal &suggestion) {
    subgraph alternative = simulate(suggestion);
    if (alternative.connected()) {
        long double prob = (long double) target_.neighbours() / alternative.neighbours() *
            utils::power(target_.graph_[suggestion.new_id_].pvalue_ / target_.graph_[suggestion.old_id_].pvalue_,
                         target_.rng_.current_beta_.alpha_);
        bool accept = target_.rng_.if_prob(std::min(1.0l, prob));
        if (accept) {
            target_.swap(alternative);
            return true;
        }
    }
    return false;
}

utils::random const &mcmc::mcmc_graph_target::get_target_rng() {
    return target_.rng_;
}
const mcmc::mcmc_graph_target::state &mcmc::mcmc_graph_target::get_state() const {
    return target_.nodes_;
}
