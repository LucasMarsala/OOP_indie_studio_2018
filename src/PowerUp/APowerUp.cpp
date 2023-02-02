//
// Created by njoachim on 18/06/19.
//

#include "APowerUp.hpp"

APowerUp::APowerUp(video::ITexture* texture, vector3df &pos,  irr::scene::ISceneManager *smgr)
: _mesh(smgr->addCubeSceneNode(5)), _smgr(smgr)
{
    if (texture) {
        _mesh->setMaterialTexture(0, texture);
        _mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }
    pos.Y += 3;
    _mesh->setPosition(pos);
    ISceneNodeAnimator *anim = _smgr->createRotationAnimator(vector3df(0, 0.25, 0));
    _mesh->addAnimator(anim);
    anim->drop();
    anim = _smgr->createFlyStraightAnimator(pos, vector3df(pos.X, pos.Y + 3, pos.Z), 1000, true, true);
    _mesh->addAnimator(anim);
    anim->drop();
}

irr::scene::IMeshSceneNode* APowerUp::getMesh()
{
    return _mesh;
}

APowerUp::~APowerUp()
{
    _mesh->remove();
}