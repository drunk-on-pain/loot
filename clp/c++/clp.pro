#
#   Copyright (C) 2012  Robert Lohr
#
#   This library is free software; you can redistribute it and/or
#   modify it under the terms of the GNU Lesser General Public
#   License as published by the Free Software Foundation; either
#   version 2.1 of the License, or (at your option) any later version.
#
#   This library is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public
#   License along with this library; if not, write to the Free Software
#   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
#

TARGET = loot_clp

TEMPLATE = lib
CONFIG += dll c++11
QT -= gui core

QMAKE_CXXFLAGS += -mmacosx-version-min=10.7 -stdlib=libc++
LIBS += -lc++

HEADERS += \
    option.h \
    args.h \
    error.h \
    result.h \
    parser.h

SOURCES += \
    option.cpp \
    error.cpp \
    result.cpp \
    parser.cpp
