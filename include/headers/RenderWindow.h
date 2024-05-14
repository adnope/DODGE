#pragma once

#include "Player.h"
#include "Projectiles.h"

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

class RenderWindow{
public:

    RenderWindow(const char* title, int _w, int _h);
    void cleanUp();
    SDL_Texture* loadTexture(const char* filePath);
    void clear();
    void render(Player player);
    void render(SDL_Texture* tex);
    void render(Ezreal p, double deltaTime);
    void render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor, bool isHovered);
    void renderCenterX(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor, bool isHovered);
    void display();

private:

    SDL_Window* window;
    SDL_Renderer* renderer;

};