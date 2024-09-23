# - Fixes msvc toolchain issue
# cmake dosen't set `CMAKE_HOST_SYSTEM_PROCESSOR` before `project(...)`, which led to the failure of msvc configuration
if(DEFINED ENV{PROCESSOR_ARCHITEW6432})
  set(CMAKE_HOST_SYSTEM_PROCESSOR "$ENV{PROCESSOR_ARCHITEW6432}")
elseif(DEFINED ENV{PROCESSOR_ARCHITECTURE})
  set(CMAKE_HOST_SYSTEM_PROCESSOR "$ENV{PROCESSOR_ARCHITECTURE}")
endif()