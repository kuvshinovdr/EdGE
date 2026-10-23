qt_add_executable(edgegui
    forms/mainwindow.ui
    src/mainwindow.cpp
    src/main.cpp
    include/mainwindow.hpp
    include/viewmodels/graph_view_model.hpp
)

target_include_directories(edgegui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(edgegui PRIVATE edgelib Qt6::Widgets)

set_target_properties(edgegui PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
    AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/forms"
)

if(BUILD_TESTING)
    qt_add_executable(edgegui_tests
        tests/graph_view_model_test.cpp
    )

    target_include_directories(edgegui_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

    target_link_libraries(edgegui_tests PRIVATE edgelib Qt6::Test Qt6::Core)

    add_test(NAME edgegui_tests COMMAND edgegui_tests)
    set_tests_properties(edgegui_tests PROPERTIES
        ENVIRONMENT "QT_QPA_PLATFORM=offscreen"
    )
endif()
