#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

const int WindowWidth = 800;
const int WindowHeight = 600;
const int NumberOfDucks = 1;
const int FPS = 50;

struct Projectiles
{
	SDL_Texture* texture;
	SDL_Rect rect;
	int dX, dY;
};

bool IsClicked(const SDL_Rect& rect, int mouseX, int mouseY)
{
	return (mouseX >= rect.x && mouseX <= (rect.x + rect.w) && mouseY >= rect.y && mouseY <= (rect.y + rect.h));
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	int bullets = 3;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cerr << "SDL initialization failed: " << SDL_GetError() << endl;
		return 1;
	}
	if (TTF_Init() == -1)
	{
		cerr << "SDL_ttf ne se e inicializiral pravilno" << TTF_GetError() << endl;
		return 1;
	}
	SDL_Window* window = SDL_CreateWindow("EGT igra", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN);
	if (!window)
	{
		cerr << "Nqma prozorec" << SDL_GetError() << endl;
		SDL_Quit();
		return 1;
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		cerr << "ne moje da sysdade" << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	SDL_Surface* duckSurface = IMG_Load("C:/Users/Michaela/Desktop/PNG/6.png");
	if (!duckSurface)
	{
		cerr << "nqma patica surface" << SDL_GetError() << endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	SDL_Texture* duckTexture = SDL_CreateTextureFromSurface(renderer, duckSurface);
	SDL_FreeSurface(duckSurface);
	if (!duckTexture)
	{
		cerr << "nqma patica texture" << SDL_GetError() << endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	Projectiles projectile[NumberOfDucks];
	for (int i = 0; i < NumberOfDucks; ++i)
	{
		projectile[i].rect = { rand() % (WindowWidth - 150), rand() % (WindowHeight - 150), 40, 40 };
		projectile[i].dX = 5; //rand() % 5 + 1
		projectile[i].dY = 5; //rand() % 5 + 1
		projectile[i].texture = duckTexture;
	}
	TTF_Font* font = TTF_OpenFont("C:/Users/Michaela/Desktop/PNG/FFFTusj.ttf", 23);
	if (!font)
	{
		cerr << "Ne zarejda fonta" << TTF_GetError() << endl;
		SDL_DestroyTexture(duckTexture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}
	bool running = true;
	bool tryAgain = false;
	while (running)
	{
		Uint32 startTime = SDL_GetTicks();
		while (!tryAgain && bullets > 0)
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
					//bullets--;
					int mouseX = event.button.x;
					int mouseY = event.button.y;
					bool duckHit = false;
					for (int i = 0; i < NumberOfDucks; i++)
					{
						if (IsClicked(projectile[i].rect, mouseX, mouseY))
						{
							projectile[i].dX = 0;
							projectile[i].dY = 0;
							duckHit = true;
							bullets--;
						}
					}
					if (duckHit)
					{
						SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
						SDL_RenderClear(renderer);
						SDL_Texture* winTexture = nullptr;
						SDL_Surface* winSurface = IMG_Load("C:/Users/Michaela/Desktop/PNG/8.png");
						if (winSurface)
						{
							winTexture = SDL_CreateTextureFromSurface(renderer, winSurface);
							SDL_FreeSurface(winSurface);
							if (winTexture)
							{
								int WindowWidth, WindowHeight;
								SDL_GetWindowSize(window, &WindowWidth, &WindowHeight);
								SDL_Rect winRect = { 0, 0, WindowWidth, WindowHeight };
								SDL_RenderCopy(renderer, winTexture, nullptr, &winRect);
								SDL_DestroyTexture(winTexture);
							}
							else
							{
								cerr << "ne moje da syzdade win texture" << SDL_GetError() << endl;
							}
						}
						else
						{
							cerr << "ne moje da zaredi kartinkata za win" << SDL_GetError() << endl;
						}
						SDL_RenderPresent(renderer);
						SDL_Delay(1000);
						SDL_Quit();
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
			Uint32 currentTime = SDL_GetTicks();
			float deltaTime = (currentTime - startTime) / 1000.0f;
			// Clear the renderer
			SDL_SetRenderDrawColor(renderer, 50, 100, 255, 255);
			SDL_Color textColor = { 255, 255, 255 };//novo
			SDL_RenderClear(renderer);
			// Render the background texture
			SDL_Texture* backgroundTexture = nullptr;
			SDL_Surface* backgroundSurface = IMG_Load("C:/Users/Michaela/Desktop/PNG/4.png");
			if (backgroundSurface)
			{
				backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
				SDL_FreeSurface(backgroundSurface);
				if (backgroundTexture)
				{
					int WindowWidth, WindowHeight;
					SDL_GetWindowSize(window, &WindowWidth, &WindowHeight);
					SDL_Rect backgroundRect = { 0, 0, WindowWidth, WindowHeight };
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
			SDL_Surface* textSurface = nullptr;
			string bulletsLeft = "Patroni: " + to_string(bullets);
			textSurface = TTF_RenderText_Solid(font, bulletsLeft.c_str(), textColor);
			if (textSurface)
			{
				SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
				if (textSurface)
				{
					SDL_Rect textRect = { 10, 550, textSurface->w, textSurface->h };
					SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
					SDL_DestroyTexture(textTexture);
				}
				SDL_FreeSurface(textSurface);
			}
			// Render the ducks
			for (int i = 0; i < NumberOfDucks; i++) //razele pticata vurvi v ramkata
			{
				/*projectile[i].rect.x += static_cast<int>(projectile[i].dX * deltaTime);
				projectile[i].rect.y += static_cast<int>(projectile[i].dY * deltaTime);

				if (projectile[i].rect.x <= 0 || projectile[i].rect.x >= WindowWidth - projectile[i].rect.w)
				{
					projectile[i].dX *= -1;
				}

				if (projectile[i].rect.y <= 0 || projectile[i].rect.y >= WindowHeight - projectile[i].rect.h)
				{
					projectile[i].dY *= -1;
				}*/
				projectile[i].rect.x += projectile[i].dX;
				projectile[i].rect.y += projectile[i].dY;
				if (projectile[i].rect.x <= 0)
				{
					projectile[i].rect.x = 0;
					projectile[i].dX *= -1;
				}
				else if (projectile[i].rect.x >= WindowWidth - projectile[i].rect.w)
				{
					projectile[i].rect.x = WindowWidth - projectile[i].rect.w;
					projectile[i].dX *= -1;
				}
				if (projectile[i].rect.y <= 0)
				{
					projectile[i].rect.y = 0;
					projectile[i].dY *= -1;
				}
				else if (projectile[i].rect.y >= WindowHeight - projectile[i].rect.h)
				{
					projectile[i].rect.y = WindowHeight - projectile[i].rect.h;
					projectile[i].dY *= -1;
				}
				SDL_RenderCopy(renderer, projectile[i].texture, NULL, &projectile[i].rect);
			}
			// Present the renderer
			SDL_RenderPresent(renderer);
			Uint32 endTime = SDL_GetTicks();
			Uint32 frameTime = endTime - startTime;
			if (frameTime < 1000 / 50)
			{
				SDL_Delay((1000 / 50) - frameTime);
			}
			SDL_Delay(10);
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
			SDL_Texture* backgroundTexture = nullptr;
			SDL_Surface* backgroundSurface = IMG_Load("C:/Users/Michaela/Desktop/PNG/7.png");
			if (backgroundSurface)
			{
				backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
				SDL_FreeSurface(backgroundSurface);
				if (backgroundTexture)
				{
					int WindowWidth, WindowHeight;
					SDL_GetWindowSize(window, &WindowWidth, &WindowHeight);
					SDL_Rect backgroundRect = { 0, 0, WindowWidth, WindowHeight };
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
			SDL_Rect tryAgainButtonRect = { 300, 200, 200, 50 };
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &tryAgainButtonRect);
			SDL_RenderPresent(renderer);
		}
	}
	SDL_DestroyTexture(duckTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
};
