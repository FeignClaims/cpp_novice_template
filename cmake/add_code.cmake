include_guard()

if(NOT TARGET code_options)
  add_library(code_options INTERFACE)
endif()

function(add_code_options)
  set(options)
  set(one_value_args)
  set(multi_value_args DEPENDENCIES LIBRARIES INCLUDES)

  cmake_parse_arguments(args "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})

  foreach(dependency IN LISTS args_DEPENDENCIES)
    find_package(${dependency} CONFIG REQUIRED)
  endforeach()

  target_link_system_libraries(code_options INTERFACE ${args_LIBRARIES})
  target_include_directories(code_options INTERFACE ${args_INCLUDES})
endfunction()

function(add_code name)
  add_executable(${name})
  target_sources(${name}
    PRIVATE
    ${ARGN}
  )
  target_link_libraries(${name}
    PRIVATE
    cpp_novice_project_options
    cpp_novice_project_warnings
  )
  target_link_system_libraries(${name}
    PRIVATE
    code_options
  )
endfunction()