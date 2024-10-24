add_library(wrapped_fltk INTERFACE)

find_package(fltk CONFIG)

if(fltk_FOUND)
  target_include_system_directories(wrapped_fltk
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
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
else()
  target_include_system_directories(wrapped_fltk
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/fake_include>
    $<INSTALL_INTERFACE:fake_include>
  )
endif()