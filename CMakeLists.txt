cmake_minimum_required(VERSION 3.25)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(fetch_project_options)

project(cpp_novice LANGUAGES CXX)

include(enable_customized_project_options)
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
add_code(example_gui
  src/example_gui/Graph.cpp
  src/example_gui/Gui.cpp
  src/example_gui/Main.cpp
  src/example_gui/Window.cpp
)
add_code(example_single
  src/example_single/main.cpp
)
add_code(example_multiple
  src/example_multiple/main.cpp
  src/example_multiple/hello.cpp
)