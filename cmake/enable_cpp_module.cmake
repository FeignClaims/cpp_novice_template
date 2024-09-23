# - Enables C++ module
# This module enables the experimental C++ module feature since C++20.
#
# Note that this module should be included before `project(...)` with the `NO_POLICY_SCOPE` argument.
include_guard()

# Enable import scanning if supported
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.28)
  cmake_policy(SET CMP0155 NEW)
endif()

# Enable the experimental feature of importing std module
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.29.20240416)
  set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
endif()