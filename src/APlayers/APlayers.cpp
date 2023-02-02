/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** andie.cpp
*/


#include "APlayers.hpp"
#include "../Bomb/Bomb.hpp"

namespace Players {

    int APlayers::_i  = 0;
    ////////////////////////////////////////////////////////////////////////////////

    APlayers::APlayers(irr::core::vector3df Pos, irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver, irr::IrrlichtDevice *device,
    EventReceiver &receiver, State state) noexcept : _hp(2), _stock(1), _speed(30.0), _pos(Pos), _smgr(smgr), _driver(driver), _device(device), _receiver(&receiver),
    _direction(std::vector<bool>{true, true, true, true}), _idleState(true), _state(state), _power(1)
    {
    }

    APlayers::APlayers(APlayers const &aplayers) noexcept {
        (void)aplayers;//IMPLEMENT HERE
    }

    APlayers::APlayers(APlayers &&aplayers) noexcept : APlayers{aplayers} {
    }

    APlayers::~APlayers() noexcept {
        _node->remove();
        for (auto *bomb : _bombs) {
            bomb->deleteMesh();
            delete bomb;
        }
        _i = 0;
    }

    APlayers &APlayers::operator=(APlayers const &aplayers) noexcept {
        (void)aplayers;//IMPLEMENT HERE
        _mesh = aplayers._mesh;
        _node = aplayers._node;
        return *this;
    }

    APlayers &APlayers::operator=(APlayers &&aplayers) noexcept {
        return *this = aplayers;
    }

    ///////////////////////////////////////////////////////////////////////////////

    void APlayers::setRotation(irr::core::vector3df rotation)
    {
        if (!_died)
            _node->setRotation(rotation);
    }

    void APlayers::setPosition(irr::core::vector3df Pos) {
        if (!_died) {
            _pos = Pos;
            _node->setPosition(_pos);
        }
    }

    void APlayers::setDirection(std::vector<bool> direction)
    {
        _direction = direction;
    }

    void APlayers::setIdleState(bool state)
    {
        _idleState = state;
    }

    float &APlayers::getSpeed()  {
        return _speed;
    }

    std::size_t &APlayers::getStock(){
        return _stock;
    }

    std::size_t &APlayers::getPower()
    {
        return _power;
    }

    std::size_t APlayers::getHp() const {
        return _hp;
    }

    irr::core::vector3df APlayers::getRotation() const
    {
        return _node->getRotation();
    }

    irr::core::vector3df APlayers::getPosition() const {
        return _pos;
    }

    irr::core::aabbox3d<irr::f32> APlayers::getTransformedBoundingBox() const
    {
        return _node->getTransformedBoundingBox();
    }

    std::vector<bool> APlayers::getDirection() const
    {
        return _direction;
    }

    bool APlayers::getIdleState() const
    {
        return _idleState;
    }

    State APlayers::getState() const
    {
        return _state;
    }

