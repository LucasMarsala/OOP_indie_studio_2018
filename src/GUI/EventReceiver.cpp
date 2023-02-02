//
// Created by baumgartnersimon on 6/10/19.
//

#include "EventReceiver.hpp"

EventReceiver::EventReceiver()
{
    for (int  i = 0; i < KEY_KEY_CODES_COUNT; ++i)
        _keyIsDown[i] = false;
    _mouseIsDown = false;
}

EventReceiver::~EventReceiver()
{
}

bool EventReceiver::OnEvent(const SEvent& event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        _keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT )
    {
        if (event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN)
            _mouseIsDown = true;
        if (event.MouseInput.Event == irr::EMIE_LMOUSE_LEFT_UP)
            _mouseIsDown = false;
    }
    return false;
}

bool EventReceiver::isKeyDown(EKEY_CODE keyCode) const
{
    return _keyIsDown[keyCode];
}

bool EventReceiver::isMouseDown()
{
    return _mouseIsDown;
}
