/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** andie.cpp
*/

#include "AAi.hpp"

AAi::AAi(std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *mapPlayer,
std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *mapBomb,
std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *mapRadius,
Players::APlayers *player) noexcept
{
    _mapPlayer = mapPlayer;
    _mapBomb = mapBomb;
    _mapRadius = mapRadius;
    bool find = false;
    int bestX = 0;
    int bestZ = 0;
    int tmp = 0;
    int tmp2 = 0;
    int nb = 100;
    int nb2 = 100;
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 14; j++) {
            tmp = abs(player->getPosition().X - (*_mapPlayer)[i][j].second.X); 
            if (tmp < nb) {
                bestX = j;
                nb = tmp;
            }
            tmp2 = abs(player->getPosition().Z - (*_mapPlayer)[i][j].second.Z);
            if (tmp2 < nb2) {
                bestZ = i;
                nb2 = tmp2;
            }
        }
    }
    if (player->getPosition().Z <= 70) {
        player->setPosition(
            irr::core::vector3df{(*_mapPlayer)[bestZ][bestX].second.X, 0,
                (*_mapPlayer)[bestZ][bestX].second.Z});
    } else {
        player->setDead(true);
    }
    if (player->isDead())
            return;
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 14; j++) {
            if (player->getPosition().X == (*_mapPlayer)[i][j].second.X && player->getPosition().Z == (*_mapPlayer)[i][j].second.Z &&
            (*_mapPlayer)[i][j].first == '0') {
                (*_mapPlayer)[i][j].first = 'A';
                _mapZ = i;
                _mapX = j;
                find = true;
                break;
            }
        }
        if (find)
            break;
    }
}

AAi::AAi(AAi const &aai) noexcept
{
    (void)aai;
}
AAi::AAi(AAi &&aai) noexcept : AAi{aai}
{

}
AAi::~AAi() noexcept
{

}
AAi &AAi::operator=(AAi const &aai) noexcept
{
    (void)aai;
    return *this;
}
AAi &AAi::operator=(AAi &&aai) noexcept
{
    return *this = aai;
}

bool AAi::moveAiUp(Players::APlayers *player, irr::f32 deltaFrame)
{
    if (_mapZ - 1 < 0) {
        if (player->getIdleState() == false) {
            player->setIdleAnimation();
            player->setIdleState(true);
        }
        _canMove = true;
        return (false);
    }
    if (player->getPosition().Z >= (*_mapPlayer)[_mapZ - 1][_mapX].second.Z) {
        player->setPosition(irr::core::vector3df{(*_mapPlayer)[_mapZ - 1][_mapX].second.X,
        player->getPosition().Y, (*_mapPlayer)[_mapZ - 1][_mapX].second.Z});
        if ((*_mapPlayer)[_mapZ][_mapX].first == 'A')
            (*_mapPlayer)[_mapZ][_mapX].first = '0';
        player->_oldpos = irr::core::vector3df{(*_mapPlayer)[_mapZ][_mapX].second.X, player->getPosition().Y, (*_mapPlayer)[_mapZ][_mapX].second.Z};
        _mapZ--;
        _canMove = true;
        return (true);
    }
    if ((*_mapBomb)[_mapZ - 1][_mapX].first == '0') {
        player->_prop.MoveUp(*player, deltaFrame, std::vector<bool>{true, true, true, true});
        _canMove = false;
        _doMovement = true;
        return (true);
    } else {
        if (player->getIdleState() == false) {
            player->setIdleAnimation();
            player->setIdleState(true);
        }
        _canMove = true;
    }
    return (false);
}

bool AAi::moveAiDown(Players::APlayers *player, irr::f32 deltaFrame)
{
    if (_mapZ + 1 > 13) {
        player->setIdleAnimation();
        player->setIdleState(true);
        _canMove = true;
        return (false);
    }
    if (player->getPosition().Z <= (*_mapPlayer)[_mapZ + 1][_mapX].second.Z) {
        player->setPosition(irr::core::vector3df{(*_mapPlayer)[_mapZ + 1][_mapX].second.X,
        player->getPosition().Y, (*_mapPlayer)[_mapZ + 1][_mapX].second.Z});
        if ((*_mapPlayer)[_mapZ][_mapX].first == 'A')
            (*_mapPlayer)[_mapZ][_mapX].first = '0';
        player->_oldpos = irr::core::vector3df{(*_mapPlayer)[_mapZ][_mapX].second.X, player->getPosition().Y, (*_mapPlayer)[_mapZ][_mapX].second.Z};
        _mapZ++;
        _canMove = true;
        return (true);
    }
    if ((*_mapBomb)[_mapZ + 1][_mapX].first == '0') {
        player->_prop.MoveDown(*player, deltaFrame, std::vector<bool>{true, true, true, true});
        _canMove = false;
        _doMovement = true;
        return (true);
    } else {
        if (player->getIdleState() == false) {
            player->setIdleAnimation();
            player->setIdleState(true);
        }
        _canMove = true;
    }
    return (false);
}

