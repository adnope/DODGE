#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<vector>

class Entity{
public:

    Entity() {
        x = 0; y = 0; tex = NULL;
    }
    Entity(float _x, float _y, SDL_Texture* _tex) : x(_x), y(_y), tex(_tex) {}

    SDL_Texture* getTex() {

        return tex;

    }

    float getX() {
        return x;
    }

    float getY() {
        return y;
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    float getAngle() {
        return angle;
    }

protected:

    float angle;
    float x, y;
    SDL_Texture* tex;
    int width;
    int height;

};