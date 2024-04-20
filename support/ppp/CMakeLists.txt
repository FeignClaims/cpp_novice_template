if(CMAKE_VERSION VERSION_LESS 3.29.20240416)
  add_library(ppp INTERFACE)
  target_include_system_directories(ppp
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
  target_compile_features(ppp
    INTERFACE
    cxx_std_20 # FIXME: should we force cxx_std_23 instead?
  )
else()
  set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
  set(CMAKE_CXX_MODULE_STD ON)

  add_library(ppp STATIC)
  target_sources(ppp
    PUBLIC
    FILE_SET CXX_MODULES
    FILES src/PPP.ixx
  )
  target_include_system_directories(ppp
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
  target_compile_features(ppp
    PUBLIC
    cxx_std_20 # FIXME: should we force cxx_std_23 instead?
  )

  target_compile_definitions(ppp
    PUBLIC
    ppp_MODULE
  )
endif()