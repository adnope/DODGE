#include "RenderWindow.h"
#include "Player.h"
#include "Projectiles.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <vector>
#include <iostream>
#include <string>
#include <fstream>

bool init()
{

	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has failed. Errpr: " << SDL_GetError() << std::endl;
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << IMG_GetError() << std::endl;
	if ( (TTF_Init()) == -1)
		std::cout << "TTF_init has failed. Error: " << TTF_GetError() << std::endl;

	return true;
}

bool SDLinit = init();


RenderWindow window("DODGE!", 1280, 720);
SDL_Texture* playerTex = window.loadTexture("res/textures/rocket.png");
SDL_Texture* ezrealSprite = window.loadTexture("res/textures/ezreal.png");
SDL_Texture* background = window.loadTexture("res/textures/ingame_bg.png");
SDL_Texture* endScreenBg = window.loadTexture("res/textures/endscreen_bg.png");

SDL_Color blue = {29, 100, 186};
SDL_Color green = {46, 125, 50};
SDL_Color white = {255, 255, 255};
TTF_Font* endScreen90 = TTF_OpenFont("res/fonts/endscreen.ttf", 90);
TTF_Font* endScreen18 = TTF_OpenFont("res/fonts/endscreen.ttf", 18);
TTF_Font* endScreen22 = TTF_OpenFont("res/fonts/endscreen.ttf", 22);
TTF_Font* endScreen44 = TTF_OpenFont("res/fonts/endscreen.ttf", 44);

int state = 1; //0 = title screen, 1 = game, 2 = end screen
bool gameRunning = true;
Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0; 


float spawnRate = 3;
float timeSinceLastSpawn = 0;
uint64_t score = 0;
uint64_t highscore;


SDL_Event event;
bool isHovered = false;

Player player(640, 360, playerTex);
Ezreal e(ezrealSprite, player);
std::vector<Ezreal> ezreals = {};
const char* killer;


void spawn(int index) {

	if(index == 0) {

		Ezreal e(ezrealSprite, player);
		ezreals.push_back(e);

	}

}

bool checkCollisions(Player player, Ezreal e) {

	const SDL_Rect rectA = player.getCollisionBox();
	const SDL_Rect rectB = e.getCollisionBox();

	if(SDL_HasIntersection(&rectA, &rectB) == SDL_TRUE) {
		player.setDeath(true);
		return true;
	}

	return false;

}

void titleScreen() {

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			gameRunning = false;
	}




}

void endScreen() {

	

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

		if(state == 2) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if( x >= 567 && x <= 716 && y >= 620 && y <= 667 ) {
				isHovered = true;

				if(event.type == SDL_MOUSEBUTTONDOWN) {
					if(event.button.button == SDL_BUTTON_LEFT) {
						score = 0;
						state = 1;
						window.clear();
					}
				}
			}
			else isHovered = false;
		}

	}

	if(state == 1) {

		score += deltaTime * 200;
		if(score > highscore) {
			highscore = score;
			std::ofstream f("save/highscore.txt");
			f << highscore << std::endl;
			f.close();
		}

		timeSinceLastSpawn += deltaTime;

		if(timeSinceLastSpawn >= spawnRate) {

			spawn(0); //0 = Ezreal, 1 = Brand

			timeSinceLastSpawn = 0.0f;

            spawnRate -= 15 * deltaTime;
            if (spawnRate < 1.0f) {
                spawnRate = 1.0f;
            }

		}

		for (size_t i = 0; i < ezreals.size(); ) {

			ezreals[i].move(player, deltaTime);
			if( checkCollisions(player, ezreals[i]) ) {
				killer = "Ezreal's ult";
				spawnRate = 3;
				ezreals.clear();
				state = 2;
				window.clear();
				break;
			}

			if(ezreals[i].isDead) {
				ezreals.erase(ezreals.begin()+i);
			}
			else i++;

        }

		player.move(deltaTime);

	}

	if(state == 2) {

		endScreen();

	}

}

void graphics() {

	if(state == 1) {

		window.render(background);
		window.render(player);
		for(Ezreal e : ezreals) window.render(e, deltaTime);
		
		std::string numberString = std::to_string(score);
		char charArray[20];
		strcpy(charArray, "Score: ");
		strcat(charArray, numberString.c_str());
		window.render(10, 10, charArray, endScreen18, white, false);

		window.display();

	}

	if(state == 2) {

		window.render(endScreenBg);

		window.renderCenterX(400, 150, "Game Over", endScreen90, blue, false);

		char joke[100];
		strcpy(joke, "Bro tried to checkvar with ");
		strcat(joke, killer);
		window.renderCenterX(470, 240, joke, endScreen18, blue, false);

		char score_text[100];
		std::string score_str = std::to_string(score);
		strcpy(score_text, "Your score: ");
		strcat(score_text, score_str.c_str());
		window.renderCenterX(570, 440, score_text, endScreen22, blue, false);

		char highscore_text[100];
		std::string highscore_str = std::to_string(highscore);
		strcpy(highscore_text, "High score: ");
		strcat(highscore_text, highscore_str.c_str());
		window.renderCenterX(570, 510, highscore_text, endScreen22, blue, false);

		window.renderCenterX(570, 640, "RePlay", endScreen44, green, isHovered);
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

	std::ifstream highscore_file("save/highscore.txt");
	highscore_file >> highscore;
	highscore_file.close();

	const double DELAY_TIME = 1000 / 240;
	Uint32 frameStart;
    int frameTime;

	while(gameRunning) {

		frameStart = SDL_GetTicks();

		game();

		frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < DELAY_TIME) {
            SDL_Delay(DELAY_TIME - frameTime);
        }

	}
	
	window.cleanUp();
	SDL_Quit();
	
    return 0;
}