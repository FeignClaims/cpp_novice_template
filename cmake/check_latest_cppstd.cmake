include_guard()

macro(_ppp_check_compiler minimum_version)
  set(steps 20)
  math(EXPR maximum_version "${minimum_version} + ${steps} * 3")

  foreach(version RANGE ${maximum_version} ${steps} -3) # [maximum_version, maximum_version - 3, ..., minimum_version]
    if(DEFINED "CMAKE_CXX${version}_STANDARD_COMPILE_OPTION" OR DEFINED "CMAKE_CXX${version}_EXTENSION_COMPILE_OPTION")
      set(CMAKE_CXX_STANDARD "${version}")
      return()
    endif()
  endforeach()

  message(FATAL_ERROR "Your C++ compiler is too old to support C++${minimum_version}. Please update your compiler or IDE.\n"
    "(你的 C++ 编译器太老了不支持 C++${minimum_version}. 请更新你的编译器或者 IDE.)")
endmacro()

_ppp_check_compiler(20)