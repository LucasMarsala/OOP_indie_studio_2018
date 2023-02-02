//
// Created by njoachim on 18/06/19.
//

#include "Power.hpp"

Power::Power(ISceneManager *smgr, irr::video::IVideoDriver* driver, IrrlichtDevice *device, vector3df &pos) :
APowerUp(driver->getTexture("Models/PowerUp/power.png"), pos, smgr)
{
    _device = device;
}

Power::~Power()
{
}

void Power::activatePower(APlayers &player)
{
    player.getPower()++;
}