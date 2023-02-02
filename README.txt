To compile on Linux:
- mkdir build
- cd build
- cmake ..
- make
- cd ..
-./bomberman

To compile on Windows:

First solution:
- Create a build folder (MINGW : mkdir build) at the root of the project
- Go to the build folder (MINGW : cd build)
- cmake ..
- cmake --build . --config Release
- Go to Release Directory (Present at the root of the project)
- Move the executable at the root of the project (MINGW from Release Folder: mv bomberman.exe ../ )

Second Solution (recommanded):
Use the Setup.exe