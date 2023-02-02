//
// Created by njoachim on 18/06/19.
//

#include "Speed.hpp"

Speed::Speed(ISceneManager *smgr, irr::video::IVideoDriver* driver, IrrlichtDevice *device, vector3df &pos) :
    APowerUp(driver->getTexture("Models/PowerUp/speed.png"), pos, smgr)
{
    _device = device;
}

Speed::~Speed()
{
}

void Speed::activatePower(APlayers &player)
{
    player.getSpeed() += 5;
}