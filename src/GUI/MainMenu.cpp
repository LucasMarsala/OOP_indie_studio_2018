/*
** EPITECH PROJECT, 2019
** Menu
** File description:
** MainMenu functions
*/

#include "MainMenu.hpp"
#include "../Game/Game.hpp"
#include "../Exception/Error.hpp"

namespace mainMenu {
    MainMenu::MainMenu(IrrlichtDevice *device, IGUIEnvironment *gui, ISceneManager *sceneManager, ISceneManager *newSceneManager, IVideoDriver *driver) noexcept
    : _device(device), _gui(gui), _sceneManager(sceneManager), _newSceneManager(newSceneManager), _driver(driver), _start(false), _block(0), _play(false), _back(false), _map(false), _scale(0), _splash(true)
    {
        _button = new MenuButton(_device, _gui, _sceneManager, _driver);
        _settings = new Settings(_device, _gui, _sceneManager, _driver);
        _credits = new Credits(_device, _gui, _sceneManager, _driver);
        _selecting = new selecting::SelectingEvent(_device, _gui, _newSceneManager, _driver);
        _load = new LoadGame(_device, _gui, _sceneManager, _driver);
        _receiver = dynamic_cast<EventReceiver *>(_device->getEventReceiver());
        _game = new Game(_device, _gui, _sceneManager, _driver, _receiver, _settings->getDifficultyLvl());
        _inGameMenu = new InGameMenu(_device, _gui, _sceneManager, _driver);
        _background = _sceneManager->addParticleSystemSceneNode(false);
        _meteor = _sceneManager->addParticleSystemSceneNode(false);
    }

    MainMenu::~MainMenu()
    {
        delete _game;
        delete _inGameMenu;
    }

    void MainMenu::createMusic()
    {
        if (!_music.openFromFile("ressources/music/menu_music.ogg"))
            throw ErrorGetMusic("Couldn't get music file.\n");
        _music.setVolume(8);
        _music.setLoop(true);
    }

    void MainMenu::createMenu()
    {
        ITexture *image;
        IAnimatedMesh *anime;

        _button->create();
        _settings->create();
        _credits->create();
        _inGameMenu->create();
        _cam = _sceneManager->addCameraSceneNode(0, vector3df(0, 450, -50), vector3df(0,0,0));
        _light = _sceneManager->addLightSceneNode(_cam, vector3df(0, -10, 0), SColorf(1.0f, 1.0f, 1.0f, 1.0), 1000000);
        anime = _sceneManager->getMesh("ressources/Planet/planet.3ds");
        if (anime == NULL)
            throw ErrorGetPlanet("Couldn't get planet.3ds");
        _planet = _sceneManager->addAnimatedMeshSceneNode(_sceneManager->getMesh("ressources/Planet/planet.3ds"));
        _planet->setPosition(vector3df(0,-423,0));
        _planet->setRotation(vector3df(0, -100, -90));

        float factor = (140/_planet->getTransformedBoundingBox().getExtent().X) * 6;
        _planet->setScale({factor, factor, factor});

        _target = _sceneManager->addCubeSceneNode(1, _planet, -1, vector3df(-1.91, 1.28, 0.23), vector3df(0,0,0), vector3df(0.1,0.1,0.1));
        _load->create();
        _selecting->create();
        _selecting->setVisible(false);

        _em = _meteor->createBoxEmitter(
            core::aabbox3d<f32>{0, 0, 0, 3, 3, 3},
            core::vector3df(0.0f, 0.0f,0.0f),
            200 , 200,
            video::SColor(0, 255, 255, 100),
            video::SColor(0,255,255,255),
            200, 2000,0,
            core::dimension2df(1, 1),
            core::dimension2df(5, 5));

        _meteor->setEmitter(_em);
        _em->drop();
        _em = _background->createBoxEmitter(
            {-120, 0, -120, 120, 5, 120},
            core::vector3df(0.0f, 0.0f,0.0f),
            200, 200,
            video::SColor(0, 0, 0, 0),
            video::SColor(0, 0, 255,255),
            2000,2000,0,
            core::dimension2df(1, 1),
            core::dimension2df(10, 10));
        _background->setEmitter(_em);
        _em->drop();

        _meteor->setScale(core::vector3df(1, 1, 1));
        _meteor->setParent(_target);
        _meteor->setPosition(core::vector3df(42, -14.9, 16.9));
        _meteor->setMaterialFlag(video::EMF_LIGHTING, true);
        _meteor->setMaterialFlag(video::EMF_ZWRITE_ENABLE, true);
        anime = _sceneManager->getMesh("Models/Star Bit.obj");
        if (anime == NULL)
            throw ErrorGetObject("Could't get bit.obj oject");
        _meteorMesh = _sceneManager->addMeshSceneNode(anime, _meteor, 1, {3.5, 1.4, -0.6});
        _meteorMesh->setScale({0.03, 0.03, 0.03});
        _sceneManager->getMeshManipulator()->setVertexColors(_meteorMesh->getMesh(), irr::video::SColor(0, 0, 204, 205));

       _background->setScale(core::vector3df(10, 0, 10));
       _background->setPosition(core::vector3df(0, -450, 0));
       _background->setMaterialFlag(video::EMF_LIGHTING, true);
       _background->setMaterialFlag(video::EMF_ZWRITE_ENABLE, true);


       ISceneNodeAnimator* anim = _sceneManager->createRotationAnimator(vector3df(0, 0.14, 0));
       _planet->addAnimator(anim);
       anim->drop();
       image = _driver->getTexture("ressources/MenuTitle.png");
       if (image == NULL)
        throw ErrorGetMenuTitle("Couldn't get texture from menu title");
       _title = _gui->addImage(image, position2d<int>(1920/2 - 599/2, 100));
        _back = true;
        _map = false;
        _explosion = _sceneManager->addSphereSceneNode(10);
        _explosion->setVisible(false);
        createMusic();
    }

