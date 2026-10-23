find_package(doctest QUIET)

if(NOT doctest_FOUND)
    include(FetchContent)

    FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.5.3
    )

    FetchContent_MakeAvailable(doctest)
endif()

file(GLOB EDGELIB_TEST_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
)

add_executable(edgelib_tests EDGELIB_TEST_SOURCES)

target_link_libraries(edgelib_tests PRIVATE doctest::doctest)

add_test(NAME edgelib_tests COMMAND edgelib_tests)
