//
// Created by njoachim on 05/06/19.
//

#include "Map.hpp"
#include <time.h>
#include <iostream>
#include <algorithm>
#include "../PowerUp/APowerUp.hpp"

using namespace irr;
using namespace video;
using namespace core;

Map::Map(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver, irr::IrrlichtDevice* device, int complexity, int powerUp, float density) :
_smgr(smgr), _driver(driver), _device(device), _map(), _complexity(complexity), _boosts(powerUp), _density(density)
{
    irr::core::vector3df pos[] = {{70, 0, 0}, {-70, 0, 0}, {0, 0, 70},
        {0, 0, -70}};

    _terrain = smgr->addCubeSceneNode(10, 0, -1,
        irr::core::vector3df(0, -30, 0),
        irr::core::vector3df(0, 0, 0),
        irr::core::vector3df(14, 5, 14));

    _terrain->setMaterialTexture(0, _driver->getTexture("ressources/Planet/stone.png"));
    _terrain->setMaterialFlag(EMF_LIGHTING, true);
    _terrain->setVisible(false);

    _podium = _smgr->addMeshSceneNode(_smgr->getMesh("Models/podium.3ds"), 0, -1);
    _podium->setMaterialTexture(0, _driver->getTexture("Models/podium.png"));
    _podium->setVisible(false);
    _podium->setPosition({0, 0, 80});
    _podium->setScale({2, 2, 2});

    for (int i = 0; i < 4; i++) {
         if (i < 2) {
             _wall[i] = smgr->addCubeSceneNode(10, 0, -1, pos[i],
                 irr::core::vector3df(0, 0, 0),
                 irr::core::vector3df(0.01, 1, 14));
         } else {
             _wall[i] = smgr->addCubeSceneNode(10, 0, -1, pos[i],
                 irr::core::vector3df(0, 90, 0),
                 irr::core::vector3df(0.01, 1, 14));
         }
         _wall[i]->setVisible(false);
    }
    for (int y = 0; y < 14; y++) {
        std::vector<ABlock *> vec;
        for (int x = 0; x < 14; x++)
            vec.push_back(nullptr);
        _map.emplace_back(vec);
    }
    fillMap();
}

Map::Map(Map const &maps) noexcept {
    (void)maps;//IMPLEMENT HERE
}

Map::Map(Map &&map) noexcept : Map{map} {
}

Map::~Map() noexcept {
    _terrain->remove();
    for (int i = 0; i < 4; i ++)
        _wall[i]->remove();
    for (auto &ver : _map) {
        for (auto &hor : ver)
            if (hor != nullptr)
                 delete hor;
    }
    for (auto &ver : _powerUp) {
            if (ver != nullptr)
                delete ver;
    }
    _podium->remove();
}

Map &Map::operator=(Map const &map) noexcept {
    (void)map;//IMPLEMENT HERE
    return *this;
}

Map &Map::operator=(Map &&map) noexcept {
    return *this = map;
}

void Map::createMap(std::vector<std::vector<int>> map)
{
    _terrain->setVisible(true);
    _mapFillWithInt = map;
    for (int y = 0; y < 14; y++) {
        for (int x = 0; x < 14; x++) {
            if (_mapFillWithInt[y][x] == 1) {
                _map[y][x] = new ABlock(_smgr, _smgr->addMeshSceneNode(
                    _smgr->getMesh("Models/Blocks/Block.obj")->getMesh(0), 0,
                    -1,
                    irr::core::vector3df(-65 + (x * 10), -5, 65 + (-y * 10))),
                    _driver, _driver->getTexture("Models/Blocks/Block.png"),
                    _device, false, 50);
            }
            if (_mapFillWithInt[y][x] == 4) {
                _map[y][x] = new ABlock(_smgr, _smgr->addMeshSceneNode(
                    _smgr->getMesh("Models/Blocks/Brick.obj")->getMesh(0), 0,
                    -1,
                    irr::core::vector3df(-65 + (x * 10), -5, 65 + (-y * 10))),
                    _driver, _driver->getTexture("Models/Blocks/Brick.png"),
                    _device, true, 50);
                if (_map[y][x]->getPowerUp() != nullptr) {
                    _powerUp.push_back(_map[y][x]->getPowerUp());
                }
            }
        }
    }
    _podium->setVisible(true);
}

