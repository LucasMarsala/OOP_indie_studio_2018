/*
** EPITECH PROJECT, 2019
** Select
** File description:
** Seleccc
*/

#include "SelectingEvent.hpp"
#include "../Exception/Error.hpp"

namespace selecting {
    SelectingEvent::SelectingEvent(IrrlichtDevice *device, IGUIEnvironment *gui, ISceneManager *sceneManager, IVideoDriver *driver) noexcept
            : _device(device), _gui(gui) ,_sceneManager(sceneManager),_driver(driver), _focus(0), _paramsFocus(0), _oldFocus(4), _player(0), _shift(0), _start(true), _play(false), _characPos(-0.35)
    {
        _mario = new Mario(_sceneManager, _driver, _device, *_receiver, vector3df(0, 0, 0), P1);
        _luigi = new Luigi(_sceneManager, _driver, _device, *_receiver, vector3df(0, 0, 0), P2);
        _wario = new Wario(_sceneManager, _driver, _device, *_receiver, vector3df(0, 0, 0), AI);
        _yoshi = new Yoshi(_sceneManager, _driver, _device, *_receiver, vector3df(0, 0, 0), AI);
        _receiver = dynamic_cast<EventReceiver *>(_device->getEventReceiver());
    }

    SelectingEvent::~SelectingEvent()
    {
    }

    void SelectingEvent::paramsCreate()
    {
        std::vector<int> tmp;

        for (int i = 0; i < 3; i++) {
            tmp.push_back(1920/2 - 460);
            tmp.push_back(1920/2 - 60);
            tmp.push_back(1080/2 + 100 + i * 110);
            tmp.push_back(1080/2 + 100 + 55 + i * 110);
            _paramsPos.push_back(tmp);
            tmp.clear();
        }
        _barText.push_back(_device->getVideoDriver()->getTexture("ressources/Bar/0.png"));
        _barText.push_back(_device->getVideoDriver()->getTexture("ressources/Bar/25.png"));
        _barText.push_back(_device->getVideoDriver()->getTexture("ressources/Bar/50.png"));
        _barText.push_back(_device->getVideoDriver()->getTexture("ressources/Bar/75.png"));
        _barText.push_back(_device->getVideoDriver()->getTexture("ressources/Bar/100.png"));
        _paramsText.push_back(_device->getVideoDriver()->getTexture("ressources/Complexity.png"));
        _paramsText.push_back(_device->getVideoDriver()->getTexture("ressources/Density.png"));
        _paramsText.push_back(_device->getVideoDriver()->getTexture("ressources/Boost.png"));
        _paramsTextHover.push_back(_device->getVideoDriver()->getTexture("ressources/ComplexityHover.png"));
        _paramsTextHover.push_back(_device->getVideoDriver()->getTexture("ressources/DensityHover.png"));
        _paramsTextHover.push_back(_device->getVideoDriver()->getTexture("ressources/BoostHover.png"));
        for (int j = 0; j < 3; j++) {
            _params.push_back(_gui->addButton(rect<s32>(_paramsPos[j][0], _paramsPos[j][2], _paramsPos[j][1],_paramsPos[j][3]), nullptr, 0, L""));
            _params[j]->setUseAlphaChannel(true);
            _params[j]->setDrawBorder(false);
            _params[j]->setImage(_paramsText[j]);
            _params[j]->setVisible(false);
        }
        for (int j = 0; j < 3; j++) {
            _bars.push_back(_gui->addButton(rect<s32>(_paramsPos[j][0] + 250, _paramsPos[j][2], _paramsPos[j][1] + 768,_paramsPos[j][3]), nullptr, 0, L""));
            _bars[j]->setUseAlphaChannel(true);
            _bars[j]->setDrawBorder(false);
            if (j == 0)
                _bars[j]->setImage(_barText[4]);
            else
                _bars[j]->setImage(_barText[2]);
            _bars[j]->setVisible(false);
        }
        for(int i = 0; i < 5; i++)
            _childFocus.push_back(i);
        _childFocus[0] = 4;
        _childFocus[1] = 2;
        _childFocus[2] = 2;
        _values.push_back(100);
        _values.push_back(50);
        _values.push_back(50);
    }

