/*
** EPITECH PROJECT, 2019
** game
** File description:
** Game
*/

#include "Game.hpp"
#include <iostream>
#include "../Map/Map.hpp"
#include "../APlayers/APlayers.hpp"
#include "../Characters/Mario/Mario.hpp"
#include "../Properties/Properties.hpp"
#include <algorithm>
#include <fstream>

using namespace irr;
using namespace core;
using namespace video;

#include "../Window/Window.hpp"
#include "../GUI/MainMenu.hpp"
#include "../GUI/EventReceiver.hpp"
#include "../Bomb/Bomb.hpp"
#include "../PowerUp/APowerUp.hpp"
#include "../AI/AAi.hpp"

Game::Game(IrrlichtDevice *device, IGUIEnvironment *gui, ISceneManager *sceneManager, IVideoDriver *driver, EventReceiver *receiver,
int difficulty) noexcept :
_device(device), _guiEnv(gui), _sceneManager(sceneManager), _driver(driver), _receiver(receiver), _soundBar(100), _difficulty(difficulty)
{
    _map = nullptr;
}

Game::~Game() noexcept
{
    if (_map) {
        delete _map;
    }
    for (auto &player : _players) {
        delete player;
    }
    _sceneManager->getActiveCamera()->setTarget({0, 0, 0});
}

void Game::createMusic()
{
    if (!_music.openFromFile("ressources/music/in_game_music.ogg"))
        throw ErrorGetMusic("Couldn't get music file.\n");
    _music.play();
    _music.setVolume(40);
    _music.setLoop(true);
}

void Game::movePlayer(irr::f32 deltaFrame)
{
    for (auto player : _players) {
        if (player->getState() == P1 && !player->isDead()) {
            player->_prop.Move(*player, *_receiver, deltaFrame, player->getDirection(),
            std::vector<irr::EKEY_CODE>{irr::KEY_KEY_Z, irr::KEY_KEY_S, irr::KEY_KEY_Q, irr::KEY_KEY_D});
            for (int i = 0; i < 14; i++) {
                bool leave = false;
                for (int j = 0; j < 14; j++) {
                    if (_mapPlayer[i][j].first == 'P') {
                        if (player->getPosition().X - _mapPlayer[i][j].second.X > 7) {
                            _mapPlayer[i][j].first = '0';
                            _mapPlayer[i][j + 1].first = 'P';
                        }
                        if (player->getPosition().X - _mapPlayer[i][j].second.X < -7) {
                            _mapPlayer[i][j].first = '0';
                            _mapPlayer[i][j - 1].first = 'P';
                        }
                        if (player->getPosition().Z - _mapPlayer[i][j].second.Z > 7) {
                            _mapPlayer[i][j].first = '0';
                            _mapPlayer[i - 1][j].first = 'P';
                        }
                        if (player->getPosition().Z - _mapPlayer[i][j].second.Z < -7) {
                            _mapPlayer[i][j].first = '0';
                            _mapPlayer[i + 1][j].first = 'P';
                        }
                        leave = true;
                        break;
                    }
                }
                if (leave)
                    break;
            }
        }
        if (player->getState() == P2 && !player->isDead()) {
            player->_prop.Move(*player, *_receiver, deltaFrame, player->getDirection(),
             std::vector<irr::EKEY_CODE>{irr::KEY_UP, irr::KEY_DOWN, irr::KEY_LEFT, irr::KEY_RIGHT});
            for (int i = 0; i < 14; i++) {
                bool leave = false;
                for (int j = 0; j < 14; j++) {
                    if (_mapPlayer[i][j].first == 'F') {
                        if (player->getPosition().X - _mapPlayer[i][j].second.X > 8) {
                            _mapPlayer[i][j].first = '0';
                            _mapPlayer[i][j + 1].first = 'F';
                        }
                        if (player->getPosition().X - _mapPlayer[i][j].second.X < -8) {
                            _mapPlayer[i][j].first = '0';
                            _mapPlayer[i][j - 1].first = 'F';
                        }
                        if (player->getPosition().Z - _mapPlayer[i][j].second.Z > 8) {
                            _mapPlayer[i][j].first = '0';
                            _mapPlayer[i - 1][j].first = 'F';
                        }
                        if (player->getPosition().Z - _mapPlayer[i][j].second.Z < -8) {
                            _mapPlayer[i][j].first = '0';
                            _mapPlayer[i + 1][j].first = 'F';
                        }
                        leave = true;
                        break;
                    }
                }
                if (leave)
                    break;
            }
        }
    }
}