bool AAi::moveAiLeft(Players::APlayers *player, irr::f32 deltaFrame)
{
    if (_mapX - 1 < 0) {
        if (player->getIdleState() == false) {
            player->setIdleAnimation();
            player->setIdleState(true);
        }
        _canMove = true;
        return (false);
    }
    if (player->getPosition().X <= (*_mapPlayer)[_mapZ][_mapX - 1].second.X) {
        player->setPosition(irr::core::vector3df{(*_mapPlayer)[_mapZ][_mapX - 1].second.X,
        player->getPosition().Y, (*_mapPlayer)[_mapZ][_mapX - 1].second.Z});
        if ((*_mapPlayer)[_mapZ][_mapX].first == 'A')
            (*_mapPlayer)[_mapZ][_mapX].first = '0';
        player->_oldpos = irr::core::vector3df{(*_mapPlayer)[_mapZ][_mapX].second.X, player->getPosition().Y, (*_mapPlayer)[_mapZ][_mapX].second.Z};
        _mapX--;
        _canMove = true;
        return (true);
    }
    if ((*_mapBomb)[_mapZ][_mapX - 1].first == '0') {
        player->_prop.MoveLeft(*player, deltaFrame, std::vector<bool>{true, true, true, true});
        _canMove = false;
        _doMovement = true;
        return (true);
    } else {
        if (player->getIdleState() == false) {
            player->setIdleAnimation();
            player->setIdleState(true);
        }
        _canMove = true;
    }
    return (false);
}

bool AAi::moveAiRight(Players::APlayers *player, irr::f32 deltaFrame)
{
    if (_mapX + 1 > 13) {
        if (player->getIdleState() == false) {
            player->setIdleAnimation();
            player->setIdleState(true);
        }
        _canMove = true;
        return (false);
    }
    if (player->getPosition().X >= (*_mapPlayer)[_mapZ][_mapX + 1].second.X) {
        player->setPosition(irr::core::vector3df{(*_mapPlayer)[_mapZ][_mapX + 1].second.X,
        player->getPosition().Y, (*_mapPlayer)[_mapZ][_mapX + 1].second.Z});
        if ((*_mapPlayer)[_mapZ][_mapX].first == 'A')
            (*_mapPlayer)[_mapZ][_mapX].first = '0';
        player->_oldpos = irr::core::vector3df{(*_mapPlayer)[_mapZ][_mapX].second.X, player->getPosition().Y, (*_mapPlayer)[_mapZ][_mapX].second.Z};
        _mapX++;
        _canMove = true;
        return (true);
    }
    if ((*_mapBomb)[_mapZ][_mapX + 1].first == '0') {
        player->_prop.MoveRight(*player, deltaFrame, std::vector<bool>{true, true, true, true});
        _canMove = false;
        _doMovement = true;
        return (true);
    } else {
        if (player->getIdleState() == false) {
            player->setIdleAnimation();
            player->setIdleState(true);
        }
        _canMove = true;
    }
    return (false);
}

void AAi::dropAiBomb(Players::APlayers *player, irr::f32 deltaFrame)
{
    if (_cd < 0) {
        if (player->dropBomb(*_mapPlayer, irr::core::vector3df{(*_mapPlayer)[_mapZ][_mapX].second.X, 0, (*_mapPlayer)[_mapZ][_mapX].second.Z})) {
            for (int i = 0; i < 14; i++) {
                for (int j = 0; j < 14; j++)
                    if (int(player->getBombs()[player->getBombs().size() - 1]->getCube()->getPosition().X) == int((*_mapPlayer)[i][j].second.X) &&
                    int(player->getBombs()[player->getBombs().size() - 1]->getCube()->getPosition().Z) == int((*_mapPlayer)[i][j].second.Z)) {
                        (*_mapBomb)[i][j].first = player->getBombs()[player->getBombs().size() - 1]->getPower() + 48;
                    }
            }
            _cd = _cdBomb;
        }
    }
}

bool AAi::checkBombUp(Players::APlayers *player, int mapX, int mapZ)
{
    int Zpos = -100;
    int power = 0;
    int distance = 0;

    if (mapX < 0)
        return (false);
    if (mapX > 13)
        return (false);
    if (mapZ < 0)
        return (false);
    if (mapZ > 13)
        return (false);
    for (int i = mapZ; i >= 0 && (*_mapBomb)[i][mapX].first != 'S' && (*_mapBomb)[i][mapX].first != 'H'; i--) {
        if ((*_mapBomb)[i][mapX].first != '0') {
            Zpos = i;
            break;
        }
    }
    if (Zpos == -100)
        return false;
    power = (*_mapBomb)[Zpos][mapX].first - 48;
    distance = mapZ - Zpos;
    if (distance - power <= 0)
        return (true);
    return (false);
}

bool AAi::checkBombDown(Players::APlayers *player, int mapX, int mapZ)
{
    int Zpos = 100;
    int power = 0;
    int distance = 0;
    int nb = 0;

    if (mapX < 0)
        return (false);
    if (mapX > 13)
        return (false);
    if (mapZ < 0)
        return (false);
    if (mapZ > 13)
        return (false);
    for (nb = mapZ; nb < 14 && (*_mapBomb)[nb][mapX].first != 'S' && (*_mapBomb)[nb][mapX].first != 'H'; nb++) {
        if ((*_mapBomb)[nb][mapX].first != '0') {
            Zpos = nb;
            break;
        }
    }
    if (nb > 13)
        return (false);
    if (Zpos == 100)
        return (false);
    power = (*_mapBomb)[Zpos][mapX].first - 48;
    distance = Zpos - mapZ;
    if (distance - power <= 0)
        return (true);
    return (false);
}

