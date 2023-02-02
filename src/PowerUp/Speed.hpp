//
// Created by njoachim on 18/06/19.
//

#ifndef OOP_INDIE_STUDIO_2018_SPEED_HPP
#define OOP_INDIE_STUDIO_2018_SPEED_HPP

#include "APowerUp.hpp"

class Speed : public APowerUp {
    public:
        Speed(ISceneManager *smgr, irr::video::IVideoDriver* driver, IrrlichtDevice *device, vector3df &pos);
        ~Speed() override ;
        void activatePower(APlayers &player) override;
};

#endif //OOP_INDIE_STUDIO_2018_SPEED_HPP