void Game::createMap(std::vector<State> players, std::vector<std::vector<int>> map)
{
    float X = -65;
    float Z = 65;

    _map = new Map(_sceneManager, _driver, _device, 200, 3, 2/3);
    _map->createMap(map);
    loadPlayers(std::vector<int>{0, 1, 2, 3}, players);
    for (auto &itt : _players) {
        itt->setMap(_map->getMap());
    }
    for (int i = 0; i < 14; i++) {
        _mapAI.push_back(std::vector<std::pair<char, irr::core::vector3df>>{
            {'0', irr::core::vector3df{X, 0, Z}},
            {'0', irr::core::vector3df{X + 10, 0, Z}},
            {'0', irr::core::vector3df{X + 20, 0, Z}},
            {'0', irr::core::vector3df{X + 30, 0, Z}},
            {'0', irr::core::vector3df{X + 40, 0, Z}},
            {'0', irr::core::vector3df{X + 50, 0, Z}},
            {'0', irr::core::vector3df{X + 60, 0, Z}},
            {'0', irr::core::vector3df{X + 70, 0, Z}},
            {'0', irr::core::vector3df{X + 80, 0, Z}},
            {'0', irr::core::vector3df{X + 90, 0, Z}},
            {'0', irr::core::vector3df{X + 100, 0, Z}},
            {'0', irr::core::vector3df{X + 110, 0, Z}},
            {'0', irr::core::vector3df{X + 120, 0, Z}},
            {'0', irr::core::vector3df{X + 130, 0, Z}}});
        for (int j = 0; j < 14; j++) {
            if (_map->_mapFillWithInt[i][j] == 1)
                _mapAI[i][j].first = 'H';
            else if (_map->_mapFillWithInt[i][j] == 4)
                _mapAI[i][j].first = 'S';
            else
                _mapAI[i][j].first = _map->_mapFillWithInt[i][j] + 48;
        }
        Z -= 10;
    }
    _mapPlayer = _mapAI;
    _mapRadius = _mapAI;
    for (auto &player : _players) {
        if (player->getState() == P1 || player->getState() == P2) {
            int bestX = 0;
            int bestZ = 0;
            int tmp = 0;
            int tmp2 = 0;
            int nb = 100;
            int nb2 = 100;
            for (int i = 0; i < 14; i++) {
                for (int j = 0; j < 14; j++) {
                    tmp = abs(player->getPosition().X - (_mapPlayer)[i][j].second.X);
                    if (tmp < nb) {
                        bestX = j;
                        nb = tmp;
                    }
                    tmp2 = abs(player->getPosition().Z - (_mapPlayer)[i][j].second.Z);
                    if (tmp2 < nb2) {
                        bestZ = i;
                        nb2 = tmp2;
                    }
                }
            }
            if (player->getPosition().Z <= 70) {
                player->setPosition(
                    irr::core::vector3df{(_mapPlayer)[bestZ][bestX].second.X, 0,
                        (_mapPlayer)[bestZ][bestX].second.Z});
            } else {
                player->setDead(true);
            }
        }
    }
    for (auto &itt : _players) {
        if (itt->getState() == AI)
            itt->_ai = new AAi(&_mapPlayer, &_mapAI, &_mapRadius, itt);
        if (itt->getState() == P1 || itt->getState() == P2) {
            for (int i = 0; i < 14; i++) {
                for (int j = 0; j < 14; j++) {
                    if (itt->getState() == P1 && !itt->isDead() && int(itt->getPosition().X) ==
                        _mapPlayer[i][j].second.X &&
                        int(itt->getPosition().Z) == _mapPlayer[i][j].second.Z)
                        _mapPlayer[i][j].first = 'P';
                    if (itt->getState() == P2 && !itt->isDead() && int(itt->getPosition().X) ==
                        _mapPlayer[i][j].second.X &&
                        int(itt->getPosition().Z) == _mapPlayer[i][j].second.Z)
                        _mapPlayer[i][j].first = 'F';
                }
            }
        }
    }
}

