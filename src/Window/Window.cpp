/*
** EPITECH PROJECT, 2019
** window
** File description:
** window class cpp
*/

#include "Window.hpp"
#include "../Exception/Error.hpp"

namespace window {
    Window::Window() : _width(1920), _height(1080), _gameMenu(false)
    {
        EventReceiver *receiver = new EventReceiver;

        _device = irr::createDevice(irr::video::EDT_OPENGL,
            irr::core::dimension2d<irr::u32>(_width, _height), 16, false, false, true, receiver);
        ICursorControl *curs = _device->getCursorControl();
        curs->setVisible(false);
        _guiEnv = _device->getGUIEnvironment();
        _sceneManager = _device->getSceneManager();
        _newSceneManager = _device->getSceneManager()->createNewSceneManager();
        _driver = _device->getVideoDriver();
        _receiver = receiver;
        _splash = new splashScreen::Screen(_driver);
    }

    Window::~Window()
    {
        delete _splash;
        delete _menu;
    }

    void Window::setWindow()
    {
    }

    void Window::create()
    {
        _menu = new mainMenu::MainMenu(_device, _guiEnv, _sceneManager, _newSceneManager, _driver);
        _menu->createMenu();
    }

    void Window::runWindow()
    {
        ITexture *image;
        irr::u32 then = _device->getTimer()->getTime();

        create();
        while (_device->run()) {
            const u32 now = _device->getTimer()->getTime();
            const f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f;
            then = now;
            _menu->run(frameDeltaTime);
            _driver->beginScene(true, true, 0);
            image = _device->getVideoDriver()->getTexture("ressources/sky.png");
            if (image == NULL)
                throw ErrorGetSky("Couldn't get texture from sky");
            _driver->draw2DImage(image, position2d<int>(0, 0));
            _sceneManager->drawAll();
            _guiEnv->drawAll();
            if (_menu->isStart())
                _newSceneManager->drawAll();
             if (_splash->isActive()) {
                 _splash->displaySplashscreen(frameDeltaTime, _driver); 
            }
            _driver->endScene();
        }
    }

    IrrlichtDevice *Window::getDevice() const
    {
        return _device;
    }

    IGUIEnvironment *Window::getGuiEnv() const
    {
        return _guiEnv;
    }

    ISceneManager *Window::getSceneManager() const
    {
        return _sceneManager;
    }

    IVideoDriver *Window::getDriver() const
    {
        return _driver;
    }
}