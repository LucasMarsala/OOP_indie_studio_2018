//
// Created by njoachim on 05/06/19.
//

#ifndef OOP_INDIE_STUDIO_2018_BLOCK_HPP
#define OOP_INDIE_STUDIO_2018_BLOCK_HPP

#include "../Integration/Integration.hpp"
#include <iostream>

class APowerUp;

class ABlock {
    public:
        ABlock(irr::scene::ISceneManager *smgr, irr::scene::IMeshSceneNode *cube, irr::video::IVideoDriver* driver, irr::video::ITexture *texture, irr::IrrlichtDevice *device, const bool &destructible, int boost);
        ~ABlock();
        ABlock(ABlock const &) noexcept;
        ABlock(ABlock &&map) noexcept;
        ABlock &operator=(ABlock const &) noexcept;
        ABlock &operator=(ABlock &&) noexcept;
        bool isDestructible();
        void changeMesh(const std::string &path);
        void changeTexture(const std::string &path);
        void setPos(const irr::core::vector3df &pos);
        void setScale(const irr::core::vector3df &scale);
        irr::core::vector3df getPos() const;
        irr::scene::IMeshSceneNode *getCube();
        APowerUp *getPowerUp();

    private:
        bool _destructible;
        APowerUp *_powerUp;
        irr::IrrlichtDevice *_device;
        irr::scene::IMeshSceneNode *_block;
        irr::video::ITexture      *_texture;
        irr::scene::ISceneManager *_smgr;
        irr::video::IVideoDriver  *_driver;
};

#endif //OOP_INDIE_STUDIO_2018_BLOCK_HPP
