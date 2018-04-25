//
//  Board.cpp
//  Chess
//
//  Created by Adam James Leuer on 10/28/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "Board.h"

using namespace std ;

namespace Chess {
	

const Square * Board::operator () (unsigned arrIndexX, unsigned arrIndexY) const {
	return & boardRepresentation[arrIndexX][arrIndexY] ;
}
	
Square * Board::getSquareMutable(vec2<int> pos) {
	return & boardRepresentation[pos.value.x][pos.value.y] ;
}

const Square * Board::getSquare(const RankAndFile & rf) const {
	vec2<int> pos { rf.convertToPosition() } ;
	return this->operator()(pos.value.x, pos.value.y) ; //todo implement properly
}

const Square * Board::getSquare(const vec2<int> pos) const {
	return this->operator()(pos.value.x, pos.value.y) ;
}

const Square * Board::getSquare(unsigned x, unsigned y) const {
	return this->operator()(x, y) ;
}

ostream & operator << (ostream & out, const Square & square) {
	if (square.isEmpty()) {
		out << ' ' ;
	}
	else {
		out << *(square.piece) ;
	}
	return out ;
}

basic_ostream<wchar_t> & operator << (basic_ostream<wchar_t> & out, const Square & square) {
	if (square.isEmpty()) {
		out << ' ' ;
	}
	else {
		out << *(square.piece) ;
	}
	return out ;
}
	
unsigned long Board::IDs = 0 ;

Board::Board() :
	ID(IDs++),
	boardRepresentation{{
		{{{L'♜', 'a', 8, this}, {L'♟', 'a', 7, this}, {L' ', 'a', 6, this}, {L' ', 'a', 5, this}, {L' ', 'a', 4, this}, {L' ', 'a', 3, this}, {L'♙', 'a', 2, this}, {L'♖', 'a', 1, this}}},
	
		{{{L'♞', 'b', 8, this}, {L'♟', 'b', 7, this}, {L' ', 'b', 6, this}, {L' ', 'b', 5, this}, {L' ', 'b', 4, this}, {L' ', 'b', 3, this}, {L'♙', 'b', 2, this}, {L'♘', 'b', 1, this}}},
	
		{{{L'♝', 'c', 8, this}, {L'♟', 'c', 7, this}, {L' ', 'c', 6, this}, {L' ', 'c', 5, this}, {L' ', 'c', 4, this}, {L' ', 'c', 3, this}, {L'♙', 'c', 2, this}, {L'♗', 'c', 1, this}}},
	
		{{{L'♛', 'd', 8, this}, {L'♟', 'd', 7, this}, {L' ', 'd', 6, this}, {L' ', 'd', 5, this}, {L' ', 'd', 4, this}, {L' ', 'd', 3, this}, {L'♙', 'd', 2, this}, {L'♕', 'd', 1, this}}},
	
		{{{L'♚', 'e', 8, this}, {L'♟', 'e', 7, this}, {L' ', 'e', 6, this}, {L' ', 'e', 5, this}, {L' ', 'e', 4, this}, {L' ', 'e', 3, this}, {L'♙', 'e', 2, this}, {L'♔', 'e', 1, this}}},
	
		{{{L'♝', 'f', 8, this}, {L'♟', 'f', 7, this}, {L' ', 'f', 6, this}, {L' ', 'f', 5, this}, {L' ', 'f', 4, this}, {L' ', 'f', 3, this}, {L'♙', 'f', 2, this}, {L'♗', 'f', 1, this}}},
	
		{{{L'♞', 'g', 8, this}, {L'♟', 'g', 7, this}, {L' ', 'g', 6, this}, {L' ', 'g', 5, this}, {L' ', 'g', 4, this}, {L' ', 'g', 3, this}, {L'♙', 'g', 2, this}, {L'♘', 'g', 1, this}}},
	
		{{{L'♜', 'h', 8, this}, {L'♟', 'h', 7, this}, {L' ', 'h', 6, this}, {L' ', 'h', 5, this}, {L' ', 'h', 4, this}, {L' ', 'h', 3, this}, {L'♙', 'h', 2, this}, {L'♖', 'h', 1, this}}}
	}}
{
	
}

Board::Board(const Board & other) :
	ID(IDs++),
	boardRepresentation(other.boardRepresentation)
{
	/* Sets squares references to board to this */
	updateSquaresAfterCopy() ;
}

void Board::updateSquaresAfterCopy() {
	for (size_t i = 0 ; i < boardRepresentation.size() ; i++) {
		for (size_t j = 0 ; j < boardRepresentation[i].size() ; j++) {
			
			boardRepresentation[i][j].board = this ;
			/* this should update the Square's piece's board pointer as well */
		}
	}
}

bool Board::isInsideBoardBounds(const vec2<int> pos) const {
	if ((pos.value.x >= 0) && (pos.value.x < boardRepresentation.size())) {
		if ((pos.value.y >= 0) && (pos.value.y < boardRepresentation[pos.value.x].size())) {
			return true ;
		}
		else {
			return false ;
		}
	}
	else {
		return false ;
	}
}


vector<const Square *> Board::getSpecifiedSquares(const vec2<int> startingSquarePosition, const vector<Direction> & directions,
												  SafeBoolean includeFirstPieceOfColorEncountered, Color toInclude) const
{
	vector<const Square *> squares ;
	
	for (auto i = 0 ; i < directions.size() ; i++) {
		
		vec2<int> offset { directions[i] } ; //directions convert to vectors like (0, 1)
		
		for (vec2<int> next = (startingSquarePosition + offset) ; ; next = (next + offset)) {
			
			if (isInsideBoardBounds(next)) {
				
				const Square * nextSquare { getSquare(next) } ;

				
				if (nextSquare->isOccupied()) { //the other way to get out of the loop
					
					if ((includeFirstPieceOfColorEncountered == SafeBoolean::t) && (nextSquare->getPiece()->getColor() == toInclude)) {
						squares.push_back(nextSquare) ;
					}
					/* Else this is our stopping point */
					break ;
				}
				else {
					squares.push_back(nextSquare) ;
				}
				
			}
			
			else /* if (isInsideBoardBounds(next) == false) */ { //we've gone outside the bounds of the board. we can can safely break out of this loop and avoid more pointless searching, since we know there's nothing in this direction
				break ;
			}
		}
	}
	
	return squares ;
}
	
