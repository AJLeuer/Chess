//
//  Vect.cpp
//  Chess
//
//  Created by Adam James Leuer on 11/3/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "Vect.h"

using namespace std ;


RankAndFile::RankAndFile(const vec2<int> & pos) :
	RankAndFile(convertToFile(pos[0]), convertToRank(pos[1]))
{
	
}

RankAndFile & RankAndFile::operator = (const RankAndFile & rhs) {
	if (this != &rhs) {
		this->file = rhs.file ;
		this->rank = rhs.rank ;
	}
	return *this ;
}

RankAndFile & RankAndFile::operator = (const vec2<int> & pos) {
	RankAndFile other(pos) ;
	*this = other ;
	return *this ;
}

RankAndFile::operator vec2<int>() const {
	return convertToPosition() ;
}

string RankAndFile::toString() const {
	stringstream ss ;
	ss << *this ;
	return ss.str() ;
}

vec2<int> RankAndFile::convertToPosition() const {
	
	/* Chess ranks start with 1 at the bottom and increase as we move up the board,
	 but window coordinates start with y = 0 at the top, and y increases with descent.
	 So to convert our rank to a y-coordinate, we'll need to essentially swap each rank
	 value across the horizontal axis, and subtract 1 from it (rank values start at 1, but
	 vec2<int> values start at 0)
	 
	 Chess files can be converted from x-coordinates by subtracting the Unicode decimal value for 'a' -
	 97 - from the decimal value of the char representing the rank. Applied to 'a', this gives an x-coord
	 of 0, 'b' outputs as 1, 'c' is 2, etc.
	 */
	
	//convert rank to y:
	int y = this->getRank() ;
	y = (RANK_LAST - y) % RANK_LAST ;
	
	//convert file to x:
	int x = static_cast<int>(getFile() - lowerCaseA) ;
	
	return vec2<int>{x, y} ;
}

char RankAndFile::convertToFile(const unsigned x) {
	char c = static_cast<char>(x + lowerCaseA) ;
	return c ;
}

unsigned RankAndFile::convertToRank(const unsigned y) {
	auto ret = y + 1 ;
	return ret ;
}

ostream & operator<< (ostream & out , const RankAndFile & rf) {
	out << rf.file << rf.rank ;
	return out ;
}