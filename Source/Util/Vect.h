//
//  Vect.h
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
#include <array>

#include <SFML/System/Vector2.hpp>

#include "Util.h"

using namespace std;

constexpr unsigned lowerCaseA {97};

#ifdef __clang__

template <typename NumericType>
using simd_vector_2 = NumericType __attribute__((ext_vector_type(2)));

#elif _MSC_VER

template <typename NumericType>
using simd_vector_2 = std::array<NumericType, 2>;

#endif

/**
 * @note A good example of a C++ literal type
 */
template <typename NumericType>
struct vec2
{
	simd_vector_2 <NumericType> value;

	inline constexpr vec2 (const vec2 & other) : value(other.value) {}

	inline constexpr vec2 (const simd_vector_2 <NumericType> val) : value(val) {}

	template <typename NumericType0>
	inline constexpr vec2 (const simd_vector_2 <NumericType0> val) : value { static_cast<NumericType>(val[0]), static_cast<NumericType>(val[1]) } {}

	inline constexpr vec2 (NumericType x, NumericType y) : value(simd_vector_2 <NumericType> {x, y}) {}

	inline constexpr operator simd_vector_2 <NumericType> () const { return this->value; }

	template <typename NumericType0>
	inline constexpr operator simd_vector_2 <NumericType0> () const {
		return simd_vector_2 <NumericType0> {static_cast<NumericType0>(value[0]), static_cast<NumericType0>(value[1])};
	}


	inline constexpr NumericType operator [] (size_t i) const { return value[i]; }


	inline constexpr bool operator == (vec2 other) const {
		return ((this->value[0] == other.value[0]) && (this->value[1] == other.value[1]));
	}

	inline constexpr bool operator != (vec2 other) const { return (!(* this == other)); }


	inline constexpr vec2 & operator += (vec2 other)
	{
		this->value += other.value;
		return * this;
	}

	inline constexpr vec2 & operator -= (vec2 other)
	{
		this->value -= other.value;
		return * this;
	}

	inline constexpr vec2 & operator *= (vec2 other)
	{
		this->value *= other.value;
		return * this;
	}

	inline constexpr vec2 & operator /= (vec2 other)
	{
		this->value /= other.value;
		return * this;
	}


	inline constexpr vec2 & operator += (NumericType n)
	{
		this->value += n;
		return * this;
	}

	inline constexpr vec2 & operator -= (NumericType n)
	{
		this->value -= n;
		return * this;
	}

	template <typename NumericType0>
	inline constexpr vec2 <NumericType> & operator *= (NumericType0 n)
    {
		this->value *= n;
		return * this;
	}

	template <typename NumericType0>
	inline constexpr vec2 <NumericType> & operator /= (NumericType0 n)
    {
		this->value /= n;
		return * this;
	}


	/*
	 * Compiler seems to provide these operator overloads implicitly, retaining for reference and/or the possibility
	 * we run into problem later
	 *
	 * Update: four years later, when trying to compile this with MSVC, it turns out these are now needed. So thanks, old me */

	inline friend constexpr vec2 operator + (const vec2 v0, const vec2 v1) { return vec2<NumericType> { (v0.value[0] + v1.value[0]), (v0.value[1] + v1.value[1]) } ; }

	inline friend constexpr vec2 operator - (const vec2 v0, const vec2 v1) { return vec2<NumericType> { (v0.value[0] - v1.value[0]), (v0.value[1] - v1.value[1]) } ; }

	inline friend constexpr vec2 operator * (const vec2 v0, const vec2 v1) { return vec2<NumericType> { (v0.value[0] * v1.value[0]), (v0.value[1] * v1.value[1]) } ; }

	inline friend constexpr vec2 operator / (const vec2 v0, const vec2 v1) { return vec2<NumericType> { (v0.value[0] / v1.value[0]), (v0.value[1] / v1.value[1]) } ; }


	inline friend constexpr vec2 operator + (const vec2 v, const NumericType n)
	{
		return vec2 {(v.value[0] + n), (v.value[1] + n)};
	}

	inline friend constexpr vec2 operator - (const vec2 v, const NumericType n)
	{
		return vec2 {(v.value[0] - n), (v.value[1] - n)};
	}

	inline friend constexpr vec2 operator * (const vec2 v, const NumericType n)
	{
		return vec2 {(v.value[0] * n), (v.value[1] * n)};
	}

	inline friend constexpr vec2 operator / (const vec2 v, const NumericType n)
	{
		return vec2 {(v.value[0] / n), (v.value[1] / n)};
	}

};


/**
 * @note A good example of a C++ literal type
 */
struct Direction {

protected:

	const simd_vector_2 <int> value;

public:

	constexpr Direction (const simd_vector_2 <int> val) : value(val) {}

	constexpr Direction (const int h, const int v) : value(simd_vector_2 <int> {h, v}) {}