    void SelectingEvent::create()
    {
        ITexture *image;
        std::vector<int> tmp;

        for (int i = 0; i < 4; i++) {
            tmp.push_back(1920/2 - 750 + i * 400);
            tmp.push_back(1080/2 - 817/2);
            _pos.push_back(tmp);
            tmp.clear();
        }
        _sceneManager->addLightSceneNode(0, vector3df(0, 100, 0), SColorf(1.0f, 1.0f, 1.0f, 1.0), 1000000);
        _characPos.push_back(-0.6);
        _characPos.push_back(-0.2);
        _characPos.push_back(0.23);
        _characPos.push_back(0.65);
        _mario->setPosition(vector3df(-0.6, 0, 0));
        _mario->_node->setScale(vector3df(0.0025, 0.0045, 0.0025));
        _charac.push_back(_mario->_node);
        _luigi->setPosition(vector3df(-0.2, 0, 0));
        _luigi->_node->setScale(vector3df(0.03, 0.041, 0.03));
        _charac.push_back(_luigi->_node);
        _wario->setPosition(vector3df(0.23, 0, 0));
        _wario->_node->setScale(vector3df(0.1, 0.22, 0.1));
        _charac.push_back(_wario->_node);
        _yoshi->setPosition(vector3df(0.65, 0, 0));
        _yoshi->_node->setScale(vector3df(0.03, 0.047, 0.03));
        _charac.push_back(_yoshi->_node);
        image = _device->getVideoDriver()->getTexture("ressources/PlayerOne.png");
        if (image == NULL) {
            throw ErrorGetPlayerOne("Couldn't get texture from player one");
        }
        _rec.push_back(image);
        image = _device->getVideoDriver()->getTexture("ressources/PlayerTwo.png");
        if (image == NULL) {
            throw ErrorGetPlayerTwo("Couldn't get texture from player two");
        }
        _rec.push_back(image);
        image = _device->getVideoDriver()->getTexture("ressources/NoPlayer.png");
        if (image == NULL)
            throw ErrorGetNoPlayer("Couldn't get texture from no player");
        _rec.push_back(image);
        _image.push_back(_gui->addImage(_rec[0], position2d<int>(_pos[0][0], _pos[0][1])));
        _image.push_back(_gui->addImage(_rec[1], position2d<int>(_pos[1][0], _pos[1][1])));
        _image.push_back(_gui->addImage(_rec[2], position2d<int>(_pos[2][0], _pos[2][1])));
        _image.push_back(_gui->addImage(_rec[2], position2d<int>(_pos[3][0], _pos[3][1])));
        _butt = _gui->addButton(rect<s32>(1700, 900, 1850, 955), 0,0, L"");
        _butt->setUseAlphaChannel(true);
        _butt->setDrawBorder(false);
        image = _device->getVideoDriver()->getTexture("ressources/Play.png");
        if (image == NULL)
            throw ErrorGetPlayButton("Couldn't get texture from play button");
        _butt->setImage(image);
        _player.push_back(0);
        _player.push_back(1);
        _player.push_back(2);
        _player.push_back(2);
        for (int i = 0; i < 3; i++)
            _available.push_back(0);
        paramsCreate();
    }

    bool SelectingEvent::checkAvailable()
    {
        for (int i = 0; i < 4; i++) {
            _states.push_back(AI);
        }
        for (int i = 0; i < 4; i++) {
            _states[i] = static_cast<State>(_player[i]);
            _available[_player[i]]++;
        }
        if ((_available[0] == 1 && (_available[1] == 0 || _available[1] == 1)) || (_available[2] == 4)) {
            for (int i = 0; i < 3; i++)
                _available[i] = 0;
            return true;
        } else {
            for (int i = 0; i < 3; i++)
                _available[i] = 0;
            return false;
        }
    }

