//
//  Position.cpp
//  Chess
//
//  Created by Adam James Leuer on 11/3/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "Position.h"

using namespace std ;

const Direction Direction::up  		 { vec2<int>{ 0, -1} } ;
const Direction Direction::down 	 { vec2<int>{ 0,  1} } ;
const Direction Direction::left 	 { vec2<int>{-1,  0} } ;
const Direction Direction::right 	 { vec2<int>{ 1,  0} } ;

const Direction Direction::upLeft    { vec2<int>{-1, -1} } ;
const Direction Direction::upRight   { vec2<int>{ 1, -1} } ;
const Direction Direction::downLeft  { vec2<int>{-1,  1} } ;
const Direction Direction::downRight { vec2<int>{ 1,  1} } ; 

RankAndFile::RankAndFile(const Position & pos) :
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

RankAndFile & RankAndFile::operator = (const Position & pos) {
	RankAndFile other(pos) ;
	*this = other ;
	return *this ;
}

RankAndFile::operator Position() const {
	return convertToPosition() ;
}

string RankAndFile::toString() const {
	stringstream ss ;
	ss << *this ;
	return ss.str() ;
}

Position RankAndFile::convertToPosition() const {
	int ind0 = this->getRank() ;
	ind0-- ;
	int ind1 = static_cast<int>(getFile() - lowerCaseA) ;
	return Position{ind0, ind1} ;
}

char RankAndFile::convertToFile(const unsigned arrIndex0) {
	char c = static_cast<char>(arrIndex0 + lowerCaseA) ;
	return c ;
}

unsigned RankAndFile::convertToRank(const unsigned arrIndex1) {
	auto ret = arrIndex1 + 1 ;
	return ret ;
}

ostream & operator<< (ostream & out , const RankAndFile & rf) {
	out << rf.file << rf.rank ;
	return out ;
}