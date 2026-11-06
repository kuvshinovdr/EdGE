#include <edgelib/edge_list.hpp>

#include <doctest/doctest.h>
#include <map>

TEST_SUITE("Edge list") {
	TEST_CASE("Check basic variant: vector/vector") {
		auto const edges = std::vector<std::tuple<int, int>>
			{
				{ 0, 2 },
				{ 1, 2 },
				{ 2, 3 },
			};

		auto const adjlist =
			edgelib::directedEdgeListToAdjacencyList(edges,
							std::vector<std::vector<int>>(4));

		REQUIRE(adjlist.size() == 4);
		CHECK(adjlist[0] == std::vector{2});
		CHECK(adjlist[1] == std::vector{2});
		CHECK(adjlist[2] == std::vector{3});
		CHECK(adjlist[3].empty());
	}

	TEST_CASE("Check basic variant: map/vector") {
		using EL = std::vector<std::tuple<int, int>>;
		auto const edges = EL
			{
			 { 0, 2 },
			 { 1, 2 },
			 { 2, 3 },
			 };

		auto const adjlist =
			edgelib::directedEdgeListToAdjacencyList(edges,
							std::map<int, std::vector<int>>{});

		REQUIRE(adjlist.size() == 3);
		CHECK(adjlist.at(0) == std::vector{2});
		CHECK(adjlist.at(1) == std::vector{2});
		CHECK(adjlist.at(2) == std::vector{3});
	}
}