void Map::createMap()
{
    _terrain->setVisible(true);
    for (int y = 0; y < 14; y++) {
        for (int x = 0; x < 14; x++) {
            if (_mapFillWithInt[y][x] == 1) {
                _map[y][x] = new ABlock(_smgr, _smgr->addMeshSceneNode(
                    _smgr->getMesh("Models/Blocks/Block.obj")->getMesh(0), 0,
                    -1,
                    irr::core::vector3df(-65 + (x * 10), -5, 65 + (-y * 10))),
                    _driver, _driver->getTexture("Models/Blocks/Block.png"),
                    _device, false, _boosts);
            }
            if (_mapFillWithInt[y][x] == 4) {
                _map[y][x] = new ABlock(_smgr, _smgr->addMeshSceneNode(
                    _smgr->getMesh("Models/Blocks/Brick.obj")->getMesh(0), 0,
                    -1,
                    irr::core::vector3df(-65 + (x * 10), -5, 65 + (-y * 10))),
                    _driver, _driver->getTexture("Models/Blocks/Brick.png"),
                    _device, true, _boosts);
                if (_map[y][x]->getPowerUp() != nullptr) {
                    _powerUp.push_back(_map[y][x]->getPowerUp());
                }
            }
        }
    }
    _podium->setVisible(true);
}

bool Map::checkAround(int dir, int &x, int &y, int &path)
{
    if (dir == UP && x != 7 && _mapFillWithInt[y - 1][x] == 1 && (_mapFillWithInt[y - 1][x - 1] != 0 && _mapFillWithInt[y - 1][x + 1] != 0)) {
        _mapFillWithInt[y - 1][x] = 0;
        y--;
        path++;
        return true;
    }
    if (dir == DOWN && x != 7 && _mapFillWithInt[y + 1][x] == 1 && (_mapFillWithInt[y + 1][x - 1] != 0 && _mapFillWithInt[y + 1][x + 1] != 0)) {
        _mapFillWithInt[y + 1][x] = 0;
        y++;
        path++;
        return true;
    }
    if (dir == LEFT && y != 7 && _mapFillWithInt[y][x - 1] == 1 && (_mapFillWithInt[y + 1][x - 1] != 0 && _mapFillWithInt[y - 1][x - 1] != 0)) {
        _mapFillWithInt[y][x - 1] = 0;
        x--;
        path++;

        return true;
    }
    if (dir == RIGHT && y != 7 &&  _mapFillWithInt[y][x + 1] == 1 && (_mapFillWithInt[y + 1][x + 1] != 0 && _mapFillWithInt[y - 1][x + 1] != 0)) {
        _mapFillWithInt[y][x + 1] = 0;
        x++;
        path++;
        return true;
    }
    return (x != 7 && _mapFillWithInt[y - 1][x] == 1 && (_mapFillWithInt[y - 1][x - 1] != 0 && _mapFillWithInt[y - 1][x + 1] != 0)) ||
        (x != 7 && _mapFillWithInt[y + 1][x] == 1 && (_mapFillWithInt[y + 1][x - 1] != 0 && _mapFillWithInt[y + 1][x + 1] != 0)) ||
        (y != 7 && _mapFillWithInt[y][x - 1] == 1 && (_mapFillWithInt[y + 1][x - 1] != 0 && _mapFillWithInt[y - 1][x - 1] != 0)) ||
        (y != 7 && _mapFillWithInt[y][x + 1] == 1 && (_mapFillWithInt[y + 1][x + 1] != 0 && _mapFillWithInt[y - 1][x + 1] != 0));
}

