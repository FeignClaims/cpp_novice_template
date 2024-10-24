if(Qt6_FOUND)
  add_library(graph_lib)
  target_sources(graph_lib
    PRIVATE
    include/Gui_private.h
    include/Image_private.h
    src/Colormap.cpp
    src/Graph.cpp
    src/GUI.cpp
    src/Simple_window.cpp
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
    wrapped_qt
  )
else()
  add_library(graph_lib INTERFACE)
  target_include_system_directories(graph_lib
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/fake_include>
    $<INSTALL_INTERFACE:fake_include>
  )

  target_link_libraries(graph_lib
    INTERFACE
    ppp
    wrapped_qt
  )
endif()