    void SelectingEvent::eventManager(double time)
    {
        ITexture *image;
        static double timecpy = 0;
        _time = time;
        timecpy += time;
        if (_focus < 4 && _focus >= 0) {
            if (_receiver->isKeyDown(KEY_RIGHT) && _focus >= 0 &&
                timecpy > 0.2) {
                _start = false;
                timecpy = 0;
                _shift = 0;
                _oldFocus = _focus;
                if (_focus == 3)
                    _paramsFocus = 0;
                _focus++;
            }
            if (_receiver->isKeyDown(KEY_LEFT) && _focus < 5 && timecpy > 0.2) {
                _start = false;
                timecpy = 0;
                _shift = 0;
                _oldFocus = _focus;
                if (_focus == 0) {
                    _focus = 7;
                } else
                    _focus--;
            }
            if (_receiver->isKeyDown(KEY_UP) && timecpy > 0.2 && _focus != 4) {
                if (_player[_focus] == 0)
                    _player[_focus] = 2;
                else
                    _player[_focus]--;
                _image[_focus]->setImage(_rec[_player[_focus]]);
                timecpy = 0;
            }
            if (_receiver->isKeyDown(KEY_DOWN) && timecpy > 0.2 &&
                _focus != 4) {
                if (_player[_focus] == 2)
                    _player[_focus] = 0;
                else
                    _player[_focus]++;
                _image[_focus]->setImage(_rec[_player[_focus]]);
                timecpy = 0;
            }
        } else if (_focus < 8 && _focus >= 4) {
            if (_receiver->isKeyDown(KEY_DOWN) && timecpy > 0.2) {
                timecpy = 0;
                for (int j = 0; j < 3; j++)
                    _params[j]->setImage(_paramsText[j]);
                if (_focus == 7) {
                    _focus = 0;
                } else if (_focus == 6) {
                    ++_focus;
                } else if (_focus < 7 && _focus >= 4){
                    ++_focus;
                    ++_paramsFocus;
                }
            }
            if (_receiver->isKeyDown(KEY_UP) && timecpy > 0.2) {
                timecpy = 0;
                for (int j = 0; j < 3; j++)
                    _params[j]->setImage(_paramsText[j]);
                --_focus;
                if (_focus == 7)
                    _paramsFocus = 2;
                if (_paramsFocus != 0 && _focus != 7 && _focus != 6)
                    --_paramsFocus;

            }
            if (_receiver->isKeyDown(KEY_RIGHT) && timecpy > 0.2 && _childFocus[_paramsFocus] < 4 && _childFocus[_paramsFocus] >= 0) {
                timecpy = 0;
                if (_focus == 7)
                    _focus = 0;
                else {
                    _values[_paramsFocus] += 25;
                    ++_childFocus[_paramsFocus];
                }
            }
            if (_receiver->isKeyDown(KEY_LEFT) && timecpy > 0.2 && _childFocus[_paramsFocus] < 4 + 1 && _childFocus[_paramsFocus] > 0) {
                timecpy = 0;
                if (_focus != 7) {
                    _values[_paramsFocus] -= 25;
                    --_childFocus[_paramsFocus];
                }
            }
        } if (_focus == 7) {
            _paramsFocus = 2;
            image = _device->getVideoDriver()->getTexture("ressources/PlayHover.png");
            if (image == NULL)
                throw ErrorGetPlayButtonHover("Couldn't get texture from play button hover");
            _butt->setImage(image);
        } else {
            image = _device->getVideoDriver()->getTexture("ressources/Play.png");
            if (image == NULL)
                throw ErrorGetPlayButton("Couldn't get texture from play button");
            _butt->setImage(image);
        }
        if (_focus == 7 && _receiver->isKeyDown(KEY_RETURN) && timecpy > 0.2) {
            if (checkAvailable()) {
                _complexity = _values[0]*2;
                _density = (float)_values[1]/100;
                _boosts = _values[2];
                _play = true;
            }
            timecpy = 0;
        }
    }

    void SelectingEvent::focus()
    {
        if (_start == 1) {
            _image[0]->setRelativePosition(position2d<int>(_pos[0][0], _pos[0][1] - 20));
            _charac[0]->setPosition(vector3df(-0.6,0 + 0.055, 0));
        } else {
            if (_shift < 20 && _focus < 4) {
                _image[_focus]->setRelativePosition(position2d<int>(_pos[_focus][0], _pos[_focus][1] - _shift));
                _charac[_focus]->setPosition(vector3df(_characPos[_focus], 0 + _shift * 0.00275, 0));
                _shift += 200 * _time;
            }
            if (_focus < 7 && _focus >= 4) {
                _params[_paramsFocus]->setImage(_paramsTextHover[_paramsFocus]);
            }
        }
        _bars[_paramsFocus]->setImage(_barText[_childFocus[_paramsFocus]]);
    }

    void SelectingEvent::buttonReset()
    {
        static int unShift = 20;

        if (_oldFocus != 4) {
            if (unShift > 0) {
                _image[_oldFocus]->setRelativePosition(position2d<int>(_pos[_oldFocus][0], _pos[_oldFocus][1] - unShift));
                _charac[_oldFocus]->setPosition(vector3df(_characPos[_oldFocus],0 + unShift * 0.00275, 0));
                unShift -= 200 * _time;
            } else {
                _oldFocus = 4;
                unShift = 20;
            }
        }
    }

    void SelectingEvent::run(double time)
    {
        eventManager(time);
        focus();
        buttonReset();
    }

    void SelectingEvent::setVisible(bool visible)
    {
        for (int i = 0; i < 4; i++) {
            _image[i]->setVisible(visible);
            _charac[i]->setVisible(visible);
        }
        for (int i = 0; i < 3; i++) {
            _params[i]->setVisible(visible);
            _bars[i]->setVisible(visible);
        }
        _butt->setVisible(visible);
    }

    bool SelectingEvent::isPlay() const
    {
        return _play;
    }

    void SelectingEvent::setPlay(bool play)
    {
        SelectingEvent::_play = play;
    }

    const std::vector<State> &SelectingEvent::getPlayer() const
    {
        return _states;
    }

    int SelectingEvent::getComplexity() const
    {
        return _complexity;
    }

    float SelectingEvent::getDensity() const
    {
        return _density;
    }

    int SelectingEvent::getBoosts() const
    {
        return _boosts;
    }

}
