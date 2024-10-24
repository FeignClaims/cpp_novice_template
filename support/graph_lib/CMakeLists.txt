find_package(fltk CONFIG)

if(fltk_FOUND)
  add_library(graph_lib)
  target_sources(graph_lib
    PRIVATE
    src/Graph.cpp
    src/Gui.cpp
    src/Window.cpp
  )
  target_include_system_directories(graph_lib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )

  target_link_libraries(graph_lib
    PUBLIC
    ppp
    wrapped_fltk
  )
else()
  add_library(graph_lib INTERFACE)
  target_include_system_directories(graph_lib
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/fake_include>
    $<INSTALL_INTERFACE:fake_include>
  )

  target_link_Libraries(graph_lib
    INTERFACE
    ppp
    wrapped_fltk
  )
endif()