cmake_minimum_required(VERSION 3.16)

project(pascc LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/frontend")
file(MAKE_DIRECTORY "${GENERATED_DIR}")

BISON_TARGET(
  PascalParser
  "${CMAKE_CURRENT_SOURCE_DIR}/frontend/pascal_s_parser.y"
  "${GENERATED_DIR}/pascal_s_parser.tab.cpp"
  DEFINES_FILE "${GENERATED_DIR}/pascal_s_parser.tab.h"
)

FLEX_TARGET(
  PascalLexer
  "${CMAKE_CURRENT_SOURCE_DIR}/frontend/pascal_s_lexer.l"
  "${GENERATED_DIR}/pascal_s_lexer.cpp"
)

ADD_FLEX_BISON_DEPENDENCY(PascalLexer PascalParser)

add_executable(
  pascc
  pascal_s_driver.cpp
  frontend/ast.cpp
  semantic/semantic.cpp
  codegen/codegen.cpp
  "${BISON_PascalParser_OUTPUTS}"
  "${FLEX_PascalLexer_OUTPUTS}"
)

add_executable(
  dummy_pascc
  testing/dummy.cpp
)

target_include_directories(
  pascc
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/frontend"
    "${CMAKE_CURRENT_SOURCE_DIR}/semantic"
    "${CMAKE_CURRENT_SOURCE_DIR}/codegen"
    "${GENERATED_DIR}"
)

if(MSVC)
  target_compile_options(pascc PRIVATE /W4)
else()
  target_compile_options(pascc PRIVATE -Wall -Wextra -pedantic)
endif()

set_target_properties(
  pascc
  PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/bin"
)

set_target_properties(
  dummy_pascc
  PROPERTIES
    OUTPUT_NAME "pascc_dummy"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/bin"
)
