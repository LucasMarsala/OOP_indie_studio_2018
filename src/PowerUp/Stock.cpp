//
// Created by njoachim on 18/06/19.
//

#include "Stock.hpp"

Stock::Stock(ISceneManager *smgr, irr::video::IVideoDriver* driver, IrrlichtDevice *device, vector3df &pos) :
    APowerUp(driver->getTexture("Models/PowerUp/stock.png"), pos, smgr)
{
    _device = device;
}

Stock::~Stock()
{
}

void Stock::activatePower(APlayers &player)
{
    player.getStock()++;
}