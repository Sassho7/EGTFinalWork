#include <iostream>
#include <string>

#include "Projectile.h"
#include "Game.h"

using namespace std;

int main(int argc, char* argv[])
{
	Game game;
	game.Initialize();
	game.Run();
	return 0;
}