#pragma once
#include "Entity.h"
#include<SDL.h>
#include<SDL_image.h>
#include<cmath>
#include<iostream>

class Projectiles : public Entity{
private:

    const int speed = 5;
    float destX, destY;

public:

    Projectiles(float _x, float _y, SDL_Texture* _tex) {
        destX = _x;
        destY = _y;
        width = 50;
        height = 50;
        x = _x + 30;
        y = _y + 25;
        tex = _tex;
    }

    void takeMouseInput() {
        int _x, _y;
        SDL_GetMouseState(&_x, &_y);
        destX = _x;
        destY = _y;
    }

    void move() {

        float dx = destX - x;
        float dy = destY - y;

        float distance = std::sqrt(dx * dx + dy * dy);

        if(distance > 0) {
            dx /= distance;
            dy /= distance;
        }
        
        x += dx * speed;
        y += dy * speed;

        if (std::abs(x - destX) < speed && std::abs(y - destY) < speed) {
            x = destX;
            y = destY;
        }

    }

};