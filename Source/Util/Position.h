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
#include <ostream>
#include <sstream>
#include <utility>

#include <SFML/System/Vector2.hpp>

using namespace std ;

constexpr unsigned lowerCaseA{97} ;

template<typename NumericType>
using vec2 = NumericType __attribute__((ext_vector_type(2))) ;

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
 * @note For conversion betweem SFML's vector type and native hardware (i.e. SSE, AltiVec, etc.) vector types (will probably work with other generic vector
 * data types as well)
 */
template<typename NumericType>
vec2<NumericType> convertToNativeVectorType(const sf::Vector2<NumericType> & sf_vec) {
	vec2<NumericType> vector ;
	vector[0] = sf_vec.x ;
	vector[1] = sf_vec.y ;
	return vector ;
}

/**
 * @note For conversion betweem SFML's vector type and native hardware (i.e. SSE, AltiVec, etc.) vector types (will probably work with other generic vector
 * data types as well)
 */
template<typename NumericType>
sf::Vector2<NumericType> convertToSFMLVectorType(const vec2<NumericType> & native_vec) {
	sf::Vector2<NumericType> vector ;
	vector.x = native_vec[0] ;
	vector.y = native_vec[1]  ;
	return vector ;
}

/**
 * @note For conversion betweem SFML's vector type and native hardware (i.e. SSE, AltiVec, etc.) vector types (will probably work with other generic vector
 * data types as well)
 */
template<typename NumericType0, typename NumericType1>
vec2<NumericType0> convertToNativeVectorType(const sf::Vector2<NumericType1> & sf_vec) {
	vec2<NumericType0> vector ;
	vector[0] = sf_vec.x ;
	vector[1] = sf_vec.y ;
	return vector ;
}

/**
 * @note For conversion betweem SFML's vector type and native hardware (i.e. SSE, AltiVec, etc.) vector types (will probably work with other generic vector
 * data types as well)
 */
template<typename NumericType0, typename NumericType1>
sf::Vector2<NumericType0> convertToSFMLVectorType(const vec2<NumericType1> & native_vec) {
	sf::Vector2<NumericType0> vector ;
	vector.x = native_vec[0] ;
	vector.y = native_vec[1]  ;
	return vector ;
}

template <typename Character, typename NumericType>
basic_ostream<Character> & operator << (basic_ostream<Character> & out, const vec2<NumericType> & vect) {
	out << "x = " << vect[0] << " y = " << vect[1] ;
	return out ;
}

/**
 * A vector type (2-vector) used to represent a position on the chess board purely numerically,
 * with (0, 0) equal to a1, etc. Can be explicitely converted to a RankAndFile object, 
 * and vice versa.
 */
typedef vec2<unsigned int> Position ;



/**
 * Used to represents a position on the chess board in algebraic notation, where the first square
 * is a1, etc. Can be explicitely and implicitely converted to a Position (where a1 would equal the 2-vector (0, 0)), and vice versa.
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
