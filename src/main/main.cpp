#include <iostream>
#include "../objects/graph.hpp"
#include "../mcmc/mcmc.hpp"
#include "../mcmc/utils.hpp"
#include "../mcmc/mcmc_graph_target.hpp"

using namespace std;
using namespace objects;
using namespace mcmc;

int main() {

    auto test_graph = subgraph({
        node(0.5, {edge(1), edge(2), edge(3)}),
        node(0.3, {edge(0), edge(4)}),
        node(0.1, {edge(0), edge(6)}),
        node(0.2, {edge(0)}),
        node(0.8, {edge(1), edge(6)}),
        node(0.4, {}),
        node(0.9, {edge(2), edge(4)})
    });

    auto target = mcmc_graph_target(test_graph, 4);
    auto mcmc_process = mcmc_worker<mcmc_graph_target>(target, 100);
    mcmc_process.run();
    mcmc_process.status();

}
