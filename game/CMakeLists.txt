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
        Classes/Life.cpp
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
