add_library(edgelib INTERFACE)

# Headers listed as INTERFACE sources are never compiled; this only makes
# IDEs (e.g. Qt Creator) show them in the project tree.
target_sources(edgelib INTERFACE
    include/edgelib/graph.hpp
)

target_include_directories(edgelib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(edgelib INTERFACE cxx_std_23)

if(BUILD_TESTING)
    find_package(doctest QUIET)

    if(NOT doctest_FOUND)
        include(FetchContent)

        # doctest v2.5.3 declares a cmake_minimum_required below 3.5,
        # which CMake 4.x rejects by default.
        set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

        FetchContent_Declare(
            doctest
            GIT_REPOSITORY https://github.com/doctest/doctest.git
            GIT_TAG v2.5.3
        )

        FetchContent_MakeAvailable(doctest)
    endif()

    add_executable(edgelib_tests
        tests/main.cpp
        tests/graph_test.cpp
        tests/edge_list_test.cpp
        include/edgelib/graph.hpp # TODO: remove it
        include/edgelib/edge_like.hpp
        include/edgelib/vertex_like.hpp
        tests/concepts_check.cpp
    )

    target_link_libraries(edgelib_tests PRIVATE edgelib doctest::doctest)

    add_test(NAME edgelib_tests COMMAND edgelib_tests)
endif()
