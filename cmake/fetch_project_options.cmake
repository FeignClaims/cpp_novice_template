# - A macro that fetches project_options
# This module fetches project_options from the specified repository and tag
#
# fetch_project_options(<git_repository>  <git_tag>)
include_guard()

macro(fetch_project_options git_repository git_tag)
  include(FetchContent)
  FetchContent_Declare(_project_options
    GIT_REPOSITORY ${git_repository}
    GIT_TAG ${git_tag}
    GIT_SHALLOW true
  )
  FetchContent_MakeAvailable(_project_options)
  include(${_project_options_SOURCE_DIR}/Index.cmake)
  include(${_project_options_SOURCE_DIR}/src/DynamicProjectOptions.cmake)
endmacro()

fetch_project_options(https://gitee.com/cpp_tutorial/project_options.git v0.35.1)