#include "RenderWindow.h"
#include "Entity.h"
#include "Player.h"
#include "Math.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
		std::cout << "SDL initialization failed! SDL Error: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

    RenderWindow window("DODGE!", 1280, 720);

	SDL_Texture* background = window.loadTexture("res/space_background.png");

	SDL_Texture* playerTex = window.loadTexture("res/rocket.png");
	Player player(640, 360, playerTex);
	
	int frameStart;
	int frameTicks;
	const int TICKS_PER_FRAME = 1000 / 60;

	//--------Main Loop--------
	bool gameRunning = true;
	SDL_Event event;

	while (gameRunning)
	{

		frameStart = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
				
			if (event.type == SDL_MOUSEBUTTONDOWN) {

				if (event.button.button == SDL_BUTTON_RIGHT) {
					player.takeMouseInput();
				}
				
			}
		}

		window.clear();
		window.render(background);
		
		player.move();
		window.render(player);
		std::cout << player.getAngle() << std::endl;
		
		window.display();

		frameTicks = SDL_GetTicks() - frameStart;
		if(frameTicks < TICKS_PER_FRAME) {
			SDL_Delay(TICKS_PER_FRAME - frameTicks);
		}
	}
	//------Exit Main Loop------
	
	window.cleanUp();
	SDL_Quit();

    return 0;
}