    bool APlayers::dropBomb(std::vector<std::vector<std::pair<char, irr::core::vector3df>>> mapAI)
    {
        int XCenterUp = _node->getTransformedBoundingBox().getCenter().X;
        int XCenterDown = _node->getTransformedBoundingBox().getCenter().X;
        int XDiffUp = 0;
        int XDiffDown = 0;
        int XPos = 0;
        int ZCenterUp = int(_node->getTransformedBoundingBox().getCenter().Z);
        int ZCenterDown = int(_node->getTransformedBoundingBox().getCenter().Z);
        int ZDiffUp = 0;
        int ZDiffDown = 0;
        int ZPos = 0;

        if (_state != AI) {
            if (abs(_oldpos.X) > abs(_node->getTransformedBoundingBox().getCenter().X)) {
                if (abs(_oldpos.X) - abs(_node->getTransformedBoundingBox().getCenter().X) > 2)
                    return (false);
            } else if (abs(_node->getTransformedBoundingBox().getCenter().X) - abs(_oldpos.X) > 2)
                return (false);
            if (abs(_oldpos.Z) > abs(_node->getTransformedBoundingBox().getCenter().Z)) {
                if (abs(_oldpos.Z) - abs(_node->getTransformedBoundingBox().getCenter().Z) > 2)
                    return (false);
            } else if (abs(_node->getTransformedBoundingBox().getCenter().Z) - abs(_oldpos.Z) > 2)
                return (false);
        }
        while (XCenterUp % 5 != 0)
            XCenterUp++;
        if (XCenterUp % 10 == 0)
                XCenterUp += 5;
        while (XCenterDown % 5 != 0)
            XCenterDown--;
        if (XCenterDown % 10 == 0)
            XCenterDown -= 5;
        while (ZCenterUp % 5 != 0)
            ZCenterUp++;
        if (ZCenterUp % 10 == 0)
                ZCenterUp += 5;
        while (ZCenterDown % 5 != 0)
            ZCenterDown--;
        if (ZCenterDown % 10 == 0)
            ZCenterDown -= 5;
        if (_node->getTransformedBoundingBox().getCenter().X < 0) {
                XDiffUp = float(abs(_node->getTransformedBoundingBox().getCenter().X) - abs(XCenterUp));
                XDiffDown = float(abs(XCenterDown) - abs(_node->getTransformedBoundingBox().getCenter().X));
        } else if (_node->getTransformedBoundingBox().getCenter().X > 0) {
            XDiffUp = float(abs(XCenterUp) - abs(_node->getTransformedBoundingBox().getCenter().X));
            XDiffDown = float(abs(_node->getTransformedBoundingBox().getCenter().X) - abs(XCenterDown));
        }
        if (_node->getTransformedBoundingBox().getCenter().Z < 0) {
            ZDiffUp = float(abs(_node->getTransformedBoundingBox().getCenter().Z) - abs(ZCenterUp));
            ZDiffDown = float(abs(ZCenterDown) - abs(_node->getTransformedBoundingBox().getCenter().Z));
        } else {
            ZDiffUp = float(abs(ZCenterUp) - abs(_node->getTransformedBoundingBox().getCenter().Z));
            ZDiffDown = float(abs(_node->getTransformedBoundingBox().getCenter().Z) - abs(ZCenterDown));
        }
        if (XDiffUp < XDiffDown)
            XPos = XCenterUp;
        else
            XPos = XCenterDown;
        if (ZDiffUp < ZDiffDown)
            ZPos = ZCenterUp;
        else
            ZPos = ZCenterDown;
        if (ZDiffUp > 0 && ZDiffUp == ZDiffDown * -1)
            ZPos = ZCenterUp;
        if (ZDiffUp < 0 && ZDiffUp == ZDiffDown * -1)
            ZPos = ZCenterDown;
        if (XDiffUp > 0 && XDiffUp == XDiffDown * -1)
            XPos = XCenterUp;
        if (XDiffUp < 0 && XDiffUp == XDiffDown * -1)
            XPos = XCenterDown;
        if (_node->getRotation().Y == 90 && XDiffUp == 0 && XDiffDown == 0)
            XPos = XCenterUp;
        if (_node->getRotation().Y == 0 && ZDiffUp == 0 && ZDiffDown == 0) {
            ZPos = ZCenterUp;
        }
        if (_bombs.size() != 0) {
            for (auto bomb : _bombs) {
                if (bomb->getCube() != nullptr && ZPos < 0 && int(bomb->getCube()->getTransformedBoundingBox().getCenter().X) == XPos &&
                int(bomb->getCube()->getTransformedBoundingBox().getCenter().Z) == ZPos - 1)
                    return (false);
                if (bomb->getCube() != nullptr && ZPos > 0 && int(bomb->getCube()->getTransformedBoundingBox().getCenter().X) == XPos &&
                int(bomb->getCube()->getTransformedBoundingBox().getCenter().Z) == ZPos - 2)
                    return (false);
            }
        }
        for (int i = 0; i < 14; i++) {
            for (int j = 0 ; j < 14; j++) {
                if (mapAI[i][j].second.X == XPos && mapAI[i][j].second.Z == ZPos) {
                    if (mapAI[i][j].first == 'S' || mapAI[i][j].first == 'H') {
                        if (_node->getRotation().Y == 90)
                            XPos = XCenterDown;
                        if (_node->getRotation().Y == -90)
                            XPos = XCenterUp;
                        if (_node->getRotation().Y == 0)
                            ZPos = ZCenterDown;
                        if (_node->getRotation().Y == 180)
                            ZPos = ZCenterUp;
                    }
                }
            }
        }
        if (_bombs.size() < _stock) {
            _bombs.emplace_back(new Bomb(_smgr, _smgr->addMeshSceneNode(
                _smgr->getMesh("Models/Bomb/Bomb.obj")->getMesh(0), 0, -1, irr::core::vector3df(XPos, 0, ZPos)), _device,
                _driver->getTexture("Models/Bomb/Bomb.png"), _power, _map));
            return (true);
        }
    }

