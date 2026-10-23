find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(edgegui
    forms/mainwindow.ui
    src/mainwindow.cpp
    src/main.cpp
)

target_link_libraries(edgegui PRIVATE Qt6::Widgets)

set_target_properties(edgegui PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

target_include_directories(edgegui
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../edgelib/include
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(edgegui PRIVATE stdc++exp)
endif()
