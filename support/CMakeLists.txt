add_subdirectory(ppp)
add_subdirectory(wrapped_qt)

add_library(support INTERFACE)
target_link_libraries(support
  INTERFACE
  ppp
  wrapped_qt
)