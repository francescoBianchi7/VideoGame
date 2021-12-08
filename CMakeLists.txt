cmake_minimum_required(VERSION 3.20)
project(VideoGame)

set(CMAKE_CXX_STANDARD 14)

add_executable(VideoGame source/main.cpp source/GameEngine.cpp headers/GameEngine.h states/State.cpp states/State.h states/GameState.cpp states/GameState.h entities/Entity.cpp entities/Entity.h states/MainMenuState.cpp states/MainMenuState.h source/Button.cpp headers/Button.h)

include_directories(headers c:/SFML/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(VideoGame ${SFML_LIBRARIES})
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

#copy dlls to build directories
IF(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()