    void MainMenu::manageSound()
    {
        _music.setVolume(_settings->_soundBar / 12.5);
        _button->_soundBar = _settings->_soundBar;
        _credits->_soundBar = _settings->_soundBar;
        _load->_soundBar = _settings->_soundBar;
        _game->_soundBar = _settings->_soundBar;
        _inGameMenu->_soundBar = _settings->_soundBar;
    }

    void MainMenu::run(double time)
    {
        static bool isSetting = false;
        static double clockMusic = 0;
        static double clock = 0;
        static bool isStart = false;
        static float i = _target->getPosition().Y;
        static float z = _target->getPosition().Z;
        static bool mus = false;

        if (_receiver->isKeyDown(KEY_DOWN)) {
             i -= 0.1;
        }
        if (_receiver->isKeyDown(KEY_UP)) {
            i += 0.1;
        }
        _time = time;
        clockMusic += time;
        clock+=time;
        if (_button->isSettingsOn())
            isSetting = true;
        if (isSetting) {
            _button->setVisible(false);
            _settings->setVisible(true);
            _settings->eventManager(_time);
            _settings->focus();
            manageSound();
        } else if (_button->isCreditsOn() && !_button->isStartOn()) {
            _button->setVisible(false);
            _title->setVisible(false);
            _credits->setVisible(true);
            _credits->eventManager(time);
        } else {
            if (!_button->isStartOn() && !_play && !_load->isSelectOn() && !_splash)
                _button->eventManager(_time);
            _button->buttonReset();
            _button->focus();
        }
        if (_credits->isBackOn()) {
            _credits->setVisible(false);
            _button->setVisible(true);
            _button->setCreditsOn(false);
            _credits->setBackOn(false);
            _title->setVisible(true);
        }
        if (_settings->isBackOn()) {
            if (_inGameMenu->isMenu()) {
                _inGameMenu->setOptions(false);
                _inGameMenu->setVisible(true);
                _button->setSettingsOn(false);
                _settings->setBackOn(false);
                isSetting = false;
            } else {
                _button->setVisible(true);
                isSetting = false;
                _button->setSettingsOn(false);
                _settings->setBackOn(false);
            }
        }
        if (clockMusic > 12 && !mus) {
            _music.play();
            clockMusic = 0;
            _splash = false;
            mus = true;
        }
        if (_button->isStartOn()) {
            setVisible(false);
            _load->setVisible(true);
            _load->eventManager(time);
            _load->focus();
            _load->buttonReset();
            _start = _button->isStartOn();
        }
        if (_load->isSelectOn()) {
            _button->setStartOn(false);
            _load->setVisible(false);
            _selecting->setVisible(true);
            _selecting->run(time);
        }
        if (_selecting->isPlay()) {
            _music.setVolume(0);
            _load->setSelectOn(false);
            _planet->removeAnimators();
            _selecting->setVisible(false);
            if (_back) {
                _y = _planet->getRotation().Y;
                _x = _planet->getRotation().X;
                _speedx = (77 - _planet->getRotation().X) / 100;
                _speedy = (-33 - _planet->getRotation().Y) / 100;
                _back = false;
            }
            if (_block == 0) {
                rotation();
            } else
                fallMeteor(false);
            _play = true;
        }
        if (_play && _receiver->isKeyDown(KEY_ESCAPE) && clock > 0.2) {
            _inGameMenu->setVisible(true);
            _inGameMenu->setMenu(true);
            clock = 0;
        }
        if (_inGameMenu->isExit()) {
            _back = true;
            _play = false;
            _map = false;
            delete _game;
            _game = new Game(_device, _gui, _sceneManager, _driver, _receiver, _settings->getDifficultyLvl());
            antiRotation();
            _inGameMenu->setVisible(false);
            _button->setVisible(true);
            _inGameMenu->setExit(false);
            _game->_music.stop();
            _selecting->setPlay(false);
            _block = 0;
            _title->setVisible(true);
            _load->setLoad(false);
        }
        if (_inGameMenu->isOptions()) {
            _inGameMenu->setVisible(false);
            _button->setSettingsOn(true);
        }
        if (_inGameMenu->isSave()) {
            _game->saveMap();
            _inGameMenu->setSave(false);
        }
        if (_inGameMenu->isMenu())
            _inGameMenu->run(time);
            _music.setVolume(_settings->_soundBar / 12.5);
        if (_load->isLoad()) {
            _button->setStartOn(false);
            _music.stop();
            _load->setSelectOn(false);
            _planet->removeAnimators();
            _load->setVisible(false);
            if (_back) {
                _y = _planet->getRotation().Y;
                _x = _planet->getRotation().X;
                _speedx = (77 - _planet->getRotation().X) / 100;
                _speedy = (-33 - _planet->getRotation().Y) / 100;
                _back = false;
            }
            if (_block == 0) {
                rotation();
            } else
                fallMeteor(true);
            _play = true;
        }
    }

