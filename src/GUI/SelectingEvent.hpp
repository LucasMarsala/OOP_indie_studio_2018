/*
** EPITECH PROJECT, 2019
** SelectEvent
** File description:
** evenements
*/


#ifndef SELECTINGEVENT_HPP_
#define SELECTINGEVENT_HPP_

#include <iostream>
#include "../Integration/Integration.hpp"
#include <vector>
#include <variant>
#include "EventReceiver.hpp"
#include "../Characters/Mario/Mario.hpp"
#include "../Characters/Wario/Wario.hpp"
#include "../Characters/Luigi/Luigi.hpp"
#include "../Characters/Yoshi/Yoshi.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace selecting {
    class SelectingEvent {
    public:
        explicit SelectingEvent(IrrlichtDevice *, IGUIEnvironment *, ISceneManager *, IVideoDriver *) noexcept;
        SelectingEvent(SelectingEvent const &) noexcept = delete;
        explicit SelectingEvent(SelectingEvent &&) noexcept = delete;
        ~SelectingEvent() noexcept;

        SelectingEvent &operator=(SelectingEvent const &) noexcept;
        SelectingEvent &operator=(SelectingEvent &&) noexcept;

        void eventManager(double time);
        void focus();
        void buttonReset();
        void create();
        void setVisible(bool);
        bool checkAvailable();
        void paramsCreate();
        void run(double time);

        bool isPlay() const;
        void setPlay(bool play);

        int getComplexity() const;
        float getDensity() const;
        int getBoosts() const;

        const std::vector<State> &getPlayer() const;

        private:
        IrrlichtDevice *_device;
        IGUIEnvironment *_gui;
        ISceneManager *_sceneManager;
        IVideoDriver *_driver;
        EventReceiver *_receiver;
        IGUIButton *_butt;
        std::vector<ITexture *> _rec;
        std::vector<ITexture *> _barText;
        std::vector<ITexture *> _paramsText;
        std::vector<ITexture *> _paramsTextHover;
        std::vector<IGUIImage *> _image;
        std::vector<IAnimatedMeshSceneNode *> _charac;
        std::vector<double> _characPos;
        std::vector<std::vector<int>> _pos;
        std::vector<std::vector<int>> _paramsPos;
        std::vector<int> _player;
        std::vector<State> _states;
        std::vector<int> _available;
        std::vector<IGUIButton *> _params;
        std::vector<IGUIButton *> _bars;
        std::vector<int> _childFocus;
        Mario *_mario;
        Wario *_wario;
        Luigi *_luigi;
        Yoshi *_yoshi;
        bool _start;
        int _focus;
        int _paramsFocus;
        double _time;
        int _oldFocus;
        int _shift;
        bool _play;
        std::vector<int> _values;
        int _complexity;
        float _density;
        int _boosts;
    };
}

#endif /* !SELECTINGEVENT_HPP_ */
