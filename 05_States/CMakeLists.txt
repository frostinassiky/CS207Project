
cmake_minimum_required(VERSION 3.8)
project(TankCraft)

include_directories(Include)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
		Source/Main.cpp
		Source/LoadingState.cpp
		Source/ParallelTask.cpp
		Source/Aircraft.cpp
		Source/Application.cpp
		Source/Command.cpp
		Source/CommandQueue.cpp
		Source/Entity.cpp
		Source/GameState.cpp
		Source/MenuState.cpp
		Source/PauseState.cpp
		Source/Player.cpp
		Source/SceneNode.cpp
		Source/SpriteNode.cpp
		Source/State.cpp
		Source/StateStack.cpp
		Source/TitleState.cpp
		Source/Utility.cpp
		Source/World.cpp Source/Component.cpp Source/Component.h Source/Container.cpp Source/Container.h Source/Button.cpp Source/Button.h Source/Label.cpp Source/Label.h)
add_executable(TankCraft ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(TankCraft ${SFML_LIBRARIES})
endif()