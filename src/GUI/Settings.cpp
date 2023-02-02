/*
** EPITECH PROJECT, 2019
** Settings
** File description:
** set ings
*/

#include "Settings.hpp"
#include "../Exception/Error.hpp"

Settings::Settings(IrrlichtDevice *device, IGUIEnvironment *gui, ISceneManager *sceneManager, IVideoDriver *driver) noexcept
: _device(device), _gui(gui), _sceneManager(sceneManager), _driver(driver), _focus(0), _backOn(false), _soundBar(100)
{
    _receiver = dynamic_cast<EventReceiver *>(_device->getEventReceiver());
}

Settings::~Settings()
{
}

void Settings::init()
{
    std::vector<int> tmp;
    std::vector<int> tmpChild;
    ITexture *image;

    for (int i = 0; i < 2; i++) {
        tmp.push_back(250 - 350 / 2);
        tmp.push_back(250 + 350 / 2);
        tmp.push_back(1080/2 - 55 + i * 75);
        tmp.push_back(1080/2 + i * 75);
        _pos.push_back(tmp);
        tmp.clear();
    }
    for(int i = 0; i < 5; i++)
        _childFocus.push_back(i);
    _childFocus[0] = 4;
    _childFocus[1] = 1;
    image = _device->getVideoDriver()->getTexture("ressources/Volume.png");
    if (image == NULL)
        throw ErrorGetVolume("Couldn't get texture from volume");
    _buttonsText.push_back(image);
    image = _device->getVideoDriver()->getTexture("ressources/Difficulty.png");
    if (image == NULL)
        throw ErrorGetVsync("Couldn't get texture from Difficulty");
    _buttonsText.push_back(image);
    image = _device->getVideoDriver()->getTexture("ressources/VolumeHover.png");
    if (image == NULL)
        throw ErrorGetVolumeHover("Couldn't get texture from volume hover");
    _hoverText.push_back(image);
    image = _device->getVideoDriver()->getTexture("ressources/DifficultyHover.png");
    if (image == NULL)
        throw ErrorGetVsyncHover("Couldn't get texture from Difficulty hover");
    _hoverText.push_back(image);
    image = _device->getVideoDriver()->getTexture("ressources/Bar/0.png");
    if (image == NULL)
        throw ErrorGetBar0("Couldn't get texture from bar0");
    _barText.push_back(image);
    image = _device->getVideoDriver()->getTexture("ressources/Bar/25.png");
    if (image == NULL)
        throw ErrorGetBar25("Couldn't get texture from bar25");
    _barText.push_back(image);
    image = _device->getVideoDriver()->getTexture("ressources/Bar/50.png");
    if (image == NULL)
        throw ErrorGetBar50("Couldn't get texture from bar50");
    _barText.push_back(image);
    image = _device->getVideoDriver()->getTexture("ressources/Bar/75.png");
    if (image == NULL)
        throw ErrorGetBar75("Couldn't get texture from bar75");
    _barText.push_back(image);
    image = _device->getVideoDriver()->getTexture("ressources/Bar/100.png");
    if (image == NULL)
        throw ErrorGetBar100("Couldn't get texture from bar100");
    _barText.push_back(image);
    image = _device->getVideoDriver()->getTexture("ressources/Easy.png");
    if (image == NULL)
        throw ErrorGetYesImage("Couldn't get texture from easy image");
    _difficultyText.push_back(image);
    image = _device->getVideoDriver()->getTexture("ressources/Normal.png");
    if (image == NULL)
        throw ErrorGetNoImage("Couldn't get texture from normal image");
    _difficultyText.push_back(image);
    image = _device->getVideoDriver()->getTexture("ressources/Hard.png");
    if (image == NULL)
        throw ErrorGetNoImage("Couldn't get texture from hard image");
    _difficultyText.push_back(image);
    image = _device->getVideoDriver()->getTexture("ressources/EasyHover.png");
    if (image == NULL)
        throw ErrorGetYesImage("Couldn't get texture from easy hover image");
    _difficultyTextHover.push_back(image);
    image = _device->getVideoDriver()->getTexture("ressources/NormalHover.png");
    if (image == NULL)
        throw ErrorGetNoImage("Couldn't get texture from normal hover image");
    _difficultyTextHover.push_back(image);
    image = _device->getVideoDriver()->getTexture("ressources/HardHover.png");
    if (image == NULL)
        throw ErrorGetNoImage("Couldn't get texture from hard hover image");
    _difficultyTextHover.push_back(image);
    _maxFocus.push_back(4);
    _maxFocus.push_back(2);
}

