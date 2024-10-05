include_guard()

macro(_ppp_check_compiler)
  foreach(version RANGE 50 13 -3) # [50, 47, ..., 11]
    if(DEFINED "CMAKE_CXX${version}_STANDARD_COMPILE_OPTION" OR DEFINED "CMAKE_CXX${version}_EXTENSION_COMPILE_OPTION")
      set(CMAKE_CXX_STANDARD "${version}")
      return()
    endif()
  endforeach()

  message(FATAL_ERROR "Your C++ compiler is too old to support C++11. Please update your compiler or IDE.\n"
    "(你的 C++ 编译器太老了不支持 C++11. 请更新你的编译器或者 IDE.)")
endmacro()

_ppp_check_compiler()