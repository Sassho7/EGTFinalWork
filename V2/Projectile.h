#pragma once
#include <SDL.h>

class Projectile
{
public:
	Projectile();
	Projectile(SDL_Texture* texture, int x, int y, int w, int h, int dx, int dy);
	~Projectile();
	void SetRect(int x, int y, int w, int h);
	bool IsClicked(int mouseX, int mouseY);
	SDL_Texture* texture;
	SDL_Rect* rect;
	int dX, dY;
};