void Settings::createSound()
{
        if (!_soundBuffer.loadFromFile("ressources/music/move_select.wav"))
            throw ErrorGetMusic("Couldn't get sound file");
        if (!_accept.loadFromFile("ressources/music/select_butt.wav"))
            throw ErrorGetMusic("Couldn't get sound file");
        _sound.setBuffer(_soundBuffer);
        _acceptSound.setBuffer(_accept);
        _sound.setVolume(_soundBar);
        _acceptSound.setVolume(_soundBar);
}

void Settings::create()
{
    IGUIButton *button;
    ITexture *image;

    init();
    for (int j = 0; j < 2; j++) {
        button = _gui->addButton(rect<s32>(_pos[j][0], _pos[j][2], _pos[j][1], _pos[j][3]), 0,0, L"");
        if (button == NULL)
            throw ErrorAddButton("Couldn't add button");
        _buttons.push_back(button);
        _buttons[j]->setUseAlphaChannel(true);
        _buttons[j]->setDrawBorder(false);
        _buttons[j]->setImage(_buttonsText[j]);
        _buttons[j]->setVisible(false);
    }
    for (int j = 0; j < 3; j++) {
        button = _gui->addButton(rect<s32>(_pos[1][0] + 350 + j * 275, _pos[1][2], _pos[1][0] + 625 + j * 275,_pos[1][3]), nullptr, 0, L"");
        if (button == NULL)
            throw ErrorAddButton("Couldn't add button");
        _difficulty.push_back(button);
        _difficulty[j]->setUseAlphaChannel(true);
        _difficulty[j]->setDrawBorder(false);
        _difficulty[j]->setImage(_difficultyText[j]);
        _difficulty[j]->setVisible(false);
    }
    _bar = _gui->addButton(rect<s32>(_pos[0][0] + 350, _pos[0][2], _pos[0][0]  + 350 + 519, _pos[0][3]), nullptr, 0, L"");
    if (_bar == NULL)
        throw ErrorAddButton("Couln't add button bar");
    _bar->setUseAlphaChannel(true);
    _bar->setDrawBorder(false);
    _bar->setImage(_barText[4]);
    _bar->setVisible(false);
    _back = _gui->addButton(rect<s32>(1700, 900, 1780, 972), nullptr, 0, L"");
    if (_back == NULL)
        throw ErrorAddButton("Couldn't add button back");
    _back->setUseAlphaChannel(true);
    _back->setDrawBorder(false);
    image = _device->getVideoDriver()->getTexture("ressources/Back.png");
    if (image == NULL)
        throw ErrorGetBackImage("Could't get texture form back image");
    _back->setImage(image);
    _back->setVisible(false);
    createSound();
}

