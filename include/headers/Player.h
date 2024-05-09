#pragma once

#include"RenderWindow.h"

#include<SDL.h>
#include<SDL_image.h>

#include<cmath>
#include<iostream>

class Player{
private:

    float angle;
    float x;
    float y;
    SDL_Texture* tex;
    const float speed = 2.5;
    float destX;
    float destY;
    const int width = 50;
    const int height = 50;

public:

    Player() {
        x = 0; y = 0; destX = 0; destY = 0; tex = NULL;
    }

    Player(float _x, float _y, SDL_Texture* _tex) {

        destX = _x;
        destY = _y;

        x = destX + 25;
        y = destY + 25;

        angle = 0;

        tex = _tex;

    }

    SDL_Texture* getTex() { return tex; }

    float getX() const { return x; }
    float getY() const { return y; }
    void setPos(float _x, float _y) { x = _x; y = _y; }

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    float getAngle() const { return angle; }

    void takeMouseInput() {

        angle = 0;

        int _x, _y;
        SDL_GetMouseState(&_x, &_y);
        destX = _x;
        destY = _y;

        float dX = destX - x;
        float dY = destY - y;

        angle = atan2(dY, dX) * 180 / 3.141592 + 90;

    }

    void move(double deltaTime) {

        float dx = destX - x;
        float dy = destY - y;

        float distance = std::sqrt(dx * dx + dy * dy);

        if(distance > 0) {
            dx /= distance;
            dy /= distance;
        }
        
        x += dx * speed * deltaTime * 100;
        y += dy * speed * deltaTime * 100;

        if (std::abs(x - destX) < speed && std::abs(y - destY) < speed) {
            x = destX;
            y = destY;
        }
        
    }

};