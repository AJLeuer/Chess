//
//  Board.h
//  Chess
//
//  Created by Adam James Leuer on 10/28/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __Chess__Board__
#define __Chess__Board__

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <functional>
#include <initializer_list>
#include <limits>

#include "Color.h"
#include "Piece.h"
#include "Square.h"

#include "../Util/Util.h"
#include "../Util/NotificationSystem.h"
#include "../Util/Vect.h"



using namespace std ;

class Board {
	
private:
	
	/**
	 * The number of rows on the chessboard
	 */
	static constexpr unsigned ranks = 8 ;
	
	/**
	 * The number of columns on the chessboard
	 */
	static constexpr unsigned files = 8 ;
	
	array<array<Square, files>, ranks> boardRepresentation ;
	
	friend class Player ;
	
	friend class Game ;

	friend void runChessGameTests() ;
	
public:
	
	inline const vec2<int> getMaxPosition() { return vec2<int>{(int)boardRepresentation.size(), (int)boardRepresentation[0].size()} ; }
	
	Board() ;
	
	Board(const Board & other) ;
	
	~Board() {}
	
	Board & operator = (const Board & other) ;
	
	/**
	 * @return A pointer to the Square at the position specified by x and y
	 *
	 * @seealso getSquare()
	 */
	const Square * operator () (unsigned arrIndexX, unsigned arrIndexY) const ;
	
	/**
	 * @return A pointer to the Square at the position specified by rf
	 *
	 * @seealso operator () (unsigned, unsigned)
	 */
	const Square * getSquare(const RankAndFile & rf) const ;
	
	/**
	 * @param pos The position of the Square to return
	 *
	 * @return A pointer to the Square at the position specified by pos
	 */
	const Square * getSquare(const vec2<int> pos) const ;
	
	const Square * getSquare(unsigned x, unsigned y) const ;
	
	/**
	 * @param pos This function checks whether pos is within the bounds of the Chess board
	 *
	 * @return true if vec2<int> pos exists on the board, false otherwise
	 */
	bool isInsideBoardBounds(const vec2<int> pos) const ;
	
	friend std::ostream & operator << (std::ostream & , const Board &) ;
	
	template <typename Character>
	friend basic_ostream<Character> & operator << (basic_ostream<Character> & out, const Board & board) ;
	
	/**
	 * @return A vector of Squares that match the given criteria
	 *
	 * @param startingSquarePosition The position of the first square processed
	 * @param directions The directions in which to search
	 * @param stopAtFirstPiece Whether, for every specified direction searched, the function should stop when it first encounters a Square holding a
	 * piece, or continue to the edge of the board
	 *
	 * @note Unlike the overload getSpecifiedSquares(const vec2<int>, const vector<Direction> &, int), this version of the function
	 * searches to the edge of the board in every specified direction (unless the parameter stopAtFirstPiece is given as true, in which
	 * case, for every direction searched, the function will only search as far as the first Square with a piece on it).
	 */
	vector<const Square *> getSpecifiedSquares(const vec2<int> startingSquarePosition, const vector<Direction> & directions, bool stopAtFirstPiece) const ;
	
	/**
	 * @return A vector of Squares that match the given criteria
	 *
	 * @param startingSquarePosition The position of the first square processed
	 * @param directions The directions in which to search
	 * @param searchDistance The distance to search in all specified directions
	 */
	vector<const Square *> getSpecifiedSquares(const vec2<int> startingSquarePosition, const vector<Direction> & directions, int searchDistance) const ;
	
	/**
	 * @return A vector of Squares that match the given criteria
	 *
	 * @param startingSquarePosition The position of the first square processed
	 * @param searchRadius Specifies the range of other squares to include
	 */
	vector<const Square *> getSpecifiedSquares(const vec2<int> startingSquarePosition, int searchRadius) const ;
	
