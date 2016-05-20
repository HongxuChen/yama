cmake_minimum_required(VERSION 2.8)

set(LLVM_SUFFIX "-3.7")
set(CMAKE_C_COMPILER "clang${LLVM_SUFFIX}")
set(CMAKE_CXX_COMPILER "clang++${LLVM_SUFFIX}")


PROJECT(LLVMLearn)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(Llvm REQUIRED)
add_definitions("${LLVM_CFLAGS}")
add_definitions("-O3 -fno-rtti -Wextra -Wno-unused-parameter -ggdb ")

set(MY_LLVM_VERSION "${LLVM_VERSION}")
setup_package_version_variables(MY_LLVM)
message(STATUS "MAJOR: ${MY_LLVM_VERSION_MAJOR}")
message(STATUS "MAJOR: ${MY_LLVM_VERSION_MINOR}")

set(CMAKE_C_COMPILER_ID "Clang")

if ("${CMAKE_GENERATOR}" STREQUAL "Ninja")
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_definitions("-fcolor-diagnostics")
    endif ()
endif ()

set(CMAKE_CXX_FLAGS "-std=c++1y")

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_BINARY_DIR})
include_directories(${LLVM_SRC_ROOT}/tools/clang/include)
include_directories(${LLVM_OBJ_ROOT}/tools/clang/include)

link_directories(${LLVM_LIBRARY_DIR})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(FULL_LLVM_LIBS ${LLVM_SYSTEM_LIBS} ${LLVM_MODULE_LIBS})

configure_file(
        ${CMAKE_SOURCE_DIR}/include/Version.hh.in
        ${CMAKE_BINARY_DIR}/Version.hh
)

# set(CMAKE_VERBOSE_MAKEFILE 1)

# -------------------------------------------------------------------
add_subdirectory(lib)
