cmake_minimum_required(VERSION 4.0)

project(edge VERSION 0.0.1 LANGUAGES CXX)

# Global C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTS "Build the testing suite" ON)

if(BUILD_TESTS)
    include(CTest)
endif()

if(BUILD_TESTS)
# Being header-only the library contains only tests as a build target
    add_subdirectory(edgelib)
endif()

add_subdirectory(edgegui)
