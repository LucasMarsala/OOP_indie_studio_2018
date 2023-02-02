//
// Created by njoachim on 11/06/19.
//

#include "Bomb.hpp"
#include <iostream>
#include "../Blocks/ABlock.hpp"

using namespace irr;

Bomb::Bomb(irr::scene::ISceneManager *smgr, irr::scene::IMeshSceneNode *cube, irr::IrrlichtDevice *device, irr::video::ITexture *texture, int power, std::vector<std::vector<ABlock *>> *map)
    : _smgr(smgr), _bomb(cube), _device(device), _texture(texture), _power(power), _map(map)
{
    if (texture) {
        cube->setMaterialTexture(0, texture);
        cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }
    irr::core::vector3df extent = cube->getTransformedBoundingBox().getExtent();
    irr::f32 factor = 10 / extent.X - 0.06;
    irr::core::vector3d<irr::f32> factorEscalate(factor, factor, factor);
    cube->setScale(factorEscalate);
    _scale = factor;
    _indexX = (-65 - cube->getPosition().X) / 10;
    _indexY = (65 - cube->getPosition().Z) / 10 / -1;
    _indexY < 0 ? _indexY *= -1 : 0;
    _indexX < 0 ? _indexX *= -1 : 0;
    _ps = _smgr->addParticleSystemSceneNode(false);
    _ps2 = _smgr->addParticleSystemSceneNode(false);
    _bombCenter.X = cube->getPosition().X;
    _bombCenter.Z = cube->getPosition().Z;
}

Bomb::~Bomb()
{
    _ps->remove();
    _ps2->remove();
}

void Bomb::displayParticles()
{
    scene::IParticleEmitter* em = _ps->createBoxEmitter(
        _vertical,
       core::vector3df(0.0f, 0.0f,0.0f),
       200 * _power , 200 * _power,
       video::SColor(0,249,255,0),
       video::SColor(0,255,0,0),
       2000,2000,0,
       core::dimension2df(1.f,1.f),
       core::dimension2df(1.f,1.f));

    _ps->setEmitter(em);
    em->drop();
    em = _ps->createBoxEmitter(
        _horizontal,
        core::vector3df(0.0f, 0.0f,0.0f),
        200 * _power , 200 * _power,
        video::SColor(0,249,255,0),
        video::SColor(0,255,0,0),
        2000,2000,0,
        core::dimension2df(1.f,1.f),
        core::dimension2df(1.f,1.f));
    _ps2->setEmitter(em);
    em->drop();

    _ps->setScale(core::vector3df(10, 10, 10));
    _ps->setPosition(core::vector3df(_bomb->getPosition().X - 5, 0 ,_bomb->getPosition().Z - 5));
    _ps->setMaterialFlag(video::EMF_LIGHTING, true);
    _ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, true);
    _ps2->setScale(core::vector3df(10, 10, 10));
    _ps2->setPosition(core::vector3df(_bomb->getPosition().X - 5, 0 ,_bomb->getPosition().Z - 5));
    _ps2->setMaterialFlag(video::EMF_LIGHTING, true);
    _ps2->setMaterialFlag(video::EMF_ZWRITE_ENABLE, true);
}

