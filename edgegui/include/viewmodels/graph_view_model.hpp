#ifndef EDGEGUI_GRAPH_VIEW_MODEL_HPP
#define EDGEGUI_GRAPH_VIEW_MODEL_HPP

#include <graph.hpp>

#include <cstddef>
#include <functional>

// Pure C++ viewmodel (no Qt): testable without QApplication or an event loop.
class GraphViewModel {
public:
    using NodeCountListener = std::function<void(std::size_t)>;

    void setNodeCountListener(NodeCountListener listener) { nodeCountListener_ = std::move(listener); }

    void addNode(const edgelib::Graph::NodeId& id) {
        graph_.addNode(id);
        notifyNodeCount();
    }

    void addEdge(const edgelib::Graph::NodeId& from, const edgelib::Graph::NodeId& to) {
        graph_.addEdge(from, to);
        notifyNodeCount();
    }

    [[nodiscard]] std::size_t nodeCount() const { return graph_.nodeCount(); }

    [[nodiscard]] const edgelib::Graph& graph() const { return graph_; }

private:
    void notifyNodeCount() {
        if (nodeCountListener_) {
            nodeCountListener_(graph_.nodeCount());
        }
    }

    edgelib::Graph graph_;
    NodeCountListener nodeCountListener_;
};

#endif//EDGEGUI_GRAPH_VIEW_MODEL_HPP
