/*
** EPITECH PROJECT, 2019
** Settings
** File description:
** Settings class
*/


#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <iostream>
#include "../Integration/Integration.hpp"
#include <SFML/Audio.hpp>
#include <vector>
#include <variant>
#include "EventReceiver.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Settings {
public:
    explicit Settings(IrrlichtDevice *device, IGUIEnvironment *gui, ISceneManager *sceneManager, IVideoDriver *driver) noexcept;
    Settings(Settings const &) noexcept = delete;
    explicit Settings(Settings &&) noexcept = delete;
    ~Settings() noexcept;
    Settings &operator=(Settings const &) noexcept;
    Settings &operator=(Settings &&) noexcept;

    void create();
    void createSound();
    void init();
    void focus();
    void setVisible(bool);
    void eventManager(double time);

    bool isBackOn() const;
    void setBackOn(bool _backOn);
    int getDifficultyLvl() const;

    int _soundBar;
    sf::Sound _sound;
    sf::Sound _acceptSound;

private:
    IrrlichtDevice *_device;
    IGUIEnvironment *_gui;
    ISceneManager *_sceneManager;
    IVideoDriver *_driver;
    std::vector<ITexture *> _hoverText;
    std::vector<ITexture *> _buttonsText;
    std::vector<ITexture *> _barText;
    std::vector<ITexture *> _difficultyText;
    std::vector<ITexture *> _difficultyTextHover;
    std::vector<IGUIButton *> _buttons;
    std::vector<IGUIButton *> _difficulty;
    IGUIButton *_bar;
    IGUIButton *_back;
    std::vector<std::vector<int>> _pos;
    std::vector<std::vector<int>> _childPos;
    EventReceiver *_receiver;
    double _time;
    int _focus;
    std::vector<int> _childFocus;
    std::vector<int> _maxFocus;
    int _difficultyLvl = 1;
    bool _backOn;
            sf::SoundBuffer _soundBuffer;
        sf::SoundBuffer _accept;
};

#endif /* !SETTINGS_HPP_ */