bool AAi::checkBombRight(Players::APlayers *player, int mapX, int mapZ)
{
    int Xpos = 200;
    int power = 0;
    int distance = 0;
    int nb = 0;

    if (mapX < 0)
        return (false);
    if (mapX > 13)
        return (false);
    if (mapZ < 0)
        return (false);
    if (mapZ > 13)
        return (false);
    for (nb = mapX; nb < 14 && (*_mapBomb)[mapZ][nb].first != 'S' && (*_mapBomb)[mapZ][nb].first != 'H'; nb++) {
        if ((*_mapBomb)[mapZ][nb].first != '0') {
            Xpos = nb;
            break;
        }
    }
    if (nb > 13)
        return (false);
    if (Xpos == 200)
        return (false);
    power = (*_mapBomb)[mapZ][Xpos].first - 48;
    distance = Xpos - mapX;
    if (distance - power <= 0)
        return (true);
    return (false);
}

bool AAi::checkBombLeft(Players::APlayers *player, int mapX, int mapZ)
{
    int Xpos = -100;
    int power = 0;
    int distance = 0;

    if (mapX < 0)
        return (false);
    if (mapX > 13)
        return (false);
    if (mapZ < 0)
        return (false);
    if (mapZ > 13)
        return (false);
    for (int i = mapX; i >= 0 && (*_mapBomb)[mapZ][i].first != 'S' && (*_mapBomb)[mapZ][i].first != 'H'; i--) {
        if ((*_mapBomb)[mapZ][i].first != '0') {
            Xpos = i;
            break;
        }
    }
    if (Xpos == -100)
        return (false);
    power = (*_mapBomb)[mapZ][Xpos].first - 48;
    distance = mapX - Xpos;
    if (distance - power <= 0)
        return (true);
    return (false);
}

bool AAi::checkBombCenter(Players::APlayers *player)
{
    if ((*_mapBomb)[_mapZ][_mapX].first != '0')
        return (true);
}

void AAi::doScriptAverage(Players::APlayers *player, irr::f32 deltaFrame)
{
    bool find = false;
    _cdBomb = 2;
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 14; j++) {
            if (player->getPosition().X == (*_mapPlayer)[i][j].second.X && player->getPosition().Z == (*_mapPlayer)[i][j].second.Z &&
            (*_mapPlayer)[i][j].first == '0') {
                (*_mapPlayer)[i][j].first = 'A';
                find = true;
                break;
            }
        }
        if (find)
            break;
    }
    if (_canMove) {
        _random = 0;
    }
    _cd -= deltaFrame;
    if (checkBombUp(player, _mapX, _mapZ) && checkBombDown(player, _mapX, _mapZ) && _canMove) {
        if (!moveAiRight(player, deltaFrame) && _canMove) {
                if (!moveAiLeft(player, deltaFrame) && _canMove) {
                    if (!moveAiUp(player, deltaFrame) && _canMove) {
                        if (_canMove) {
                            moveAiDown(player, deltaFrame);
                            _random = 2;
                        }
                    } else {
                        _random = 1;
                    }
            } else {
                _random = 3;
            }
        } else {
            _random = 4;
        }
    } else if (checkBombUp(player, _mapX, _mapZ) && _canMove) {
        if (!moveAiDown(player, deltaFrame) && _canMove) {
            if (!moveAiRight(player, deltaFrame) && _canMove) {
                if (_canMove) {
                    moveAiLeft(player, deltaFrame);
                    _random = 3;
                }
            } else {
                _random = 4;
            }
        } else {
            _random = 2;
        }
    }
    else if (checkBombDown(player, _mapX, _mapZ) && _canMove) {
        if(!moveAiUp(player, deltaFrame) && _canMove) {
            if (!moveAiRight(player, deltaFrame) && _canMove) {
                if (_canMove) {
                    moveAiLeft(player, deltaFrame);
                    _random = 3;
                }
            } else {
                _random = 4;
            }
        } else {
            _random = 1;
        }
    }
    if (checkBombLeft(player, _mapX, _mapZ) && checkBombRight(player, _mapX, _mapZ) && _canMove) {
        if (!moveAiUp(player, deltaFrame) && _canMove) {
                if (!moveAiDown(player, deltaFrame) && _canMove) {
                    if (!moveAiLeft(player, deltaFrame) && _canMove) {
                        if (_canMove) {
                            moveAiRight(player, deltaFrame);
                            _random = 4;
                        }
                    } else {
                        _random = 3;
                    }
            } else {
                _random = 2;
            }
        } else {
            _random = 1;
        }
    }
    else if (checkBombLeft(player, _mapX, _mapZ) && _canMove) {
        if (!moveAiRight(player, deltaFrame) && _canMove) {
            if (!moveAiUp(player, deltaFrame) && _canMove) {
                if (_canMove) {
                    moveAiDown(player, deltaFrame);
                    _random = 2;
                }
            } else {
                _random = 1;
            }
        } else {
            _random = 4;
        }
    }
    else if (checkBombRight(player, _mapX, _mapZ) && _canMove) {
        if (!moveAiLeft(player, deltaFrame) && _canMove) {
            if (!moveAiUp(player, deltaFrame) && _canMove) {
                if (_canMove) {
                    moveAiDown(player, deltaFrame);
                    _random = 2;
                }
            } else {
                _random = 1;
            }
        } else {
            _random = 3;
        }
    }
    if (_random == 1)
        moveAiUp(player, deltaFrame);
    if (_random == 2)
        moveAiDown(player, deltaFrame);
    if (_random == 3) {
            moveAiLeft(player, deltaFrame);
    }
    if (_random == 4) {
        moveAiRight(player, deltaFrame);
    }
    if (_canMove)
        _random = rand() % 8 + 5;
    if (_random == 5) {
        if (_mapZ - 1 >= 0 && !checkBombRight(player, _mapX, _mapZ - 1) && !checkBombLeft(player, _mapX, _mapZ - 1) &&
        !checkBombUp(player, _mapX, _mapZ - 1)) {
            if(moveAiUp(player, deltaFrame))
                _canDrop = true;
        } else
            _canDrop = false;
    }
    if (_random == 6) {
        if (_mapZ + 1 < 14 && !checkBombRight(player, _mapX, _mapZ + 1) && !checkBombLeft(player, _mapX, _mapZ + 1) &&
        !checkBombDown(player, _mapX, _mapZ + 1)) {
            if (moveAiDown(player, deltaFrame))
                _canDrop = true;
        } else
            _canDrop = false;
    }
    if (_random == 7) {
        if (_mapX - 1 >= 0 && (!checkBombUp(player, _mapX - 1, _mapZ) && !checkBombDown(player, _mapX - 1, _mapZ)) &&
        !checkBombLeft(player, _mapX - 1, _mapZ)) {
            if (moveAiLeft(player, deltaFrame))
                _canDrop = true;
        } else
            _canDrop = false;
    }
    if (_random == 8) {
        if (_mapX + 1 < 14 && (!checkBombUp(player, _mapX + 1, _mapZ) && !checkBombDown(player, _mapX + 1, _mapZ)) &&
        !checkBombRight(player, _mapX - 1, _mapZ)) {
            if (moveAiRight(player, deltaFrame))
                _canDrop = true;
        } else
            _canDrop = false;
    }
    if (!_canDrop)
        return;
    if (_mapZ - 1 >= 0 && (*_mapBomb)[_mapZ - 1][_mapX].first == 'S')
        dropAiBomb(player, deltaFrame);
    if (_mapZ + 1 < 14 && (*_mapBomb)[_mapZ + 1][_mapX].first == 'S')
        dropAiBomb(player, deltaFrame);
    if (_mapX - 1 >= 0 && (*_mapBomb)[_mapZ][_mapX - 1].first == 'S')
        dropAiBomb(player, deltaFrame);
    if (_mapX + 1 < 14 && (*_mapBomb)[_mapZ][_mapX + 1].first == 'S')
        dropAiBomb(player, deltaFrame);
}

