#include <edgelib/vertex_like.hpp>
#include <edgelib/edge_like.hpp>

#include <tuple>
#include <array>
#include <string>

using namespace edgelib;

static_assert(RegularTotallyOrdered<int>);
static_assert(RegularTotallyOrdered<float>);
static_assert(RegularTotallyOrdered<std::string>);
static_assert(RegularTotallyOrdered<std::array<int, 10>>);
static_assert(RegularTotallyOrdered<void*>);

static_assert(VertexHandle<int>);
static_assert(VertexHandle<float>);
static_assert(VertexHandle<std::string>);
static_assert(VertexHandle<std::array<int, 10>>);
static_assert(VertexHandle<void*>);

