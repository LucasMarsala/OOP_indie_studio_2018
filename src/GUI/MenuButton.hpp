/*
** EPITECH PROJECT, 2019
** Menu
** File description:
** The Menu Class
*/


#ifndef menuButton
    #define menuButton

#include <iostream>
#include "../Integration/Integration.hpp"
#include <vector>
#include <variant>
#include "EventReceiver.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//remove device

namespace mainMenu {
    class MenuButton {
    public:
        explicit MenuButton(IrrlichtDevice *, IGUIEnvironment *, ISceneManager *, IVideoDriver *);
        MenuButton(MenuButton const &) = delete;
        explicit MenuButton(MenuButton &&) = delete;
        ~MenuButton();

        MenuButton &operator=(MenuButton const &);
        MenuButton &operator=(MenuButton &&);

        void init();
        void eventManager(double time);
        void buttonReset();
        void focus();
        void create();
        void createSound();
        void setVisible(bool);

        bool isSettingsOn() const;
        void setSettingsOn(bool);
        bool isCreditsOn() const;
        void setCreditsOn(bool);
        bool isStartOn() const;
        void setStartOn(bool startOn);

        sf::Sound _sound;
        sf::Sound _acceptSound;
        int _soundBar;
        private:
        IrrlichtDevice *_device;
        IGUIEnvironment *_gui;
        ISceneManager *_sceneManager;
        IVideoDriver *_driver;
        std::vector<IGUIButton *> _buttons;
        std::vector<ITexture *> _hoverText;
        std::vector<ITexture *> _buttonsText;
        EventReceiver *_receiver;
        std::vector<std::vector<int>> _pos;
        double _time;
        int _focus;
        int _oldFocus;
        int _shift;
        int _start;
        bool _settingsOn;
        bool _creditsOn;
        bool _startOn;
        sf::SoundBuffer _soundBuffer;
        sf::SoundBuffer _accept;
    };
}
#endif /* !menuButton */
