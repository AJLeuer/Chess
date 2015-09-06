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
#include "../Util/Vect.h"



using namespace std ;

namespace Chess {
	
class Game ;

class Board {
	
protected:
	
	static unsigned long IDs ;
	
	const unsigned long ID ;
	
	array<array<Square, files>, ranks> boardRepresentation ;
	
	const Game * game = nullptr ;
	
	/**
	 * @return A pointer to the Square at the position specified by pos
	 *
	 * @seealso getSquare()
	 */
	virtual Square * getSquareMutable(vec2<int> pos) ;
	
	void updateSquaresAfterCopy() ;
	
	friend class Piece ;
	
	friend class Player ;
	
	friend class AI ;
	
	friend class Game ;
	
	friend class TemporaryBoard ;
	
	friend void runChessGameTests() ;
	
public:
	
	inline virtual const vec2<int> getMaxPosition() { return vec2<int>{(int)boardRepresentation.size(), (int)boardRepresentation[0].size()} ; }
	
	Board() ;
	
	Board(const Board & other) ;
	
	virtual ~Board() {}
	
	Board & operator = (const Board & other) = delete ;
	
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
	
	
	vector<const Square *> getSpecifiedSquares(const vec2<int> startingSquarePosition, const vector<Direction> & directions,
											   SafeBoolean includeFirstPieceOfColorEncountered, Color toInclude) const ;
	
												//need to use a SafeBoolean here instead of a bool, otherwise danger of mixing up calls between these
												//two overloads
	
	vector<const Square *> getSpecifiedSquares(const vec2<int> startingSquarePosition, const vector<Direction> & directions, int maxSearchDistance,
											   SafeBoolean includeFirstPieceOfColorEncountered, Color toInclude) const ;
	
	
	/**
	 * @return A vector of Squares that match the given criteria
	 *
	 * @param startingSquarePosition The position of the first square processed
	 * @param searchRadius Specifies the range of other squares to include
	 */
	vector<const Square *> getSpecifiedSquares(const vec2<int> startingSquarePosition, int searchRadius) const ;
	
	/**
	 * Finds the Piece on this board that matches the given argument. There are two requirements for a match:
	 * first that the two pieces are at the same position on their respective boards (and they may belong to different boards),
	 * second is that they are of the same type. Note that this function does not verify that they are the same object (and indeed
	 * the very purpose of this function is such that in most cases the argument and the return value should point to different objects
	 * entirely).
	 *
	 * @param piece The piece to match
	 */
	Piece * findMatch(const Piece * piece) ;
	
	
	/**
	 * Calculates a numeric value based on the current state of the chess board (including the existence and configuration of pieces)m
	 * from the perspective of the player playing the Chess::Color color. In other words, if e.g. the player playing white requests the current
	 * value of the board, it will be calculated by subtracting the sum of the extant black pieces from the sum of the remaining white ones.
	 *
	 * @param callingPlayersColor The color of the player from whose perspective the value of the game state is calculated
	 */
	virtual const short evaluate(const Chess::Color callingPlayersColor) const ;
	
	/**
	 * Same as running evaluate() after moving piece to the specified RankAndFile. Does not actually change the state of the board.
	 *
	 * @param callingPlayersColor The color of the player from whose perspective the value of the game state is calculated
	 * @param piece The Piece that would move
	 * @param moveTo Where piece would move
	 */
	const short evaluateAfterHypotheticalMove(const Piece * piece, const vec2<int> moveTo) const ;
	
} ;


/**
 * Overload stream output to allow printing the chess board in its current state.
 *
 * @note basic_ostream<char> == std::ostream, allows writing to basic_ostream<wchar_t> as well
 */
template <typename Character>
basic_ostream<Character> & operator << (basic_ostream<Character> & out, const Board & board) {
	out << L"┌───┬───┬───┬───┬───┬───┬───┬───┐" << endl ;
	
	for (unsigned i = 0; i < ranks ; i++) {
		
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