bool AAi::findNearestSoftBlock(Players::APlayers *player)
{
    std::deque<int> path;
    int posX = _mapX;
    int posZ = _mapZ;
    int random = 0;
    int nbSoft = 0;
    int max = 0;

    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 14; j++) {
            if ((*_mapBomb)[i][j].first == 'S')
                nbSoft++;
        }
    }
    if (nbSoft == 0)
        return(false);
    while (1) {
        if (max == 100) {
            return (false);
        }
        random = rand() % 4 + 1;
        if (path.size() != 0){ 
            if (path[path.size() - 1] == 1)
                while (random == 2)
                    random = rand() % 4 + 1;
            if (path[path.size() - 1] == 2)
                while (random == 1)
                    random = rand() % 4 + 1;
            if (path[path.size() - 1] == 3)
                while (random == 4)
                    random = rand() % 4 + 1;
            if (path[path.size() - 1] == 4)
                while (random == 3)
                    random = rand() % 4 + 1;
        }
        if (random == 1) {
            if ((posZ - 1 >= 0 && (*_mapBomb)[posZ - 1][posX].first == '0')) {
                posZ--;
                path.push_back(1);
                if (posZ - 1 >= 0 && (*_mapBomb)[posZ - 1][posX].first == 'S')
                    break;
                if (posX + 1 < 14 && (*_mapBomb)[posZ][posX + 1].first == 'S')
                    break;
                if (posX - 1 >= 0 && (*_mapBomb)[posZ][posX - 1].first == 'S')
                    break;
            }
        }
        if (random == 2) {
            if (posZ + 1 < 14 && (*_mapBomb)[posZ + 1][posX].first == '0') {
                posZ++;
                path.push_back(2);
                if (posZ + 1 < 14 && (*_mapBomb)[posZ + 1][posX].first == 'S')
                    break;
                if (posX + 1 < 14 && (*_mapBomb)[posZ][posX + 1].first == 'S')
                    break;
                if (posX - 1 >= 0 && (*_mapBomb)[posZ][posX - 1].first == 'S')
                    break;
            }
        }
        if (random == 3) {
            if (posX - 1 >= 0 && (*_mapBomb)[posZ][posX - 1].first == '0') {
                posX--;
                path.push_back(3);
                if (posX - 1 >= 0 && (*_mapBomb)[posZ][posX - 1].first == 'S')
                    break;
                if (posZ + 1 < 14 && (*_mapBomb)[posZ + 1][posX].first == 'S')
                    break;
                if (posZ - 1 >= 0 && (*_mapBomb)[posZ - 1][posX].first == 'S')
                    break;
            }
        }
        if (random == 4) {
            if (posX + 1 < 14 && (*_mapBomb)[posZ][posX + 1].first == '0') {
                posX++;
                path.push_back(4);
                if ((posX + 1 < 14 && (*_mapBomb)[posZ][posX + 1].first == 'S'))
                    break;
                if (posZ + 1 < 14 && (*_mapBomb)[posZ + 1][posX].first == 'S')
                    break;
                if (posZ - 1 >= 0 && (*_mapBomb)[posZ - 1][posX].first == 'S')
                    break;
            }
        }
        max++;
    }
    _moves = path;
    return (true);
}

