#pragma once

#include "Entity.h"
#include "Player.h"
#include<SDL.h>
#include<SDL_image.h>

class RenderWindow{
public:

    RenderWindow(const char* title, int _w, int _h);
    void cleanUp();
    SDL_Texture* loadTexture(const char* filePath);
    void clear();
    void render(Player player);
    void render(SDL_Texture* tex);
    void display();

private:

    SDL_Window* window;
    SDL_Renderer* renderer;

};