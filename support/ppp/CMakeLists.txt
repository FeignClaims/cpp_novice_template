if(CMAKE_CXX_MODULE_STD)
  add_library(ppp)
  target_sources(ppp
    PUBLIC
    FILE_SET CXX_MODULES
    FILES src/PPP.ixx
  )
  target_compile_definitions(ppp
    PUBLIC
    PPP_SUPPORT_MODULE
  )

  set(scope PUBLIC)
else()
  add_library(ppp INTERFACE)
  set(scope INTERFACE)
endif()

target_include_system_directories(ppp
  ${scope}
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(ppp
  ${scope}
  cpp_novice_project_options
)