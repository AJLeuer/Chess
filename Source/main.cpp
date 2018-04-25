//
//  main.cpp
//  Chess
//
//  Created by Adam James Leuer on 10/28/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include <iostream>

#include "./Util/Config.h"
#include "./Util/Color.h"

#include "./Game/Game.h"


using namespace Chess;

int main (int argc, char ** argv) {

	currentDirectory = argv[0];

	Game game;

	game.playDebugGame();

	return 0;
}
