# - Customization point for project_options: https://github.com/aminya/project_options
# This module customizes and runs `dynamic_project_options(...)`.
#
# Note that this module should be included this module after `project(...)`.
include_guard()

if(NOT __project_options_POPULATED)
  message(FATAL_ERROR "please `include(_fetch_project_options)`")
endif()

set(ENABLE_DEVELOPER_MODE ON)
set(WARNINGS_AS_ERRORS_DEFAULT OFF)

# tools
set(ENABLE_CONAN_DEFAULT OFF)
set(ENABLE_CACHE_DEFAULT OFF)
set(ENABLE_CLANG_TIDY_DEFAULT OFF)
set(ENABLE_CPPCHECK_DEFAULT OFF)
set(ENABLE_INCLUDE_WHAT_YOU_USE_DEFAULT OFF)

# compile_commands.json
set(ENABLE_COMPILE_COMMANDS_SYMLINK_DEFAULT ON)

# hardening
set(ENABLE_CONTROL_FLOW_PROTECTION_DEFAULT ON)
set(ENABLE_ELF_PROTECTION_DEFAULT OFF)
set(ENABLE_OVERFLOW_PROTECTION_DEFAULT ON)
set(ENABLE_RUNTIME_SYMBOLS_RESOLUTION_DEFAULT ON)

if(WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(ENABLE_STACK_PROTECTION_DEFAULT OFF)
else()
  set(ENABLE_STACK_PROTECTION_DEFAULT ON)
endif()

# optimization
set(ENABLE_INTERPROCEDURAL_OPTIMIZATION_DEFAULT ON)
set(ENABLE_NATIVE_OPTIMIZATION_DEFAULT ON)

dynamic_project_options(
  PREFIX
  "cpp_novice" # set a prefix in case this project is used as a subproject

  MSVC_WARNINGS
  /W4 # Baseline reasonable warnings
  /permissive- # standards conformance mode for MSVC compiler.
  /w14242 # 'identifier': conversion from 'type1' to 'type1', possible loss of data
  /w14254 # 'operator': conversion from 'type1:field_bits' to 'type2:field_bits', possible loss of data
  /w14263 # 'function': member function does not override any base class virtual member function
  /w14265 # 'classname': class has virtual functions, but destructor is not virtual instances of this class may not be destructed correctly
  /w14287 # 'operator': unsigned/negative constant mismatch
  /w14296 # 'operator': expression is always 'boolean_value'
  /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
  /w14545 # expression before comma evaluates to a function which is missing an argument list
  /w14546 # function call before comma missing argument list
  /w14547 # 'operator': operator before comma has no effect; expected operator with side-effect
  /w14549 # 'operator': operator before comma has no effect; did you intend 'operator'?
  /w14555 # expression has no effect; expected expression with side- effect
  /w14619 # pragma warning: there is no warning number 'number'
  /w14640 # Enable warning on thread un-safe static member initialization
  /w14826 # Conversion from 'type1' to 'type_2' is sign-extended. This may cause unexpected runtime behavior.
  /w14905 # wide string literal cast to 'LPSTR'
  /w14906 # string literal cast to 'LPWSTR'
  /w14928 # illegal copy-initialization; more than one user-defined conversion has been implicitly applied
  /we4289 # nonstandard extension used: 'variable': loop control variable declared in the for-loop is used outside the for-loop scope

  CLANG_WARNINGS
  -Wall
  -Wextra # reasonable and standard
  -Wextra-semi # warn about semicolon after in-class function definition
  -Wcast-align # warn for potential performance problem casts
  -Wdouble-promotion # warn if float is implicit promoted to double
  -Wformat=2 # warn on security issues around functions that format output (ie printf)
  -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
  -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
  -Wmissing-noreturn
  -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
  -Wnull-dereference # warn if a null dereference is detected
  -Wold-style-cast # warn for c-style casts
  -Woverloaded-virtual # warn if you overload (not override) a virtual function
  -Wpacked
  -Wpedantic # warn if non-standard C++ is used
  -Wshadow # warn the user if a variable declaration shadows one from a parent context
  -Wno-sign-conversion # disable integral sign conversion checks
  -Wunused # warn on anything being unused
  -ftemplate-backtrace-limit=0
  -fconstexpr-backtrace-limit=0

  GCC_WARNINGS
  -Wall
  -Wextra
  -Wextra-semi
  -Wcast-align
  -Wdouble-promotion
  -Wduplicated-cond # warn if if / else chain has duplicated conditions
  -Wduplicated-branches # warn if if / else branches have duplicated code
  -Wformat=2
  -Wimplicit-fallthrough
  -Wmisleading-indentation
  -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
  -Wnon-virtual-dtor
  -Wnull-dereference
  -Wold-style-cast
  -Woverloaded-virtual
  -Wpedantic
  -Wshadow
  -Wno-sign-conversion # disable integral sign conversion checks
  -Wunused
  -Wuseless-cast # warn if you perform a cast to the same type
  -ftemplate-backtrace-limit=0
)
