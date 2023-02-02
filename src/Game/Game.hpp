/*
** EPITECH PROJECT, 2019
** Game class
** File description:
** game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "../GUI/EventReceiver.hpp"
#include "../Map/Map.hpp"
#include "../APlayers/APlayers.hpp"
#include "../Characters/Mario/Mario.hpp"
#include "../Characters/Luigi/Luigi.hpp"
#include "../Characters/Yoshi/Yoshi.hpp"
#include "../Characters/Wario/Wario.hpp"
#include "../AI/AAi.hpp"
#include "../Integration/Integration.hpp"

class Game {
    public:
        explicit Game(IrrlichtDevice *, IGUIEnvironment *, ISceneManager *, IVideoDriver *, EventReceiver *, int difficulty) noexcept;
        Game(Game const &) noexcept = delete;
        explicit Game(Game &&) noexcept = delete;
        ~Game() noexcept;

        Game &operator=(Game const &) noexcept;
        Game &operator=(Game &&) noexcept;

        void run(double &, bool, int);

        void loadPlayers(std::vector<int> players, std::vector<State> states);
        void loadPlayerOne(int model, State state);
        void loadPlayerTwo(int model, State state);
        void loadPlayerThree(int model, State state);
        void loadPlayerFour(int model, State state);
        void update(irr::f32 deltaFrame);
        void movePlayer(irr::f32 deltaFrame);
        void collidePlayer(Players::APlayers *player, irr::f32 deltaFrame);
        void dropPlayerBomb(Players::APlayers *player, irr::EKEY_CODE key);
        void createMap(std::vector<State>, int complexity, int powerUp, float density);
        void createMap(std::vector<State>, std::vector<std::vector<int>>);
        void createMusic();
        void collideWithExplosion(Players::APlayers *player);
        void collideWithBomb(Players::APlayers *player);
        void saveMap();
        void loadMap();
        void checkMapRadius();
        void victory();

        sf::Music _music;
        int _soundBar;
        sf::Sound _sound;
        sf::SoundBuffer _buff;
    
    private:
        IrrlichtDevice *_device;
        IGUIEnvironment *_guiEnv;
        ISceneManager *_sceneManager;
        IVideoDriver *_driver;
        EventReceiver *_receiver;
        std::vector<vector3df> _pos;
        ILightSceneNode *_light;
        Map *_map;
        double _time;
        bool _victory = false;
        std::vector<Players::APlayers *> _players;
        std::vector<std::vector<std::pair<char, irr::core::vector3df>>> _mapAI;
        std::vector<std::vector<std::pair<char, irr::core::vector3df>>> _mapPlayer;
        std::vector<std::vector<std::pair<char, irr::core::vector3df>>> _mapPowerUp;
        std::vector<std::vector<std::pair<char, irr::core::vector3df>>> _mapRadius;
        int _difficulty;
};

#endif /* !GAME_HPP_ */