void Game::createMap(std::vector<State> players, int complexity, int powerUp, float density)
{
    float X = -65;
    float Z = 65;

    _map = new Map(_sceneManager, _driver, _device, complexity, powerUp, density);
    _map->createMap();
    createMusic();
    _pos.push_back(vector3df{-65, 0, 65});
    _pos.push_back(vector3df{65, 0, 65});
    _pos.push_back(vector3df{-65, 0, -65});
    _pos.push_back(vector3df{65, 0, -65});
    loadPlayers(std::vector<int>{0, 1, 2, 3}, players);
    for (auto &itt : _players) {
        itt->setMap(_map->getMap());
    }
    for (int i = 0; i < 14; i++) {
        _mapAI.push_back(std::vector<std::pair<char, irr::core::vector3df>>
        {{'0', irr::core::vector3df{X, 0, Z}},
        {'0', irr::core::vector3df{X + 10, 0, Z}},
        {'0', irr::core::vector3df{X + 20, 0, Z}},
        {'0', irr::core::vector3df{X + 30, 0, Z}},
        {'0', irr::core::vector3df{X + 40, 0, Z}},
        {'0', irr::core::vector3df{X + 50, 0, Z}},
        {'0', irr::core::vector3df{X + 60, 0, Z}},
        {'0', irr::core::vector3df{X + 70, 0, Z}},
        {'0', irr::core::vector3df{X + 80, 0, Z}},
        {'0', irr::core::vector3df{X + 90, 0, Z}},
        {'0', irr::core::vector3df{X + 100, 0, Z}},
        {'0', irr::core::vector3df{X + 110, 0, Z}},
        {'0', irr::core::vector3df{X + 120, 0, Z}},
        {'0', irr::core::vector3df{X + 130, 0, Z}}});
        for (int j = 0; j < 14; j++) {
            if (_map->_mapFillWithInt[i][j] == 1)
                _mapAI[i][j].first = 'H';
            else if (_map->_mapFillWithInt[i][j] == 4)
                _mapAI[i][j].first = 'S';
            else
                _mapAI[i][j].first = _map->_mapFillWithInt[i][j] + 48;
        }
        Z -= 10;
    }
    _mapPlayer = _mapAI;
    _mapRadius = _mapAI;
    for (auto &itt : _players) {
        if (itt->getState() == AI)
            itt->_ai = new AAi(&_mapPlayer, &_mapAI, &_mapRadius, itt);
        if (itt->getState() == P1 || itt->getState() == P2) {
            for (int i = 0; i < 14; i++) {
                for (int j = 0; j < 14; j++) {
                    if (itt->getState() == P1 && int(itt->getPosition().X) == _mapPlayer[i][j].second.X &&
                    int(itt->getPosition().Z) == _mapPlayer[i][j].second.Z)
                        _mapPlayer[i][j].first = 'P';
                    if (itt->getState() == P2 && int(itt->getPosition().X) == _mapPlayer[i][j].second.X &&
                    int(itt->getPosition().Z) == _mapPlayer[i][j].second.Z)
                        _mapPlayer[i][j].first = 'F';
                }
            }
        }
    }
}

void Game::collideWithExplosion(Players::APlayers *player)
{
    std::vector<bool> tmp{true, true, true, true};
    for (auto play : _players) {
        for (int i = 0; i < play->getBombs().size(); i++) {
            if ((!play->getBombs()[i]->_removed && player->_prop.CollideWith(*player, *(play->getBombs()[i]->getParticleOne()), &tmp,
                std::vector<irr::f32>{0, 0, 0})) || (!play->getBombs()[i]->_removed && player->_prop.CollideWith(*player,
                        *(play->getBombs()[i]->getParticleTwo()), &tmp,
                        std::vector<irr::f32>{0, 0, 0}))) {
                player->die();
                player->_node->removeAnimators();
            }
        }
    }
}

