//
// Created by njoachim on 11/06/19.
//

#ifndef OOP_INDIE_STUDIO_2018_BOMB_HPP
#define OOP_INDIE_STUDIO_2018_BOMB_HPP

#include "../Integration/Integration.hpp"
#include "../Exception/Error.hpp"
#include <vector>
#include <SFML/Audio.hpp>

using namespace irr;

class ABlock;

class Bomb {
    public:
        Bomb(irr::scene::ISceneManager *smgr, irr::scene::IMeshSceneNode *cube, irr::IrrlichtDevice* device, irr::video::ITexture *_texture, int power, std::vector<std::vector<ABlock *>> *map);
        ~Bomb();
        bool detonate(std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *,
        std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *,
        std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *, double &deltaFrame);
        void displayParticles();
        void radius(std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *,
        std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *,
        std::vector<std::vector<std::pair<char, irr::core::vector3df>>> *);
        void setDetonateTime(float);
        irr::scene::IMeshSceneNode *getCube() const;
        irr::scene::IParticleSystemSceneNode *getParticleOne() const;
        irr::scene::IParticleSystemSceneNode *getParticleTwo() const;
        int getPower() const;
        irr::core::vector3df getBombCenter() const;
        bool _removed = true;
        void deleteMesh();
        void createSound();
    private:
        irr::video::ITexture *_texture;
        irr::scene::ISceneManager *_smgr;
        irr::scene::IMeshSceneNode *_bomb;
        irr::IrrlichtDevice *_device;
        std::vector<std::vector<ABlock *>> *_map;
        scene::IParticleSystemSceneNode* _ps = nullptr;
        scene::IParticleSystemSceneNode* _ps2 = nullptr;
        core::aabbox3d<f32> _vertical = {0, 0, 0, 1, 0, 1};
        core::aabbox3d<f32> _horizontal = {0, 0, 0, 1, 0, 1};
        int _indexX;
        int _indexY;
        float _scale;
        int _power;
        enum { UP, DOWN, LEFT, RIGHT };
        bool _trig = true;
        float _time = 0;
        float _detonateTime = 2;
        bool _setparticle = false;
        irr::core::vector3df _bombCenter;
        sf::Sound _sound;
        sf::SoundBuffer _buff;
};

#endif //OOP_INDIE_STUDIO_2018_BOMB_HPP
