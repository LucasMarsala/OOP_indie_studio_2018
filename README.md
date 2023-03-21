# OOP_indie_studio_2018
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/585426d4db494ecb921ee34a572e250f)](https://www.codacy.com/gh/LucasMarsala/OOP_indie_studio_2018/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=LucasMarsala/OOP_indie_studio_2018&amp;utm_campaign=Badge_Grade)

Last project of the second year at Epitech. The aim of the project was to create a bomberman game using libirrlicht & libsfml.


![Screenshot_2023-03-21_10-54-13](https://user-images.githubusercontent.com/39527261/226572038-031fd963-3833-4091-b11f-815d63c6bc04.png)
![Screenshot_2023-03-21_10-54-43](https://user-images.githubusercontent.com/39527261/226572050-b5691eaa-2535-4c6d-9a1a-61fb5209f8f6.png)

## Prerequisite

  Docker version 20.10 and docker-compose version 1.29.2 or g++ version 12.2.0 and make version 4.3 or libsfml version 2.5 and libirrlicht version 1.8.

## On Windows

```
  # First solution:
  $ mkdir build # Create a build folder at the root of the project
  $ cd build # Go to the build folder
  $ cmake ..
  $ cmake --build . --config Release
  # Go to Release Directory (Present at the root of the project)
  $ mv bomberman.exe ../ #Move the executable at the root of the project
```

```
  # Second Solution (recommanded):
  $ Use the setup.exe
  # It will install all the dependencies and packages to run the application.
  # Then, you can search on Windows an application named bomberman.
  # Next enjoy the game !
```

## On Linux

```
$ sudo apt install -y libsfml-dev libirrlicht-dev
$ make
$ ./bomberman
```

## Build with docker

```
$ sudo apt install -y x11-xserver-utils
$ xhost +local:
$ docker-compose build
$ docker-compose up
```
