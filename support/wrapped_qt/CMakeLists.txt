find_package(Qt6 CONFIG COMPONENTS Core Widgets)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(wrapped_qt INTERFACE)

if(Qt6_FOUND)
  target_link_system_libraries(wrapped_qt
    INTERFACE
    Qt6::Core
    Qt6::Widgets
  )
else()
  target_include_system_directories(wrapped_qt
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
endif()