//
//  main.cpp
//  Chess
//
//  Created by Adam James Leuer on 10/28/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include <iostream>

#include "Board.h"

int main(int argc, const char * argv[]) {
	// insert code here...
	
	Piece * p = new Rook("♕") ;
	auto str = p->getSymbol() ;
	
	Board b ;

	std::cout << str << endl ;
	
    return 0;
}
