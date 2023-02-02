/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** andie.cpp
*/

#ifndef OTM_HPP_
#define OTM_HPP_

#include "../Integration/Integration.hpp"
#include "../Properties/Properties.hpp"
#include "../AI/AAi.hpp"
#include <deque>
#include <vector>

class Bomb;
class ABlock;


class AAi;

namespace Players {

    class APlayers {
        public:
            explicit APlayers(irr::core::vector3df, irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver, irr::IrrlichtDevice *device,
            EventReceiver &receiver, State state) noexcept;
            APlayers(APlayers const &) noexcept;
            explicit APlayers(APlayers &&) noexcept;
            virtual ~APlayers() noexcept;
            APlayers &operator=(APlayers const &) noexcept;
            APlayers &operator=(APlayers &&) noexcept;
            void setPosition(irr::core::vector3df);
            void setRotation(irr::core::vector3df);
            void setIdleState(bool);
            void setDirection(std::vector<bool>);
            virtual void setWalkAnimation() = 0;
            virtual void setIdleAnimation() = 0;
            virtual void setWinAnimation() = 0;
            void setCd(float);
            float &getSpeed();
            std::size_t &getStock();
            std::size_t &getPower();
            std::size_t getHp() const;
            irr::core::vector3df getPosition() const;
            irr::core::vector3df getRotation() const;
            irr::core::aabbox3d<irr::f32> getTransformedBoundingBox() const;
            std::deque<Bomb *> getBombs() const;
            std::vector<bool> getDirection() const;
            bool getIdleState() const;
            State getState() const;
            float getCd() const;
            void subCd(float);
            void die();
            bool dropBomb(std::vector<std::vector<std::pair<char, irr::core::vector3df>>>);
            bool dropBomb(std::vector<std::vector<std::pair<char, irr::core::vector3df>>>, irr::core::vector3df);
            void checkBomb(std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *,
            std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *,
            std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *, double &deltaFrame);
            void setMap(std::vector<std::vector<ABlock *>> &map);
            irr::scene::IAnimatedMesh *_mesh;
            irr::scene::IAnimatedMeshSceneNode *_node;
            Properties<MOVE> _prop;
            irr::core::vector3df _oldpos;
            AAi *_ai = nullptr;
            bool isDead();
            void setDead(bool);

        protected:
            std::size_t _hp;
            float _speed;
            bool _died = false;
            irr::scene::ISceneManager *_smgr;
            irr::video::IVideoDriver *_driver;
            irr::IrrlichtDevice *_device;
            EventReceiver *_receiver;
            std::vector<bool> _direction;
            bool _idleState;
            State _state;
            std::vector<std::vector<ABlock *>> *_map;
            std::deque<Bomb *> _bombs;
            irr::core::vector3df _pos;
            std::size_t _stock;
            std::size_t _power;
            float _cd = 0;
            static int _i;
    };

}

#endif
