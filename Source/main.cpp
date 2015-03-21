//
//  main.cpp
//  Chess
//
//  Created by Adam James Leuer on 10/28/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include <iostream>
#include <chrono>

#include "Config.h"
#include "./Util/Position.h"
#include "./Game/Game.h"

using namespace std ;


int main(int argc, const char * argv[]) {
	currentDirectory = *argv ;


	Game game ;
	game.runTests() ;
	
    return 0 ;
}