void AAi::doScriptEasy(Players::APlayers *player, irr::f32 deltaFrame)
{
    bool find = false;
    bool danger = false;

    _doMovement = false;
    _cdBomb = 2.0;
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 14; j++) {
            if (player->getPosition().X == (*_mapPlayer)[i][j].second.X && player->getPosition().Z == (*_mapPlayer)[i][j].second.Z &&
            (*_mapPlayer)[i][j].first == '0') {
                (*_mapPlayer)[i][j].first = 'A';
                find = true;
                break;
            }
        }
        if (find)
            break;
    }
    _cd -= deltaFrame;
    if (_canMove)
        _random = 0;
    if (checkBombCenter(player)) {
        _moves.clear();
        danger = true;
        if (!_doMovement && !moveAiUp(player, deltaFrame) && _canMove) {
            if (!_doMovement && !moveAiDown(player, deltaFrame) && _canMove) {
                if (!_doMovement && !moveAiRight(player, deltaFrame) && _canMove) {
                    if (_canMove)
                        if (!_doMovement && moveAiLeft(player, deltaFrame)) {
                            _random = 3;
                            _doMovement = true;
                        }
                } else {
                    _doMovement = true;
                    _random = 4;
                }
            } else {
                _doMovement = true;
                _random = 2;
            }
        } else {
            _doMovement = true;
            _random = 1;
        }
    }
    if (checkBombUp(player, _mapX, _mapZ)) {
        if (!_doMovement && !moveAiLeft(player, deltaFrame) && _canMove) {
            if (!_doMovement && !moveAiRight(player, deltaFrame) && _canMove) {
                if (!_doMovement && !moveAiDown(player, deltaFrame) && _canMove) {
                    if (_canMove) {
                        if (!_doMovement && moveAiUp(player, deltaFrame)) {
                            _doMovement = true;
                            _random = 1;
                        }
                    }
                } else {
                    _doMovement = true;
                    _random = 2;
                }
            } else {
                _doMovement = true;
                _random = 4;
            }
        } else {
            _doMovement = true;
            _random = 3;
        }
        danger = true;
    }
    if (!_doMovement && checkBombDown(player, _mapX, _mapZ)) {
        if (!_doMovement &&!moveAiLeft(player, deltaFrame) && _canMove) {
            if (!_doMovement && !moveAiRight(player, deltaFrame) && _canMove) {
                if (!_doMovement && !moveAiUp(player, deltaFrame) && _canMove) {
                    if (_canMove) {
                        if (!_doMovement && moveAiDown(player, deltaFrame)) {
                            _doMovement = true;
                            _random = 2;
                        }
                    }
                } else {
                    _doMovement = true;
                    _random = 1;
                }
            } else {
                _doMovement = true;
                _random = 4;
            }
        } else {
            _doMovement = true;
            _random = 3;
        }
        danger = true;
    }
    if (checkBombLeft(player, _mapX, _mapZ)) {
        if (!_doMovement && !moveAiUp(player, deltaFrame) && _canMove) {
            if (!_doMovement && !moveAiDown(player, deltaFrame) && _canMove) {
                if (!_doMovement && !moveAiRight(player, deltaFrame) && _canMove) {
                    if (_canMove) {
                        if (!_doMovement && moveAiLeft(player, deltaFrame)) {
                            _doMovement = true;
                            _random = 3;
                        }
                    }
                } else {
                    _doMovement = true;
                    _random = 4;
                }
            } else {
                _doMovement = true;
                _random = 2;
            }
        } else {
            _doMovement = true;
            _random = 1;
        }
        danger = true;
    }
    if (checkBombRight(player, _mapX, _mapZ)) {
        if (!_doMovement && !moveAiUp(player, deltaFrame) && _canMove) {
            if (!_doMovement && !moveAiDown(player, deltaFrame) && _canMove) {
                if (!_doMovement && !moveAiLeft(player, deltaFrame) && _canMove) {
                    if (_canMove) {
                        if (!_doMovement && moveAiRight(player, deltaFrame)) {
                            _doMovement = true;
                            _random = 4;
                        }
                    }
                } else {
                    _doMovement = true;
                    _random = 3;
                }
            } else {
                _doMovement = true;
                _random = 2;
            }
        } else {
            _doMovement = true;
            _random = 1;
        }
        danger = true;
    }
    if (_random == 1 && !_doMovement) {
        if (_mapZ - 1 >= 0 && !checkBombRight(player, _mapX, _mapZ - 1) && !checkBombLeft(player, _mapX, _mapZ - 1) &&
        !checkBombUp(player, _mapX, _mapZ - 1))
            moveAiUp(player, deltaFrame);
    }
    if (_random == 2 && !_doMovement) {
        if (_mapZ + 1 < 14 && !checkBombRight(player, _mapX, _mapZ + 1) && !checkBombLeft(player, _mapX, _mapZ + 1) &&
        !checkBombDown(player, _mapX, _mapZ + 1)) {
            moveAiDown(player, deltaFrame);
        }
    }
    if (_random == 3 && !_doMovement)
        if (_mapX - 1 >= 0 && (!checkBombUp(player, _mapX - 1, _mapZ) && !checkBombDown(player, _mapX - 1, _mapZ)) &&
        !checkBombLeft(player, _mapX - 1, _mapZ)) {
            moveAiLeft(player, deltaFrame);
        }
    if (_random == 4 && !_doMovement) {
        if (_mapX + 1 < 14 && (!checkBombUp(player, _mapX + 1, _mapZ) && !checkBombDown(player, _mapX + 1, _mapZ)) &&
        !checkBombRight(player, _mapX - 1, _mapZ)) {
            moveAiRight(player, deltaFrame);
        }
    }
    if (danger) {
        return;
    }
    if (_moves.size() == 0) {
        findNearestSoftBlock(player);
    }
    if (_moves.size() != 0) {
        if (_moves[0] == 1 && !_doMovement) {
            if (_mapZ - 1 >= 0 && !checkBombRight(player, _mapX, _mapZ - 1) && !checkBombLeft(player, _mapX, _mapZ - 1) &&
            !checkBombUp(player, _mapX, _mapZ - 1))
                if (moveAiUp(player, deltaFrame))
                    ;
        }
        if (_moves[0] == 2 && !_doMovement) {
            if (_mapZ + 1 < 14 && !checkBombRight(player, _mapX, _mapZ + 1) && !checkBombLeft(player, _mapX, _mapZ + 1) &&
            !checkBombDown(player, _mapX, _mapZ + 1)) {
                if (moveAiDown(player, deltaFrame))
                ;
            }
        }
        if (_moves[0] == 3 && !_doMovement) {
            if (_mapX - 1 >= 0 && (!checkBombUp(player, _mapX - 1, _mapZ) && !checkBombDown(player, _mapX - 1, _mapZ)) &&
            !checkBombLeft(player, _mapX - 1, _mapZ)) {
                if (moveAiLeft(player, deltaFrame))
                    ;
            }
        }
        if (_moves[0] == 4 && !_doMovement) {
            if (_mapX + 1 < 14 && (!checkBombUp(player, _mapX + 1, _mapZ) && !checkBombDown(player, _mapX + 1, _mapZ)) &&
            !checkBombRight(player, _mapX - 1, _mapZ)) {
                if (moveAiRight(player, deltaFrame))
                    ;
            }
        }
        if (_canMove) {
            _moves.pop_front();
            if (_moves.size() == 0) {
                if (_cd <= 0)
                    dropAiBomb(player, deltaFrame);
            }
        }
    }
}

