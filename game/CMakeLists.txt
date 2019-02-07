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
cmake_minimum_required(VERSION 3.1)

set(APP_NAME pong)
set(LIB_NAME ${APP_NAME}_lib)
project (${APP_NAME})

set(MAIN_CPP
    proj.linux/main.cpp
)

set(GAME_SRC
        Classes/AppDelegate.cpp
        Classes/GameScene.cpp
        Classes/Ball.cpp
        Classes/Paddle.cpp
        Classes/PaddleController.cpp
        Classes/VisibleRect.cpp
        Classes/AudioPlayer.cpp
        Classes/Brick.cpp
        Classes/ContactHelper.cpp
        Classes/Score.cpp
        Classes/BonusDropper.cpp
        ${PLATFORM_SPECIFIC_SRC}
        ${MAIN_CPP}
        )


# MyGame
if( ANDROID )
    add_library(${APP_NAME} SHARED ${GAME_SRC})
    IF(CMAKE_BUILD_TYPE MATCHES RELEASE)
        ADD_CUSTOM_COMMAND(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    ENDIF()
else()
    add_executable(${APP_NAME} ${GAME_SRC})
endif()

target_include_directories(${APP_NAME} PRIVATE
    Classes
)
target_link_libraries(${APP_NAME} PRIVATE
    cocos2d
)

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

if ( WIN32 )
  #also copying dlls to binary directory for the executable to run
  pre_build(${APP_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
	)
elseif( ANDROID )
else()
  pre_build(${APP_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
    )
endif()

# включаем тесты
# enable_testing()
# add_subdirectory(tests)
