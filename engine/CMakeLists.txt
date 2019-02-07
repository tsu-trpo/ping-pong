#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/
cmake_policy(SET CMP0017 NEW)

cmake_minimum_required(VERSION 3.1)

set(COCOS2D_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)

# Configure libcocos2d
set(BUILD_CPP_EMPTY_TEST OFF CACHE BOOL "turn off build cpp-empty-test")
set(BUILD_CPP_TESTS OFF CACHE BOOL "turn off build cpp-tests")
set(BUILD_LUA_LIBS OFF CACHE BOOL "turn off build lua related targets")
set(BUILD_JS_LIBS OFF CACHE BOOL "turn off build js related targets")
add_subdirectory(${COCOS2D_ROOT})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${COCOS2D_ROOT}/cmake/Modules/")
include(CocosBuildHelpers)

# Some macro definitions
if(WINDOWS)
  if(BUILD_SHARED_LIBS)
    target_compile_definitions(cocos2d PUBLIC
        _USRDLL
        _EXPORT_DLL_
        _USEGUIDLL
        _USREXDLL
        _USRSTUDIODLL
    )
  else()
    target_compile_definitions(cocos2d PUBLIC
        CC_STATIC
    )
  endif()

  target_compile_definitions(cocos2d PUBLIC
      COCOS2DXWIN32_EXPORTS
      _WINDOWS
      WIN32
      _WIN32
  )
  set(PLATFORM_FOLDER win32)
elseif(MACOSX OR APPLE)
  target_compile_definitions(cocos2d PUBLIC
      CC_TARGET_OS_MAC
      USE_FILE32API
  )
  set(PLATFORM_FOLDER mac)
elseif(LINUX)
  target_compile_definitions(cocos2d PUBLIC
      LINUX 
  )
  set(PLATFORM_FOLDER linux)
elseif(ANDROID)
  target_compile_definitions(cocos2d PUBLIC
      USE_FILE32API
  )
  set(PLATFORM_FOLDER android)
else()
  message( FATAL_ERROR "Unsupported platform, CMake will exit" )
endif()


# Compiler options
if(MSVC)
  # скорее всего этот блок сломался,
  # нужно его актуализировать
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrt /NODEFAULTLIB:libcmt")
  else()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:libcmt")
  endif()
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS
                  -wd4251 -wd4244 -wd4334 -wd4005 -wd4820 -wd4710
                  -wd4514 -wd4056 -wd4996 -wd4099)
else()
  if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(cocos2d PUBLIC
        USE_FILE32API=1
    )
  endif()
endif(MSVC)

target_include_directories(cocos2d PUBLIC
  /usr/local/include/GLFW
  /usr/include/GLFW
  ${COCOS2D_ROOT}
  ${COCOS2D_ROOT}/cocos
  ${COCOS2D_ROOT}/external
  ${COCOS2D_ROOT}/cocos/platform
  ${COCOS2D_ROOT}/cocos/audio/include/
)
if ( WIN32 )
  target_include_directories(cocos2d INTERFACE
    ${COCOS2D_ROOT}/external/glfw3/include/win32
    ${COCOS2D_ROOT}/external/win32-specific/gles/include/OGLES
  )
endif( WIN32 )

if ( WIN32 )
  #also copying dlls to binary directory for the executable to run
  pre_build(${APP_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
  )
endif()
