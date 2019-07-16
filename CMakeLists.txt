cmake_minimum_required(VERSION 3.13)

project(caster LANGUAGES CXX VERSION 1.0.0)

option(CASTER_BUILD_EXAMPLE "whether to build example code(s)" OFF)

add_subdirectory(include)

if(CASTER_BUILD_EXAMPLE OR (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    add_subdirectory(example)
endif()
