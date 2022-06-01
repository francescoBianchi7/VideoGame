cmake_minimum_required(VERSION 3.5)
add_subdirectory(./lib/googletest)

set(gtest_SOURCE_DIR, ./lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp CollisionTEST.cpp)
add_executable(runTests ${TEST_SOURCE_FILES})
target_link_libraries(runTests gtest gtest_main core)
target_precompile_headers(runTests PRIVATE${headers/PreCompHeaders.h})
include_directories(headers c:/SFML/include)
#SFML
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(runTests ${SFML_LIBRARIES})
endif()

file(COPY gtest_assets DESTINATION ${CMAKE_BINARY_DIR})

#copy dlls to build directories
IF(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()