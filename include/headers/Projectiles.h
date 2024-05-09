#pragma once

#include "Player.h"

#include<SDL.h>
#include<SDL_image.h>

#include<cmath>
#include<vector>
#include<random>
#include<iostream>

class Projectiles{
protected:

    SDL_Texture* sprite;
    float angle;
    float x, y;
    float dx, dy;
    float speed;
    int width, height;

public:

    SDL_Texture* getSprite() {

        return sprite;

    }

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    float getAngle() const {
        return angle;
    }

};

class Ezreal : public Projectiles{
private:
    double frameTimer;
    int currentFrame = 0;

public:

    bool isDead = false;

    std::vector<SDL_Rect> clips = {
        {0, 0, 12, 13},
        {16, 0, 12, 13},
        {32, 0, 12, 13},
        {48, 0, 12, 13}
    };

    Ezreal(SDL_Texture* _sprite, Player player) {

        speed = 0.5;

        width = 36;
        height = 39;

        sprite = _sprite;

        spawn(player);

    }

    void updateClip(double deltaTime) {

        frameTimer += deltaTime;

        if(frameTimer >= 0.033) {
            currentFrame++;
            frameTimer = 0;
        }

        if(currentFrame >= 4) currentFrame = 0;

    }

    int getCurrentFrame() {
        return currentFrame;
    }

    void spawn(Player player) {
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distX(-1500, 1500);
        std::uniform_real_distribution<float> distY(-1500, 1500);

        x = distX(gen);
        y = distY(gen);

        dx = player.getX() - x;
        dy = player.getY() - y;

        angle = atan2(dy, dx) * 180 / 3.141592;

    }

    void move(Player player, double deltaTime) {

        float distance = std::sqrt(dx * dx + dy * dy);

        if(distance > 0) {
            dx /= distance;
            dy /= distance;
        }
        
        x += dx * speed * deltaTime * 1000;
        y += dy * speed * deltaTime * 1000;

        if(x >= 2000 || y >= 2000 || x <= -2000 || y <= -2000) isDead = true; 

    }

};