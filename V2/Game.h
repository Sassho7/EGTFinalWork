#pragma once
#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Projectile.h"

using namespace std;

class Game
{
public:
	Game();
	~Game();
	void Initialize();
	void Run();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;

	SDL_Texture* duckTexture;
	SDL_Texture* backgroundTexture;
	SDL_Texture* textTexture;
	SDL_Texture* winTexture;

	SDL_Surface* backgroundSurface;
	SDL_Surface* textSurface;
	SDL_Surface* winSurface;
	SDL_Surface* duckSurface;

	SDL_Rect backgroundRect;
	SDL_Rect tryAgainButtonRect;
	SDL_Rect textRect;
	SDL_Rect winRect;

	SDL_Color textColor;
	SDL_Event event;

	Projectile* projectiles;
	int numberOfDucks;
	int bullets;
	string bulletsLeft;

	const int WindowWidth = 800;
	const int WindowHeight = 600;

};