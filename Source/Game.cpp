#include "Game.h"

Game::Game() : window(nullptr), renderer(nullptr), duck(nullptr), NumberOfBirds(1), running(true)
{

}

Game::~Game()
{

}


void Game::Initialize()
{
	srand(time(NULL));
	if (SDL_Init(SDL_INIT_VIDEO < 0))
	{
		cerr << "SDL initialization failed" << SDL_GetError() << endl;
		return;
	}
	window = SDL_CreateWindow("Egt igra", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN); //SDL_CreateShapedWindow po greshka
	if (!window)
	{
		cerr << "nqma prozorec" << SDL_GetError() << endl;
		SDL_Quit();
		return;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // trqbwa da izmislq kak da se zadawa skorosta ruchno
	if (!renderer)
	{
		cerr << "nqma rendwane" << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return;
	}

	duck = new Duck[NumberOfBirds];
	for (int i = 0; i < NumberOfBirds; i++)
	{
		duck[i] = Duck(rand() % (WindowWidth - 20), rand() & (WindowHeight - 20), 20, 20, rand() % 5 + 1, rand() % 5 + 1);
	}
}

void Game::HandleEvent()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			running = false;
		}

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			int mouseX = event.button.x;
			int mouseY = event.button.y;

			for (int i = 0; i < NumberOfBirds; i++)
			{
				if (duck[i].IsClicked(mouseX, mouseY))
				{
					duck[i] = Duck(0, 0, 0, 0, 0, 0);
				}
			}
		}
	}
}

void Game::Update()
{
	for (int i = 0; i < NumberOfBirds; i++)
	{
		duck[i].Update();

		if (duck[i].GetRect().x <= 0 || duck[i].GetRect().x >= WindowWidth - duck[i].GetRect().w)
		{
			duck[i] = Duck(rand() % (WindowWidth - 20), rand() & (WindowHeight - 20), 20, 20, rand() % 3 + 1, (rand() % 2 == 0) ? -1 : 1);
		}

		if (duck[i].GetRect().y <= 0 || duck[i].GetRect().y >= WindowHeight - duck[i].GetRect().h)
		{
			duck[i] = Duck(rand() % (WindowWidth - 20), rand() & (WindowHeight - 20), 20, 20, (rand() % 2 == 0) ? -1 : 1, rand() % 5 + 1);
		}
	}
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //e tuka trqbwa da vkaram fona
	SDL_RenderClear(renderer);

	for (int i = 0; i < NumberOfBirds; i++)
	{
		duck[i].Render(renderer);
	}
	SDL_RenderPresent(renderer);
}
void Game::Play()
{
	Initialize();

	while (running)
	{
		HandleEvent();
		Update();
		Render();
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}