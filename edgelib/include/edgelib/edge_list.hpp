#ifndef EDGELIB_EDGE_LIST_HPP
#define EDGELIB_EDGE_LIST_HPP

#include "edge_like.hpp"

#include <concepts>
#include <ranges>
#include <algorithm>
#include <vector>
#include <set>

namespace edgelib {

template <typename T, typename Item>
concept CanPushBack = requires(T& t) {
		{ t.push_back(std::declval<Item>()) };
	};

template <typename T, typename Item>
concept CanInsert = requires(T& t) {
		{ t.insert(std::declval<Item>()) };
	};

namespace config {
	template <typename T, CanPushBack<T> V>
	constexpr void insert(V& vec, T const& item)
	{
		vec.push_back(item);
	}

	template <typename K, CanInsert<K> S>
	constexpr void insert(S& set, K const& item)
	{
		set.insert(item);
	}
}

template <typename T>
concept EdgeList = std::ranges::range<T>
				&& Edge<std::ranges::range_value_t<T>>;

template <EdgeList EL>
using EdgeListVertexHandleType =
	EdgeVertexHandleType<std::ranges::range_value_t<EL>>;

constexpr auto pairsMax(auto&& pairs)
{
	static constexpr auto pairMax = [](auto const& uv)
	{
		return std::max(std::get<0>(uv), std::get<1>(uv));
	};

	return std::ranges::max(pairs | std::views::transform(pairMax));
}

namespace config {
	template <Edge E>
	requires (!EdgeHandle<E>)
	constexpr auto getVertexHandlePair(E const& e)
	{
		using std::get;
		return std::tuple(get<0>(e), get<1>(e));
	}
}

namespace impl {
	struct DefaultAddEdge
	{
		static constexpr void operator()(auto& al, auto u, auto v)
		{
			config::insert(al[u], v);
		}
	};
}

template <EdgeList EL, typename AL, typename AddEdge = impl::DefaultAddEdge>
requires VertexHandlePair<std::ranges::range_value_t<EL>>
	  || VertexEdgeHandleTriple<std::ranges::range_value_t<EL>>
[[nodiscard]] constexpr auto
directedEdgeListToAdjacencyList(EL const& el, AL&& al, AddEdge&& addEdge = {})
	-> AL
{
	for (auto& e: el) {
		auto [u, v] = config::getVertexHandlePair(e);
		addEdge(al, u, v);
	}

	return al;
}

}

#endif//EDGELIB_EDGE_LIST_HPP
