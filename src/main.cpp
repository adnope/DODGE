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
SDL_Texture* endScreenBg = window.loadTexture("res/textures/endscreen2.png");
SDL_Texture* titleScreenBg = window.loadTexture("res/textures/title_screen_bg.png");
SDL_Texture* playButton = window.loadTexture("res/textures/Play_Button_Default.png");
SDL_Texture* playButtonHovered = window.loadTexture("res/textures/Play_Button_Hover.png");
SDL_Texture* DODGE_TEXT = window.loadTexture("res/textures/DODGE.png");
SDL_Texture* replayButton = window.loadTexture("res/textures/Pause_Replay_Default.png");
SDL_Texture* replayButtonHovered = window.loadTexture("res/textures/Pause_Replay_Hover.png");
SDL_Texture* homeButton = window.loadTexture("res/textures/Pause_Home_Default.png");
SDL_Texture* homeButtonHovered = window.loadTexture("res/textures/Pause_Home_Hover.png");
SDL_Texture* pause_playButton = window.loadTexture("res/textures/Pause_Play_Default.png");
SDL_Texture* pause_playButtonHovered = window.loadTexture("res/textures/Pause_Play_Hover.png");


SDL_Color blue = {29, 100, 186};
SDL_Color green = {46, 125, 50};
SDL_Color white = {255, 255, 255};
TTF_Font* endScreen90 = TTF_OpenFont("res/fonts/endscreen.ttf", 90);
TTF_Font* endScreen18 = TTF_OpenFont("res/fonts/endscreen.ttf", 18);
TTF_Font* endScreen22 = TTF_OpenFont("res/fonts/endscreen.ttf", 22);
TTF_Font* endScreen44 = TTF_OpenFont("res/fonts/endscreen.ttf", 44);
TTF_Font* bernhard20 = TTF_OpenFont("res/fonts/bernhard.ttf", 20);
TTF_Font* bernhard30 = TTF_OpenFont("res/fonts/bernhard.ttf", 30);

int state = 0; //0 = title screen, 1 = game, 2 = end screen
bool gameRunning = true;
Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0; 


float spawnRate = 2;
float timeSinceLastSpawn = 0;
uint64_t score = 0;
uint64_t highscore;


SDL_Event event;
bool isHovered = false;
bool isHovered2 = false;

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
		return true;
	}

	return false;

}

void titleScreen() {

	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency() );

	while (SDL_PollEvent(&event))
	{

		if (event.type == SDL_QUIT)
			gameRunning = false;

		int x, y;
		SDL_GetMouseState(&x, &y);
		if( x >= 479 && x <= 1280 - 479 && y >= 319 && y <= 720 - 237 ) {
			isHovered = true;

			if(event.type == SDL_MOUSEBUTTONDOWN) {
				if(event.button.button == SDL_BUTTON_LEFT) {
					state = 1;
					window.clear();
				}
			}
		}
		else isHovered = false;

	}


	window.render(titleScreenBg);
	window.renderCenterX(150, DODGE_TEXT, NULL,  false);
	window.renderCenterX(320, playButton, playButtonHovered, isHovered);

	char highscore_text[100];
	std::string highscore_str = std::to_string(highscore);
	strcpy(highscore_text, "High Score: ");
	strcat(highscore_text, highscore_str.c_str());
	window.renderCenterX(550, highscore_text, endScreen44, white, false);

	window.display();

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

			if( x >= 490 && x <= 578 && y >= 360 && y <= 448 ) {
				isHovered = true;

				if(event.type == SDL_MOUSEBUTTONDOWN) {
					if(event.button.button == SDL_BUTTON_LEFT) {
						score = 0;
						player.setPos(640, 360);
						state = 1;
						window.clear();
					}
				}
			}
			else isHovered = false;

			if( x >= 705 && x <= 793 && y >= 360 && y <= 448 ) {
				isHovered2 = true;

				if(event.type == SDL_MOUSEBUTTONDOWN) {
					if(event.button.button == SDL_BUTTON_LEFT) {
						score = 0;
						player.setPos(640, 360);
						state = 0;
						window.clear();
					}
				}
			}
			else isHovered2 = false;

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
            if (spawnRate < 0.5f) {
                spawnRate = 0.5f;
            }

		}

		for (size_t i = 0; i < ezreals.size(); ) {

			ezreals[i].move(player, deltaTime);
			if( checkCollisions(player, ezreals[i]) ) {
				killer = "Ezreal's ult";
				spawnRate = 2;
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

		char joke[100];
		strcpy(joke, "Bro tried to checkvar with ");
		strcat(joke, killer);
		window.renderCenterX(180, joke, bernhard20, white, false);

		char score_text[100];
		std::string score_str = std::to_string(score);
		strcpy(score_text, "Your Score: ");
		strcat(score_text, score_str.c_str());
		window.renderCenterX(270, score_text, bernhard30, white, false);

		char highscore_text[100];
		std::string highscore_str = std::to_string(highscore);
		strcpy(highscore_text, "High Score: ");
		strcat(highscore_text, highscore_str.c_str());
		window.renderCenterX(540, highscore_text, bernhard30, white, false);

		window.render(490, 360, replayButton, replayButtonHovered, isHovered);
		window.render(705, 360, homeButton, homeButtonHovered, isHovered2);

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