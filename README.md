# OOP_indie_studio_2018
Last project of the second year at Epitech. The aim of the project was to create a bomberman game using libirrlicht & libsfml.

## Prerequisite

  Docker version 20.10 and docker-compose version 1.29.2 or gcc version 12.2.0 and make version 4.3.

## On Windows

```
  $ Double click on setup.exe
  # It will install all the dependencies and packages to run the application.
  # Then, you can search on Windows an application named bomberman.
  # Next enjoy the game !
```

## Build with docker

```
$ sudo apt install -y x11-xserver-utils
$ xhost +local:
$ docker-compose build
$ docker-compose up
```

## Build with makefile

```
$ sudo apt install -y libsfml-dev libirrlicht-dev
$ make
$ ./bomberman
```
