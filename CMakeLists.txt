cmake_minimum_required(VERSION 4.0)

project(edge VERSION 0.0.1 LANGUAGES CXX)

# Global C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest) # Defines BUILD_TESTING (ON by default) and calls enable_testing()

find_package(Qt6 REQUIRED COMPONENTS Widgets Test)

qt_standard_project_setup()

add_subdirectory(edgelib)
add_subdirectory(edgegui)
