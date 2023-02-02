/*
** EPITECH PROJECT, 2019
** Credits
** File description:
** Credit
*/

#include <iostream>
#include "Credits.hpp"
#include "../Exception/Error.hpp"

Credits::Credits(IrrlichtDevice *device, IGUIEnvironment *gui, ISceneManager *sceneManager, IVideoDriver *driver) noexcept
: _device(device), _gui(gui), _sceneManager(sceneManager), _driver(driver), _backOn(false), _creditsOn(false)
{
    _receiver = dynamic_cast<EventReceiver *>(_device->getEventReceiver());
}

Credits::~Credits()
{
}

void Credits::createSound()
{
    if (!_buff.loadFromFile("ressources/music/select_butt.wav"))
        throw ErrorGetMusic("Couldn't get sound file");
    _sound.setBuffer(_buff);
    _sound.setVolume(100);
}

void Credits::create()
{
    ITexture *image;

    image = _driver->getTexture("ressources/credits.png");
    if (image == NULL)
        throw ErrorGetCreditsImage("Couldn't get texture from credits image");
    _credits = _gui->addImage(image, position2d<int>(0, 0));
    _credits->setVisible(false);
    _back = _gui->addButton(rect<s32>(1700, 900, 1780, 972), nullptr, 0, L"");
    _back->setUseAlphaChannel(true);
    _back->setDrawBorder(false);
    image = _device->getVideoDriver()->getTexture("ressources/BackHover.png");
    if (image == NULL)
        throw ErrorGetBackImageHover("Could't get texture from back image hover");
    _back->setImage(image);
    _back->setVisible(false);
    createSound();
}

void Credits::eventManager(double time)
{
    _sound.setVolume(_soundBar);
    static double timecpy = 0;
    timecpy += time;
    if (_receiver->isKeyDown(KEY_RETURN) && timecpy > 0.2 && _creditsOn) {
        _creditsOn = false;
        timecpy = 0;
        _backOn = true;
        _sound.play();
    }
    if (_receiver->isKeyDown(KEY_ESCAPE) && timecpy > 0.2 && _creditsOn) {
        _creditsOn = false;
        timecpy = 0;
        _backOn = true;
    }
}

void Credits::setVisible(bool visible)
{
    if (visible) {
        _creditsOn = true;
        _credits->setVisible(true);
        _back->setVisible(true);

    } else {
        _credits->setVisible(false);
        _back->setVisible(false);
    }
}

Credits &Credits::operator=(Credits const &cmenu) noexcept
{
    return *this;
}

Credits &Credits::operator=(Credits &&cmenu) noexcept
{
    return *this = cmenu;
}

bool Credits::isBackOn() const
{
    return _backOn;
}

void Credits::setBackOn(bool backOn)
{
    _backOn = backOn;
}