void Game::collideWithBomb(Players::APlayers *player)
{
    if (player->getState() == P1) {
        for (int i = 0; i < 14; i++) {
            bool leave = false;
            for (int j = 0; j < 14; j++) {
                if (_mapPlayer[i][j].first == 'P') {
                    if (i + 1 < 14 && _mapAI[i + 1][j].first != '0' &&
                    player->getPosition().Z - _mapAI[i + 1][j].second.Z < 8) {
                        player->setDirection(std::vector<bool>{true, false, true, true});
                        leave = true;
                        break;
                    }
                    if (i - 1 >= 0 && _mapAI[i - 1][j].first != '0' &&
                    player->getPosition().Z - _mapAI[i - 1][j].second.Z > -8) {
                        player->setDirection(std::vector<bool>{false, true, true, true});
                        leave = true;
                        break;
                    }
                    if (j - 1 >= 0 && _mapAI[i][j - 1].first != '0' &&
                    player->getPosition().X - _mapAI[i][j - 1].second.X < 8) {
                        player->setDirection(std::vector<bool>{true, true, false, true});
                        leave = true;
                        break;
                    }
                    if (j + 1 < 14 && _mapAI[i][j + 1].first != '0' &&
                    player->getPosition().X - _mapAI[i][j + 1].second.X > -8) {
                        player->setDirection(std::vector<bool>{true, true, true, false});
                        leave = true;
                        break;
                    }
                }
            }
            if (leave)
                break;
        }
    }
    if (player->getState() == P2) {
        for (int i = 0; i < 14; i++) {
            bool leave = false;
            for (int j = 0; j < 14; j++) {
                if (_mapPlayer[i][j].first == 'F') {
                    if (i + 1 < 14 && _mapAI[i + 1][j].first != '0' &&
                    player->getPosition().Z - _mapAI[i + 1][j].second.Z < 8) {
                        player->setDirection(std::vector<bool>{true, false, true, true});
                        leave = true;
                        break;
                    }
                    if (i - 1 >= 0 && _mapAI[i - 1][j].first != '0' &&
                    player->getPosition().Z - _mapAI[i - 1][j].second.Z > -8) {
                        player->setDirection(std::vector<bool>{false, true, true, true});
                        leave = true;
                        break;
                    }
                    if (j - 1 >= 0 && _mapAI[i][j - 1].first != '0' &&
                    player->getPosition().X - _mapAI[i][j - 1].second.X < 8) {
                        player->setDirection(std::vector<bool>{true, true, false, true});
                        leave = true;
                        break;
                    }
                    if (j + 1 < 14 && _mapAI[i][j + 1].first != '0' &&
                    player->getPosition().X - _mapAI[i][j + 1].second.X > -8) {
                        player->setDirection(std::vector<bool>{true, true, true, false});
                        leave = true;
                        break;
                    }
                }
            }
            if (leave)
                break;
        }
    }
}

