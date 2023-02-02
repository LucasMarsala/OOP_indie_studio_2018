/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Mario
*/

#ifndef MARIO_HPP_
#define MARIO_HPP_

#include "../../Integration/Integration.hpp"
#include "../../APlayers/APlayers.hpp"
#include "../../Properties/Properties.hpp"

class ABlock;

class Mario : public Players::APlayers {
    public:
        Mario(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver, irr::IrrlichtDevice *device, EventReceiver &receiver, 
        irr::core::vector3df pos, State state);
        ~Mario();
        void setWalkAnimation() override;
        void setIdleAnimation() override;
        void setWinAnimation() override;
};

#endif /* !MARIO_HPP_ */
