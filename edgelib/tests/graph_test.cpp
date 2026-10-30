#include <edgelib/graph.hpp>

#include <doctest/doctest.h>

TEST_SUITE("Graph") {
    TEST_CASE("addNode creates an isolated node") {
        edgelib::Graph graph;

        CHECK_FALSE(graph.hasNode("a"));

        graph.addNode("a");

        CHECK(graph.hasNode("a"));
        CHECK(graph.nodeCount() == 1);
        CHECK(graph.edgeCount() == 0);
        CHECK(graph.neighbors("a").empty());
    }

    TEST_CASE("addEdge is idempotent and implicitly adds nodes") {
        edgelib::Graph graph;

        graph.addEdge("a", "b");
        graph.addEdge("a", "b");

        CHECK(graph.hasEdge("a", "b"));
        CHECK_FALSE(graph.hasEdge("b", "a"));
        CHECK(graph.edgeCount() == 1);
        CHECK(graph.nodeCount() == 2);
        CHECK(graph.neighbors("a").contains("b"));
        CHECK(graph.neighbors("b").empty());
    }
}