bool AAi::findSafePath(Players::APlayers *player)
{
    std::deque<int> path;
    int posX = _mapX;
    int posZ = _mapZ;
    int random = 0;
    int nbSoft = 0;
    int max = 0;

    while ((*_mapRadius)[posZ][posX].first != '0') {
        if (max == 200) {
            return (false);
        }
        random = rand() % 4 + 1;
        if (path.size() != 0){ 
            if (path[path.size() - 1] == 1)
                while (random == 2)
                    random = rand() % 4 + 1;
            if (path[path.size() - 1] == 2)
                while (random == 1)
                    random = rand() % 4 + 1;
            if (path[path.size() - 1] == 3)
                while (random == 4)
                    random = rand() % 4 + 1;
            if (path[path.size() - 1] == 4)
                while (random == 3)
                    random = rand() % 4 + 1;
        }
        if (random == 1) {
            if (posZ - 1 >= 0 && (*_mapBomb)[posZ - 1][posX].first == '0') {
                posZ--;
                path.push_back(1);
            }
        }
        if (random == 2) {
            if (posZ + 1 < 14 && (*_mapBomb)[posZ + 1][posX].first == '0') {
                posZ++;
                path.push_back(2);
            }
        }
        if (random == 3) {
            if (posX - 1 >= 0 && (*_mapBomb)[posZ][posX - 1].first == '0') {
                posX--;
                path.push_back(3);
            }
        }
        if (random == 4) {
            if (posX + 1 < 14 && (*_mapBomb)[posZ][posX + 1].first == '0') {
                posX++;
                path.push_back(4);
            }
        }
        max++;
    }
    _movesSafe = path;
    return (true);
}

bool AAi::checkNbSoftBlock()
{
    int nb = 0;

    for (int i = 0; i < 14; i++)
        for (int j = 0; j < 14; j++)
            if ((*_mapBomb)[i][j].first == 'S')
                nb++;
    if (nb == 0)
        return (false);
    return (true);
}

