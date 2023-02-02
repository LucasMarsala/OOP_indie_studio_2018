/*
** EPITECH PROJECT, 2019
** window
** File description:
** Window class
*/


#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "../Integration/Integration.hpp"
#include "../GUI/EventReceiver.hpp"
#include "../GUI/MainMenu.hpp"
#include "../GUI/SelectingEvent.hpp"
#include "../Game/Game.hpp"
#include "../splashscreen/Splash.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace window {
	class Window {
	public:
		explicit Window();
		Window(Window const &) = delete;
		explicit Window(Window &&) = delete;
		~Window();

		Window &operator=(Window const &);
		Window &operator=(Window &&);

        IrrlichtDevice *getDevice() const;
        IGUIEnvironment *getGuiEnv() const;
        ISceneManager *getSceneManager() const;
        IVideoDriver *getDriver() const;
        void create();
		void setWindow();
		void runWindow();

	private:
        const int _width;
        const int _height;
        IrrlichtDevice *_device;
        IGUIEnvironment *_guiEnv;
        ISceneManager *_sceneManager;
        ISceneManager *_newSceneManager;
        IVideoDriver *_driver;
		EventReceiver *_receiver;
        mainMenu::MainMenu *_menu;
        splashScreen::Screen *_splash;
		double _time;
		bool _gameMenu;
	};
}
#endif /* !WINDOW_HPP_ */