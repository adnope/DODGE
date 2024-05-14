# DODGE
DODGE is a game created for my university project using C++ and [SDL2](https://www.libsdl.org/).

## Screenshots
![]() 

![]()

## Background
DODGE is a game where you, as the player, try to dodge as much projectiles as possible.
The game gets harder the more you are into it, with the projectiles spawning more and more.
The player uses ``right-click`` to move the character, and dies when hit by a SINGLE object.

## Features
1. Two types of projectiles with different speed.
2. Player's spells including ``Flash`` and ``Ghost``.
3. Highscore system.

## Prerequisites
1. [Mingw64](https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/)
2. [SDL2](https://github.com/libsdl-org/SDL/releases/tag/release-2.30.3), [SDL_Image](https://github.com/libsdl-org/SDL_image) and [SDL_TTF](https://github.com/libsdl-org/SDL_ttf)

## Compiling
### Windows
After installing all the dependencies, execute the following command in the project's directory:
```
g++ -std=c++20 -Wall -I"include" -I"include/sdl2" -I"include/headers" src/*.cpp -o bin/game.exe -L"lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

```
The compiled ``.exe`` is located in ``./bin``. For it to run, you must copy the ``./res`` folder as well as all ``.dll`` files from your SDL installation to its directory.

Or instead, execute this command in terminal inside the game's directory:
```
make run

```
This command compiles and create the ``.exe`` executable located in ``/bin`` and launch it right after.
### Linux
DODGE is currently only available on Windows. I will try to bring it to Linux in the future.

## Future Intentions
- New projectiles, different properties.
- More characters and skins.
