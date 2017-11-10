cmake_minimum_required(VERSION 3.8)
project(TankCraft)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Game.h Game.cpp Entity.cpp Entity.h Tank.cpp Tank.h SceneNode.cpp SceneNode.h SpriteNode.cpp SpriteNode.h World.cpp World.h)
add_executable(TankCraft ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(TankCraft ${SFML_LIBRARIES})
endif()