void Bomb::radius(std::vector<std::vector<std::pair<char, irr::core::vector3df>>> * mapPlayer,
std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *mapBomb,
std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *mapRadius)
{
    std::vector<bool> destroyed = {true, true, true, true};

    if (_indexX > 13 || _indexY > 13)
        return;
    for (int i = 1; i <= _power; i++) {
        if (_indexY != 0 && _indexY - i > -1 && destroyed[0]) {
            if ((*_map)[_indexY - i][_indexX] != nullptr && (*_map)[_indexY - i][_indexX]->isDestructible()) {
                (*mapBomb)[_indexY - i][_indexX].first = '0';
                (*mapPlayer)[_indexY - i][_indexX].first = '0';
                (*mapRadius)[_indexY - i][_indexX].first = '0';
                delete (*_map)[_indexY - i][_indexX];
                (*_map)[_indexY - i][_indexX] = nullptr;
                _vertical.MaxEdge.Z++;
                destroyed[0] = false;
            } else if ((*_map)[_indexY - i][_indexX] != nullptr) {
                destroyed[0] = false;
            } else {
                _vertical.MaxEdge.Z++;
            }
        }
        if (_indexY != 13 && _indexY + i < 14 && destroyed[1]) {
            if ((*_map)[_indexY + i][_indexX] != nullptr && (*_map)[_indexY + i][_indexX]->isDestructible()) {
                (*mapBomb)[_indexY + i][_indexX].first = '0';
                (*mapPlayer)[_indexY + i][_indexX].first = '0';
                (*mapRadius)[_indexY + i][_indexX].first = '0';
                delete (*_map)[_indexY + i][_indexX];
                (*_map)[_indexY + i][_indexX] = nullptr;
                destroyed[1] = false;
                _vertical.MinEdge.Z--;
            } else if ((*_map)[_indexY + i][_indexX] != nullptr) {
                destroyed[1] = false;
            } else {
                _vertical.MinEdge.Z--;
            }
        }
        if (_indexX != 0 && _indexX - i > -1 && destroyed[2]) {
            if ((*_map)[_indexY][_indexX - i] != nullptr && (*_map)[_indexY][_indexX - i]->isDestructible()) {
                (*mapBomb)[_indexY][_indexX - i].first = '0';
                (*mapPlayer)[_indexY][_indexX - i].first = '0';
                (*mapRadius)[_indexY][_indexX - i].first = '0';
                delete (*_map)[_indexY][_indexX - i];
                (*_map)[_indexY][_indexX - i] = nullptr;
                destroyed[2] = false;
                _horizontal.MinEdge.X--;
            } else if ((*_map)[_indexY][_indexX - i] != nullptr) {
                destroyed[2] = false;
            } else {
                _horizontal.MinEdge.X--;
            }
        }
        if (_indexX != 13 && _indexX + i < 14 && destroyed[3]) {
            if ((*_map)[_indexY][_indexX + i] != nullptr && (*_map)[_indexY][_indexX + i]->isDestructible()) {
                (*mapBomb)[_indexY][_indexX + i].first = '0';
                (*mapPlayer)[_indexY][_indexX + i].first = '0';
                (*mapRadius)[_indexY][_indexX + i].first = '0';
                delete (*_map)[_indexY][_indexX + i];
                (*_map)[_indexY][_indexX + i] = nullptr;
                destroyed[3] = false;
                _horizontal.MaxEdge.X++;
            } else if ((*_map)[_indexY][_indexX + i] != nullptr) {
                destroyed[3] = false;
            } else {
                    _horizontal.MaxEdge.X++;
            }
        }
    }
}

void Bomb::createSound()
{
    if (!_buff.loadFromFile("ressources/music/bomb_explo.ogg"))
        throw ErrorGetMusic("Couldn't get sound file");
    _sound.setBuffer(_buff);
    _sound.setVolume(80);
}

bool Bomb::detonate(std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *mapPlayer,
std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *mapBomb,
std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *mapRadius,double &deltaFrame)
{
    static float scale = _scale;

    _time += deltaFrame;

    if (_time < _detonateTime && _removed) {
            _bomb->setScale(irr::core::vector3df{_scale, _scale, _scale});
            if (_trig) {
                _scale += 0.09  * deltaFrame;
                if (_scale > 0.07)
                    _trig = false;
            }
            if (!_trig) {
                _scale -= 0.09 * deltaFrame;
                if (_scale < scale)
                    _trig = true;
            }
    } else {
        if (_removed) {
            _removed = false;
            radius(mapPlayer, mapBomb, mapRadius);
            createSound();
            _sound.play();
            displayParticles();
             _bomb->remove();
             _bomb = nullptr;
            _time = 0;
        }
        if (_time > 0.5) {
            _scale = scale;
            return true;
        }
    }
    return false;
}

void Bomb::deleteMesh()
{
    if (_removed)
        _bomb->remove();
}

void Bomb::setDetonateTime(float detonateTime)
{
    _detonateTime = detonateTime;
}

irr::scene::IMeshSceneNode *Bomb::getCube() const
{
    return _bomb;
}

irr::scene::IParticleSystemSceneNode *Bomb::getParticleOne() const
{
    return _ps;
}

irr::scene::IParticleSystemSceneNode *Bomb::getParticleTwo() const
{
    return _ps2;
}

int Bomb::getPower() const
{
    return _power;
}

irr::core::vector3df Bomb::getBombCenter() const
{
    return _bombCenter;
}