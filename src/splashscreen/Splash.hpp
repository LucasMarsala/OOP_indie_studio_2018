/*
** EPITECH PROJECT, 2019
** Credits class
** File description:
** Credits
*/


#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include "../Integration/Integration.hpp"
#include <SFML/Audio.hpp>
#include <vector>
#include <string>


using namespace irr;
using namespace core;
using namespace video;
using namespace gui;

namespace splashScreen {
    class Screen {
        public:
            explicit Screen(IVideoDriver *);
    		Screen(Screen const &) noexcept = delete;
    		explicit Screen(Screen &&) noexcept = delete;
            ~Screen() noexcept;
            bool isActive();
            void displaySplashscreen(const f32, IVideoDriver *);
            void createMusic();

        private:
            std::vector<ITexture *> _screen;
            bool _active;
            int _counter;
            sf::Music _music;
    };
}
#endif /* !CREDITS_HPP_ */
