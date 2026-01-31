cmake_minimum_required(VERSION 3.14)
project(MyGMockTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_COVERAGE "Enable coverage flags (gcc/clang)" OFF)

if(ENABLE_COVERAGE)
  message(STATUS "Coverage enabled: adding --coverage flags")
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
  else()
    message(WARNING "Coverage option is enabled but compiler is not GCC/Clang - skipping")
  endif()
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(mylib STATIC src/mylib.cpp)
target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(sample_test test/sample_test.cpp)
target_link_libraries(sample_test PRIVATE mylib gmock_main)

add_test(NAME sample_test COMMAND sample_test)
