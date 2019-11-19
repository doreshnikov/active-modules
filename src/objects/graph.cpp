#include <queue>
#include "graph.hpp"

objects::node::node(long double pvalue, std::vector<edge> const &edges) : pvalue_(pvalue), edges_(edges) {}
objects::node::node(const objects::node &other) = default;
objects::node::~node() = default;

objects::edge::edge(std::size_t to) : to_(to) {}
objects::edge::edge(const objects::edge &other) = default;
objects::edge::~edge() = default;

objects::subgraph::subgraph(const std::vector<node> &graph) :
    size_(graph.size()), graph_(graph), nodes_(), neighbours_(), rng_() {}
objects::subgraph::subgraph(const objects::subgraph &other) = default;
objects::subgraph::~subgraph() = default;

std::size_t objects::subgraph::nodes() const {
    return nodes_.size();
}
std::size_t objects::subgraph::neighbours() const {
    return neighbours_.size();
}
// TODO: dynamic connectivity (possibly)
bool objects::subgraph::connected() const {
    std::set<std::size_t> visited;
    std::queue<std::size_t> q;
    q.push(*nodes_.begin());
    while (!q.empty()) {
        std::size_t v = q.front();
        q.pop();
        visited.insert(v);
        for (auto const &e : graph_[v].edges_) {
            if (visited.count(e.to_) == 0 && nodes_.count(e.to_) > 0) {
                q.push(e.to_);
            }
        }
    }
    return visited.size() == nodes();
}

void objects::subgraph::add_node(std::size_t id) {
    neighbours_.erase(id);
    for (auto const &e : graph_[id].edges_) {
        if (nodes_.count(e.to_) == 0) {
            neighbours_.insert(e.to_);
        }
    }
    nodes_.insert(id);
}
void objects::subgraph::remove_node(std::size_t id) {
    nodes_.erase(id);
    for (auto const &e : graph_[id].edges_) {
        std::size_t v = e.to_;
        if (neighbours_.count(v) > 0) {
            bool keep = false;
            for (auto const &ve : graph_[v].edges_) {
                keep = keep || (nodes_.count(ve.to_) > 0);
            }
            if (!keep) {
                neighbours_.erase(v);
            }
        }
    }
    neighbours_.insert(id);
}
// TODO: this works too slow (maybe replace std::set with something else)
std::size_t objects::subgraph::take_node() const {
    return *std::next(nodes_.begin(), rng_.randint(nodes()));
}
// TODO: this works too slow (maybe replace std::set with something else)
std::size_t objects::subgraph::take_neighbour() const {
    if (neighbours_.empty()) {
        std::size_t index = rng_.randint(size_ - nodes());
        for (std::size_t i = 0; nodes_.count(i) > 0; i++) {
            index++;
        }
        return index;
    }
    return *std::next(neighbours_.begin(), rng_.randint(neighbours()));
}

void objects::subgraph::swap(subgraph &other) {
    std::swap(nodes_, other.nodes_);
    std::swap(neighbours_, other.neighbours_);
}