bool AAi::findPlayer(Players::APlayers *player)
{
    std::deque<int> path;
    int posX = _mapX;
    int posZ = _mapZ;
    int random = 0;
    int nbSoft = 0;
    int max = 0;

    while ((*_mapPlayer)[posZ][posX].first != 'P' && (*_mapPlayer)[posZ][posX].first != 'F') {
        if (max == 200) {
            return (false);
        }
        random = rand() % 4 + 1;
        if (path.size() != 0){ 
            if (path[path.size() - 1] == 1)
                while (random == 2)
                    random = rand() % 4 + 1;
            if (path[path.size() - 1] == 2)
                while (random == 1)
                    random = rand() % 4 + 1;
            if (path[path.size() - 1] == 3)
                while (random == 4)
                    random = rand() % 4 + 1;
            if (path[path.size() - 1] == 4)
                while (random == 3)
                    random = rand() % 4 + 1;
        }
        if (random == 1) {
            if (posZ - 1 >= 0 && (*_mapBomb)[posZ - 1][posX].first == '0') {
                posZ--;
                path.push_back(1);
            }
        }
        if (random == 2) {
            if (posZ + 1 < 14 && (*_mapBomb)[posZ + 1][posX].first == '0') {
                posZ++;
                path.push_back(2);
            }
        }
        if (random == 3) {
            if (posX - 1 >= 0 && (*_mapBomb)[posZ][posX - 1].first == '0') {
                posX--;
                path.push_back(3);
            }
        }
        if (random == 4) {
            if (posX + 1 < 14 && (*_mapBomb)[posZ][posX + 1].first == '0') {
                posX++;
                path.push_back(4);
            }
        }
        if ((*_mapPlayer)[posZ][posX].first == 'A' && posZ != _mapZ && posX != _mapX)
            break;
        max++;
    }
    _targetX = posX;
    _targetZ = posZ;
    _movesToPlayer = path;
    return (true);
}

void AAi::doScriptMedium(Players::APlayers *player, irr::f32 deltaFrame)
{
    bool find = false;
    _cdBomb = 0.8;
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 14; j++) {
            if (player->getPosition().X == (*_mapPlayer)[i][j].second.X && player->getPosition().Z == (*_mapPlayer)[i][j].second.Z &&
            (*_mapPlayer)[i][j].first == '0') {
                (*_mapPlayer)[i][j].first = 'A';
                find = true;
                break;
            }
        }
        if (find)
            break;
    }
    _cd -= deltaFrame;
    if ((*_mapRadius)[_mapZ][_mapX].first == 'X') {
        _nearBombX = _mapX;
        _nearBombZ = _mapZ;
        _moves.clear();
        _movesToPlayer.clear();
        if (_movesSafe.size() == 0)
            findSafePath(player);
        if (_movesSafe.size() != 0) {
            if (_movesSafe[0] == 1)
                moveAiUp(player, deltaFrame);
            if (_movesSafe[0] == 2)
                moveAiDown(player, deltaFrame);
            if (_movesSafe[0] == 3)
                moveAiLeft(player, deltaFrame);
            if (_movesSafe[0] == 4)
                moveAiRight(player, deltaFrame);
            if (_canMove) {
                _movesSafe.pop_front();
            }
        }
        return;
    }
    if (_moves.size() != 0) {
        if (_moves[0] == 1) {
            if (_mapZ - 1 >= 0 && (*_mapRadius)[_mapZ - 1][_mapX].first == 'X')
                return;
        }
        if (_moves[0] == 2) {
            if (_mapZ + 1 < 14 && (*_mapRadius)[_mapZ + 1][_mapX].first == 'X')
                return;
        }
        if (_moves[0] == 3) {
            if (_mapX - 1 >= 0 && (*_mapRadius)[_mapZ][_mapX - 1].first == 'X')
                return;
        }
        if (_moves[0] == 4) {
            if (_mapX + 1 < 14 && (*_mapRadius)[_mapZ][_mapX + 1].first == 'X')
                return;
        }
    }
    if (checkNbSoftBlock()) {
        if ((*_mapRadius)[_mapZ][_mapX].first != 'X') {
            _movesSafe.clear();
            _movesToPlayer.clear();
            if (_moves.size() == 0)
                findNearestSoftBlock(player);
            if (_moves.size() != 0) {
                if (_moves[0] == 1)
                    moveAiUp(player, deltaFrame);
                if (_moves[0] == 2)
                    moveAiDown(player, deltaFrame);
                if (_moves[0] == 3)
                    moveAiLeft(player, deltaFrame);
                if (_moves[0] == 4)
                    moveAiRight(player, deltaFrame);
                if (_canMove) {
                    _moves.pop_front();
                    if (_moves.size() == 0)
                        dropAiBomb(player, deltaFrame);
                }
            }
        }
    }
    if (!checkNbSoftBlock()) {
        _movesSafe.clear();
        _moves.clear();
        if (_canMove)
            if ((*_mapPlayer)[_targetZ][_targetX].first != 'A' && (*_mapPlayer)[_targetZ][_targetX].first != 'P' &&
                (*_mapPlayer)[_targetZ][_targetX].first != 'F') {
                    _movesToPlayer.clear();
                }
        if (_movesToPlayer.size() == 0)
            if (!findPlayer(player)) {
                if (_canMove)
                    _random = rand() % 4 + 1;
                if (_random == 1)
                    moveAiUp(player, deltaFrame);
                if (_random == 2)
                    moveAiDown(player, deltaFrame);
                if (_random == 3)
                    moveAiLeft(player, deltaFrame);
                if (_random == 4)
                    moveAiRight(player, deltaFrame);
            }
        if (_movesToPlayer.size() != 0) {
            if (_movesToPlayer[0] == 1)
                moveAiUp(player, deltaFrame);
            if (_movesToPlayer[0] == 2)
                moveAiDown(player, deltaFrame);
            if (_movesToPlayer[0] == 3)
                moveAiLeft(player, deltaFrame);
            if (_movesToPlayer[0] == 4)
                moveAiRight(player, deltaFrame);
            if (_canMove) {
                _movesToPlayer.pop_front();
                if (_movesToPlayer.size() <= 2)
                    dropAiBomb(player, deltaFrame);
            }
        }
    }
}

