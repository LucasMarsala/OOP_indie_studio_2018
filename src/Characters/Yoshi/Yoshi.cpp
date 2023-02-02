/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Yoshi
*/

#include "Yoshi.hpp"

#include <iostream>

Yoshi::Yoshi(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver, irr::IrrlichtDevice *device, EventReceiver &receiver, 
irr::core::vector3df pos, State state) :
APlayers(pos, smgr, driver, device, receiver, state)
{
    irr::core::vector3df extent;
    irr::f32 factor = 0;
    _mesh = smgr->getMesh("Models/Yoshi/yoshi_idle_ok.b3d");
    irr::core::aabbox3df box = _mesh->getBoundingBox();
    box.MinEdge.X = -7.15107;
    box.MinEdge.Y = -0.000759413;
    box.MinEdge.Z = -5.72089;
    box.MaxEdge.X = 7.15107;
    box.MaxEdge.Y = 14.439;
    box.MaxEdge.Z = 4.06946;
    _mesh->setBoundingBox(box);
    if (!_mesh)
        exit(84);
    _node = smgr->addAnimatedMeshSceneNode(_mesh);
    if (_node) {
        _node->setMaterialTexture(1, driver->getTexture("Models/Yoshi/yoshi_texture_eye.png"));
        _node->setMaterialTexture(1, driver->getTexture("Models/Yoshi/yoshi_texture.png"));
    }
    extent = _node->getBoundingBox().getExtent();
    factor = 12.5 / extent.X;
    irr::core::vector3d<irr::f32> factorEscalate(factor, factor, factor);
    _node->setScale(factorEscalate);
    setPosition(pos);
    _node->setMaterialFlag(video::EMF_LIGHTING, false);
    _oldpos = pos;
}

Yoshi::~Yoshi()
{
}

void Yoshi::setWalkAnimation()
{
    irr::core::vector3df extent;
    irr::f32 factor = 0;
    irr::core::vector3df oldPosition = _node->getPosition();
    irr::core::vector3df oldRotation = _node->getRotation();
    irr::core::vector3df oldScale = _node->getScale();

    _node->remove();
    _node = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh("Models/Yoshi/yoshi_run.b3d"));
    extent = _node->getTransformedBoundingBox().getExtent();
    factor = 12.5 / extent.X;
    irr::core::vector3d<irr::f32> factorEscalate(factor, factor, factor);
    _node->setScale(factorEscalate);
    if (_node) {
        _node->setMaterialTexture(1, _driver->getTexture("Models/Yoshi/yoshi_texture_eye.png"));
        _node->setMaterialTexture(1, _driver->getTexture("Models/Yoshi/yoshi_texture.png"));
    }
    _node->setPosition(oldPosition);
    _node->setRotation(oldRotation);
    _node->setScale(oldScale);
    _node->setAnimationSpeed(90);
    _node->setMaterialFlag(video::EMF_LIGHTING, false);
}

void Yoshi::setIdleAnimation()
{
    irr::core::vector3df extent;
    irr::f32 factor = 0;
    irr::core::vector3df oldPosition = _node->getPosition();
    irr::core::vector3df oldRotation = _node->getRotation();
    irr::core::vector3df oldScale = _node->getScale();

    _node->remove();
    _node = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh("Models/Yoshi/yoshi_idle_ok.b3d"));
    extent = _node->getTransformedBoundingBox().getExtent();
    factor = 12.5 / extent.X;
    irr::core::vector3d<irr::f32> factorEscalate(factor, factor, factor);
    _node->setScale(factorEscalate);
    if (_node) {
        _node->setMaterialTexture(1, _driver->getTexture("Models/Yoshi/yoshi_texture_eye.png"));
        _node->setMaterialTexture(1, _driver->getTexture("Models/Yoshi/yoshi_texture.png"));
    }
    _node->setPosition(oldPosition);
    _node->setRotation(oldRotation);
    _node->setScale(oldScale);
    _node->setMaterialFlag(video::EMF_LIGHTING, false);
}

void Yoshi::setWinAnimation()
{
    irr::core::vector3df extent;
    irr::f32 factor = 0;
    irr::core::vector3df oldPosition = _node->getPosition();
    irr::core::vector3df oldRotation = _node->getRotation();
    irr::core::vector3df oldScale = _node->getScale();

    _node->remove();
    _node = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh("Models/Yoshi/yoshi_win.b3d"));
    extent = _node->getTransformedBoundingBox().getExtent();
    factor = 12.5 / extent.X;
    irr::core::vector3d<irr::f32> factorEscalate(factor, factor, factor);
    _node->setScale(factorEscalate);
    if (_node) {
        _node->setMaterialTexture(1, _driver->getTexture("Models/Yoshi/yoshi_texture_eye.png"));
        _node->setMaterialTexture(1, _driver->getTexture("Models/Yoshi/yoshi_texture.png"));
    }
    _node->setPosition(oldPosition);
    _node->setRotation(oldRotation);
    _node->setScale(oldScale);
    _node->setMaterialFlag(video::EMF_LIGHTING, false);
}