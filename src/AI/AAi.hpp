/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** AAi
*/

#ifndef AAI_HPP_
#define AAI_HPP_

#include "../GUI/EventReceiver.hpp"
#include "../APlayers/APlayers.hpp"
#include "../Bomb/Bomb.hpp"
#include <vector>
#include "../Integration/Integration.hpp"
#include <deque>

namespace Players {
    class APlayers;
};

class AAi {
    public:
        explicit AAi(std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *_mapPlayer,
        std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *_mapBomb,
        std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *_mapRadius,
        Players::APlayers *player) noexcept;
        AAi(AAi const &) noexcept;
        explicit AAi(AAi &&) noexcept;
        ~AAi() noexcept;
        AAi &operator=(AAi const &) noexcept;
        AAi &operator=(AAi &&) noexcept;
        bool moveAiUp(Players::APlayers *player, irr::f32 deltaFrame);
        bool moveAiDown(Players::APlayers *player, irr::f32 deltaFrame);
        bool moveAiLeft(Players::APlayers *player, irr::f32 deltaFrame);
        bool moveAiRight(Players::APlayers *player, irr::f32 deltaFrame);
        void doScriptAverage(Players::APlayers *player, irr::f32 deltaFrame);
        void doScriptEasy(Players::APlayers *player, irr::f32 deltaFrame);
        void doScriptMedium(Players::APlayers *player, irr::f32 deltaFrame);
        void doScriptHard(Players::APlayers *player, irr::f32 deltaFrame);
        void dropAiBomb(Players::APlayers *player, irr::f32 deltaFrame);
        bool checkBombUp(Players::APlayers *player, int, int);
        bool checkBombDown(Players::APlayers *player, int, int);
        bool checkBombLeft(Players::APlayers *player, int, int);
        bool checkBombRight(Players::APlayers *player, int, int);
        bool checkBombCenter(Players::APlayers *player);
        bool findSafePath(Players::APlayers *player);
        bool findNearestSoftBlock(Players::APlayers *player);
        bool findPlayer(Players::APlayers *player);
        bool checkNbSoftBlock();
    private:
        std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *_mapPlayer;
        std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *_mapBomb;
        std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *_mapRadius;
        int _mapX = 0;
        int _mapZ = 0;
        int _nearBombX = 0;
        int _nearBombZ = 0;
        bool _canMove = true;
        int _random = 0;
        float _cd = 0;
        bool _canDrop = true;
        std::deque<int> _moves;
        std::deque<int> _movesSafe;
        std::deque<int> _movesToPlayer;
        bool _doMovement;
        float _cdBomb = 0;
        int _chooseStrat = 0;
        int _targetX = 0;
        int _targetZ = 0;
};

#endif /* !AAI_HPP_ */