void AAi::doScriptHard(Players::APlayers *player, irr::f32 deltaFrame)
{
    bool find = false;
    _cdBomb = 0.8;
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 14; j++) {
            if (player->getPosition().X == (*_mapPlayer)[i][j].second.X && player->getPosition().Z == (*_mapPlayer)[i][j].second.Z &&
            (*_mapPlayer)[i][j].first == '0') {
                (*_mapPlayer)[i][j].first = 'A';
                find = true;
                break;
            }
        }
        if (find)
            break;
    }
    _cd -= deltaFrame;
    if ((*_mapRadius)[_mapZ][_mapX].first == 'X') {
        _nearBombX = _mapX;
        _nearBombZ = _mapZ;
        _moves.clear();
        _movesToPlayer.clear();
        if (_movesSafe.size() == 0)
            findSafePath(player);
        if (_movesSafe.size() != 0) {
            if (_movesSafe[0] == 1)
                moveAiUp(player, deltaFrame);
            if (_movesSafe[0] == 2)
                moveAiDown(player, deltaFrame);
            if (_movesSafe[0] == 3)
                moveAiLeft(player, deltaFrame);
            if (_movesSafe[0] == 4)
                moveAiRight(player, deltaFrame);
            if (_canMove) {
                _movesSafe.pop_front();
            }
        }
        return;
    }
    if ((*_mapRadius)[_nearBombZ][_nearBombX].first == 'X')
        return;
    if (checkNbSoftBlock()) {
        if ((*_mapRadius)[_mapZ][_mapX].first != 'X') {
            _movesSafe.clear();
            if (_chooseStrat == 0)
                _chooseStrat = rand() % 2 + 1;
            if (_chooseStrat == 1) {
                if (_canMove)
                    if ((*_mapPlayer)[_targetZ][_targetX].first != 'A' && (*_mapPlayer)[_targetZ][_targetX].first != 'P' &&
                        (*_mapPlayer)[_targetZ][_targetX].first != 'F') {
                            _movesToPlayer.clear();
                        }
                if (_movesToPlayer.size() == 0)
                    if (!findPlayer(player))
                        _chooseStrat = 2;
                if (_movesToPlayer.size() != 0) {
                    if (_movesToPlayer[0] == 1)
                        moveAiUp(player, deltaFrame);
                    if (_movesToPlayer[0] == 2)
                        moveAiDown(player, deltaFrame);
                    if (_movesToPlayer[0] == 3)
                        moveAiLeft(player, deltaFrame);
                    if (_movesToPlayer[0] == 4)
                        moveAiRight(player, deltaFrame);
                    if (_canMove) {
                        _movesToPlayer.pop_front();
                        if (_movesToPlayer.size() <= 2) {
                            dropAiBomb(player, deltaFrame);
                            _chooseStrat = 0;
                        }
                    }
                }
            }
            if (_chooseStrat == 2) {
                if (_moves.size() == 0)
                    findNearestSoftBlock(player);
                if (_moves.size() != 0) {
                    if (_moves[0] == 1)
                        moveAiUp(player, deltaFrame);
                    if (_moves[0] == 2)
                        moveAiDown(player, deltaFrame);
                    if (_moves[0] == 3)
                        moveAiLeft(player, deltaFrame);
                    if (_moves[0] == 4)
                        moveAiRight(player, deltaFrame);
                    if (_canMove) {
                        _moves.pop_front();
                        if (_moves.size() == 0) {
                            dropAiBomb(player, deltaFrame);
                            _chooseStrat = 0;
                        }
                    }
                }
            }
        }
        return;
    }
    if (!checkNbSoftBlock()) {
        _movesSafe.clear();
        _moves.clear();
        if (_canMove)
            if ((*_mapPlayer)[_targetZ][_targetX].first != 'A' && (*_mapPlayer)[_targetZ][_targetX].first != 'P' &&
            (*_mapPlayer)[_targetZ][_targetX].first != 'F') {
                _movesToPlayer.clear();
            }
        if (_movesToPlayer.size() == 0)
            if (!findPlayer(player)) {
                if (_canMove)
                    _random = rand() % 4 + 1;
                if (_random == 1)
                    moveAiUp(player, deltaFrame);
                if (_random == 2)
                    moveAiDown(player, deltaFrame);
                if (_random == 3)
                    moveAiLeft(player, deltaFrame);
                if (_random == 4)
                    moveAiRight(player, deltaFrame);
            }
        if (_movesToPlayer.size() != 0) {
            if (_movesToPlayer[0] == 1)
                moveAiUp(player, deltaFrame);
            if (_movesToPlayer[0] == 2)
                moveAiDown(player, deltaFrame);
            if (_movesToPlayer[0] == 3)
                moveAiLeft(player, deltaFrame);
            if (_movesToPlayer[0] == 4)
                moveAiRight(player, deltaFrame);
            if (_canMove) {
                _movesToPlayer.pop_front();
                if (_movesToPlayer.size() <= 2)
                    dropAiBomb(player, deltaFrame);
            }
        }
    }
}