	/**
	 * Calls a function, searchFunction, intended to process specific squares on the board, starting at startingSquare and including all
	 * other squares within a distance less than or equal to searchRadius that lie in directions specified by directions. The function in
	 * question should take a vector of squares as an argument, and will return a result of the specified type T.
	 *
	 * @param T The type returned by searchFunction
	 * @param searchFunction The function to run over the specified squares
	 * @param startingSquarePosition The position of the first square processed
	 * @param directions The directions in which to search
	 * @param searchDistance The distance to search in all specified directions
	 */
	template <typename T>
	T runSearchFunction(function<T (vector<const Square *> & squares)> searchFunction, const vec2<int> startingSquarePosition, const vector<Direction> & directions, int searchDistance) const ;
	
	/**
	 * Calls a function, searchFunction, intended to process squares in an area of the board. The function in question should take
	 * a square as an argument, and will return a result of the specified type T. The function will be applied to a vector
	 * of all squares specified withing searchRadius, starting at startingSquare
	 *
	 * @param T The type returned by searchFunction
	 * @param searchFunction The function to run over the specified squares
	 * @param startingSquarePosition The position of the first square processed
	 * @param searchRadius Specifies the range of other squares to include
	 */
	template <typename T>
	T runSearchFunction(function<T(vector<const Square *> & squares)> & searchFunction, const vec2<int> startingSquarePosition, int searchRadius) const ;
	
	
	/**
	 * Calculates a numeric value based on the current state of the chess board (including the existence and configuration of pieces)m
	 * from the perspective of the player playing the ChessColor color. In other words, if e.g. the player playing white requests the current
	 * value of the board, it will be calculated by subtracting the sum of the extant black pieces from the sum of the remaining white ones.
	 *
	 * @param callingPlayersColor The color of the player from whose perspective the value of the game state is calculated
	 */
	const short evaluate(const ChessColor callingPlayersColor) const ;
	
} ;

/*
class HypotheticalBoardState : public Board {

	
}; */



template <typename T>
T Board::runSearchFunction(function<T (vector<const Square *> & squares)> searchFunction, const vec2<int> startingSquarePosition, const vector<Direction> & directions, int searchDistance) const {
	
	vector<const Square *> argSquares = getSpecifiedSquares(startingSquarePosition, directions, searchDistance) ;
	
	return searchFunction(argSquares) ;
}


template <typename T>
T Board::runSearchFunction(function<T(vector<const Square *> & squares)> & searchFunction, const vec2<int> startingSquarePosition, int searchRadius) const {
	
	vector<const Square *> argSquares = getSpecifiedSquares(startingSquarePosition, searchRadius) ;
	
	return searchFunction(argSquares) ;
}


/**
 * Overload stream output to allow printing the chess board in its current state.
 *
 * @note basic_ostream<char> == std::ostream, allows writing to basic_ostream<wchar_t> as well
 */
template <typename Character>
basic_ostream<Character> & operator << (basic_ostream<Character> & out, const Board & board) {
	out << L"┌───┬───┬───┬───┬───┬───┬───┬───┐" << endl ;
	
	for (unsigned i = 0; i < Board::ranks ; i++) {
		
		out << L"│ " << *(board.getSquare((unsigned)0, i)) << L" │ " << *(board.getSquare((unsigned)1, i)) << L" │ " << *(board.getSquare((unsigned)2, i)) << L" │ " << *(board.getSquare((unsigned)3, i)) << L" │ " << *(board.getSquare((unsigned)4, i)) << L" │ " << *(board.getSquare((unsigned)5, i)) << L" │ " << *(board.getSquare((unsigned)6, i)) << L" │ " << *(board.getSquare((unsigned)7, i)) << L" │" << endl ;
		
		if (i < 7) {
			out << L"├───┼───┼───┼───┼───┼───┼───┼───┤" << endl ;
		}
		else { //at the end
			out << L"└───┴───┴───┴───┴───┴───┴───┴───┘" << endl ;
		}
		
	}
	return out ;
}















#endif /* defined(__Chess__Board__) */
