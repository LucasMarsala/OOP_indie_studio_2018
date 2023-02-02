/*
** EPITECH PROJECT, 2019
** LoadGame
** File description:
** Load class
*/

#ifndef LOADGAME_HPP_
#define LOADGAME_HPP_

#include "EventReceiver.hpp"
#include "../Integration/Integration.hpp"
#include <vector>

class LoadGame {
	public:
	    explicit LoadGame(IrrlichtDevice *, IGUIEnvironment *, ISceneManager *, IVideoDriver *) noexcept;
        LoadGame(LoadGame const &) noexcept = delete;
        explicit LoadGame(LoadGame &&) noexcept = delete;
        ~LoadGame() noexcept;

        void create();
        void focus();
        void createSound();
        void buttonReset();
        void eventManager(double);
        void setVisible(bool);

		bool isSelectOn() const;
        void setSelectOn(bool);

        bool isLoad() const;
        void setLoad(bool _load);

        int _soundBar;

    private:
        IrrlichtDevice *_device;
        IGUIEnvironment *_gui;
        ISceneManager *_sceneManager;
        IVideoDriver *_driver;
		EventReceiver *_receiver;
		std::vector<IGUIButton *> _buttons;
		std::vector<ITexture *> _hover;
		std::vector<ITexture *> _text;
		std::vector<std::vector<int>> _pos;
		int _focus;
		int _oldFocus;
        double _time;
        int _start;
        int _shift;
        bool _selectOn;
        bool _load;
        sf::Sound _sound;
        sf::Sound _acceptSound;
            sf::SoundBuffer _soundBuffer;
    sf::SoundBuffer _accept;
};

#endif /* !LOADGAME_HPP_ */