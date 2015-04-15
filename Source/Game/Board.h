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

#include "Chess.h"
#include "Piece.h"
#include "Square.h"

#include "../Util/Util.h"
#include "../Util/NotificationSystem.h"
#include "../Util/Vect.h"



using namespace std ;

namespace Chess {
	
	

class Board {
	
protected:
	
	static unsigned long IDs ;
	
	/**
	 * The number of rows on the chessboard
	 */
	static constexpr unsigned ranks = 8 ;
	
	/**
	 * The number of columns on the chessboard
	 */
	static constexpr unsigned files = 8 ;
	
	const unsigned long ID ;
	
	array<array<Square, files>, ranks> boardRepresentation ;
	
	friend class Player ;
	
	friend class Game ;
	
	friend class TemporaryBoard ;

	friend void runChessGameTests() ;
	
public:
	
	inline virtual const vec2<int> getMaxPosition() { return vec2<int>{(int)boardRepresentation.size(), (int)boardRepresentation[0].size()} ; }
	
	Board() ;
	
	Board(const Board & other) ;
	
	virtual ~Board() {}
	
	virtual Board & operator = (const Board & other) ;
	
	inline unsigned long getID() const { return ID ; }
	
	/**
	 * @return A pointer to the Square at the position specified by x and y
	 *
	 * @seealso getSquare()
	 */
	virtual const Square * operator () (unsigned arrIndexX, unsigned arrIndexY) const ;
	
	/**
	 * @return A pointer to the Square at the position specified by rf
	 *
	 * @seealso operator () (unsigned, unsigned)
	 */
	virtual const Square * getSquare(const RankAndFile & rf) const ;
	
	/**
	 * @param pos The position of the Square to return
	 *
	 * @return A pointer to the Square at the position specified by pos
	 */
	virtual const Square * getSquare(const vec2<int> pos) const ;
	
	virtual const Square * getSquare(unsigned x, unsigned y) const ;
	
	/**
	 * @param pos This function checks whether pos is within the bounds of the Chess board
	 *
	 * @return true if vec2<int> pos exists on the board, false otherwise
	 */
	virtual bool isInsideBoardBounds(const vec2<int> pos) const ;
	
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
	 */ /*
	vector<const Square *> getSpecifiedSquares(const vec2<int> startingSquarePosition, const vector<Direction> & directions, bool stopAtFirstPiece) const ; */
	

	vector<const Square *> getSpecifiedSquares(const vec2<int> startingSquarePosition, const vector<Direction> & directions,
											   Color includeFirstPieceOfColorEncountered, Color stopBeforeFirstEnountered) const ;
	
	vector<const Square *> getSpecifiedSquares(const vec2<int> startingSquarePosition, const vector<Direction> & directions, int maxSearchDistance,
											   Color includeFirstPieceOfColorEncountered, Color stopBeforeFirstEnountered) const ;
	
	/**
	 * @return A vector of Squares that match the given criteria
	 *
	 * @param startingSquarePosition The position of the first square processed
	 * @param directions The directions in which to search
	 * @param searchDistance The distance to search in all specified directions
	 */ /*
	vector<const Square *> getSpecifiedSquares(const vec2<int> startingSquarePosition, const vector<Direction> & directions, int searchDistance) const ; */
	
	/**
	 * @return A vector of Squares that match the given criteria
	 *
	 * @param startingSquarePosition The position of the first square processed
	 * @param searchRadius Specifies the range of other squares to include
	 */
	vector<const Square *> getSpecifiedSquares(const vec2<int> startingSquarePosition, int searchRadius) const ;
	
	
	/**
	 * Calculates a numeric value based on the current state of the chess board (including the existence and configuration of pieces)m
	 * from the perspective of the player playing the Chess::Color color. In other words, if e.g. the player playing white requests the current
	 * value of the board, it will be calculated by subtracting the sum of the extant black pieces from the sum of the remaining white ones.
	 *
	 * @param callingPlayersColor The color of the player from whose perspective the value of the game state is calculated
	 */
	virtual const short evaluate(const Chess::Color callingPlayersColor) const ;
	
} ;


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

	
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
}

#endif /* defined(__Chess__Board__) */
