find_package(Python3 REQUIRED COMPONENTS Development.Module)

add_library(rd_03d_parser_python MODULE
    rd_03d_parser_module.c
    py_rd_03d_parser.c
)

target_link_libraries(rd_03d_parser_python
    PRIVATE
        rd_03d_parser
        Python3::Module
)

target_include_directories(rd_03d_parser_python
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
set_target_properties(rd_03d_parser_python PROPERTIES
    PREFIX ""
    OUTPUT_NAME "rd_03d_parser"
)

install(
    TARGETS rd_03d_parser_python
    LIBRARY DESTINATION .
    RUNTIME DESTINATION .
)

install(
    FILES rd_03d_parser.pyi
    DESTINATION .
)
