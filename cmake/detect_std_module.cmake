include_guard()

function(_reset_std_module_properties)
  get_property(_targets DIRECTORY "${directory}" PROPERTY BUILDSYSTEM_TARGETS)
  list(FILTER _targets INCLUDE REGEX [[__cmake_cxx.*]])

  foreach(target IN LISTS _targets)
    if(TARGET ${std_module_target})
      target_link_libraries(${std_module_target}
          PRIVATE
          cpp_novice_project_options
      )
      set_target_properties(${std_module_target}
          PROPERTIES
        CXX_EXTENSIONS OFF
      )
    endif()
  endforeach()
endfunction()

if(23 IN_LIST CMAKE_CXX_COMPILER_IMPORT_STD)
  # FIXME: homebrew clang can't find libc++.modules.json without some manual work,
  # see https://gitlab.kitware.com/cmake/cmake/-/issues/25965
  if(APPLE AND("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))
    message(STATUS
      "Currently this template dosen't support `import std;` for homebrew clang, as it requires manual fix by novices themselves.\n"
      "  See https://gitlab.kitware.com/cmake/cmake/-/issues/25965 for the workaround.\n"
      "(当前本模板不支持为 homebrew 安装的 clang 提供 `import std;` 支持, 因为它需要初学者自己进行手动修复.)\n"
      "  (请参见 https://gitlab.kitware.com/cmake/cmake/-/issues/25965 获取解决方法.)")
    return()
  endif()

  # Enable importing std module
  set(CMAKE_CXX_MODULE_STD ON)

  # Required because std module's properties are set before `project(...)`,
  # thus before `cpp_novice_fetch_project_options.cmake`
  _reset_std_module_properties()
endif()