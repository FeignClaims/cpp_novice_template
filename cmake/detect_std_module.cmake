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
  if(APPLE)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
      message(STATUS
        "AppleClang does not currently support `import std;`. Please use Homebrew Clang instead.\n"
        "(AppleClang 目前不支持 `import std;`，请使用 Homebrew 安装的 Clang。)")
      return()
    endif()

    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
      if(CMAKE_VERSION VERSION_LESS "4.2")
        message(STATUS
          "This template requires CMake 4.2 or newer to enable `import std;` with Homebrew Clang.\n"
          "  Current CMake version: ${CMAKE_VERSION}. Please upgrade CMake.\n"
          "(本模板使用 Homebrew Clang 启用 `import std;` 需要 CMake 4.2 或更高版本。\n"
          "  当前 CMake 版本为 ${CMAKE_VERSION}，请升级 CMake。)")
        return()
      endif()

      # Homebrew's Clang may return only "libc++.modules.json" from
      # -print-file-name, even though the metadata is installed in lib/c++.
      # CMake 4.2+ lets us correct that path before generating the std targets.
      if(23 IN_LIST CMAKE_CXX_COMPILER_IMPORT_STD
        AND CMAKE_CXX_STDLIB_MODULES_JSON STREQUAL "libc++.modules.json")
        # Resolve symlinks so this also works with Homebrew's bin/clang++ link.
        file(REAL_PATH "${CMAKE_CXX_COMPILER}" _clang_real_path)
        cmake_path(GET _clang_real_path PARENT_PATH _clang_bin_dir)
        cmake_path(GET _clang_bin_dir PARENT_PATH _clang_prefix)
        set(_libcxx_modules_json "${_clang_prefix}/lib/c++/libc++.modules.json")

        if(EXISTS "${_libcxx_modules_json}")
          set(CMAKE_CXX_STDLIB_MODULES_JSON "${_libcxx_modules_json}")
          message(STATUS "Using libc++ module metadata: ${CMAKE_CXX_STDLIB_MODULES_JSON}")
        endif()
      endif()
    endif()
  endif()

  # Enable importing std module
  set(CMAKE_CXX_MODULE_STD ON CACHE BOOL "" FORCE)

  # Required because std module's properties are set before `project(...)`,
  # thus before `cpp_novice_fetch_project_options.cmake`
  _reset_std_module_properties()
endif()
