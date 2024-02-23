#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL.h>

#include "Duck.h"

using namespace std;

class Game
{
public:
	Game();
	~Game();
	void Play();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Duck* duck;
	const int NumberOfBirds;
	bool running;
	void Initialize();
	void HandleEvent();
	void Update();
	void Render();

	const int WindowWidth = 800;
	const int WindowHeight = 600;
};