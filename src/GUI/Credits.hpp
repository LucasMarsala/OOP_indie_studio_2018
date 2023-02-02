/*
** EPITECH PROJECT, 2019
** Credits class
** File description:
** Credits
*/

#include <vector>
#include "../Integration/Integration.hpp"
#include "EventReceiver.hpp"

#ifndef CREDITS_HPP_
#define CREDITS_HPP_

class Credits {
public:
    explicit Credits(IrrlichtDevice *device, IGUIEnvironment *gui, ISceneManager *sceneManager, IVideoDriver *driver) noexcept;
    Credits(Credits const &) noexcept = delete;
    explicit Credits(Credits &&) noexcept = delete;
    ~Credits() noexcept;

    Credits &operator=(Credits const &) noexcept;
    Credits &operator=(Credits &&) noexcept;

    void create();
    void setVisible(bool);
    void eventManager(double time);
    void createSound();

    bool isBackOn() const;
    void setBackOn(bool _backOn);

    int _soundBar;

    private:
    IrrlichtDevice *_device;
    IGUIEnvironment *_gui;
    ISceneManager *_sceneManager;
    IVideoDriver *_driver;
    IGUIImage *_credits;
    IGUIButton *_creditsBack;
    IGUIButton *_back;
    EventReceiver *_receiver;
    bool _backOn;
    bool _creditsOn;
    sf::Sound _sound;
    sf::SoundBuffer _buff;
};

#endif /* !CREDITS_HPP_ */