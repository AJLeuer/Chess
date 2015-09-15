//
//  main.cpp
//  Chess
//
//  Created by Adam James Leuer on 10/28/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include <iostream>
#include <chrono>
#include <functional>
#include <vector>
#include <list>
#include <typeinfo>

#include "./Util/Config.h"
#include "./Util/Vect.h"
#include "./Util/Color.h"

#include "./Game/Game.h"

using namespace std ;
using namespace Chess ;


int main(int argc, char ** argv) {
	
	currentDirectory = argv[0] ;
	//cout << "The directory is: " << currentDirectory << endl ;

	Game game ;

    	game.playDebugGame() ;

	return 0 ;
}
