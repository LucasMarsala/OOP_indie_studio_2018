/*
** EPITECH PROJECT, 2019
** nano
** File description:
** hpp
*/

#ifndef ERROR_HPP
#define ERROR_HPP

#include <iostream>
#include <stdexcept>

class Error : public std::exception
{
    public:
        Error(std::string const &message = "Unknown");
        const char *what(void) const noexcept;
    private:
        std::string _message;
};

class ErrorGetTexture : public Error
{
    public:
        ErrorGetTexture(std::string const &message) : Error(message) {}
};

class ErrorGetPlanet : public Error
{
    public:
        ErrorGetPlanet(std::string const &message) : Error(message) {}
};

class ErrorGetStartButton : public Error
{
    public:
        ErrorGetStartButton(std::string const &message) : Error(message) {}
};

class ErrorGetSettingsButton : public Error
{
    public:
        ErrorGetSettingsButton(std::string const &message) : Error(message) {}
};

class ErrorGetCreditsButton : public Error
{
    public:
        ErrorGetCreditsButton(std::string const &message) : Error(message) {}
};

class ErrorGetExitButton : public Error
{
    public:
        ErrorGetExitButton(std::string const &message) : Error(message) {}
};

class ErrorGetStartButtonHover : public Error
{
    public:
        ErrorGetStartButtonHover(std::string const &message) : Error(message) {}
};

class ErrorGetSettingsButtonHover : public Error
{
    public:
        ErrorGetSettingsButtonHover(std::string const &message) : Error(message) {}
};

class ErrorGetCreditsButtonHover : public Error
{
    public:
        ErrorGetCreditsButtonHover(std::string const &message) : Error(message) {}
};

class ErrorGetExitButtonHover : public Error
{
    public:
        ErrorGetExitButtonHover(std::string const &message) : Error(message) {}
};

class ErrorGetVolume : public Error
{
    public:
        ErrorGetVolume(std::string const &message) : Error(message) {}
};

class ErrorGetVsync : public Error
{
    public:
        ErrorGetVsync(std::string const &message) : Error(message) {}
};

class ErrorGetVolumeHover : public Error
{
    public:
        ErrorGetVolumeHover(std::string const &message) : Error(message) {}
};

class ErrorGetVsyncHover : public Error
{
    public:
        ErrorGetVsyncHover(std::string const &message) : Error(message) {}
};

class ErrorGetBar0 : public Error
{
    public:
        ErrorGetBar0(std::string const &message) : Error(message) {}
};

class ErrorGetBar25 : public Error
{
    public:
        ErrorGetBar25(std::string const &message) : Error(message) {}
};

class ErrorGetBar50 : public Error
{
    public:
        ErrorGetBar50(std::string const &message) : Error(message) {}
};

class ErrorGetBar75 : public Error
{
    public:
        ErrorGetBar75(std::string const &message) : Error(message) {}
};

class ErrorGetBar100 : public Error
{
    public:
        ErrorGetBar100(std::string const &message) : Error(message) {}
};

class ErrorGetYesImage : public Error
{
    public:
        ErrorGetYesImage(std::string const &message) : Error(message) {}
};

class ErrorGetNoImage : public Error
{
    public:
        ErrorGetNoImage(std::string const &message) : Error(message) {}
};

class ErrorGetYesImageHover : public Error
{
    public:
        ErrorGetYesImageHover(std::string const &message) : Error(message) {}
};

class ErrorGetNoImageHover : public Error
{
    public:
        ErrorGetNoImageHover(std::string const &message) : Error(message) {}
};

class ErrorAddButton : public Error
{
    public:
        ErrorAddButton(std::string const &message) : Error(message) {}
};

class ErrorGetBackImage : public Error
{
    public:
        ErrorGetBackImage(std::string const &message) : Error(message) {}
};

class ErrorGetBackImageHover : public Error
{
    public:
        ErrorGetBackImageHover(std::string const &message) : Error(message) {}
};

class ErrorGetCreditsImage : public Error
{
    public:
        ErrorGetCreditsImage(std::string const &message) : Error(message) {}
};

class ErrorGetSky : public Error
{
    public:
        ErrorGetSky(std::string const &message) : Error(message) {}
};

class ErrorGetWarrioAnime : public Error
{
    public:
        ErrorGetWarrioAnime(std::string const &message) : Error(message) {}
};

class ErrorGetMenuTitle : public Error
{
    public:
        ErrorGetMenuTitle(std::string const &message) : Error(message) {}
};

class ErrorGetNoPlayer : public Error
{
    public:
        ErrorGetNoPlayer(std::string const &message) : Error(message) {}
};

class ErrorGetPlayerOne : public Error
{
    public:
        ErrorGetPlayerOne(std::string const &message) : Error(message) {}
};

class ErrorGetPlayerTwo : public Error
{
    public:
        ErrorGetPlayerTwo(std::string const &message) : Error(message) {}
};

class ErrorGetPlayButton : public Error
{
    public:
        ErrorGetPlayButton(std::string const &message) : Error(message) {}
};

class ErrorGetPlayButtonHover : public Error
{
    public:
        ErrorGetPlayButtonHover(std::string const &message) : Error(message) {}
};

class ErrorGetLoadGame : public Error
{
    public:
        ErrorGetLoadGame(std::string const &message) : Error(message) {}
};

class ErrorGetNewGame : public Error
{
    public:
        ErrorGetNewGame(std::string const &message) : Error(message) {}
};

class ErrorGetLoadGameHover : public Error
{
    public:
        ErrorGetLoadGameHover(std::string const &message) : Error(message) {}
};

class ErrorGetNewGameHover : public Error
{
    public:
        ErrorGetNewGameHover(std::string const &message) : Error(message) {}
};

class ErrorGetObject : public Error
{
    public:
        ErrorGetObject(std::string const &message) : Error(message) {}
};

class ErrorGetMusic : public Error
{
    public:
    ErrorGetMusic(std::string const &message) : Error(message) {}
};

class ErrorGetSaveMap : public Error
{
    public:
    ErrorGetSaveMap(std::string const &message) : Error(message) {}
};

#endif /* Error */
