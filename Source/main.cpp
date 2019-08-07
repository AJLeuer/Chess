#include <iostream>

#include "./Util/Config.h"
#include "./Util/Color.h"

#include "./Game/Game.h"


using namespace Chess;

int main (int argc, char ** argv)
{
	currentDirectory = argv[0];

	Game game;

	game.playDebugGame();

	return 0;
}
