/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Wario
*/

#ifndef WARIO_HPP_
#define WARIO_HPP_

#include "../../Integration/Integration.hpp"
#include "../../APlayers/APlayers.hpp"
#include "../../Properties/Properties.hpp"

class Wario : public Players::APlayers {
    public:
        Wario(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver, irr::IrrlichtDevice *device, EventReceiver &receiver, 
        irr::core::vector3df pos, State state);
        ~Wario();
        void setWalkAnimation() override;
        void setIdleAnimation() override;
        void setWinAnimation() override;
};

#endif /* !Wario_HPP_ */
