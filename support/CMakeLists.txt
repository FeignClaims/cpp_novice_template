add_subdirectory(ppp)
add_subdirectory(wrapped_fltk)
add_subdirectory(graph_lib)

add_library(support INTERFACE)
target_link_libraries(support
  INTERFACE
  ppp
  wrapped_fltk
  graph_lib
)