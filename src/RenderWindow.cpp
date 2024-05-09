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

    if(loaded == nullptr) std::cout << "Failed to load Texture!" << SDL_GetError() << std::endl;

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

// void RenderWindow::render(Projectiles p) {

//     static int count = 0;

//     std::vector<SDL_Rect> clips = p.clips;

//     SDL_Rect destRect;

//     destRect.x = p.getX() - p.getWidth() / 2;
//     destRect.y = p.getY() - p.getHeight() / 2;
//     destRect.w = p.getWidth();
//     destRect.h = p.getHeight();

//     SDL_Rect srcRect = clips[count / 4];

//     SDL_RenderCopyEx(renderer, p.getSprite(), &srcRect, &destRect, p.getAngle(), NULL, SDL_FLIP_NONE);

//     count++;
//     if(count >= 16) count = 0;
// }

void RenderWindow::render(Ezreal e, double deltaTime) {

    e.updateClip(deltaTime);
    int i = e.getCurrentFrame();
    SDL_Rect srcRect = e.clips[i];

    // static int count = 0;
    // std::vector<SDL_Rect> clips = e.clips;
    // SDL_Rect srcRect = clips[count / 250];
    // count++; if(count >= 1000) count = 0;

    SDL_Rect destRect;

    destRect.x = e.getX() - e.getWidth() / 2;
    destRect.y = e.getY() - e.getHeight() / 2;
    destRect.w = e.getWidth();
    destRect.h = e.getHeight();

    SDL_RenderCopyEx(renderer, e.getSprite(), &srcRect, &destRect, e.getAngle(), NULL, SDL_FLIP_NONE);

}