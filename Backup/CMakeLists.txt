cmake_minimum_required(VERSION 3.8)
project(Project)
include_directories(Include)
include_directories(Media)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Main.cpp
        Game.cpp
        Aircraft.cpp
        Application.cpp
        Button.cpp
        Command.cpp
        CommandQueue.cpp
        Component.cpp
        Container.cpp
        DataTables.cpp
        Entity.cpp
        GameOverState.cpp
        GameState.cpp
        Label.cpp
        MenuState.cpp
        PauseState.cpp
        Pickup.cpp
        Player.cpp
        Projectile.cpp
        SceneNode.cpp
        SettingsState.cpp
        SpriteNode.cpp
        TextNode.cpp
        State.cpp
        StateStack.cpp
        TitleState.cpp
        Utility.cpp
        World.cpp)
add_executable(Project ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Project ${SFML_LIBRARIES})
endif()