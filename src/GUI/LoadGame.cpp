/*
** EPITECH PROJECT, 2019
** LoadGAME
** File description:
** LOAD
*/

#include <fstream>
#include "LoadGame.hpp"
#include "../Exception/Error.hpp"

LoadGame::LoadGame(IrrlichtDevice *device, IGUIEnvironment *gui, ISceneManager *sceneManager, IVideoDriver *driver) noexcept
    : _device(device), _gui(gui), _sceneManager(sceneManager), _driver(driver), _oldFocus(2), _focus(0), _start(1), _shift(0), _selectOn(false), _load(false), _soundBar(100)
{
    _receiver = dynamic_cast<EventReceiver *>(_device->getEventReceiver());
}

LoadGame::~LoadGame()
{
}

void LoadGame::createSound()
{
    if (!_soundBuffer.loadFromFile("ressources/music/move_select.wav"))
        throw ErrorGetMusic("Couldn't get sound file");
    if (!_accept.loadFromFile("ressources/music/select_butt.wav"))
        throw ErrorGetMusic("Couldn't get sound file");
    _sound.setBuffer(_soundBuffer);
    _acceptSound.setBuffer(_accept);
    _sound.setVolume(100);
    _acceptSound.setVolume(100);
}

void LoadGame::create()
{
    ITexture *image;
    std::vector<int> tmp;

    for (int i = 0; i < 2; i++) {
        tmp.push_back(300 - 350 / 2);
        tmp.push_back(300 + 350 / 2);
        tmp.push_back(1080 / 2 - 55 + i * 55);
        tmp.push_back(1080 / 2 + i * 55);
        _pos.push_back(tmp);
        tmp.clear();
    }
    image = _device->getVideoDriver()->getTexture("ressources/NewGameHover.png");
    if (image == NULL)
        throw ErrorGetNewGameHover("Couldn't get new game hover image");
    _hover.push_back(image);
    image = _device->getVideoDriver()->getTexture("ressources/LoadGameHover.png");
    if (image == NULL)
        throw ErrorGetLoadGameHover("Couldn't get load game hover image");
    _hover.push_back(image);
    image = _device->getVideoDriver()->getTexture("ressources/NewGame.png");
    if (image == NULL)
        throw ErrorGetNewGame("Couldn't get new game image");
    _text.push_back(image);
    image = _device->getVideoDriver()->getTexture("ressources/LoadGame.png");
    if (image == NULL)
        throw ErrorGetLoadGame("Couldn't get load game image");
    _text.push_back(image);
    for (int i = 0; i < 2; i++) {
        _buttons.push_back(_gui->addButton(rect<s32>(_pos[i][0], _pos[i][2], _pos[i][1], _pos[i][3]), 0, 0, L""));
        _buttons[i]->setUseAlphaChannel(true);
        _buttons[i]->setDrawBorder(false);
        _buttons[i]->setImage(_text[i]);
    }
    setVisible(false);
    createSound();
}

void LoadGame::eventManager(double time)
{
    _sound.setVolume(_soundBar);
    _acceptSound.setVolume(_soundBar);
    static double timecpy = 0;
    _time = time;
    timecpy += time;
    if (_receiver->isKeyDown(KEY_DOWN) && timecpy > 0.2 && _focus >= 0) {
        _start = 0;
        timecpy = 0;
        _shift = 0;
        for (int j = 0; j < 2; j++)
            _buttons[j]->setImage(_text[j]);
        _oldFocus = _focus;
        if (_focus == 1)
            _focus = 0;
        else
            ++_focus;
        _sound.play();
    }
    if (_receiver->isKeyDown(KEY_UP) && timecpy > 0.2 && _focus < 2) {
        _start = 0;
        timecpy = 0;
        _shift = 0;
        for (int j = 0; j < 2; j++)
            _buttons[j]->setImage(_text[j]);
        _oldFocus = _focus;
        if (_focus == 0)
            _focus = 1;
        else
            --_focus;
        _sound.play();
    }
    if (_focus == 0 && _receiver->isKeyDown(KEY_RETURN) && timecpy > 0.2) {
        timecpy = 0;
        _selectOn = true;
        _acceptSound.play();
    }
    if (_focus == 1 && _receiver->isKeyDown(KEY_RETURN) && timecpy > 0.2) {
        timecpy = 0;
        std::ifstream f("MapSave.txt");
        if (f.good()) {
            _load = true;
            _acceptSound.play();
        }
    }
}

void LoadGame::focus()
{
    if (_start == 1) {
        _buttons[0]->setImage(_text[0]);
        _buttons[0]->setRelativePosition(rect<s32>(_pos[0][0] + 20, _pos[0][2],_pos[0][1] + 20, _pos[0][3]));
    } else {
        _buttons[_focus]->setImage(_text[_focus]);
        if (_shift < 20) {
            _buttons[_focus]->setRelativePosition(rect<s32>(_pos[_focus][0] + _shift, _pos[_focus][2],_pos[_focus][1] + _shift, _pos[_focus][3]));
            _shift += 200 * _time;
        }
    }
    _buttons[_focus]->setImage(_hover[_focus]);
}

void LoadGame::buttonReset()
{
    static int unShift = 20;

    if (_oldFocus != 2) {
        if (unShift > 0) {
            _buttons[_oldFocus]->setRelativePosition(rect<s32>(_pos[_oldFocus][0] + unShift, _pos[_oldFocus][2],_pos[_oldFocus][1] + unShift, _pos[_oldFocus][3]));
            unShift -= 200 * _time;
        } else {
            _oldFocus = 2;
            unShift = 20;
        }
    }
}

void LoadGame::setVisible(bool visible)
{
    for (int i = 0; i < 2; i++) {
        _buttons[i]->setVisible(visible);
    }
}

bool LoadGame::isSelectOn() const
{
    return _selectOn;
}

void LoadGame::setSelectOn(bool selectOn)
{
    _selectOn = selectOn;
}

bool LoadGame::isLoad() const
{
    return _load;
}

void LoadGame::setLoad(bool _load)
{
    LoadGame::_load = _load;
}

