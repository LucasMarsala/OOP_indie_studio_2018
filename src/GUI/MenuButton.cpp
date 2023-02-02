//
// Created by baumgartnersimon on 6/13/19.
//

#include "MenuButton.hpp"
#include "../Exception/Error.hpp"

namespace mainMenu {
    MenuButton::MenuButton(IrrlichtDevice *device, IGUIEnvironment *gui, ISceneManager *sceneManager, IVideoDriver *driver)
        : _device(device), _gui(gui), _sceneManager(sceneManager),_driver(driver), _focus(0), _shift(0), _oldFocus(4),_start(1), _settingsOn(false), _creditsOn(false), _startOn(false), _soundBar(100)
    {
        _receiver = dynamic_cast<EventReceiver *>(_device->getEventReceiver());
    }

    MenuButton::~MenuButton()
    {
    }

    void MenuButton::createSound()
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

    void MenuButton::init()
    {
        std::vector<int> tmp;
        ITexture *image;

        for (int i = 0; i < 4; i++) {
            tmp.push_back(250 - 275 / 2);
            tmp.push_back(250 + 275 / 2);
            tmp.push_back(1080/2 - 110 + i * 75);
            tmp.push_back(1080/2 - 55 + i * 75);
            _pos.push_back(tmp);
            tmp.clear();
        }
        image = _device->getVideoDriver()->getTexture("ressources/StartButton.png");
        if (image == NULL)
            throw ErrorGetStartButton("Couldn't get texture from start button");
        _buttonsText.push_back(image);
        image = _device->getVideoDriver()->getTexture("ressources/SettingsButton.png");
        if (image == NULL)
            throw ErrorGetSettingsButton("Couldn't get texture from settings button");
        _buttonsText.push_back(image);
        image = _device->getVideoDriver()->getTexture("ressources/CreditsButton.png");
        if (image == NULL)
            throw ErrorGetCreditsButton("Coudln't get texture from credits button");
        _buttonsText.push_back(image);
        image = _device->getVideoDriver()->getTexture("ressources/ExitButton.png");
        if (image == NULL)
            throw ErrorGetExitButton("Coudln't get texture from exit button");
        _buttonsText.push_back(image);
        image = _device->getVideoDriver()->getTexture("ressources/StartButtonHover.png");
        if (image == NULL)
            throw ErrorGetStartButtonHover("Couldn't get texture from start button hover");
        _hoverText.push_back(image);
        image = _device->getVideoDriver()->getTexture("ressources/SettingsButtonHover.png");
        if (image == NULL)
            throw ErrorGetSettingsButtonHover("Couldn't get texture from settings button hover");
        _hoverText.push_back(image);
        image = _device->getVideoDriver()->getTexture("ressources/CreditsButtonHover.png");
        if (image == NULL)
            throw ErrorGetCreditsButtonHover("Couldn't get texture from credits button hover");
        _hoverText.push_back(image);
        image = _device->getVideoDriver()->getTexture("ressources/ExitButtonHover.png");
        if (image == NULL)
            throw ErrorGetExitButtonHover("Couldn't get texture from exit button hover");
        _hoverText.push_back(_device->getVideoDriver()->getTexture("ressources/ExitButtonHover.png"));
    }

    void MenuButton::create()
    {
        IGUIButton *button;

        init();
        for (int j = 0; j < 4; j++) {
            button = _gui->addButton(rect<s32>(_pos[j][0], _pos[j][2], _pos[j][1], _pos[j][3]), 0, 0, L"");
            if (button == NULL)
                throw ErrorAddButton("Couldn't create menu button");
            _buttons.push_back(button);
            _buttons[j]->setUseAlphaChannel(true);
            _buttons[j]->setDrawBorder(false);
            if (_buttonsText[j])
                _buttons[j]->setImage(_buttonsText[j]);
        }
        createSound();
    }

    void MenuButton::eventManager(double time)
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
            for (int j = 0; j < 4; j++)
                _buttons[j]->setImage(_buttonsText[j]);
            _oldFocus = _focus;
            if (_focus == 3)
                _focus = 0;
            else
                ++_focus;
            _sound.play();
        }
        if (_receiver->isKeyDown(KEY_UP) && timecpy > 0.2 && _focus < 4) {
            _start = 0;
            timecpy = 0;
            _shift = 0;
            for (int j = 0; j < 4; j++)
                _buttons[j]->setImage(_buttonsText[j]);
            _oldFocus = _focus;
            if (_focus == 0)
                _focus = 3;
            else
                --_focus;
            _sound.play();
        }
        if (_focus == 0 && _receiver->isKeyDown(KEY_RETURN) && timecpy > 0.2) {
            timecpy = 0;
            _startOn = true;
            _acceptSound.play();
            
        }
        if (_focus == 1 && _receiver->isKeyDown(KEY_RETURN) && timecpy > 0.2) {
            timecpy = 0;
            _settingsOn = true;
            _acceptSound.play();
        }
        if (_focus == 2 && _receiver->isKeyDown(KEY_RETURN) && timecpy > 0.2) {
            timecpy = 0;
            _creditsOn = true;
            _acceptSound.play();
        }
        if (_focus == 3 && _receiver->isKeyDown(KEY_RETURN) && timecpy > 0.2) {
            timecpy = 0;
            _acceptSound.play();
            _device->closeDevice();
        }
    }

    void MenuButton::focus()
    {
        if (_start == 1) {
            _buttons[0]->setImage(_hoverText[0]);
            _buttons[0]->setRelativePosition(rect<s32>(_pos[0][0] + 20, _pos[0][2],_pos[0][1] + 20, _pos[0][3]));
        } else {
            _buttons[_focus]->setImage(_hoverText[_focus]);
            if (_shift < 20) {
                _buttons[_focus]->setRelativePosition(rect<s32>(_pos[_focus][0] + _shift, _pos[_focus][2],_pos[_focus][1] + _shift, _pos[_focus][3]));
                _shift += 200 * _time;
            }
        }
    }

    void MenuButton::buttonReset()
    {
        static int unShift = 20;

        if (_oldFocus != 4) {
            if (unShift > 0) {
                _buttons[_oldFocus]->setRelativePosition(rect<s32>(_pos[_oldFocus][0] + unShift, _pos[_oldFocus][2],_pos[_oldFocus][1] + unShift, _pos[_oldFocus][3]));
                unShift -= 200 * _time;
            } else {
                _oldFocus = 4;
                unShift = 20;
            }
        }
    }

    void MenuButton::setVisible(bool visible)
    {
        if (visible) {
            for (int j = 0; j < 4; j++) {
                _buttons[j]->setVisible(true);
            }
        } else {
            _settingsOn = 0;
            for (int i = 0; i < 4; i++) {
                _buttons[i]->setVisible(false);
            }
        }
    }

    MenuButton &MenuButton::operator=(MenuButton const &mbutton)
    {
        return *this;
    }

    MenuButton &MenuButton::operator=(MenuButton &&mbutton)
    {
        return *this = mbutton;
    }

    bool MenuButton::isSettingsOn() const
    {
        return _settingsOn;
    }

    void MenuButton::setSettingsOn(bool settingsOn)
    {
        _settingsOn = settingsOn;
    }

    bool MenuButton::isCreditsOn() const
    {
        return _creditsOn;
    }

    void MenuButton::setCreditsOn(bool creditsOn)
    {
        _creditsOn = creditsOn;
    }

    bool MenuButton::isStartOn() const
    {
        return _startOn;
    }

    void MenuButton::setStartOn(bool startOn)
    {
        MenuButton::_startOn = startOn;
    }
}
