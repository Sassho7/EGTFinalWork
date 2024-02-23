#pragma once
#include <SDL.h>

class Duck
{
public:
	Duck();
	Duck(int x, int y, int width, int height, int dX, int dY);
	~Duck();
	void Update();
	void Render(SDL_Renderer* renderer);
	bool IsClicked(int mouseX, int mouseY) const;
	SDL_Rect GetRect() const;

private:
	SDL_Rect rect;
	int dX;
	int dY;
};