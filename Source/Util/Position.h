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
#include <stdexcept>

#include <SFML/System/Vector2.hpp>

using namespace std ;

constexpr unsigned lowerCaseA {97} ;

template <typename NumericType>
using vec2 = NumericType __attribute__((ext_vector_type(2))) ;

/**
 * Code partial credit StackOverflow:
 * @link http://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector
 */
template <typename VectorType>
inline size_t hashVector(const VectorType & vect, size_t vectorSize) {
	size_t seed = 0;

	for (auto i = 0 ; i < vectorSize ; i++) {
		seed ^= vect[i] + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	
	return seed;
}

template <typename VectorType>
inline size_t hashTwoVector(const VectorType twoVect) {
	auto hash = hashVector(twoVect, 2) ;
	return hash ;
}
	

/**
 * @note A good example of a C++ literal type
 */
struct Direction {
	
protected:
	
	const vec2<int> value ;
	
public:

	constexpr Direction(const vec2<int> val) : value(val) {}
	
	constexpr Direction(const int h, const int v) : value(vec2<int> {h, v}) {}

	constexpr operator vec2<int>() const { return this->value ; }

	template <typename NumericType>
	friend vec2<NumericType> operator * (const Direction &, const NumericType) ;
	
	template <typename NumericType>
	friend vec2<NumericType> operator + (const Direction &, const vec2<NumericType>) ;

} ;

namespace Directions {
	
	static constexpr Direction up  		 { vec2<int>{ 0, -1} } ;
	static constexpr Direction down 	 { vec2<int>{ 0,  1} } ;
	static constexpr Direction left 	 { vec2<int>{-1,  0} } ;
	static constexpr Direction right 	 { vec2<int>{ 1,  0} } ;
	
	static constexpr Direction upLeft    { vec2<int>{-1, -1} } ;
	static constexpr Direction upRight   { vec2<int>{ 1, -1} } ;
	static constexpr Direction downLeft  { vec2<int>{-1,  1} } ;
	static constexpr Direction downRight { vec2<int>{ 1,  1} } ;
	
}


template <typename NumericType>
vec2<NumericType> operator * (const Direction & direction, const NumericType n) {
	
	vec2<NumericType> ret ;
	
	ret.x = direction.value.x * n ;
	ret.y = direction.value.y * n ;
	
	return ret ;
}

template <typename NumericType>
vec2<NumericType> operator + (const Direction & direction, const vec2<NumericType> vec) {
	
	vec2<NumericType> ret ;
	
	ret.x = direction.value.x + vec.x ;
	ret.y = direction.value.y + vec.y ;
	
	return ret ;
}

/*
template <typename N>
bool equal(vec2<N> lhs, vec2<N> rhs) {
	if (lhs[0] == rhs[0]) {
		if (lhs[1] == rhs[1]) {
			return true ;
		}
		return false ;
	}
	return false ;
} */

/**
 * @note For conversion betweem SFML's vector type and native hardware (i.e. SSE, AltiVec, etc.) vector types (will probably work with other generic vector
 * data types as well)
 */
template <typename NumericType>
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
template <typename NumericType>
sf::Vector2<NumericType> convertToSFMLVectorType(const vec2<NumericType> & native_vec) {
	sf::Vector2<NumericType> vector ;
	vector.x = native_vec[0] ;
	vector.y = native_vec[1]  ;
	return vector ;
}

/**
 * @note For conversion betweem SFML's vector type and native hardware (i.e. SSE, AltiVec, etc.) vector types (will probably work with other generic vector data types as well)
 */
template<typename OutputNumericType, typename InputNumericType>
vec2<OutputNumericType> convertToNativeVectorType(const sf::Vector2<InputNumericType> & sf_vec) {
	vec2<OutputNumericType> vector ;
	vector[0] = sf_vec.x ;
	vector[1] = sf_vec.y ;
	return vector ;
}

/**
 * @note For conversion betweem SFML's vector type and native hardware (i.e. SSE, AltiVec, etc.) vector types (will probably work with other generic vector data types as well)
 */
template <typename OutputNumericType, typename InputNumericType>
sf::Vector2<OutputNumericType> convertToSFMLVectorType(const vec2<InputNumericType> & native_vec) {
	sf::Vector2<OutputNumericType> vector ;
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
typedef vec2<int> Position ;

template <typename NumericType>
NumericType calculateDistance(const Position startingPosition) {
	return NumericType() ;
}

/**
 * Used to represents a position on the chess board in algebraic notation, where the first square
 * is a1, etc. Can be explicitely and implicitely converted to a Position (where a1 would equal the 2-vector (0, 0)), and vice versa.
 *
 * @see Wikipedia's article on <a href="http://en.wikipedia.org/wiki/Algebraic_notation_(chess)">Algebraic notation (chess)</a>
 */
struct RankAndFile {
	
protected:
	
	static constexpr char FILE_FIRST {'a'} ;
	static constexpr char FILE_LAST  {'h'} ;
	
	static constexpr unsigned short RANK_FIRST {1} ;
	static constexpr unsigned short RANK_LAST  {8} ;
	
	char file ;
	
	unsigned rank ;
	
	static char convertToFile(const unsigned x) ;
	static unsigned convertToRank(const unsigned y) ;
	
	friend void runChessGameTests() ;
	
public:
	
	RankAndFile(const char & file, const unsigned rank) : file(file), rank(rank) {}
	
	RankAndFile(const Position & pos) ;
	
	RankAndFile(const RankAndFile & other) : RankAndFile(other.file, other.rank) {}
	
	~RankAndFile() {}
	
	RankAndFile & operator = (const RankAndFile & rhs) ;
	
	RankAndFile & operator = (const Position & pos) ;
	
	operator Position() const ;
	
	string toString() const ;
	
	Position convertToPosition() const ;

	const char getFile() const { return file ; }
	const unsigned & getRank() const { return rank ; }
	
	friend std::ostream & operator<< (ostream & , const RankAndFile &) ;
	
} ;

#endif
