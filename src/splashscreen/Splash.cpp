/*
** EPITECH PROJECT, 2019
** Credits class
** File description:
** Credits
*/

#include <iostream>
#include "Splash.hpp"
#include "../Exception/Error.hpp"

namespace splashScreen {
    Screen::Screen(IVideoDriver *driver) : _counter(0), _active(true)
    {
        for (int i = 1; i < 92; i++) {
            if (i < 10) {
                std::string str = "ressources/splashscreen/tile00" + std::to_string(i) + ".png";
                ITexture *image = driver->getTexture(str.c_str());
                if (!image)
                    throw ErrorGetTexture("Couldn't open texture from splash");
                _screen.push_back(image);
            } else {
                std::string str = "ressources/splashscreen/tile0" + std::to_string(i) + ".png";
                ITexture *image = driver->getTexture(str.c_str());
                if (!image)
                    throw ErrorGetTexture("Couldn't open texture from splash");
                _screen.push_back(image);
            }
        }
        createMusic();
        _music.play();
    }

    Screen::~Screen()
    {
    }

    bool Screen::isActive(void)
    {
        return _active;
    }

    void Screen::displaySplashscreen(const f32 frameDeltaTime, IVideoDriver *driver)
    {
        static float timecpy = 0;

        timecpy += frameDeltaTime;
        if (_counter >= 91)
            _active = false;
        if (_active == true) {
            driver->draw2DImage(_screen[_counter], position2d<s32>(0,0), rect<s32>(0,0,1920,1080), 0, SColor (255,255,255,255), true);
        }
        if (timecpy > 0.08) {
            _counter++;
            timecpy = 0;
        }
    }

    void Screen::createMusic()
    {
    if (!_music.openFromFile("ressources/music/troll.ogg"))
        throw ErrorGetMusic("Couldn't get music file.\n");
    _music.setVolume(100);
    }
}
