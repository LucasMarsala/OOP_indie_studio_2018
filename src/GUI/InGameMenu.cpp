//
// Created by baumgartnersimon on 6/21/19.
//

#include "InGameMenu.hpp"


InGameMenu::InGameMenu(IrrlichtDevice *device, IGUIEnvironment *gui, ISceneManager *sceneManager, IVideoDriver *driver) noexcept
:_device(device), _gui(gui), _sceneManager(sceneManager),  _driver(driver), _block(0), _focus(0), _oldFocus(3), _start(1), _menu(false), _options(false), _clock(0), _exit(false), _soundBar(100), _save(false)
{
    _receiver = dynamic_cast<EventReceiver *>(_device->getEventReceiver());
}

InGameMenu::~InGameMenu() noexcept
{
}

void InGameMenu::createSound()
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

void InGameMenu::create()
{
    std::vector<int> tmp;

    for (int i = 0; i < 4; i++) {
        if (i == 2 || i == 3) {
            tmp.push_back(1920/2 - 400 / 2);
            tmp.push_back(1920/2 + 400 / 2);
            tmp.push_back(1080 / 2 - 105 + i * 55);
            tmp.push_back(1080 / 2 + i * 55);
            _pos.push_back(tmp);
            tmp.clear();
        } else {
            tmp.push_back(1920/2 - 275 / 2);
            tmp.push_back(1920/2 + 275 / 2);
            tmp.push_back(1080 / 2 - 105 + i * 55);
            tmp.push_back(1080 / 2 + i * 55);
            _pos.push_back(tmp);
            tmp.clear();
        }
    }
    _hover.push_back(_device->getVideoDriver()->getTexture("ressources/ResumeHover.png"));
    _hover.push_back(_device->getVideoDriver()->getTexture("ressources/OptionsHover.png"));
    _hover.push_back(_device->getVideoDriver()->getTexture("ressources/SaveGameHover.png"));
    _hover.push_back(_device->getVideoDriver()->getTexture("ressources/ExitToMenuHover.png"));
    _text.push_back(_device->getVideoDriver()->getTexture("ressources/Resume.png"));
    _text.push_back(_device->getVideoDriver()->getTexture("ressources/Options.png"));
    _text.push_back(_device->getVideoDriver()->getTexture("ressources/SaveGame.png"));
    _text.push_back(_device->getVideoDriver()->getTexture("ressources/ExitToMenu.png"));
    for (int i = 0; i < 4; i++) {
        _buttons.push_back(_gui->addButton(rect<s32>(_pos[i][0], _pos[i][2], _pos[i][1], _pos[i][3]), 0, 0, L""));
        _buttons[i]->setUseAlphaChannel(true);
        _buttons[i]->setDrawBorder(false);
        _buttons[i]->setImage(_text[i]);
    }
    setVisible(false);
    createSound();
}

void InGameMenu::eventManager()
{
    _sound.setVolume(_soundBar);
    _acceptSound.setVolume(_soundBar);
    _clock+=_time;
    if (_receiver->isKeyDown(KEY_DOWN) && _clock > 0.2 && _focus >= 0) {
        _start = 0;
        _clock = 0;
        _shift = 0;
        for (int j = 0; j < 4; j++)
            _buttons[j]->setImage(_text[j]);
        _oldFocus = _focus;
        if (_focus == 3)
            _focus = 0;
        else
            ++_focus;
        _sound.play();
    }
    if (_receiver->isKeyDown(KEY_UP) && _clock > 0.2 && _focus < 4) {
        _start = 0;
        _clock = 0;
        _shift = 0;
        for (int j = 0; j < 4; j++)
            _buttons[j]->setImage(_text[j]);
        _oldFocus = _focus;
        if (_focus == 0)
            _focus = 3;
        else
            --_focus;
        _sound.play();
    }
    if (_focus == 0 && _receiver->isKeyDown(KEY_RETURN) && _clock > 0.2 && !_options) {
        setVisible(false);
        _clock = 0;
        _menu = false;
        _acceptSound.play();
    }
    if (_focus == 1 && _receiver->isKeyDown(KEY_RETURN) && _clock > 0.2 && !_options) {
        setVisible(false);
        _clock = 0;
        _options = true;
        _acceptSound.play();
    }
    if (_focus == 2 && _receiver->isKeyDown(KEY_RETURN) && _clock > 0.2 && !_options) {
        _clock = 0;
        _save = true;
        _acceptSound.play();
    }
    if (_focus == 3 && _receiver->isKeyDown(KEY_RETURN) && _clock > 0.2 && !_options) {
        _clock = 0;
        setVisible(false);
        _menu = false;
        _exit = true;
        _acceptSound.play();
    }
    if (!_options && _receiver->isKeyDown(KEY_ESCAPE) && _clock > 0.2) {
        setVisible(false);
        _clock = 0;
        _menu = false;
    } else if (_options && _receiver->isKeyDown(KEY_ESCAPE) && _clock > 0.2) {
        _options = false;
        _clock = 0;
        _menu = true;
        
    }
}

void InGameMenu::focus()
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

void InGameMenu::buttonReset()
{
    static int unShift = 20;

    if (_oldFocus != 3) {
        if (unShift > 0) {
            _buttons[_oldFocus]->setRelativePosition(rect<s32>(_pos[_oldFocus][0] + unShift, _pos[_oldFocus][2],_pos[_oldFocus][1] + unShift, _pos[_oldFocus][3]));
            unShift -= 200 * _time;
        } else {
            _oldFocus = 3;
            unShift = 20;
        }
    }
}

void InGameMenu::run(double time)
{
    _time = time;
    if (!_options) {
        eventManager();
        focus();
        buttonReset();
    }
}

void InGameMenu::setVisible(bool visible)
{
    for (int i = 0; i < 4; i++) {
        _buttons[i]->setVisible(visible);
    }
}

bool InGameMenu::isMenu() const
{
    return _menu;
}

void InGameMenu::setMenu(bool menu)
{
    InGameMenu::_menu = menu;
}

bool InGameMenu::isExit() const
{
    return _exit;
}

void InGameMenu::setExit(bool exit)
{
    _exit = exit;
}

bool InGameMenu::isOptions() const
{
    return _options;
}

void InGameMenu::setOptions(bool _options)
{
    InGameMenu::_options = _options;
}

bool InGameMenu::isSave() const
{
    return _save;
}

void InGameMenu::setSave(bool _save)
{
    InGameMenu::_save = _save;
}
