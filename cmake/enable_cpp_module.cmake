# - Enables C++ module
# This module enables the experimental C++ module feature since C++20.
#
# Must be included before `project(...)`
# Copied and edited from https://github.com/BAN-43-32532/cmake-import-std
include_guard()

if(CMAKE_VERSION VERSION_LESS "3.30")
  return()
endif()

# Enable import scanning if supported
cmake_policy(SET CMP0155 NEW)

set(_tmp "${CMAKE_BINARY_DIR}/cmExperimental.cxx")

if(EXISTS "${_tmp}")
  message(STATUS "Using cached cmExperimental.cxx: ${_tmp}.\n"
    "   If you wish to refresh it (e.g. you are using a different CMake version), "
    "please delete this file manually."
  )
else()
  set(_url "https://gh-proxy.org/https://raw.githubusercontent.com/Kitware/CMake/v${CMAKE_VERSION}/Source/cmExperimental.cxx")
  message(STATUS "Downloading cmExperimental.cxx from: ${_url}")
  file(DOWNLOAD "${_url}" "${_tmp}" STATUS _dl_status SHOW_PROGRESS TIMEOUT 15)

  list(GET _dl_status 0 _dl_exit)

  if(NOT _dl_exit EQUAL 0)
    message(FATAL_ERROR
      "Failed to download cmExperimental.cxx.\n"
      "   Download status: ${_dl_status}"
    )
  endif()
endif()

file(READ "${_tmp}" _file_contents)
string(REGEX MATCH
  "\\{[ \t\n\r]*\"CxxImportStd\"[ \t\n\r]*,[ \t\n\r]*\"([0-9a-fA-F-]+)\""
  _match "${_file_contents}"
)

if(NOT _match)
  message(FATAL_ERROR "Failed to extract CxxImportStd GUID from cmExperimental.cxx")
endif()

set(CXX_IMPORT_STD_GUID "${CMAKE_MATCH_1}")

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "${CXX_IMPORT_STD_GUID}")
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "${CXX_IMPORT_STD_GUID}" CACHE STRING "" FORCE)

set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON CACHE BOOL "" FORCE)