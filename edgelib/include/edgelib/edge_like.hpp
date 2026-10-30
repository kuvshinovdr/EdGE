#ifndef EDGELIB_EDGE_LIKE_HPP
#define EDGELIB_EDGE_LIKE_HPP

#include "vertex_like.hpp"

namespace edgelib {

/// Ребро, представленное идентификатором аналогично вершине.
template <typename T>
concept EdgeHandle = RegularTotallyOrdered<T>;

namespace impl {
    constexpr auto first2(auto&& t) {
        auto [u, _] = t;
        return u;
    }

    constexpr auto second2(auto&& t) {
        auto [_, v] = t;
        return v;
    }

    constexpr auto first3(auto&& t) {
        auto [u, _2, _3] = t;
        return u;
    }

    constexpr auto second3(auto&& t) {
        auto [_1, v, _3] = t;
        return v;
    }

    constexpr auto third3(auto&& t) {
        auto [_1, _2, h] = t;
        return t;
    }
}

/// Ребро, представленное парой вершин.
template <typename T>
concept VertexHandlePair =
    requires(T const& e) {
        { impl::first2(e)  } -> VertexHandle;
        { impl::second2(e) } -> VertexHandle;
    };

/// Ребро, представленное парой вершин и идентификатором самого ребра.
/// Иногда может быть достаточно просто прицепить атрибут к паре индексов вершин третьим аргументом.
/// Можно обеспечить такое поведение через фиктивный диапазон, который по "хэндлу" ребра возвращает его же.
template <typename T>
concept VertexEdgeHandleTriple =
    requires(T const& e) {
        { impl::first3(e)  } -> VertexHandle;
        { impl::second3(e) } -> VertexHandle;
        { impl::third3(e)  } -> EdgeHandle;
    };

/// Объединение трёх вариантов представления ребра.
template <typename T>
concept Edge = EdgeHandle<T>
            || VertexHandlePair<T>
            || VertexEdgeHandleTriple<T>;

}

#endif//EDGELIB_EDGE_LIKE_HPP