    void MainMenu::rotation()
    {
        if (_x < 76 || _x > 78)
            _x += _speedx;
        else
            _block = true;
        if ((_y < -35 || _y > -34))
            _y += _speedy;
        _planet->setRotation(vector3df(_x, _y, _planet->getRotation().Z));
    }

    void MainMenu::antiRotation()
    {
        _music.play();
        _explosion->setVisible(false);
        _em = _meteor->createBoxEmitter(
            core::aabbox3d<f32>{0, 0, 0, 3, 3, 3},
            core::vector3df(0.0f, 0.0f,0.0f),
            200 , 200,
            video::SColor(0, 255, 255, 100),
            video::SColor(0,255,255,255),
            200, 2000,0,
            core::dimension2df(1, 1),
            core::dimension2df(5, 5));

        _meteor->setEmitter(_em);
        _meteorMesh->setVisible(true);
        _em->drop();
        _meteor->removeAnimators();
        _planet->setRotation(vector3df(0, -100, -90));
        _meteor->setScale(core::vector3df(1, 1, 1));
        _meteor->setParent(_target);
        _meteor->setPosition(core::vector3df(42, -14.9, 16.9));
        _meteor->setMaterialFlag(video::EMF_LIGHTING, true);
        _meteor->setMaterialFlag(video::EMF_ZWRITE_ENABLE, true);
        _planet->addAnimator(_sceneManager->createRotationAnimator(vector3df(0, 0.14, 0)));
        _cam->addAnimator(_sceneManager->createFlyStraightAnimator(_meteor->getPosition(), {0, 450, -50}, 500));
        _y = _planet->getRotation().Y;
        _x = _planet->getRotation().X;
        _speedx = (77 - _planet->getRotation().X) / 100;
        _speedy = (-33 - _planet->getRotation().Y) / 100;
        _reset[0] = true;
        _reset[1] = true;
        _meteor->setVisible(true);
    }

    void MainMenu::fallMeteor(bool load)
    {
        if (_reset[0]) {
            _meteor->setPosition({-10, 30, -30});
            _anim = _sceneManager->createFlyStraightAnimator(_cam->getPosition(), {0, 120, -50}, 500);
            _cam->addAnimator(_anim);
            _anim->drop();
            _anim = _sceneManager->createFlyStraightAnimator(_meteor->getPosition(), _target->getPosition(), 1000);
             _meteor->addAnimator(_anim);
            _anim->drop();
            _reset[0] = false;
        }
       if (_meteor->getPosition() == _target->getPosition() && _reset[1]) {
            _scale = 0.1;
           _explosion->setVisible(true);
           _meteorMesh->setVisible(false);
            _meteor->setVisible(false);
            _reset[1] = false;
       }
       if (!_map && _scale > 11 && !_reset[1]) {
           _music.stop();
           if (load) {
                _game->loadMap();
                _game->createMusic();
            } else {
                _game->createMap(_selecting->getPlayer(), _selecting->getComplexity(), _selecting->getBoosts(), _selecting->getDensity());
                _game->createMusic();
            }
            _map = true;
        }
       if (!_reset[1] && _scale < 14) {
           _scale += 10 * _time;
           _explosion->setScale({_scale, _scale, _scale});
       }
        if (_scale > 14 && _map)
            _game->run(_time, _inGameMenu->isMenu(), _settings->getDifficultyLvl());
    }

    MainMenu &MainMenu::operator=(MainMenu const &cmenu) noexcept
    {
        return *this;
    }

    MainMenu &MainMenu::operator=(MainMenu &&cmenu) noexcept
    {
        return *this = cmenu;
    }

    bool MainMenu::isStart() const
    {
        return _start;
    }

    void MainMenu::setVisible(bool visible)
    {
        _button->setVisible(visible);
        _title->setVisible(visible);
    }

    bool MainMenu::isPlay() const
    {
        return _play;
    }
}