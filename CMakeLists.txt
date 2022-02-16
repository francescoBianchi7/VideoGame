cmake_minimum_required(VERSION 3.20)
project(VideoGame)

set(CMAKE_CXX_STANDARD 14)

add_executable(VideoGame source/main.cpp source/GameEngine.cpp headers/GameEngine.h states/State.cpp states/State.h states/GameState.cpp states/GameState.h entities/Entity.cpp entities/Entity.h states/MainMenuState.cpp states/MainMenuState.h source/GUI.cpp headers/GUI.h entities/GameCharacter.cpp entities/GameCharacter.h Components/MovementComponent.cpp Components/MovementComponent.h Components/AnimationComponent.cpp Components/AnimationComponent.h states/EditorState.cpp states/EditorState.h Components/HitboxComponent.cpp Components/HitboxComponent.h GUI/PauseMenu.cpp GUI/PauseMenu.h states/SettingState.cpp states/SettingState.h Tiles/Tile.cpp Tiles/Tile.h Map/TileMap.cpp Map/TileMap.h)
target_precompile_headers(VideoGame PRIVATE${headers/PreCompHeaders.h})

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