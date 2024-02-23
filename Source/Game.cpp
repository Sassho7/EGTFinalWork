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
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderClear(renderer); //chisti ekrana

	SDL_Texture* backgroundTexture = nullptr;
	SDL_Surface* backgroundSurface = IMG_Load("C:/Users/Michaela/Desktop/4.png"); // zarejda kartinkata

	if (backgroundSurface)
	{
		backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
		SDL_FreeSurface(backgroundSurface);
		if (backgroundTexture)
		{
			int WindowWidth, WindowHeight;
			SDL_GetWindowSize(window, &WindowWidth, &WindowHeight); // vzima razmerite na prozoreca

			SDL_Rect backgroundRect = { 0, 0, WindowWidth, WindowHeight };
			SDL_RenderCopy(renderer, backgroundTexture, nullptr, &backgroundRect); //rendva da moje da pokrie celiq prozorec

			SDL_DestroyTexture(backgroundTexture);
		}
		else
		{
			cerr << "Ne moja da syzdade texture" << SDL_GetError() << endl;
		}
	}
	else
	{
		cerr << "Ne moja da zaredi kartinkata" << SDL_GetError() << endl;
	}

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