#include "RenderWindow.h"
#include <iostream>

RenderWindow::RenderWindow(const char* title, int _w, int _h) : window(NULL), renderer(NULL)
{

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _w, _h, SDL_WINDOW_SHOWN);

    if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

}

void RenderWindow::cleanUp() {

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

}

SDL_Texture* RenderWindow::loadTexture(const char* filePath) {

    SDL_Texture* loaded = IMG_LoadTexture(renderer, filePath);

    return loaded;

}

void RenderWindow::clear() {

    SDL_RenderClear(renderer);

}

void RenderWindow::display() {

    SDL_RenderPresent(renderer);

}

void RenderWindow::render(Player player) {

    SDL_Rect destRect;
    destRect.x = player.getX() - player.getWidth() / 2;
    destRect.y = player.getY() - player.getHeight() / 2;
    destRect.w = player.getWidth();
    destRect.h = player.getHeight();

    SDL_RenderCopyEx(renderer, player.getTex(), NULL, &destRect, player.getAngle(), NULL, SDL_FLIP_NONE);

}

void RenderWindow::render(SDL_Texture* tex) {

    SDL_RenderCopy(renderer, tex, NULL, NULL);

}