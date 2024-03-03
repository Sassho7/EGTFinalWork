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
	SDL_Texture* duckTexture;
	TTF_Font* font;

	Projectile* projectiles;
	int numberOfDucks;
	int bullets;

	const int WindowWidth = 800;
	const int WindowHeight = 600;

};