#ifndef EDGELIB_EDGE_LIST_HPP
#define EDGELIB_EDGE_LIST_HPP

#include "edge_like.hpp"

#include <ranges>
#include <algorithm>
#include <vector>

namespace edgelib {

template <typename T>
concept EdgeList = std::ranges::range<T>
				&& Edge<std::ranges::range_value_t<T>>;

[[nodiscard]] auto directedEdgeListToAdjacencyList(
	std::vector<std::tuple<std::size_t, std::size_t>> const& el)
	-> std::vector<std::vector<std::size_t>>
{
	if (el.empty()) {
		return {};
	}

	auto const pairMax = [](std::tuple<std::size_t, std::size_t> uv)
	{
		return std::max(std::get<0>(uv), std::get<1>(uv));
	};

	auto const maxVertexIndex = std::ranges::max(
		el | std::views::transform(pairMax));

	auto result = std::vector<std::vector<std::size_t>>(maxVertexIndex + 1);
	for (auto [u, v]: el) {
		result[u].push_back(v);
	}

	return result;
}

}

#endif//EDGELIB_EDGE_LIST_HPP