	vector<const Square *> Board::getSpecifiedSquares(const vec2<int> startingSquarePosition, const vector<Direction> & directions,
													  int maxSearchDistance, SafeBoolean includeFirstPieceOfColorEncountered, Color toInclude) const
{
	
	vector<const Square *> squares ;
	
	for (auto i = 0 ; i < directions.size() ; i++) {
		
		vec2<int> offset { directions[i] } ; //directions convert to vectors like (0, 1)
		
		vec2<int> next = (startingSquarePosition + offset) ;
		vec2<int> endpoint = startingSquarePosition + (offset * maxSearchDistance) ;
		
		for (; ; next = (next + offset)) {
			
			if (isInsideBoardBounds(next)) {
				
				const Square * nextSquare { getSquare(next) } ;
				
				if (nextSquare->isOccupied()) { //the other way to get out of the loop
					
					if ((includeFirstPieceOfColorEncountered == SafeBoolean::t) && (nextSquare->getPiece()->getColor() == toInclude)) {
						squares.push_back(nextSquare) ;
					}
					/* Else this is our stopping point */
					break ;
				}
				else {
					squares.push_back(nextSquare) ;
				}
				
				if (next == endpoint) {
					break ;
				}
			}
			
			else /* if (isInsideBoardBounds(next) == false) */ { //we've gone outside the bounds of the board. we can can safely break out of this loop and avoid more pointless searching, since we know there's nothing in this direction
				break ;
			}
		}
	}
	
	return squares ;
}


vector<const Square *> Board::getSpecifiedSquares(const vec2<int> startingSquarePosition, int searchRadius) const {
	
	vector<const Square *> squares ;
	
	for (vec2<int> currentIndex {(startingSquarePosition.value.x - searchRadius),(startingSquarePosition.value.y - searchRadius) } ;
		 currentIndex.value.x <=(startingSquarePosition.value.x + searchRadius) ; currentIndex.value.x++) {
		
		for (currentIndex.value.y = (startingSquarePosition.value.y - searchRadius) ;
			 currentIndex.value.y <= (startingSquarePosition.value.y + searchRadius) ; currentIndex.value.y++) {
			
			if (isInsideBoardBounds(currentIndex)) {
				const Square * sq { getSquare(currentIndex) } ;
				squares.push_back(sq) ;
			}
			
		}
		
	}
	
	return squares ;
}
	
Piece * Board::findMatch(const Piece * piece) {
	
	Square * sq = getSquareMutable(* piece->getPosition()) ;
	
	if (sq->piece != nullptr) {

		if (sq->piece->getType() == piece->getType()) {
			
			return sq->piece ;
		}
	}
	
	return nullptr ;
}



const short Board::evaluate(const Chess::Color callingPlayersColor) const {
	
	short black_sum = 0 ;
	short white_sum = 0 ;
	
	for (auto & i : boardRepresentation) {
		for (auto & j : i) {
			if (j.piece != nullptr) {
				if (j.piece->getColor() == Chess::Color::black) {
					black_sum += j.piece->getValue() ;
				}
				else { //if color == white
					white_sum += j.piece->getValue() ;
				}
			}
		}
	}
	
	if (callingPlayersColor == Chess::Color::black) {
		constexpr short largestShort = numeric_limits<short>::max() ; //debug variable
		short result = black_sum - white_sum ;
		return result ;
	}
	else /* if (callingPlayersColor == Chess::Color::white) */ {
		short result = white_sum - black_sum ;
		return result ;
	}
}
	
const short Board::evaluateAfterHypotheticalMove(const Piece * piece, const vec2<int> moveTo) const {
	
	Board testBoard(* this) ;
	
	Piece * testPiece = testBoard.findMatch(piece) ;
	
	testPiece->move(moveTo) ;
	
	return testBoard.evaluate(piece->getColor()) ;
}

    void runChessGameTests() {

    }


}