void Map::checkBackward(int &x, int &y)
{
    std::vector<std::pair<int, int>> pos;
    std::vector<std::vector<int>> tmp = _mapFillWithInt;

    while (!(
        (x != 7 && _mapFillWithInt[y - 1][x] == 1 && (_mapFillWithInt[y - 1][x - 1] != 0 && _mapFillWithInt[y - 1][x + 1] != 0)) ||
        (x != 7 && _mapFillWithInt[y + 1][x] == 1 && (_mapFillWithInt[y + 1][x - 1] != 0 && _mapFillWithInt[y + 1][x + 1] != 0)) ||
        (y != 7 && _mapFillWithInt[y][x - 1] == 1 && (_mapFillWithInt[y + 1][x - 1] != 0 && _mapFillWithInt[y - 1][x - 1] != 0)) ||
        (y != 7 && _mapFillWithInt[y][x + 1] == 1 && (_mapFillWithInt[y + 1][x + 1] != 0 && _mapFillWithInt[y - 1][x + 1] != 0)))) {
        int path = 0;

        !tmp[y - 1][x] ? path++ : 0;
        !tmp[y + 1][x] ? path++ : 0;
        !tmp[y][x - 1] ? path++ : 0;
        !tmp[y][x + 1] ? path++ : 0;

        if (path >= 2) {
            pos.emplace_back(std::pair<int, int>{x,  y});
        }
        if (tmp[y][x - 1] == 0) {
            x--;
            tmp[y][x] = 3;
        }
        else if (tmp[y][x + 1] == 0) {
            x++;
            tmp[y][x] = 3;
        }
        else if (tmp[y - 1][x] == 0) {
            y--;
            tmp[y][x] = 3;
        }
        else if (tmp[y + 1][x] == 0) {
            y++;
            tmp[y][x] = 3;
        }
        else if (!pos.empty()){
            x = pos[0].first;
            y = pos[0].second;
            pos.erase(pos.begin());
        } else {
            break;
        }
    }
}

void Map::completeMap()
{
    _mapFillWithInt.erase(_mapFillWithInt.begin());
    _mapFillWithInt.erase(_mapFillWithInt.end() - 1);
    for (int y = 0; y < 7; ++y) {
        _mapFillWithInt[y].erase(_mapFillWithInt[y].begin());
        _mapFillWithInt[y].erase(_mapFillWithInt[y].end() - 1);
        for (int x = 0; x < 7; ++x)
            _mapFillWithInt[y].emplace_back(_mapFillWithInt[y][6 - x]);
    }
    for (int y = 0; y < 7; ++y)
        _mapFillWithInt.emplace_back(_mapFillWithInt[6 - y]);
}

void Map::fillMap()
{
    srand(time(nullptr));

    _mapFillWithInt.push_back({2, 2, 2, 2, 2, 2, 2 ,2 ,2});
    for (int y = 0; y < 7; y++) {
        std::vector<int> col = {2 ,1, 1, 1, 1, 1, 1, 1, 2};
        if (y == 0)
            col[1] = 0;
        _mapFillWithInt.push_back(col);
    }
    _mapFillWithInt.push_back({2, 2, 2, 2, 2, 2, 2 ,2 ,2});

    int x = 1;
    int y = 2;
    int nbr = 0;
    int path = 0;

    _mapFillWithInt[y][x] = 0;
    _mapFillWithInt[1][2] = 0;
    for (int i = 0; true; i++) {
        int dir = rand() % 4;
        if (i > _complexity && std::find(_mapFillWithInt[7].begin(),_mapFillWithInt[7].end(), 0) != _mapFillWithInt[7].end()) {
            int i = 1;
            for (i; _mapFillWithInt[i][7] != 0 && i < 8; i++);
            if (i != 8)
                break;
        }
        if (!checkAround(dir, x, y, path))
            checkBackward(x, y);
    }
    path = path * _density; //nombre de blocs destructibles
    while (nbr < path) {
        for (y = 1; y < 8; y++) {
            for (x = 1; x < 8; x++) {
                if (_mapFillWithInt[y][x] == 0 && !(y == 1 && x == 2) &&
                    !(y == 2 && x == 1) && !(y == 1 && x == 1) &&
                    rand() % 2 == 0) {
                    nbr++;
                    _mapFillWithInt[y][x] = 4;
                }
                if (nbr > path)
                    break;
            }
            if (nbr > path)
                break;
        }
        if (nbr > path)
            break;
    }
    completeMap();
}

std::vector<std::vector<ABlock *>> &Map::getMap()
{
    return _map;
}

std::vector<irr::scene::IMeshSceneNode *> Map::getWall() const
{
    return _wall;
}

void Map::playerPowerUp(APlayers *player)
{
    int itterator = 0;

    for (auto *itt : _powerUp) {
        if (itt->getMesh()->getTransformedBoundingBox().intersectsWithBox(player->_node->getTransformedBoundingBox())) {
            itt->activatePower(*player);
            _powerUp.erase(_powerUp.begin() + itterator);
            delete itt;
        }
        itterator++;
    }
}