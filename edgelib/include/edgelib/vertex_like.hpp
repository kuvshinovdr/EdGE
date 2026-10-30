#ifndef EDGELIB_VERTEX_LIKE_HPP
#define EDGELIB_VERTEX_LIKE_HPP

#include <concepts>

namespace edgelib {

/// Регулярный тип можно инициализировать по умолчанию, копировать, перемещать и сравнивать на равенство.
/// К этому добавляем требование полной упорядоченности оператором <.
template <typename T>
concept RegularTotallyOrdered = std::regular<T>
                             && std::totally_ordered<T>;

/// Предполагается, что вершину графа представляет
/// регулярный объект из упорядоченного множества значений,
/// такой как число, указатель или строка.
template <typename T>
concept VertexHandle = RegularTotallyOrdered<T>;

}

#endif//VERTEX_LIKE_HPP
