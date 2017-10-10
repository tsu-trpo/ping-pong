project(${APP_NAME}_tests)

#спсиок тестов
add_executable(${PROJECT_NAME}
    example.cpp
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${LIB_NAME}
    cocos2d
    gtest
)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME} --gtest_color=yes
)

add_custom_target(${PROJECT_NAME}_autorun
    ALL
    ctest --output-on-failure
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
