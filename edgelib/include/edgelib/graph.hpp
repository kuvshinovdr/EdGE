#ifndef EDGELIB_GRAPH_HPP
#define EDGELIB_GRAPH_HPP

#include <cstddef>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace edgelib {

class Graph {
public:
    using NodeId = std::string;
    using Neighbors = std::unordered_set<NodeId>;

    void addNode(const NodeId& id) { adjacency_.try_emplace(id); }

    // Idempotent; implicitly adds missing nodes.
    void addEdge(const NodeId& from, const NodeId& to) {
        if (hasEdge(from, to)) {
            return;
        }
        adjacency_[from].insert(to);
        adjacency_.try_emplace(to);
        ++edgeCount_;
    }

    [[nodiscard]] bool hasNode(const NodeId& id) const { return adjacency_.contains(id); }

    [[nodiscard]] bool hasEdge(const NodeId& from, const NodeId& to) const {
        const auto it = adjacency_.find(from);
        return it != adjacency_.end() && it->second.contains(to);
    }

    [[nodiscard]] Neighbors neighbors(const NodeId& id) const {
        const auto it = adjacency_.find(id);
        if (it == adjacency_.end()) {
            return {};
        }
        return it->second;
    }

    [[nodiscard]] std::size_t nodeCount() const { return adjacency_.size(); }

    [[nodiscard]] std::size_t edgeCount() const { return edgeCount_; }

private:
    std::unordered_map<NodeId, Neighbors> adjacency_;
    std::size_t edgeCount_ = 0;
};

} // namespace edgelib

#endif//EDGELIB_GRAPH_HPP
