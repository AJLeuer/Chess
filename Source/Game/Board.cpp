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

Square::Square(const Square & other) :
	rankAndFile(other.rankAndFile),
	position(other.position),
	board(other.board),
	piece((other.piece != nullptr) ? Piece::init(other.piece->getSymbol(), & other.position, & other.board, & other) : nullptr)
{
	registerForPieceMovement() ;
}

Square::Square(const char file, const unsigned rank, const Board * board) :
	rankAndFile(file, rank),
	position(rankAndFile),
	board(board),
	piece(nullptr)
{
	registerForPieceMovement() ;
}

Square::Square(Piece * piece, const char file, const unsigned rank, const Board * board) :
	Square(file, rank, board)
{
	this->piece = piece ;
}

Square::Square(const wchar_t pieceSymbol, const char file, const unsigned rank, const Board * board) :
	Square(Piece::init(pieceSymbol, & position, & this->board, this), file, rank, board) {}

Square & Square::operator = (const Square & other) {
	if (this != & other) {
		this->rankAndFile = other.rankAndFile ;
		this->position = other.position ;
		board = other.board ;
		
		if (this->piece != nullptr) {
			delete this->piece ;
		}
		
		if (other.piece != nullptr) {
			piece = Piece::init(other.piece->getSymbol(), other.piece->getPosition(), & other.board, this) ;
		}
		
	}
	return * this ;
}

void Square::receiveMovingPiece(Piece * pieceMovingTo) {
	if (this->isOccupied()) {
		//then a piece was captured
		handlePieceCapture(pieceMovingTo) ;
	}
	
	clearCurrentPiece(this->piece) ;
	setCurrentPiece(pieceMovingTo) ;
}

void Square::setCurrentPiece(Piece * pieceMovingTo) {
	this->piece = pieceMovingTo ;
	this->piece->setCurrentPosition(& this->position) ;
}

void Square::clearCurrentPiece(Piece * toClear) {
	
	//debug code only, remove this
	assert(this->piece == toClear) ;
	
	if (piece != nullptr) {
		this->piece->clearCurrentPosition() ;
		this->piece = nullptr ;
	}
}

void Square::destroyCurrentPiece() {
	if (piece != nullptr) {
		delete this->piece ;
	}
	piece = nullptr ;
}

void Square::handlePieceCapture(Piece * pieceCapturing) {
	//notify everything that was registered for a capture event for our piece
	Notification<Piece>::notify(EventType::pieceSpecifiedByIDWasCaptured, this->piece, {board->getID(), pieceCapturing->getID()}) ;
	
	destroyCurrentPiece() ;
}

void Square::registerForPieceMovement() {
	
	using namespace std::placeholders ;
	
	auto receiveMovingP = std::bind(&Square::receiveMovingPiece, this, _1) ;
	Notification<Piece> notifyWhenPieceMovesHere (EventType::pieceArrivingAtPositionSpecifiedByPositionID, receiveMovingP, {board->getID(),generateID<int>(this->getPosition())}) ;
	
	auto clearCurrentP = std::bind(& Square::clearCurrentPiece, this, _1) ;
	Notification<Piece> notifyWhenPieceLeaves (EventType::pieceLeavingPositionSpecifiedByPositionID, clearCurrentP, {board->getID(), generateID<int>(this->getPosition())}) ;
	
	notifyWhenPieceMovesHere.registerForCallback() ;
	notifyWhenPieceLeaves.registerForCallback() ;
}

const Square * Board::operator () (unsigned arrIndexX, unsigned arrIndexY) const {
	return & boardRepresentation[arrIndexX][arrIndexY] ;
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
	
		{{{L'♞', 'b', 8, this}, {L'♟', 'b', 7, this}, {L' ', 'b', 6, this}, {L' ', 'b', 5, this}, {L' ', 'b', 4, this}, {L' ', 'c', 3, this}, {L'♙', 'b', 2, this}, {L'♘', 'b', 1, this}}},
	
		{{{L'♝', 'c', 8, this}, {L'♟', 'c', 7, this}, {L' ', 'c', 6, this}, {L' ', 'c', 5, this}, {L' ', 'c', 4, this}, {L' ', 'c', 3, this}, {L'♙', 'c', 2, this}, {L'♗', 'c', 1, this}}},
	
		{{{L'♛', 'd', 8, this}, {L'♟', 'd', 7, this}, {L' ', 'd', 6, this}, {L' ', 'd', 5, this}, {L' ', 'd', 4, this}, {L' ', 'e', 3, this}, {L'♙', 'd', 2, this}, {L'♕', 'd', 1, this}}},
	
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

}

Board & Board::operator = (const Board & other) {
	if (this != & other) {
		this->boardRepresentation = other.boardRepresentation ;
	}
	return * this ;
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


vector<const Square *> Board::getSpecifiedSquares(const vec2<int> startingSquarePosition, const vector<Direction> & directions, Color includeFirstPieceOfColorEncountered, Color stopBeforeFirstEnountered) const
{
	vector<const Square *> squares ;
	
	for (auto i = 0 ; i < directions.size() ; i++) {
		
		vec2<int> offset { directions[i] } ; //directions convert to vectors like (0, 1)
		
		for (vec2<int> next = (startingSquarePosition + offset) ; ; next = (next + offset)) {
			
			if (isInsideBoardBounds(next)) {
				
				const Square * nextSquare { getSquare(next) } ;

				
				if (nextSquare->isOccupied()) { //the other way to get out of the loop
					
					if (nextSquare->getPiece()->getColor() == includeFirstPieceOfColorEncountered) {
						squares.push_back(nextSquare) ;
					}
					/* else (nextSquare->getPiece()->getColor() == stopBeforeFirstEncountered), so don't include this Square */
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
												  int maxSearchDistance, Color includeFirstPieceOfColorEncountered, Color stopBeforeFirstEnountered) const
{
	vector<const Square *> squares ;
	
	for (auto i = 0 ; i < directions.size() ; i++) {
		
		vec2<int> offset { directions[i] } ; //directions convert to vectors like (0, 1)
		
		vec2<int> next = (startingSquarePosition + offset) ;
		vec2<int> endpoint = next + (offset * maxSearchDistance) ;
		
		for (; ; next = (next + offset)) {
			
			if (isInsideBoardBounds(next)) {
				
				const Square * nextSquare { getSquare(next) } ;
				
				if (nextSquare->isOccupied()) { //the other way to get out of the loop
					
					if (nextSquare->getPiece()->getColor() == includeFirstPieceOfColorEncountered) {
						squares.push_back(nextSquare) ;
					}
					/* else (nextSquare->getPiece()->getColor() == stopBeforeFirstEncountered), so don't include this Square */
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


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

}




