# - Fetches project_options: https://github.com/aminya/project_options
# This module fetches project_options from the specified repository and tag.
#
# `fetch_project_options(<git_repository> <git_tag (i.e., branch name or tag name)>)`
#
# It is highly recommended to include this module before `project(...)`, which is a must when using `run_vcpkg()` or
# `run_conan()`
include_guard()

macro(fetch_project_options git_repository git_tag)
  include(FetchContent)
  FetchContent_Declare(__project_options
    GIT_REPOSITORY ${git_repository}
    GIT_TAG ${git_tag}
    GIT_SHALLOW true
  )
  FetchContent_MakeAvailable(__project_options)
  include(${__project_options_SOURCE_DIR}/Index.cmake)
  include(${__project_options_SOURCE_DIR}/src/DynamicProjectOptions.cmake)
endmacro()

# Fetch from a mirror of https://github.com/aminya/project_options, since it is difficult to access github in China
fetch_project_options(https://gitee.com/cpp_tutorial/project_options.git v0.35.1)