void Game::collidePlayer(Players::APlayers *player, irr::f32 deltaFrame)
{
    std::vector<bool> direction{true, true, true, true};

    if (abs(player->_oldpos.X) > abs(player->_node->getTransformedBoundingBox().getCenter().X)) {
            if (abs(player->_oldpos.X) - abs(player->_node->getTransformedBoundingBox().getCenter().X) > 3)
                return;
    } else if (abs(player->_node->getTransformedBoundingBox().getCenter().X) - abs(player->_oldpos.X)> 3)
        return;
    if (abs(player->_oldpos.Z) > abs(player->_node->getTransformedBoundingBox().getCenter().Z)) {
        if (abs(player->_oldpos.Z) - abs(player->_node->getTransformedBoundingBox().getCenter().Z) > 3)
            return;
    } else if (abs(player->_node->getTransformedBoundingBox().getCenter().Z) - abs(player->_oldpos.Z)> 3)
        return;
    if (player->getState() == AI) {
        _map->playerPowerUp(player);
        return;
    }
    for (auto it = _map->getMap().begin(); it != _map->getMap().end(); it++) {
        for (int y = 0; y < 14; y++) {
            if ((*it)[y] != nullptr && !player->getIdleState()) {
                if (player->_prop.CollideWith(*player, *(*it)[y]->getCube(), &direction,
                std::vector<irr::f32>{3, 3, 3}, player->getSpeed(), deltaFrame, true)) {
                    player->setDirection(direction);
                    break;
                } else {
                    player->setDirection(direction);
                }
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        if (player->_prop.CollideWith(*player, *_map->getWall()[i], &direction,
            std::vector<irr::f32>{2, 2, 2}, player->getSpeed(), deltaFrame))
            break;
    }
    _map->playerPowerUp(player);
}

void Game::dropPlayerBomb(Players::APlayers *player, irr::EKEY_CODE key)
{
    if (player->getCd() > 0)
        return;
    if (_receiver->isKeyDown(key)) {
        for (int i = 0; i < 14; i++) {
            bool leave = false;
                for (int j = 0; j < 14; j++) {
                    if (player->getState() == P1 && _mapPlayer[i][j].first == 'P') {
                        if (player->dropBomb(_mapAI, irr::core::vector3df{_mapAI[i][j].second.X, 0, _mapAI[i][j].second.Z})) {
                            _mapAI[i][j].first = player->getPower() + 48;
                            player->setCd(0.3);
                            leave = true;
                            break;
                        }
                    }
                    if (player->getState() == P2 && _mapPlayer[i][j].first == 'F') {
                        if (player->dropBomb(_mapAI, irr::core::vector3df{_mapAI[i][j].second.X, 0, _mapAI[i][j].second.Z})) {
                            _mapAI[i][j].first = player->getPower() + 48;
                            player->setCd(0.3);
                            leave = true;
                            break;
                        }
                    }
            }
            player->setCd(0.2);
            if (leave)
                break;
        }
    }
}

void Game::checkMapRadius()
{
    for (auto player : _players) {
        for (int nb = 0; nb < player->getBombs().size(); nb++) {
            for (int i = 0; i < 14; i++) {
                for (int j = 0; j < 14; j++) {
                    if (_mapRadius[i][j].second.X == player->getBombs()[nb]->getBombCenter().X &&
                    _mapRadius[i][j].second.Z == player->getBombs()[nb]->getBombCenter().Z) {
                        _mapRadius[i][j].first = 'X';
                        for (int inc = 0; i + inc < 14 && inc <= player->getBombs()[nb]->getPower() &&
                        _mapRadius[i + inc][j].first != 'S' && _mapRadius[i + inc][j].first != 'H'; inc++)
                            _mapRadius[i + inc][j].first = 'X';
                        for (int inc = 0; i - inc >= 0 && inc <= player->getBombs()[nb]->getPower() &&
                        _mapRadius[i - inc][j].first != 'S' && _mapRadius[i - inc][j].first != 'H'; inc++)
                            _mapRadius[i - inc][j].first = 'X';
                        for (int inc = 0; j + inc < 14 && inc <= player->getBombs()[nb]->getPower() &&
                        _mapRadius[i][j + inc].first != 'S' && _mapRadius[i][j + inc].first != 'H'; inc++)
                            _mapRadius[i][j + inc].first = 'X';
                        for (int inc = 0; j - inc >= 0 && inc <= player->getBombs()[nb]->getPower() &&
                        _mapRadius[i][j - inc].first != 'S' && _mapRadius[i][j - inc].first != 'H'; inc++)
                            _mapRadius[i][j - inc].first = 'X';
                    }
                }
            }
        }
    }
}

void Game::update(irr::f32 deltaFrame)
{
    for (auto player : _players) {
        checkMapRadius();
        player->checkBomb(&_mapPlayer, &_mapAI, &_mapRadius, _time);
        checkMapRadius();
        collideWithExplosion(player);
        if (player->getState() == P1)
            dropPlayerBomb(player, irr::KEY_LSHIFT);
        if (player->getState() == P2)
            dropPlayerBomb(player, irr::KEY_RSHIFT);
        if (player->getState() == P1 || player->getState() == P2) {
            collidePlayer(player, deltaFrame);
            collideWithBomb(player);
        }
        if (player->getState() == AI && !player->isDead()) {
            if (_difficulty == 0)
                player->_ai->doScriptEasy(player, deltaFrame);
            if (_difficulty == 1)
                player->_ai->doScriptMedium(player, deltaFrame);
            if (_difficulty == 2)
                player->_ai->doScriptHard(player, deltaFrame);
            collidePlayer(player, deltaFrame);
        }
        player->subCd(deltaFrame);
    }
    movePlayer(deltaFrame);
    victory();
}

void Game::run(double &time, bool isMenu, int difficulty)
{
    if (_difficulty != difficulty) {
        for (int i = 0; i < 14; i++)
            for (int j = 0; j < 14; j++)
                if (_mapPlayer[i][j].first == 'A')
                    _mapPlayer[i][j].first = '0';
        for (auto &itt : _players) {
            if (itt->getState() == AI) {
                delete itt->_ai;
                itt->_ai = new AAi(&_mapPlayer, &_mapAI, &_mapRadius, itt);
            }
        }
    }
    _difficulty = difficulty;
    _music.setVolume(_soundBar);
    _time = time;
    if (!isMenu)
        update(_time);
}

void Game::loadPlayers(std::vector<int> players, std::vector<State> states)
{
    loadPlayerOne(players[0], states[0]);
    loadPlayerTwo(players[1], states[1]);
    loadPlayerThree(players[2], states[3]);
    loadPlayerFour(players[3], states[2]);
}

void Game::loadPlayerOne(int model, State state)
{
    if (model == 0)
        _players.push_back(new Mario(_sceneManager, _driver, _device, *_receiver, _pos[0], state));
    if (model == 1)
        _players.push_back(new Luigi(_sceneManager, _driver, _device, *_receiver, _pos[0], state));
    if (model == 2)
        _players.push_back(new Yoshi(_sceneManager, _driver, _device, *_receiver, _pos[0], state));
    if (model == 3)
        _players.push_back(new Wario(_sceneManager, _driver, _device, *_receiver, _pos[0], state));
    _players[_players.size() - 1]->setRotation(irr::core::vector3df{0, 0, 0});
}

void Game::loadPlayerTwo(int model, State state)
{
    if (model == 0)
        _players.push_back(new Mario(_sceneManager, _driver, _device, *_receiver, _pos[1], state));
    if (model == 1)
        _players.push_back(new Luigi(_sceneManager, _driver, _device, *_receiver, _pos[1], state));
    if (model == 2)
        _players.push_back(new Yoshi(_sceneManager, _driver, _device, *_receiver, _pos[1], state));
    if (model == 3)
        _players.push_back(new Wario(_sceneManager, _driver, _device, *_receiver, _pos[1], state));
    _players[_players.size() - 1]->setRotation(irr::core::vector3df{0, 0, 0});
}

void Game::loadPlayerThree(int model, State state)
{
    if (model == 0)
        _players.push_back(new Mario(_sceneManager, _driver, _device, *_receiver, _pos[2], state));
    if (model == 1)
        _players.push_back(new Luigi(_sceneManager, _driver, _device, *_receiver, _pos[2], state));
    if (model == 2)
        _players.push_back(new Yoshi(_sceneManager, _driver, _device, *_receiver, _pos[2], state));
    if (model == 3)
        _players.push_back(new Wario(_sceneManager, _driver, _device, *_receiver, _pos[2], state));
    _players[_players.size() - 1]->setRotation(irr::core::vector3df{0, 180, 0});

}

void Game::loadPlayerFour(int model, State state)
{
    if (model == 0)
        _players.push_back(new Mario(_sceneManager, _driver, _device, *_receiver, _pos[3], state));
    if (model == 1)
        _players.push_back(new Luigi(_sceneManager, _driver, _device, *_receiver, _pos[3], state));
    if (model == 2)
        _players.push_back(new Yoshi(_sceneManager, _driver, _device, *_receiver, _pos[3], state));
    if (model == 3)
        _players.push_back(new Wario(_sceneManager, _driver, _device, *_receiver, _pos[3], state));
    _players[_players.size() - 1]->setRotation(irr::core::vector3df{0, 180, 0});
}

void Game::saveMap()
{
    std::ofstream myfile;
    myfile.open("MapSave.txt");
    for (int i = 0; i < _players.size(); i++)
        myfile << _players[i]->getState() << std::endl;
    for (int i = 0; i < _mapPlayer.size(); i++) {
        for (int j = 0; j < _mapPlayer[i].size(); j++)
            myfile << _mapPlayer[i][j].first;
        myfile << std::endl;
    }
    myfile << std::endl;
    myfile << std::endl;
    for (int i = 0; i < _players.size(); i++) {
        myfile << _players[i]->getPosition().X << std::endl;
        myfile << _players[i]->getPosition().Y << std::endl;
        myfile << _players[i]->getPosition().Z << std::endl;
    }
    for (int i = 0; i < _players.size(); i++) {
        myfile << _players[i]->getStock() << std::endl;
        myfile << _players[i]->getSpeed() << std::endl;
        myfile << _players[i]->getPower() << std::endl;
    }
    myfile.close();
}

void Game::loadMap()
{
    std::vector<State> players;
    std::vector<std::vector<int>> map;
    std::vector<int> tmp = {1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::ifstream myfile;
    char c;
    int lineNb = 0;
    std::string line;
    vector3df pos;

    for (int y = 0; y < 14; y++) {
        map.push_back(tmp);
    }
    myfile.open("MapSave.txt");
    if (myfile.is_open())
    {
        for (int i = 0; i < 4; i++) {
            getline(myfile, line);
            players.push_back(static_cast<State>(atoi(line.c_str())));
        }
        myfile.get(c);
        for (int i = 0; lineNb < 15; i++)
        {
            if (c == '\n') {
                lineNb++;
                i = -1;
            } else {
                if (c == 'H') {
                    map[lineNb][i] = 1;
                } else if (c == 'S')
                    map[lineNb][i] = 4;
                else
                    map[lineNb][i] = 0;
            }
            myfile.get(c);
        }
        for (int i = 0; i < 4; i++) {
            getline(myfile, line);
            pos.X = atoi(line.c_str());
            getline(myfile, line);
            pos.Y = atoi(line.c_str());
            getline(myfile, line);
            pos.Z = atoi(line.c_str());
            _pos.push_back(pos);
        }
        createMap(players, map);
        for (int i = 0; i < 4; i++) {
            getline(myfile, line);
            _players[i]->getStock() = atoi(line.c_str());
            getline(myfile, line);
            _players[i]->getSpeed() = atoi(line.c_str());
            getline(myfile, line);
            _players[i]->getPower() = atoi(line.c_str());
            _pos.push_back(pos);
        }
    }
    else
        throw ErrorGetSaveMap("Couldn't open MapSave file");
}

void Game::victory()
{
    int i = 0;

    for (auto &player : _players) {
        if (player->isDead()) {
            i++;
        }
    }
    if (i >= 3 && !_victory) {
        for (auto &player : _players) {
            if (!player->isDead())
                player->die();
        }
        _victory = true;
        _sceneManager->getActiveCamera()->removeAnimators();
        ISceneNodeAnimator *anim = _sceneManager->createFlyStraightAnimator(
             _sceneManager->getActiveCamera()->getPosition(), {0, 30, 50}, 3000);
         _sceneManager->getActiveCamera()->addAnimator(anim);
       anim->drop();
        _sceneManager->getActiveCamera()->setTarget({0, 20, 90});
        _light = _sceneManager->addLightSceneNode(_sceneManager->getActiveCamera(), vector3df(0, 100, 90), SColorf(1.0f, 1.0f, 1.0f, 1.0), 1000000);
    }
}
