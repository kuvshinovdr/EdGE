#ifndef EDGELIB_EDGE_LIKE_HPP
#define EDGELIB_EDGE_LIKE_HPP

#include "vertex_like.hpp"

#include <tuple>

namespace edgelib {

namespace impl {
	template <typename T>
	concept TupleLike = requires {
        std::tuple_size<std::remove_cvref_t<T>>::value;
	};

	template <typename T>
    concept Pair = TupleLike<T> && std::tuple_size_v<std::remove_cvref_t<T>> == 2;

	template <typename T>
    concept Triple = TupleLike<T> && std::tuple_size_v<std::remove_cvref_t<T>> == 3;
}

/// Ребро, представленное идентификатором аналогично вершине.
template <typename T>
concept EdgeHandle = RegularTotallyOrdered<T>
				  && !impl::Pair<T>
				  && !impl::Triple<T>;

namespace impl {
	constexpr auto first(Pair auto&& t) {
		auto [u, _] = t;
        return u;
    }

	constexpr auto second(Pair auto&& t) {
		auto [_, v] = t;
        return v;
    }

	constexpr auto first(Triple auto&& t) {
        auto [u, _2, _3] = t;
        return u;
    }

	constexpr auto second(Triple auto&& t) {
        auto [_1, v, _3] = t;
        return v;
    }

	constexpr auto third(Triple auto&& t) {
        auto [_1, _2, h] = t;
        return h;
    }
}

/// Ребро, представленное парой вершин.
template <typename T>
concept VertexHandlePair = impl::Pair<T> &&
	requires(T& e) {
        { impl::first(e)  } -> VertexHandle;
        { impl::second(e) } -> VertexHandle;
        { impl::second(e) } -> std::same_as<decltype(impl::first(e))>;
    };

/// Ребро, представленное парой вершин и идентификатором самого ребра.
/// Иногда может быть достаточно просто прицепить атрибут к паре индексов вершин третьим аргументом.
/// Можно обеспечить такое поведение через фиктивный диапазон, который по "хэндлу" ребра возвращает его же.
template <typename T>
concept VertexEdgeHandleTriple = impl::Triple<T> &&
	requires(T& e) {
        { impl::first(e)  } -> VertexHandle;
        { impl::second(e) } -> VertexHandle;
        { impl::second(e) } -> std::same_as<decltype(impl::first(e))>;
        { impl::third(e)  } -> EdgeHandle;
    };

/// Объединение трёх вариантов представления ребра.
template <typename T>
concept Edge = EdgeHandle<T>
			|| VertexHandlePair<T>
            || VertexEdgeHandleTriple<T>;

}

#endif//EDGELIB_EDGE_LIKE_HPP
