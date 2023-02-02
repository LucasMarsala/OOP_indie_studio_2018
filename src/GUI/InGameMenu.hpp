//
// Created by baumgartnersimon on 6/21/19.
//

#include <iostream>
#include "../Integration/Integration.hpp"
#include <vector>
#include <variant>
#include "Settings.hpp"
#include "MenuButton.hpp"
#include "Credits.hpp"
#include "LoadGame.hpp"
#include "../Exception/Error.hpp"

#ifndef PROJECT_INGAMEMENU_HPP
    #define PROJECT_INGAMEMENU_HPP

class InGameMenu {
    public:
    explicit InGameMenu(IrrlichtDevice *, IGUIEnvironment *, ISceneManager *, IVideoDriver *) noexcept;
    InGameMenu(InGameMenu const &) noexcept = delete;
    explicit InGameMenu(InGameMenu &&) noexcept = delete;
    ~InGameMenu() noexcept;

    InGameMenu &operator=(InGameMenu const &) noexcept;
    InGameMenu &operator=(InGameMenu &&) noexcept;

    void create();
    void focus();
    void buttonReset();
    void eventManager();
    void run(double time);
    void setVisible(bool);

    bool isMenu() const;
    void setMenu(bool _menu); 
    void createSound();
    bool isExit() const;
    void setExit(bool _exit);
    bool isOptions() const;
    void setOptions(bool);
    bool isSave() const;
    void setSave(bool _save);

    int _soundBar;

    private:
    EventReceiver *_receiver; 
    IrrlichtDevice *_device;
    IGUIEnvironment *_gui;
    ISceneManager *_sceneManager;
    IVideoDriver *_driver;
    std::vector<IGUIButton *> _buttons;
    std::vector<ITexture *> _hover;
    std::vector<ITexture *> _text;
    std::vector<std::vector<int>> _pos;
    double _time;
    int _focus;
    int _start;
    int _shift;
    int _oldFocus;
    int _block;
    bool _menu;
    bool _options;
    double _clock;
    bool _exit;
    bool _save;
    sf::Sound _sound;
    sf::Sound _acceptSound;
    sf::SoundBuffer _soundBuffer;
    sf::SoundBuffer _accept;
};

#endif //PROJECT_INGAMEMENU_HPP
