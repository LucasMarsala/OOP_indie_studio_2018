cmake_minimum_required(VERSION 3.11)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/Irrlicht" ${CMAKE_MODULE_PATH})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set(IRRLICHT_LIBRARY "${PROJECT_SOURCE_DIR}/Irrlicht/Irrlicht.lib" ${IRRLICHT_LIBRARY})
set(CMAKE_EXE_LINKER_FLAGS "-W -Wall -Wextra -lIrrlicht -lsfml-audio -lsfml-system")
set(SFML_LIBRARY_AUDIO "${PROJECT_SOURCE_DIR}/SFML/lib/sfml-audio.lib" ${SFML_LIBRARY_AUDIO})
set(SFML_LIBRARY_SYSTEM "${PROJECT_SOURCE_DIR}/SFML/lib/sfml-system.lib" ${SFML_LIBRARY_SYSTEM})
set(SFML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/SFML/include" ${SFML_INCLUDE_DIR})

add_executable(bomberman main.cpp 
                src/Map/Map.cpp src/Map/Map.hpp 
                src/Blocks/ABlock.cpp src/Blocks/ABlock.hpp
                src/Integration/Integration.hpp
        src/GUI/EventReceiver.cpp src/GUI/EventReceiver.hpp
                src/APlayers/APlayers.cpp src/APlayers/APlayers.hpp
                src/Characters/Mario/Mario.cpp src/Characters/Mario/Mario.hpp
                src/Characters/Luigi/Luigi.cpp src/Characters/Luigi/Luigi.hpp
                src/Characters/Yoshi/Yoshi.cpp src/Characters/Yoshi/Yoshi.hpp
                src/Characters/Wario/Wario.cpp src/Characters/Wario/Wario.hpp
                src/Properties/Properties.cpp src/Properties/Properties.hpp
                src/Bomb/Bomb.cpp src/Bomb/Bomb.hpp
        src/GUI/MainMenu.cpp src/GUI/MainMenu.hpp
        src/Window/Window.cpp src/Window/Window.hpp
                src/PowerUp/APowerUp.cpp src/PowerUp/APowerUp.hpp
                src/PowerUp/Speed.cpp src/PowerUp/Speed.hpp
                src/PowerUp/Stock.cpp src/PowerUp/Stock.hpp
                src/PowerUp/Power.cpp src/PowerUp/Power.hpp
        src/GUI/Settings.cpp src/GUI/Settings.hpp
        src/GUI/MenuButton.cpp src/GUI/MenuButton.hpp
        src/GUI/Credits.cpp src/GUI/Credits.hpp
        src/GUI/SelectingEvent.cpp src/GUI/SelectingEvent.hpp
                src/splashscreen/Splash.cpp src/splashscreen/Splash.hpp
        src/GUI/InGameMenu.cpp src/GUI/InGameMenu.hpp
                src/Game/Game.cpp src/Game/Game.hpp
                src/Exception/Error.cpp src/Exception/Error.hpp
        src/GUI/LoadGame.cpp src/GUI/LoadGame.hpp
                src/AI/AAi.cpp src/AI/AAi.hpp)

find_package(Irrlicht REQUIRED)
target_link_libraries(bomberman ${IRRLICHT_LIBRARY})
target_link_libraries(bomberman ${SFML_LIBRARY_AUDIO})
target_link_libraries(bomberman ${SFML_LIBRARY_SYSTEM})
target_include_directories(bomberman PRIVATE ${IRRLICHT_INCLUDE_DIR})
target_include_directories(bomberman PRIVATE ${SFML_INCLUDE_DIR})
