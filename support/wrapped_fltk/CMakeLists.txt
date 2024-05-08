add_library(wrapped_fltk INTERFACE)
target_include_system_directories(wrapped_fltk
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
find_package(fltk CONFIG)

if(fltk_FOUND)
  target_compile_definitions(wrapped_fltk
    INTERFACE
    CPP_NOVICE_FLTK_FOUND
  )

  if(TARGET fltk::fltk) # fltk installed by conan
    target_link_system_libraries(wrapped_fltk
      INTERFACE
      fltk::fltk
    )
  else() # fltk installed by vcpkg
    target_link_system_libraries(wrapped_fltk
      INTERFACE
      fltk
      fltk_images
    )
  endif()
endif()