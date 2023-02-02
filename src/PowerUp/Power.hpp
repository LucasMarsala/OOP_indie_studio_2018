//
// Created by njoachim on 18/06/19.
//

#ifndef OOP_INDIE_STUDIO_2018_POWER_HPP
#define OOP_INDIE_STUDIO_2018_POWER_HPP

#include "APowerUp.hpp"

class Power : public APowerUp{
    public:
        Power(ISceneManager *smgr, irr::video::IVideoDriver* driver, IrrlichtDevice *device, vector3df &pos);
        ~Power() override;
        void activatePower(APlayers &player) override;

};

#endif //OOP_INDIE_STUDIO_2018_POWER_HPP
