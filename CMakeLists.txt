cmake_minimum_required(VERSION 3.11)

project(bomberman)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/Irrlicht" ${CMAKE_MODULE_PATH})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
#set(IRRLICHT_LIBRARY "${PROJECT_SOURCE_DIR}/Irrlicht/Irrlicht.lib" ${IRRLICHT_LIBRARY})
set(CMAKE_EXE_LINKER_FLAGS "-D_GNU_SOURCE -W -std=c++17 -Wextra -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio -lIrrlicht")
#set(SFML-2.5.0_LIBRARY_AUDIO "${PROJECT_SOURCE_DIR}/SFML-2.5.0/lib/sfml-audio.lib" ${SFML-2.5.0_LIBRARY_AUDIO})
#set(SFML-2.5.0_LIBRARY_SYSTEM "${PROJECT_SOURCE_DIR}/SFML-2.5.0/lib/sfml-system.lib" ${SFML-2.5.0_LIBRARY_SYSTEM})
#set(SFML-2.5.0_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/SFML-2.5.0/include" ${SFML-2.5.0_INCLUDE_DIR})

add_executable(bomberman main.cpp
                src/Map/Map.cpp
                src/Blocks/ABlock.cpp
                src/GUI/EventReceiver.cpp
                src/APlayers/APlayers.cpp
                src/Characters/Mario/Mario.cpp
                src/Characters/Luigi/Luigi.cpp
                src/Characters/Yoshi/Yoshi.cpp
                src/Characters/Wario/Wario.cpp
                src/Properties/Properties.cpp
                src/Bomb/Bomb.cpp src/Bomb/Bomb.hpp
                src/GUI/MainMenu.cpp
                src/Window/Window.cpp
                src/PowerUp/APowerUp.cpp
                src/PowerUp/Speed.cpp
                src/PowerUp/Stock.cpp
                src/PowerUp/Power.cpp
                src/GUI/Settings.cpp
                src/GUI/MenuButton.cpp
                src/GUI/Credits.cpp
                src/GUI/SelectingEvent.cpp
                src/splashscreen/Splash.cpp
                src/GUI/InGameMenu.cpp
                src/Game/Game.cpp
                src/Exception/Error.cpp
                src/GUI/LoadGame.cpp
                src/AI/AAi.cpp)

#find_package(Irrlicht REQUIRED)
#target_link_libraries(bomberman ${IRRLICHT_LIBRARY})
#target_link_libraries(bomberman ${SFML-2.5.0_LIBRARY_AUDIO})
#target_link_libraries(bomberman ${SFML-2.5.0_LIBRARY_SYSTEM})
#target_include_directories(bomberman PRIVATE ${IRRLICHT_INCLUDE_DIR})
#target_include_directories(bomberman PRIVATE ${SFML-2.5.0_INCLUDE_DIR})
