cmake_minimum_required(VERSION 3.25)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(enable_cpp_module NO_POLICY_SCOPE)
include(cpp_novice_fetch_project_options)

project(cpp_novice LANGUAGES CXX)

include(ppp_check_compiler)
include(detect_std_module)
include(cpp_novice_custom_project_options)
include(add_code)
add_subdirectory(support)

# -----------------------------------------------------------------------------------------------------------------------
add_code_options(
  DEPENDENCIES

  LIBRARIES
  support

  INCLUDES
  include
)

# ------------------------------------------------------------------------------------------------------------------------
add_code(test
  test/main.cpp
)
add_code(example_single
  src/example_single/main.cpp
)
add_code(example_multiple
  src/example_multiple/main.cpp
  src/example_multiple/hello.cpp
)