include_guard()

macro(_add_cppstd_to_conan cppstd)
  find_program(conan_command "conan")

  if(conan_command-NOTFOUND)
    return()
  endif()

  set(setting_file "${CMAKE_BINARY_DIR}/conan/settings_user.yml")

  string(REGEX REPLACE [[\..*]] "" compiler_major_version ${CMAKE_CXX_COMPILER_VERSION})

  if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(compiler "clang")
  elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*")
    set(compiler "gcc")
  endif()

  file(WRITE ${setting_file}
    "compiler:
  ${compiler}:
    version: [\"${compiler_major_version}\"]
    cppstd: [\"${cppstd}\"]
"
  )

  execute_process(
    COMMAND ${conan_command} config install ${setting_file}
  )
endmacro()

macro(_enable_libcxx_for_clang)
  # Make clang installed by homebrew or linuxbrew use libc++ and be able to compile `std::println("Hello C++{}", 23);`
  if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    cmake_path(GET CMAKE_CXX_COMPILER PARENT_PATH compiler_bin_path)
    cmake_path(GET compiler_bin_path PARENT_PATH compiler_root)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -L${compiler_root}/lib -Wl,-rpath,${compiler_root}/lib -Wno-unused-command-line-argument")
  endif()
endmacro()

macro(_ppp_check_compiler minimum_version)
  set(steps 20)
  math(EXPR maximum_version "${minimum_version} + ${steps} * 3")

  foreach(version RANGE ${maximum_version} ${steps} -3) # [maximum_version, maximum_version - 3, ..., minimum_version]
    if(DEFINED "CMAKE_CXX${version}_STANDARD_COMPILE_OPTION" OR DEFINED "CMAKE_CXX${version}_EXTENSION_COMPILE_OPTION")
      set(CMAKE_CXX_STANDARD "${version}")
      _add_cppstd_to_conan("${version}")
      _enable_libcxx_for_clang()
      return()
    endif()
  endforeach()

  message(FATAL_ERROR "Your C++ compiler is too old to support C++${minimum_version}. Please update your compiler or IDE.\n"
    "(你的 C++ 编译器太老了不支持 C++${minimum_version}. 请更新你的编译器或者 IDE.)")
endmacro()

_ppp_check_compiler(20)