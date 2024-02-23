#include "Duck.h"

Duck::Duck() : rect({ 0, 0, 0, 0 }), dX(0), dY(0) //trqbvashe da dobavq
{

}

Duck::Duck(int x, int y, int width, int height, int dX, int dY) : rect({ x, y, width, height }), dX(dX), dY(dY)
{

}

Duck::~Duck()
{

}

SDL_Rect Duck::GetRect() const
{
	return rect;
}

void Duck::Update()
{
	rect.x += dX;
	rect.y += dY;
}

void Duck::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 123, 123, 123, 123);
	SDL_RenderFillRect(renderer, &rect);// &rect/&projectile[i].rect
}

bool Duck::IsClicked(int mouseX, int mouseY) const
{
	return (mouseX >= rect.x && mouseX <= (rect.x + rect.w) && mouseY >= rect.y && mouseY <= (rect.y + rect.h));
}