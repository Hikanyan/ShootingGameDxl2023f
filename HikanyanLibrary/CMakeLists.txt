cmake_minimum_required(VERSION 3.20)

project(HikanyanLibrary VERSION 0.1.0 LANGUAGES CXX)

option(HIKANYAN_BUILD_TESTS "Build HikanyanLibrary tests" ON)

add_library(hikanyan_library
    src/debug.cpp
    src/game_object.cpp
    src/scene_manager.cpp
)

add_library(Hikanyan::Library ALIAS hikanyan_library)

target_compile_features(hikanyan_library PUBLIC cxx_std_20)

target_include_directories(hikanyan_library
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if(MSVC)
    target_compile_options(hikanyan_library PRIVATE /W4 /permissive-)
else()
    target_compile_options(hikanyan_library PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(HIKANYAN_BUILD_TESTS)
    enable_testing()
    add_executable(hikanyan_library_tests tests/library_tests.cpp)
    target_link_libraries(hikanyan_library_tests PRIVATE Hikanyan::Library)
    add_test(NAME hikanyan_library_tests COMMAND hikanyan_library_tests)
endif()