void Settings::eventManager(double time)
{
    ITexture *image;
    static double timecpy = 0;
    _time = time;
    timecpy += time;

    if (_receiver->isKeyDown(KEY_DOWN) && timecpy > 0.2 && _focus < 2 && _focus >= 0) {
        timecpy = 0;
        for (int j = 0; j < 2; j++)
            _buttons[j]->setImage(_buttonsText[j]);
        image = _device->getVideoDriver()->getTexture("ressources/Back.png");
        if (image == NULL)
            throw ErrorGetBackImage("Couldn't get texture from back image");
        _back->setImage(image);
        ++_focus;
        _sound.play();
    }
    if (_receiver->isKeyDown(KEY_UP) && timecpy > 0.2 && _focus < 3 && _focus > 0) {
        timecpy = 0;
        for (int j = 0; j < 2; j++)
            _buttons[j]->setImage(_buttonsText[j]);
            image = _device->getVideoDriver()->getTexture("ressources/Back.png");
            if (image == NULL)
                throw ErrorGetBackImage("Couldn't get texture from back image");
        _back->setImage(image);
        --_focus;
        _sound.play();
    }
    if (_receiver->isKeyDown(KEY_RIGHT) && timecpy > 0.2 && _childFocus[_focus] < _maxFocus[_focus] && _childFocus[_focus] >= 0) {
        timecpy = 0;
        if (_focus == 1)
            _difficulty[_childFocus[1]]->setImage(_difficultyText[_childFocus[1]]);
        ++_childFocus[_focus];
        if (_soundBar < 100 && _focus == 0) {
            _soundBar += 25;
            _sound.setVolume(_soundBar);
            _acceptSound.setVolume(_soundBar);
        }
    }
    if (_receiver->isKeyDown(KEY_LEFT) && timecpy > 0.2 && _childFocus[_focus] < _maxFocus[_focus] + 1 && _childFocus[_focus] > 0) {
        timecpy = 0;
        if (_focus == 1)
            _difficulty[_childFocus[1]]->setImage(_difficultyText[_childFocus[1]]);
        --_childFocus[_focus];
        if (_soundBar > 0 && _focus == 0) {
            _soundBar -= 25;
            _sound.setVolume(_soundBar);
            _acceptSound.setVolume(_soundBar);
        }
    }
    if (_receiver->isKeyDown(KEY_ESCAPE) && timecpy > 0.2) {
        timecpy = 0;
        _backOn = true;
        setVisible(false);
    }
}

void Settings::focus()
{
    ITexture *image;
    _bar->setImage(_barText[_childFocus[0]]);
    _difficulty[_childFocus[1]]->setImage(_difficultyTextHover[_childFocus[1]]);
    if (_focus == 2) {
        image = _device->getVideoDriver()->getTexture("ressources/BackHover.png");
        if (image == NULL)
            throw ErrorGetBackImageHover("Couldn't get texture from back image");
        _back->setImage(image);
        if (_receiver->isKeyDown(KEY_RETURN)) {
            _backOn = true;
            setVisible(false);
            _acceptSound.play();
        }
    } else {
        _difficultyLvl = _childFocus[1];
        _buttons[_focus]->setImage(_hoverText[_focus]);
    }
}

void Settings::setVisible(bool visible)
{
    ITexture *image;
    if (visible) {
        for (int j = 0; j < 2; j++)
            _buttons[j]->setVisible(true);
        for (int j = 0; j < 3; j++)
            _difficulty[j]->setVisible(true);
        _bar->setVisible(true);
        _back->setVisible(true);
    } else {
        _focus = 0;
        image = _device->getVideoDriver()->getTexture("ressources/Back.png");
        if (image == NULL)
            throw ErrorGetBackImage("Couldn't get texture from back image");
        _back->setImage(image);
        for (int i = 0; i < 2; i++)
            _buttons[i]->setVisible(false);
        for (int j = 0; j < 3; j++)
            _difficulty[j]->setVisible(false);
        _bar->setVisible(false);
        _back->setVisible(false);
    }
}

Settings &Settings::operator=(Settings const &cmenu) noexcept
{
    return *this;
}

Settings &Settings::operator=(Settings &&cmenu) noexcept
{
    return *this = cmenu;
}

bool Settings::isBackOn() const
{
    return _backOn;
}

void Settings::setBackOn(bool _backOn)
{
    Settings::_backOn = _backOn;
}

int Settings::getDifficultyLvl() const
{
    return _difficultyLvl;
}