	constexpr operator simd_vector_2 <int> () const { return this->value; }

	template <typename NumericType>
	friend simd_vector_2 <NumericType> operator * (const Direction &, const NumericType);

	template <typename NumericType>
	friend simd_vector_2 <NumericType> operator + (const Direction &, const simd_vector_2 <NumericType>);

};

namespace Directions {

	static constexpr Direction up {simd_vector_2 <int> {0, -1}};

	static constexpr Direction down {simd_vector_2 <int> {0, 1}};

	static constexpr Direction left {simd_vector_2 <int> {-1, 0}};

	static constexpr Direction right {simd_vector_2 <int> {1, 0}};

	static constexpr Direction upLeft {simd_vector_2 <int> {-1, -1}};

	static constexpr Direction upRight {simd_vector_2 <int> {1, -1}};

	static constexpr Direction downLeft {simd_vector_2 <int> {-1, 1}};

	static constexpr Direction downRight {simd_vector_2 <int> {1, 1}};

}


template <typename NumericType>
simd_vector_2 <NumericType> operator * (const Direction & direction, const NumericType n) {

	simd_vector_2 <NumericType> ret;

	ret[0] = direction.value[0] * n;
	ret[1] = direction.value[1] * n;

	return ret;
}

template <typename NumericType>
simd_vector_2 <NumericType> operator + (const Direction & direction, const simd_vector_2 <NumericType> vec) {

	simd_vector_2 <NumericType> ret;

	ret[0] = direction.value[0] + vec[0];
	ret[1] = direction.value[1] + vec[1];

	return ret;
}


/**
 * @note For conversion betweem SFML's vector type and native hardware (i.e. SSE, AltiVec, etc.) vector types (will probably work with other generic vector
 * data types as well)
 */
template <typename NumericType>
simd_vector_2 <NumericType> convertToNativeVectorType (const sf::Vector2 <NumericType> & sf_vec) {
	simd_vector_2 <NumericType> vector;
	vector[0] = sf_vec.x;
	vector[1] = sf_vec.y;
	return vector;
}

/**
 * @note For conversion betweem SFML's vector type and native hardware (i.e. SSE, AltiVec, etc.) vector types (will probably work with other generic vector
 * data types as well)
 */
template <typename NumericType>
sf::Vector2 <NumericType> convertToSFMLVectorType (const simd_vector_2 <NumericType> & native_vec) {
	sf::Vector2 <NumericType> vector;
	vector.x = native_vec[0];
	vector.y = native_vec[1];
	return vector;
}

/**
 * @note For conversion betweem SFML's vector type and native hardware (i.e. SSE, AltiVec, etc.) vector types (will probably work with other generic vector data types as well)
 */
template <typename OutputNumericType, typename InputNumericType>
simd_vector_2 <OutputNumericType> convertToNativeVectorType (const sf::Vector2 <InputNumericType> & sf_vec) {
	simd_vector_2 <OutputNumericType> vector;
	vector[0] = sf_vec.x;
	vector[1] = sf_vec.y;
	return vector;
}

/**
 * @note For conversion betweem SFML's vector type and native hardware (i.e. SSE, AltiVec, etc.) vector types (will probably work with other generic vector data types as well)
 */
template <typename OutputNumericType, typename InputNumericType>
sf::Vector2 <OutputNumericType> convertToSFMLVectorType (const simd_vector_2 <InputNumericType> & native_vec) {
	sf::Vector2 <OutputNumericType> vector;
	vector.x = native_vec[0];
	vector.y = native_vec[1];
	return vector;
}

template <typename Character, typename NumericType>
basic_ostream <Character> & operator << (basic_ostream <Character> & out, const simd_vector_2 <NumericType> & vect)
{
	out << "x = " << vect[0] << " y = " << vect[1];
	return out;
}

/**
 * Code partial credit StackOverflow:
 * @link http://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector
 */
template <typename VectorType>
inline UniqueNumericIdentifier hashVector (const VectorType & vect, size_t vectorSize)
{
	unsigned long seed = 0;

	for (auto i = 0; i < vectorSize; i++) {
		seed ^= vect[i] + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	return seed;
}


template <typename VectorType>
inline UniqueNumericIdentifier hashTwoVector (const VectorType twoVect) {
	auto hash = hashVector(twoVect, 2);
	return hash;
}

/**
 * Allows creating a unique identifying value for simd_vector_2, which isn't
 * a class and can't store a UniqueNumericIdentifier as a member variable
 */
template <typename NumericType>
inline UniqueNumericIdentifier generateID (simd_vector_2 <NumericType> vect) {
	return hashTwoVector <simd_vector_2 <NumericType>>(vect);
}


template <typename NumericType>
NumericType calculateDistance (const simd_vector_2 <int> startingPosition) {
	return NumericType();
}


#endif
