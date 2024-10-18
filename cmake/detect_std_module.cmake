# - Detects and enables `import std;`
# This module detects whether the ``import std;`` feature since C++23 is usable in the current toolchain and enables it 
# if possible.
#
# Note that this module should be included after `project(...)`. 
include_guard()

function(_reset_std_module_properties)
  get_target_property(cxx_extensions_property cpp_novice_project_options CXX_EXTENSIONS)

  get_property(targets DIRECTORY "${directory}" PROPERTY BUILDSYSTEM_TARGETS)
  list(FILTER targets INCLUDE REGEX [[__cmake_cxx.*]])

  foreach(target IN LISTS targets)
    if(TARGET ${target})
      target_link_libraries(${target}
        PRIVATE
        cpp_novice_project_options
      )
      set_target_properties(${target}
        PROPERTIES
        CXX_EXTENSIONS ${cxx_extensions_property}
      )
    endif()
  endforeach()
endfunction()

if(23 IN_LIST CMAKE_CXX_COMPILER_IMPORT_STD)
  # FIXME: homebrew clang can't find libc++.modules.json without some manual work,
  # see https://gitlab.kitware.com/cmake/cmake/-/issues/25965
  if(APPLE AND(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang"))
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