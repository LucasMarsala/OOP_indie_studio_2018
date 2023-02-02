/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Yoshi
*/

#ifndef YOSHI_HPP_
#define YOSHI_HPP_

#include "../../Integration/Integration.hpp"
#include "../../APlayers/APlayers.hpp"
#include "../../Properties/Properties.hpp"

class Yoshi : public Players::APlayers {
    public:
        Yoshi(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver, irr::IrrlichtDevice *device, EventReceiver &receiver, 
        irr::core::vector3df pos, State state);
        ~Yoshi();
        void setWalkAnimation() override;
        void setIdleAnimation() override;
        void setWinAnimation() override;
};

#endif /* !Yoshi_HPP_ */
