#ifndef ACTIVE_MODULES_GRAPH_HPP
#define ACTIVE_MODULES_GRAPH_HPP

#include <vector>
#include <set>
#include "../mcmc/utils.hpp"

namespace objects {

    struct edge {

        std::size_t to_;

        explicit edge(std::size_t to);
        edge(edge const &other);
        ~edge();

    };

    struct node {

        long double pvalue_;
        std::vector<edge> edges_;

        explicit node(long double pvalue, std::vector<edge> const &edges);
        node(node const &other);
        ~node();

    };

    struct subgraph {

        std::size_t const size_;
        std::vector<node> const graph_;
        utils::random mutable rng_;

        typedef std::set<std::size_t> state;
        state nodes_;
        state neighbours_;

        explicit subgraph(std::vector<node> const &nodes);
        subgraph(subgraph const &other);
        ~subgraph();

        std::size_t nodes() const;
        std::size_t neighbours() const;
        bool connected() const;

        void add_node(std::size_t id);
        void remove_node(std::size_t id);
        std::size_t take_node() const;
        std::size_t take_neighbour() const;

        void swap(subgraph &other);

    };

}

#endif // ACTIVE_MODULES_GRAPH_HPP
