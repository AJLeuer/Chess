//
//  main.cpp
//  Chess
//
//  Created by Adam James Leuer on 10/28/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include <iostream>

#include "NotificationSystem.h"
#include "Board.h"

#include "time.h"



void runChessGameTests() {
	
	Board b ;
	
	cout << b << endl ;
	
	auto sq = b.boardRepresentation.at(1).at(2) ;
	
	Piece * pwn = sq.piece ;
	
	pwn->move({1, 3}) ;
	
	cout << b << endl ;
	
	int a = 1 ;
}


int main(int argc, const char * argv[]) {

	runChessGameTests() ;

    return 0;
}
