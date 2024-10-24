add_library(wrapped_qt INTERFACE)

if(Qt6_FOUND)
  target_link_system_libraries(wrapped_qt
    INTERFACE
    Qt6::Widgets
  )
else()
  target_include_system_directories(wrapped_qt
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/fake_include>
    $<INSTALL_INTERFACE:fake_include>
  )
endif()