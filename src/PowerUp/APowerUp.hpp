//
// Created by njoachim on 18/06/19.
//

#ifndef OOP_INDIE_STUDIO_2018_APOWERUP_HPP
#define OOP_INDIE_STUDIO_2018_APOWERUP_HPP

#include "../Integration/Integration.hpp"
#include "../APlayers/APlayers.hpp"

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;
using namespace Players;

class APowerUp {
    public:
        APowerUp(video::ITexture* texture, vector3df &pos, irr::scene::ISceneManager *smgr);
        virtual ~APowerUp();
        irr::scene::IMeshSceneNode *getMesh();
        virtual void activatePower(Players::APlayers &player) = 0;

    protected:
        irr::scene::ISceneManager   *_smgr;
        irr::scene::IMeshSceneNode  *_mesh;
        irr::IrrlichtDevice         *_device;
};

#endif //OOP_INDIE_STUDIO_2018_APOWERUP_HPP
