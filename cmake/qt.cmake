find_package(Qt6 CONFIG COMPONENTS Widgets)

if(Qt6_FOUND)
  set(CMAKE_AUTOUIC ON)
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTORCC ON)
endif()