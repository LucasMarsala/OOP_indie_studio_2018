/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Luigi
*/

#ifndef LUIGI_HPP_
#define LUIGI_HPP_

#include "../../Integration/Integration.hpp"
#include "../../APlayers/APlayers.hpp"
#include "../../Properties/Properties.hpp"

class Luigi : public Players::APlayers {
    public:
        Luigi(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver, irr::IrrlichtDevice *device, EventReceiver &receiver, 
        irr::core::vector3df pos, State state);
        ~Luigi();
        void setWalkAnimation() override;
        void setIdleAnimation() override;
        void setWinAnimation() override;
};

#endif /* !LUIGI_HPP_ */
