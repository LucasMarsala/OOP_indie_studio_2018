/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Luigi
*/

#include "Luigi.hpp"

#include <iostream>

Luigi::Luigi(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver, irr::IrrlichtDevice *device, EventReceiver &receiver, 
irr::core::vector3df pos, State state) :
APlayers(pos, smgr, driver, device, receiver, state)
{
    irr::core::vector3df extent;
    irr::f32 factor = 0;
    _mesh = smgr->getMesh("Models/Luigi/luigi_idle.b3d");
    irr::core::aabbox3df box = _mesh->getBoundingBox();
    box.MinEdge.X = -8.2288;
    box.MinEdge.Y = -0.0341798;
    box.MinEdge.Z = -3.1172;
    box.MaxEdge.X = 8.2288;
    box.MaxEdge.Y = 17.1057;
    box.MaxEdge.Z = 3.18449;
    _mesh->setBoundingBox(box);
    if (!_mesh)
        exit(84);
    _node = smgr->addAnimatedMeshSceneNode(_mesh);
    if (_node) {
        _node->setMaterialTexture(0, driver->getTexture("Models/Luigi/luigi_texture_2.png"));
    }
    extent = _node->getBoundingBox().getExtent();
    factor = 12.5 / extent.X;
    irr::core::vector3d<irr::f32> factorEscalate(factor, factor, factor);
    _node->setScale(factorEscalate);
    setPosition(pos);
    _node->setMaterialFlag(video::EMF_LIGHTING, false);
    _oldpos = pos;
}

Luigi::~Luigi()
{
}

void Luigi::setWalkAnimation()
{
    irr::core::vector3df extent;
    irr::f32 factor = 0;
    irr::core::vector3df oldPosition = _node->getPosition();
    irr::core::vector3df oldRotation = _node->getRotation();
    irr::core::vector3df oldScale = _node->getScale();

    _node->remove();
    _node = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh("Models/Luigi/luigi_running.b3d"));
    extent = _node->getTransformedBoundingBox().getExtent();
    factor = 12.5 / extent.X;
    irr::core::vector3d<irr::f32> factorEscalate(factor, factor, factor);
    _node->setScale(factorEscalate);
    if (_node) {
        _node->setMaterialTexture(0, _driver->getTexture("Models/Luigi/luigi_texture_2.png"));
    }
    _node->setPosition(oldPosition);
    _node->setRotation(oldRotation);
    _node->setScale(oldScale);
    _node->setAnimationSpeed(90);
    _node->setMaterialFlag(video::EMF_LIGHTING, false);
}

void Luigi::setIdleAnimation()
{
    irr::core::vector3df extent;
    irr::f32 factor = 0;
    irr::core::vector3df oldPosition = _node->getPosition();
    irr::core::vector3df oldRotation = _node->getRotation();
    irr::core::vector3df oldScale = _node->getScale();

    _node->remove();
    _node = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh("Models/Luigi/luigi_idle.b3d"));
    extent = _node->getTransformedBoundingBox().getExtent();
    factor = 12.5 / extent.X;
    irr::core::vector3d<irr::f32> factorEscalate(factor, factor, factor);
    _node->setScale(factorEscalate);
    if (_node) {
        _node->setMaterialTexture(0, _driver->getTexture("Models/Luigi/luigi_texture_2.png"));
    }
    _node->setPosition(oldPosition);
    _node->setRotation(oldRotation);
    _node->setScale(oldScale);
    _node->setMaterialFlag(video::EMF_LIGHTING, false);
}

void Luigi::setWinAnimation()
{
    irr::core::vector3df extent;
    irr::f32 factor = 0;
    irr::core::vector3df oldPosition = _node->getPosition();
    irr::core::vector3df oldRotation = _node->getRotation();
    irr::core::vector3df oldScale = _node->getScale();

    _node->remove();
    _node = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh("Models/Luigi/luigi_win.b3d"));
    extent = _node->getTransformedBoundingBox().getExtent();
    factor = 12.5 / extent.X;
    irr::core::vector3d<irr::f32> factorEscalate(factor, factor, factor);
    _node->setScale(factorEscalate);
    if (_node) {
        _node->setMaterialTexture(0, _driver->getTexture("Models/Luigi/luigi_texture_2.png"));
    }
    _node->setPosition(oldPosition);
    _node->setRotation(oldRotation);
    _node->setScale(oldScale);
    _node->setMaterialFlag(video::EMF_LIGHTING, false);
}