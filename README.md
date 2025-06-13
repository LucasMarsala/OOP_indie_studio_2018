# OOP_indie_studio_2018
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/585426d4db494ecb921ee34a572e250f)](https://www.codacy.com/gh/LucasMarsala/OOP_indie_studio_2018/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=LucasMarsala/OOP_indie_studio_2018&amp;utm_campaign=Badge_Grade)
![Language](https://img.shields.io/badge/language-CPP-blue.svg)

A student-made Bomberman-style game written in C++ using SFML and irrlicht.  
Plant bombs, destroy obstacles, and defeat enemies in an explosive retro-style arcade experience!

![Screenshot_2023-03-21_10-54-13](https://user-images.githubusercontent.com/39527261/226572038-031fd963-3833-4091-b11f-815d63c6bc04.png)

## 🎮 Features

- 🧨 Classic Bomberman gameplay mechanics
- 👾 AI-controlled enemies
- 🧱 Breakable and unbreakable walls
- 🚀 Power ups
- 🧠 Simple pathfinding logic for bots
- 🎵 Sound and music support
- 🎮 Keyboard-based controls

---

## 🛠️ Built With

- **C++**
- **SFML 2.5+** — Simple and Fast Multimedia Library
- **Irrlicht** - 3D engine
  
---

## 🚀 Getting Started

### Prerequisites

Make sure you have the following installed:

- `g++` or any CPP compiler
- `cmake`
- [SFML](https://www.sfml-dev.org/download/sfml/) (Graphics/Audio library)
- [Irrlicht](https://irrlicht.sourceforge.io/?page_id=10) (3D Engine)

```bash
sudo apt install -y g++ make libcsfml-dev libirrlicht-dev
```

or a Docker version 20+

```bash
sudo apt install -y docker x11-xserver-utils
```

### How to run the project

Using CMake
```
  $ mkdir build # Create a build folder at the root of the project
  $ cmake ..
  $ cmake --build . --config Release
  # Go to Release Directory (Present at the root of the project)
  $ mv bomberman.exe ../ #Move the executable at the root of the project
```

Using installer
```
  $ Use the setup.exe
  # It will install all the dependencies and packages to run the application.
  # Then, you can search on Windows an application named bomberman.
```

Using Docker

```bash
xhost +local:
docker compose up --build
```

### Contributors
[Fred Helle](https://github.com/Benkooo)
[Joachim Novak](https://github.com/Itrasis)
[Simon Baumgartner](simon.baumgartner@epitech.eu)
[Fréderic Lim](frederic.lim@epitech.eu)
[Thibaut Burckel](thibaut.burckel@epitech.eu)
