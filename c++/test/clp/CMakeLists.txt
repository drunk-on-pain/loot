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

set(CLP_TEST_SOURCES main.cpp 
					 test.cpp)
# Workaround for OS X Mavericks (and maybe earlier)
if (${CMAKE_COMPILER_IS_GNUCXX} AND ${APPLE})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${GTEST_INCLUDE_DIRS}")
endif (${CMAKE_COMPILER_IS_GNUCXX} AND ${APPLE})

include_directories("../../include" ${GTEST_INCLUDE_DIRS})

add_definitions(-DGTEST_HAS_TR1_TUPLE=0)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_executable(loot-clp-test ${CLP_TEST_SOURCES})

target_link_libraries(loot-clp-test loot-clp ${GTEST_LIBRARY})