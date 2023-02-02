/*
** EPITECH PROJECT, 2019
** Menu
** File description:
** The Menu Class
*/


#ifndef menu
#define menu

#include <iostream>
#include "../Integration/Integration.hpp"
#include <vector>
#include <variant>
#include "Settings.hpp"
#include "MenuButton.hpp"
#include "Credits.hpp"
#include "SelectingEvent.hpp"
#include "LoadGame.hpp"
#include "InGameMenu.hpp"
#include "../Game/Game.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Game;

namespace mainMenu {
    class MainMenu {
    public:
        explicit MainMenu(IrrlichtDevice *, IGUIEnvironment *, ISceneManager *, ISceneManager *, IVideoDriver *) noexcept;
        MainMenu(MainMenu const &) noexcept = delete;
        explicit MainMenu(MainMenu &&) noexcept = delete;
        ~MainMenu() noexcept;

        MainMenu &operator=(MainMenu const &) noexcept;
        MainMenu &operator=(MainMenu &&) noexcept;

        void createMenu();
        void createMusic();
        void run(double time);
        void setVisible(bool);
        bool isStart() const;
        void rotation();
        void antiRotation();
        void fallMeteor(bool);
        bool isPlay() const;
        void manageSound();

        sf::Music _music;
    private:
        EventReceiver * _receiver;
        IMeshSceneNode* _target;
        scene::IParticleSystemSceneNode* _meteor;
        scene::IParticleSystemSceneNode* _background;
        ICameraSceneNode *_cam;
        IrrlichtDevice *_device;
        IGUIEnvironment *_gui;
        ISceneManager *_sceneManager;
        ISceneManager *_newSceneManager;
        LoadGame *_load;
        IVideoDriver *_driver;
        MenuButton *_button;
        Settings *_settings;
        IAnimatedMeshSceneNode *_planet;
        IMeshSceneNode *_explosion;
        IMeshSceneNode *_meteorMesh;
        ISceneNodeAnimator* _anim;
        scene::IParticleEmitter * _em;
        IGUIImage *_title;
        Credits *_credits;
        selecting::SelectingEvent *_selecting;
        InGameMenu *_inGameMenu;
        ILightSceneNode* _light;
        Game *_game;
        double _time;
        bool _play;
        float _scale;
        bool _start;
        int _block;
        bool _back;
        bool _map;
        bool _reset[2] = {true, true};
        sf::SoundBuffer _sound;
        float _x;
        float _y;
        float _speedx;
        float _speedy;
        bool _splash;
    };
}
#endif /* !menu */
