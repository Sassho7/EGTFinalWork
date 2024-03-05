#include "Projectile.h"

Projectile::Projectile()
{

}

Projectile::Projectile(SDL_Texture* texture, int x, int y, int w, int h, int dx, int dy) : texture(texture), dX(dx), dY(dy)
{
	rect = new SDL_Rect;
	SetRect(x, y, w, h);
}

Projectile::~Projectile()
{
	//delete rect; blagodarenie na nego
}

void Projectile::SetRect(int x, int y, int w, int h)
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}

bool Projectile::IsClicked(int mouseX, int mouseY)
{
	return (mouseX >= rect->x && mouseX <= (rect->x + rect->w) && mouseY >= rect->y && mouseY <= (rect->y + rect->h));
}
