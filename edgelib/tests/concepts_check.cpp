#include <edgelib/vertex_like.hpp>
#include <edgelib/edge_like.hpp>
#include <edgelib/edge_list.hpp>

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

static_assert(EdgeHandle<int>);
static_assert(EdgeHandle<float>);
static_assert(EdgeHandle<std::string>);
static_assert(EdgeHandle<std::array<int, 10>>);
static_assert(EdgeHandle<void*>);

static_assert(impl::Pair<std::tuple<int, bool>>);
static_assert(
	std::is_same_v<decltype(impl::first(std::tuple<int, bool>{})), int>);
static_assert(
	std::is_same_v<decltype(impl::second(std::tuple<int, bool>{})), bool>);

template <typename T>
concept CheckReq = requires(T& e) {
	{ impl::first(e)  } -> VertexHandle;
	//{ impl::second(e) } -> VertexHandle;
	//{ impl::second(e) } -> std::same_as<decltype(impl::first(e))>;
};

static_assert(VertexHandle<decltype(impl::first(std::tuple<int, int>{}))>);

static_assert(true  == VertexHandlePair<std::tuple<int, int>>);
static_assert(false == VertexHandlePair<std::tuple<int, std::string>>);

static_assert(impl::Triple<std::tuple<int, int, std::string>>);
static_assert(!impl::Pair<std::string> && !impl::Triple<std::string>);

static_assert(true  == VertexEdgeHandleTriple<std::tuple<int, int, std::string>>);
static_assert(false == VertexEdgeHandleTriple<std::tuple<int, std::string, int>>);

static_assert(false == Edge<std::tuple<void*, float>>);

static_assert(true ==  EdgeList<std::array<std::tuple<void*, void*>, 10>>);
static_assert(false == EdgeList<std::array<std::tuple<void*, float>, 10>>);
