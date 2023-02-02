/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Wario
*/

#include "Wario.hpp"

#include <iostream>

Wario::Wario(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver, irr::IrrlichtDevice *device, EventReceiver &receiver, 
irr::core::vector3df pos, State state) :
APlayers(pos, smgr, driver, device, receiver, state)
{
    irr::core::vector3df extent;
    irr::f32 factor = 0;
    _mesh = smgr->getMesh("Models/Wario/wario_idle.b3d");
    irr::core::aabbox3df box = _mesh->getBoundingBox();
    box.MinEdge.X = -2.11398;
    box.MinEdge.Y = -0.0258841;
    box.MinEdge.Z = -0.934407;
    box.MaxEdge.X = 2.08931;
    box.MaxEdge.Y = 3.19308;
    box.MaxEdge.Z = 0.905828;
    _mesh->setBoundingBox(box);
    if (!_mesh)
        exit(84);
    _node = smgr->addAnimatedMeshSceneNode(_mesh);
    if (_node)
        _node->setMaterialTexture(0, driver->getTexture("Models/Wario/wario_texture.png"));
    extent = _node->getBoundingBox().getExtent();
    factor = 7.0 / extent.X;
    irr::core::vector3d<irr::f32> factorEscalate(factor, factor, factor);
    _node->setScale(irr::core::vector3df{factorEscalate.X, factorEscalate.Y + 6, factorEscalate.Z});
    setPosition(pos);
    _node->setMaterialFlag(video::EMF_LIGHTING, false);
    _oldpos = pos;
}

Wario::~Wario()
{
}

void Wario::setWalkAnimation()
{
    irr::core::vector3df extent;
    irr::f32 factor = 0;
    irr::core::vector3df oldPosition = _node->getPosition();
    irr::core::vector3df oldRotation = _node->getRotation();
    irr::core::vector3df oldScale = _node->getScale();

    _node->remove();
    _node = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh("Models/Wario/wario_run.b3d"));
    extent = _node->getTransformedBoundingBox().getExtent();
    factor = 10.5 / extent.X;
    irr::core::vector3d<irr::f32> factorEscalate(factor, factor, factor);
    _node->setScale(factorEscalate);
    if (_node) {
        _node->setMaterialTexture(0, _driver->getTexture("Models/Wario/wario_texture.png"));
    }
    _node->setPosition(oldPosition);
    _node->setRotation(oldRotation);
    _node->setScale(oldScale);
    _node->setAnimationSpeed(90);
    _node->setMaterialFlag(video::EMF_LIGHTING, false);
}

void Wario::setIdleAnimation()
{
    irr::core::vector3df extent;
    irr::f32 factor = 0;
    irr::core::vector3df oldPosition = _node->getPosition();
    irr::core::vector3df oldRotation = _node->getRotation();
    irr::core::vector3df oldScale = _node->getScale();

    _node->remove();
    _node = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh("Models/Wario/Wario_idle.b3d"));
    extent = _node->getTransformedBoundingBox().getExtent();
    factor = 8.5 / extent.X;
    irr::core::vector3d<irr::f32> factorEscalate(factor, factor, factor);
    _node->setScale(factorEscalate);
    if (_node) {
        _node->setMaterialTexture(0, _driver->getTexture("Models/Wario/wario_texture.png"));
    }
    _node->setPosition(oldPosition);
    _node->setRotation(oldRotation);
    _node->setScale(oldScale);
    _node->setMaterialFlag(video::EMF_LIGHTING, false);
}

void Wario::setWinAnimation()
{
    irr::core::vector3df extent;
    irr::f32 factor = 0;
    irr::core::vector3df oldPosition = _node->getPosition();
    irr::core::vector3df oldRotation = _node->getRotation();
    irr::core::vector3df oldScale = _node->getScale();

    _node->remove();
    _node = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh("Models/Wario/wario_win.b3d"));
    extent = _node->getTransformedBoundingBox().getExtent();
    factor = 8.5 / extent.X;
    irr::core::vector3d<irr::f32> factorEscalate(factor, factor, factor);
    _node->setScale(factorEscalate);
    if (_node) {
        _node->setMaterialTexture(0, _driver->getTexture("Models/Wario/wario_texture.png"));
    }
    _node->setPosition(oldPosition);
    _node->setRotation(oldRotation);
    _node->setScale(oldScale);
    _node->setMaterialFlag(video::EMF_LIGHTING, false);
}