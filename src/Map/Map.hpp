//
// Created by njoachim on 05/06/19.
//

#ifndef OOP_INDIE_STUDIO_2018_MAP_HPP
#define OOP_INDIE_STUDIO_2018_MAP_HPP

#include "../Integration/Integration.hpp"
#include <vector>
#include <memory>
#include "../Blocks/ABlock.hpp"
#include "../APlayers/APlayers.hpp"

class APowerUp;

class Map {
    public:
        Map() = delete;
        Map(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver, irr::IrrlichtDevice* device, int complexity, int powerUp, float density);
        ~Map() noexcept;
        Map(Map const &) noexcept;
        explicit Map(Map &&map) noexcept;
        Map &operator=(Map const &) noexcept;
        Map &operator=(Map &&) noexcept;
        void createMap();
        void createMap(std::vector<std::vector<int>>);
        void fillMap();
        bool checkAround(int dir, int &x, int &y, int &path);
        void checkBackward(int &x, int &y);
        void completeMap();
        std::vector<irr::scene::IMeshSceneNode *> getWall() const;
        std::vector<std::vector<ABlock *>> &getMap();
        std::vector<std::vector<int>> _mapFillWithInt;
        void playerPowerUp(Players::APlayers *player);

    private:
        irr::scene::IMeshSceneNode *_terrain;
        irr::scene::IMeshSceneNode  *_podium;
        irr::IrrlichtDevice *_device;
        std::vector<irr::scene::IMeshSceneNode *> _wall = {nullptr, nullptr, nullptr, nullptr};
        irr::scene::ISceneManager *_smgr;
        irr::video::IVideoDriver *_driver;
        std::vector<std::vector<ABlock *>> _map;
        std::vector<APowerUp *> _powerUp;
        int _complexity;
        float _density;
        float _boosts;
        enum {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
};

#endif //OOP_INDIE_STUDIO_2018_MAP_HPP
