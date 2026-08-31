cmake_minimum_required(VERSION 3.20)

project(rd_03d_parser LANGUAGES C)

option(RD_03D_BUILD_PYTHON "Build Python bindings" OFF)

add_library(target_parser
    src/target_parser.c
)

target_include_directories(target_parser
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(rd_03d_parser
    src/rd_03d_parser.c
)

target_link_libraries(rd_03d_parser PRIVATE target_parser)

target_include_directories(rd_03d_parser
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)


if(RD_03D_BUILD_PYTHON)
    add_subdirectory(bindings/python)
endif()
