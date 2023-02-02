//
// Created by baumgartnersimon on 6/10/19.
//

#ifndef PROJECT_EVENTRECEIVER_HPP
#define PROJECT_EVENTRECEIVER_HPP

#include "../Integration/Integration.hpp"

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;
using namespace gui;

class EventReceiver : public IEventReceiver
{
public:
    EventReceiver();
    ~EventReceiver() override;
    virtual bool OnEvent(const SEvent& event);
    virtual bool isKeyDown(EKEY_CODE keyCode) const;
    virtual bool isMouseDown();

private:
    bool _keyIsDown[KEY_KEY_CODES_COUNT];
    bool _mouseIsDown;

};
#endif //PROJECT_EVENTRECEIVER_HPP
