#pragma once
#include "Entity.h"
#include<SDL.h>
#include<SDL_image.h>
#include<cmath>
#include<iostream>

class Player : public Entity{
private:

    const int speed = 5;
    float destX, destY;

public:

    Player(float _x, float _y, SDL_Texture* _tex) {

        angle = 0;
        destX = _x;
        destY = _y;
        width = 50;
        height = 50;
        x = _x + 25;
        y = _y + 25;
        tex = _tex;

    }

    void takeMouseInput() {

        angle = 0;

        int _x, _y;
        SDL_GetMouseState(&_x, &_y);
        destX = _x;
        destY = _y;

        float dX = std::abs(destX - x);
        float dY = std::abs(destY - y);

        if(destX >= x + speed && destY <= y - speed) {
            angle = atan(dX/dY) * 180 / 3.141592;
        }

        if(destX >= x + speed && destY >= y + speed) {
            angle = 180 - ( atan(dX/dY) * 180 / 3.141592 );
        }

        if(destX <= x - speed && destY >= y + speed) {
            angle = 180 + ( atan(dX/dY) * 180 / 3.141592 );
        }

        if(destX <= x - speed && destY <= y - speed) {
            angle = 360 - atan(dX/dY) * 180 / 3.141592;
        }

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