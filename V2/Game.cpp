#include "Game.h"

Game::Game() : window(nullptr), renderer(nullptr), duckTexture(nullptr), font(nullptr), projectiles(nullptr), numberOfDucks(1), bullets(3)
{

}

Game::~Game()
{
	SDL_DestroyTexture(duckTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	delete[] projectiles;
	SDL_Quit();
}

void Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cerr << "SDL initialization failed: " << SDL_GetError() << endl;
	}

	if (TTF_Init() == -1)
	{
		cerr << "SDL_ttf is not initialized properly: " << TTF_GetError() << endl;
	}

	window = SDL_CreateWindow("EGT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN);

	if (!window)
	{
		cerr << "Error when creating window: " << SDL_GetError() << endl;
		SDL_Quit();
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		cerr << "Cannot render window: " << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	duckSurface = IMG_Load("C:/Users/Michaela/Desktop/PNG/6.png");
	if (!duckSurface)
	{
		cerr << "There is no duck surface: " << SDL_GetError() << endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	duckTexture = SDL_CreateTextureFromSurface(renderer, duckSurface);
	SDL_FreeSurface(duckSurface);
	if (!duckTexture)
	{
		cerr << "There is no duck texture: " << SDL_GetError() << endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	projectiles = new Projectile[numberOfDucks];
	for (int i = 0; i < numberOfDucks; ++i) // speed
	{
		projectiles[i] = Projectile(duckTexture, rand() % WindowWidth, rand() % WindowHeight, 50, 50, 10, 10);
		/*projectiles[i].rect = { rand() % WindowWidth, rand() % WindowHeight, 50, 50 };
		projectiles[i].dX = 5;
		projectiles[i].dY = 5;
		projectiles[i].texture = duckTexture;*/
	}

	font = TTF_OpenFont("C:/Users/Michaela/Desktop/PNG/FFFTusj.ttf", 23);
	if (!font)
	{
		cerr << "Ne zarejda fonta" << TTF_GetError() << endl;
		SDL_DestroyTexture(duckTexture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();

		//return 1;
	}
}

void Game::Run()
{
	bool running = true;
	bool tryAgain = false;
	//projectiles = new Projectile[numberOfDucks];
	Projectile callMethod;

	while (running)
	{
		while (!tryAgain && bullets > 0)
		{
			//SDL_Event event;
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

					bool duckHit = false;

					for (int i = 0; i < numberOfDucks; i++)
					{
						Projectile& current = projectiles[i];
						if (current.IsClicked(mouseX, mouseY)) // ili callMethod
						{
							projectiles[i].dX = 0;
							projectiles[i].dY = 0;
							duckHit = true;
							bullets--;
						}
					}

					if (duckHit)
					{
						SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
						SDL_RenderClear(renderer);

						winTexture = nullptr;
						winSurface = IMG_Load("C:/Users/Michaela/Desktop/PNG/8.png");
						if (winSurface)
						{
							winTexture = SDL_CreateTextureFromSurface(renderer, winSurface);
							SDL_FreeSurface(winSurface);
							if (winTexture)
							{
								int WindowWidth, WindowHeight;
								SDL_GetWindowSize(window, &WindowWidth, &WindowHeight);
								winRect = { 0, 0, WindowWidth, WindowHeight };
								SDL_RenderCopy(renderer, winTexture, nullptr, &winRect);
								SDL_DestroyTexture(winTexture);
							}
							else
							{
								cerr << "ne moje da syzdade win texture v win " << SDL_GetError() << endl;
							}
						}
						else
						{
							cerr << "ne moje da zaredi kartinkata za win" << SDL_GetError() << endl;
						}
						SDL_RenderPresent(renderer);
						SDL_Delay(1000);
						SDL_Quit(); // End when we win
					}

					else
					{
						bullets--;
					}
				}

				if (bullets == 0)
				{
					break;
				}
			}

			// Clear the renderer
			SDL_SetRenderDrawColor(renderer, 50, 100, 255, 255);
			textColor = { 255, 255, 255 };//novo
			SDL_RenderClear(renderer);

			// Render the background texture
			backgroundTexture = nullptr;
			backgroundSurface = IMG_Load("C:/Users/Michaela/Desktop/PNG/4.png");
			if (backgroundSurface)
			{
				backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
				SDL_FreeSurface(backgroundSurface);
				if (backgroundTexture)
				{
					int WindowWidth, WindowHeight;
					SDL_GetWindowSize(window, &WindowWidth, &WindowHeight);
					backgroundRect = { 0, 0, WindowWidth, WindowHeight };
					SDL_RenderCopy(renderer, backgroundTexture, nullptr, &backgroundRect);
					SDL_DestroyTexture(backgroundTexture);
				}
				else
				{
					cerr << "ne moje da syzdade texture" << SDL_GetError() << endl;
				}
			}
			else
			{
				cerr << "ne moje da zaredi kartinkata" << SDL_GetError() << endl;
			}

			//render bullets
			textSurface = nullptr;
			bulletsLeft = "Patroni: " + to_string(bullets);
			textSurface = TTF_RenderText_Solid(font, bulletsLeft.c_str(), textColor);
			if (textSurface)
			{
				textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
				if (textSurface)
				{
					textRect = { 10, 550, textSurface->w, textSurface->h };
					SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
					SDL_DestroyTexture(textTexture);
				}
				SDL_FreeSurface(textSurface);
			}

			// Render the ducks
			for (int i = 0; i < numberOfDucks; i++) //razele pticata vurvi v ramkata
			{
				projectiles[i].rect->x += projectiles[i].dX;
				projectiles[i].rect->y += projectiles[i].dY;

				cout << "moving object: " << i << " position: (" << projectiles[i].rect->x << ", " << projectiles[i].rect->y << ")" << endl;

				if (projectiles[i].rect->x <= 0)
				{
					projectiles[i].rect->x = 0;
					projectiles[i].dX *= -1;
				}
				else if (projectiles[i].rect->x >= WindowWidth - projectiles[i].rect->w)
				{
					projectiles[i].rect->x = WindowWidth - projectiles[i].rect->w;
					projectiles[i].dX *= -1;
				}

				if (projectiles[i].rect->y <= 0)
				{
					projectiles[i].rect->y = 0;
					projectiles[i].dY *= -1;
				}
				else if (projectiles[i].rect->y >= WindowHeight - projectiles[i].rect->h)
				{
					projectiles[i].rect->y = WindowHeight - projectiles[i].rect->h;
					projectiles[i].dY *= -1;
				}

				SDL_RenderCopy(renderer, projectiles[i].texture, NULL, projectiles[i].rect);
			}

			// Present the renderer
			SDL_RenderPresent(renderer);
		}

		if (bullets == 0)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					running = false;
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					int mouseX = event.button.x;
					int mouseY = event.button.y;

					if (mouseX >= 300 && mouseX <= 500 && mouseY >= 200 && mouseY <= 250)
					{
						bullets = 3;
						tryAgain = false;
					}
				}
			}

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			backgroundTexture = nullptr;
			backgroundSurface = IMG_Load("C:/Users/Michaela/Desktop/PNG/7.png");
			if (backgroundSurface)
			{
				backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
				SDL_FreeSurface(backgroundSurface);
				if (backgroundTexture)
				{
					int WindowWidth, WindowHeight;
					SDL_GetWindowSize(window, &WindowWidth, &WindowHeight);
					backgroundRect = { 0, 0, WindowWidth, WindowHeight };
					SDL_RenderCopy(renderer, backgroundTexture, nullptr, &backgroundRect);
					SDL_DestroyTexture(backgroundTexture);
				}
				else
				{
					cerr << "ne moje da syzdade texture" << SDL_GetError() << endl;
				}
			}
			else
			{
				cerr << "ne moje da zaredi kartinkata" << SDL_GetError() << endl;
			}

			tryAgainButtonRect = { 300, 200, 200, 50 };
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &tryAgainButtonRect);

			SDL_RenderPresent(renderer);
		}
	}
}