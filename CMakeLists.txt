cmake_minimum_required(VERSION 3.25)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(fix_msvc)
include(enable_cpp_module NO_POLICY_SCOPE)
include(cpp_novice_fetch_project_options)

project(cpp_novice LANGUAGES C CXX)

include(check_latest_cppstd)
include(cpp_novice_custom_project_options)
include(detect_std_module)
include(add_program)
include(qt)
add_subdirectory(support)

# -----------------------------------------------------------------------------------------------------------------------
add_program_options(
  DEPENDENCIES

  LIBRARIES
  support

  INCLUDES
  include
)

# ------------------------------------------------------------------------------------------------------------------------
if(Qt6_FOUND)
  add_program(example_gui
    src/example_gui/main.cpp
  )
endif()

# ------------------------------------------------------------------------------------------------------------------------
add_program(test
  test/main.cpp
)
add_program(example_single
  src/example_single/main.cpp
)
add_program(example_multiple
  src/example_multiple/main.cpp
  src/example_multiple/hello.cpp
)