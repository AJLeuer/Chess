//
//  Position.h
//  Chess
//
//  Created by Adam James Leuer on 11/3/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef Chess_Position_h
#define Chess_Position_h

#include <iostream>
#include <string>
#include <sstream>
#include <utility>

using namespace std ;

constexpr unsigned lowerCaseA{97} ;

template<typename N>
using vec2 = N __attribute__((ext_vector_type(2))) ;

/* //Apparently illegal. Boo
template<typename N>
bool operator==(vec2<N> lhs, vec2<N> rhs) {
	if (lhs[0] == rhs[0]) {
		if (lhs[1] == rhs[1]) {
			return true ;
		}
		return false ;
	}
	return false ;
} */

template<typename N>
bool equal(vec2<N> lhs, vec2<N> rhs) {
	if (lhs[0] == rhs[0]) {
		if (lhs[1] == rhs[1]) {
			return true ;
		}
		return false ;
	}
	return false ;
}

/**
 * A vector type (2-vector) used to represent a position on the chess board purely numerically,
 * with (0, 0) equal to a1, etc. Can be explicitely converted to a RankAndFile object, 
 * and vice versa.
 */
typedef vec2<unsigned> Position ;



/**
 * Used to represents a position on the chess board in algebraic notation, where the first square
 * is a1, etc. Can be explicitely converted to a Position (where a1 would equal the 2-vector (0, 0)), and vice versa.
 *
 * @see Wikipedia's article on <a href="http://en.wikipedia.org/wiki/Algebraic_notation_(chess)">Algebraic notation (chess)</a>
 */
struct RankAndFile {
	
protected:
	
	char file ;
	
	unsigned rank ;
	
	static char convertToFile(const unsigned arrIndex0) ;
	static unsigned convertToRank(const unsigned arrIndex1) ;
	
	friend void runChessGameTests() ;
	
public:
	
	RankAndFile(const char & file, const unsigned rank) : file(file), rank(rank) {}
	
	RankAndFile(const Position & pos) ;
	
	RankAndFile(const RankAndFile & other) : RankAndFile(other.file, other.rank) {}
	
	~RankAndFile() {}
	
	RankAndFile & operator=(const RankAndFile & rhs) ;
	
	operator Position() const ;
	
	string toString() const ;
	
	Position convertToArrayIndex() const ;

	const char getFile() const { return file ; }
	const unsigned & getRank() const { return rank ; }
	
	friend std::ostream & operator<< (ostream & , const RankAndFile &) ;
	
} ;

#endif
