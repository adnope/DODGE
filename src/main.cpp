#include "RenderWindow.h"
#include "Player.h"
#include "Projectiles.h"

#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <iostream>

RenderWindow window("DODGE!", 1280, 720);
SDL_Texture* playerTex = window.loadTexture("res/rocket.png");
SDL_Texture* ezrealSprite = window.loadTexture("res/ezreal.png");
SDL_Texture* background = window.loadTexture("res/space_background.png");
SDL_Rect ezrealClips[4] = {
	{0, 0, 12, 13},
	{0, 0, 12, 13},
	{0, 0, 12, 13},
	{0, 0, 12, 13}
};

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	return true;
}

bool SDLinit = init();

int state = 1; //0 = title screen, 1 = game, 2 = end screen
bool gameRunning = true;
Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0; 

float spawnRate = 1;
float timeSinceLastSpawn = 0;

SDL_Event event;

Player player(640, 360, playerTex);
Ezreal e(ezrealSprite, player);
std::vector<Ezreal> enemies = {};

void spawn(int index) {

	if(index == 0) {

		Ezreal e(ezrealSprite, player);
		enemies.push_back(e);

	}

}


void titleScreen() {

}

void update() {

	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick) / (double)SDL_GetPerformanceFrequency() );

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			gameRunning = false;
			
		if (event.type == SDL_MOUSEBUTTONDOWN) {

			if (event.button.button == SDL_BUTTON_RIGHT) {
				
				if(state == 1) player.takeMouseInput();

			}
			
		}
	}

	if(state == 1) {

		timeSinceLastSpawn += deltaTime;

		if(timeSinceLastSpawn >= spawnRate) {

			spawn(0); //0 = Ezreal, 1 = Brand

			timeSinceLastSpawn = 0.0f;

            spawnRate -= 25 * deltaTime;
            if (spawnRate < 0.5f) {
                spawnRate = 0.5f;
            }

		}

		for (size_t i = 0; i < enemies.size(); ) {

			enemies[i].move(player, deltaTime);

			if(enemies[i].isDead) {
				enemies.erase(enemies.begin()+i);
			}
			else i++;

        }

		player.move(deltaTime);

	}
}

void graphics() {

	if(state == 1) {

		window.render(background);
		window.render(player);
		for(Ezreal e : enemies) window.render(e, deltaTime);
		window.display();

	}

}

void game()
{
	if (state == 0)
	{
		titleScreen();
	}
	else
	{
		update();
		graphics();
	}
}

int main(int argc, char* argv[]) {

	while(gameRunning) {

		game();

	}
	
	window.cleanUp();
	SDL_Quit();
	
    return 0;
}