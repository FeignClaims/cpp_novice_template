cmake_minimum_required(VERSION 3.25)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(fix_msvc)
include(cpp_novice_fetch_project_options)

project(cpp_novice LANGUAGES CXX)

include(ppp_check_compiler)
include(cpp_novice_custom_project_options)
include(add_program)
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
add_program(test
  test/main.cpp
)
add_program(example_gui
  src/example_gui/Graph.cpp
  src/example_gui/Gui.cpp
  src/example_gui/Main.cpp
  src/example_gui/Window.cpp
)
add_program(example_single
  src/example_single/main.cpp
)
add_program(example_multiple
  src/example_multiple/main.cpp
  src/example_multiple/hello.cpp
)