    bool APlayers::dropBomb(std::vector<std::vector<std::pair<char, irr::core::vector3df>>> map, irr::core::vector3df pos)
    {
        if (_bombs.size() != 0) {
            for (auto bomb : _bombs) {
                if (bomb->getCube() != nullptr && pos.Z < 0 && int(bomb->getCube()->getPosition().X) == pos.X &&
                int(bomb->getCube()->getPosition().Z) == pos.Z)
                    return (false);
                if (bomb->getCube() != nullptr && pos.Z > 0 && int(bomb->getCube()->getPosition().X) == pos.X &&
                int(bomb->getCube()->getPosition().Z) == pos.Z)
                    return (false);
            }
        }
        if (_bombs.size() < _stock && !_died) {
            _bombs.emplace_back(new Bomb(_smgr, _smgr->addMeshSceneNode(
                _smgr->getMesh("Models/Bomb/Bomb.obj")->getMesh(0), 0, -1, irr::core::vector3df(pos.X, 0, pos.Z)), _device,
                _driver->getTexture("Models/Bomb/Bomb.png"), _power, _map));
            return (true);
        }
        return (false);
    }

    void APlayers::checkBomb(std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *mapPlayer,
    std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *mapAI,
    std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *mapRadius, double &deltaFrame)
    {
        int i = 0;

        for (auto *itt : _bombs) {
            if (itt->detonate(mapPlayer, mapAI, mapRadius, deltaFrame)) {
                for (int i = 0; i < 14; i++) {
                bool leave = false;
                    for (int j = 0; j < 14; j++) {
                        if (itt->getBombCenter().X == (*mapAI)[i][j].second.X &&
                        itt->getBombCenter().Z == (*mapAI)[i][j].second.Z) {
                            (*mapAI)[i][j].first = '0';
                            (*mapRadius)[i][j].first = '0';
                            for (int inc = 0; i + inc < 14 && inc <= itt->getPower() &&
                            (*mapRadius)[i + inc][j].first != 'S' && (*mapRadius)[i + inc][j].first != 'H'; inc++)
                                (*mapRadius)[i + inc][j].first = '0';
                            for (int inc = 0; i - inc >= 0 && inc <= itt->getPower() &&
                            (*mapRadius)[i - inc][j].first != 'S' && (*mapRadius)[i - inc][j].first != 'H'; inc++)
                                (*mapRadius)[i - inc][j].first = '0';
                            for (int inc = 0; j + inc < 14 && inc <= itt->getPower() &&
                            (*mapRadius)[i][j + inc].first != 'S' && (*mapRadius)[i][j + inc].first != 'H'; inc++)
                                (*mapRadius)[i][j + inc].first = '0';
                            for (int inc = 0; j - inc >= 0 && inc <= itt->getPower() &&
                            (*mapRadius)[i][j - inc].first != 'S' && (*mapRadius)[i][j - inc].first != 'H'; inc++)
                                (*mapRadius)[i][j - inc].first = '0';
                            leave = true;
                            break;
                        }
                    }
                    if (leave) {
                        break;
                    }
                }
                _bombs.erase(_bombs.begin()+i);
                delete itt;
            }
            i++;
        }
    }

    void APlayers::setMap(std::vector<std::vector<ABlock *>> &map)
    {
        _map = &map;
    }

    std::deque<Bomb *> APlayers::getBombs() const
    {
        return _bombs;
    }

    void APlayers::setCd(float cd)
    {
        _cd = cd;
    }

    float APlayers::getCd() const
    {
        return _cd;
    }

    void APlayers::subCd(float time)
    {
        _cd -= time;
    }

    void APlayers::die()
    {
        setIdleAnimation();
        if (_i == 0) {
            setPosition({20, 0, 80});
            setRotation({0, 0, 0});
            _died = true;
            _i = 1;
            return;
        }
        if (_i == 1) {
            setPosition({10, 10, 80});
            setRotation({0, 0, 0});
            _died = true;
            _i = 2;
            return;
        }
        if (_i == 2) {
            setPosition({-12, 12, 80});
            setRotation({0, 0, 0});
            _died = true;
            _i = 3;
            return;
        }
        if (_i == 3) {
            setWinAnimation();
            setPosition({0, 17, 80});
            setRotation({0, 0, 0});
            _died = true;
            _i = 0;
        }
    }
    bool APlayers::isDead()
    {
        return _died;
    }

    void APlayers::setDead(bool dead)
    {
        _died = dead;
    }
}
