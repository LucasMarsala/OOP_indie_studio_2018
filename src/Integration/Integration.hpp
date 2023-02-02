//
// Created by njoachim on 10/06/19.
//

#ifndef OOP_INDIE_STUDIO_2018_INTEGRATION_HPP
#define OOP_INDIE_STUDIO_2018_INTEGRATION_HPP

#include "../../include/irrlicht/irrlicht.h"
#include "../../include/irrlicht/driverChoice.h"
#include "../../include/irrlicht/IEventReceiver.h"
#include "../../SFML/include/SFML/Audio.hpp"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "sfml-audio.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#endif //OOP_INDIE_STUDIO_2018_INTEGRATION_HPP
