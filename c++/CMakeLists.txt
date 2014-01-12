#
#   Copyright (c) 2013, Robert Lohr
#   All rights reserved.
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions are met:
#
#   1. Redistributions of source code must retain the above copyright notice, this
#      list of conditions and the following disclaimer.
#   2. Redistributions in binary form must reproduce the above copyright notice,
#      this list of conditions and the following disclaimer in the documentation
#      and/or other materials provided with the distribution.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
#   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
#   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
#   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
#   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#   The views and conclusions contained in the software and documentation are those
#   of the authors and should not be interpreted as representing official policies,
#   either expressed or implied, of the FreeBSD Project.
#

cmake_minimum_required(VERSION 2.8)

project(loot)


# Check compiler features

# Tests ans sets options for compilers
include(cmake_cxx11/CheckCXX11Features.cmake)
include(CheckIncludeFileCXX)

check_include_file_cxx("initializer_list" HAVE_INITIALIZER_LIST)

foreach (flag ${CXX11_FEATURE_LIST})
    set(${flag} 1)
endforeach (flag ${CXX11_FEATURE_LIST})

if (${MSVC})
    set(MSVC_COMPILER 1)
endif (${MSVC})

configure_file(${CMAKE_HOME_DIRECTORY}/config.h.in ${CMAKE_HOME_DIRECTORY}/include/config.h)

message(STATUS ${CMAKE_CXX_FLAGS})
message(STATUS ${CMAKE_SHARED_LINKER_FLAGS})


# 3rd party dependencies
find_package(GTest)


# Project configuration

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory("${CMAKE_SOURCE_DIR}/src/clp")

message(STATUS ${CMAKE_GENERATOR})

if (${GTEST_FOUND})
    message(STATUS "GTest found: Create test suite")
    message(STATUS ${GTEST_INCLUDE_DIRS})
    
    add_subdirectory("${CMAKE_SOURCE_DIR}/test/clp")
endif (${GTEST_FOUND})