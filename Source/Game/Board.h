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
#include <initializer_list>

#include "Util.h"
#include "NotificationSystem.h"
#include "Position.h"
#include "Color.h"
#include "Piece.h"
#include "Square.h"



class Board {
	
protected:
	
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
	
	Board() ;
	
	Board(const Board & other) ;
	
	~Board() {}
	
	Board & operator = (const Board & other) ;
	
	const Square * getSquare(unsigned rank, char file) const ;
	
	const Square * getSquare(unsigned arrIndexX, unsigned arrIndexY) const ;
	
	friend std::ostream & operator << (std::ostream & , const Board &) ;
	
	template <typename Character>
	friend basic_ostream<Character> & operator << (basic_ostream<Character> & out, const Board & board) ;
	

	/**
	 * Calculates a numeric value based on the current state of the chess board (including the existence and configuration of pieces)m
	 * from the perspective of the player playing the Color color. In other words, if e.g. the player playing white requests the current
	 * value of the board, it will be calculated by subtracting the sum of the extant black pieces from the sum of the remaining white ones.
	 *
	 * @param PlayerByColor The player from whose perspective the value of the game state is calculated
	 */
	template <typename CallingPlayerByColor>
	short evaluate() {
		
		short black_sum = 0 ;
		short white_sum = 0 ;
		
		for (auto & i : boardRepresentation) {
			for (auto & j : i) {
				if (j.piece->getColor() == Color::black) {
					black_sum += j.piece->getValue() ;
				}
				else { //if color == white
					white_sum += j.piece->getValue() ;
				}
			}
			if (typeid(CallingPlayerByColor) == typeid(Color::black)) {
				auto result = black_sum - white_sum ;
				return result ;
			}
			else if (typeid(CallingPlayerByColor) == typeid(Color::black)) {
				auto result = white_sum - black_sum ;
				return result ;
			}
		}
	}
	
	
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
		
		out << L"│ " << *(board.getSquare(i, (unsigned)0)) << L" │ " << *(board.getSquare(i, (unsigned)1)) << L" │ " << *(board.getSquare(i, (unsigned)2)) << L" │ " << *(board.getSquare(i, (unsigned)3)) << L" │ " << *(board.getSquare(i, (unsigned)4)) << L" │ " << *(board.getSquare(i, (unsigned)5)) << L" │ " << *(board.getSquare(i, (unsigned)6)) << L" │ " << *(board.getSquare(i, (unsigned)7)) << L" │" << endl ;
		
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
