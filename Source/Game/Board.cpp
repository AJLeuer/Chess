//
//  Board.cpp
//  Chess
//
//  Created by Adam James Leuer on 10/28/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "Board.h"

using namespace std ;

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

Square::Square(const string & pieceSymbol, const char file, const unsigned rank, const Board * board) :
	Square(Piece::init(stringConverter.from_bytes(pieceSymbol), & position, & this->board, this), file, rank, board) {}

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
	Notification<Piece>::notify(EventType::pieceSpecifiedByIDWasCaptured, this->piece, pieceCapturing->getID()) ;
	
	destroyCurrentPiece() ;
}

void Square::registerForPieceMovement() {
	
	using namespace std::placeholders ;
	
	auto receiveMovingP = std::bind(&Square::receiveMovingPiece, this, _1) ;
	Notification<Piece> notifyWhenPieceMovesHere (EventType::pieceArrivingAtPositionSpecifiedByPositionID, receiveMovingP, generateID<int>(this->getPosition())) ;
	
	auto clearCurrentP = std::bind(& Square::clearCurrentPiece, this, _1) ;
	Notification<Piece> notifyWhenPieceLeaves (EventType::pieceLeavingPositionSpecifiedByPositionID, clearCurrentP, generateID<int>(this->getPosition())) ;
	
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

Board::Board() :
	boardRepresentation{{
		{{{"♜", 'a', 8, this}, {"♟", 'a', 7, this}, {" ", 'a', 6, this}, {" ", 'a', 5, this}, {" ", 'a', 4, this}, {" ", 'a', 3, this}, {"♙", 'a', 2, this}, {"♖", 'a', 1, this}}},
	
		{{{"♞", 'b', 8, this}, {"♟", 'b', 7, this}, {" ", 'b', 6, this}, {" ", 'b', 5, this}, {" ", 'b', 4, this}, {" ", 'c', 3, this}, {"♙", 'b', 2, this}, {"♘", 'b', 1, this}}},
	
		{{{"♝", 'c', 8, this}, {"♟", 'c', 7, this}, {" ", 'c', 6, this}, {" ", 'c', 5, this}, {" ", 'c', 4, this}, {" ", 'c', 3, this}, {"♙", 'c', 2, this}, {"♗", 'c', 1, this}}},
	
		{{{"♛", 'd', 8, this}, {"♟", 'd', 7, this}, {" ", 'd', 6, this}, {" ", 'd', 5, this}, {" ", 'd', 4, this}, {" ", 'e', 3, this}, {"♙", 'd', 2, this}, {"♕", 'd', 1, this}}},
	
		{{{"♚", 'e', 8, this}, {"♟", 'e', 7, this}, {" ", 'e', 6, this}, {" ", 'e', 5, this}, {" ", 'e', 4, this}, {" ", 'e', 3, this}, {"♙", 'e', 2, this}, {"♔", 'e', 1, this}}},
	
		{{{"♝", 'f', 8, this}, {"♟", 'f', 7, this}, {" ", 'f', 6, this}, {" ", 'f', 5, this}, {" ", 'f', 4, this}, {" ", 'f', 3, this}, {"♙", 'f', 2, this}, {"♗", 'f', 1, this}}},
	
		{{{"♞", 'g', 8, this}, {"♟", 'g', 7, this}, {" ", 'g', 6, this}, {" ", 'g', 5, this}, {" ", 'g', 4, this}, {" ", 'g', 3, this}, {"♙", 'g', 2, this}, {"♘", 'g', 1, this}}},
	
		{{{"♜", 'h', 8, this}, {"♟", 'h', 7, this}, {" ", 'h', 6, this}, {" ", 'h', 5, this}, {" ", 'h', 4, this}, {" ", 'h', 3, this}, {"♙", 'h', 2, this}, {"♖", 'h', 1, this}}}
	}}
{
	
}

Board::Board(const Board & other) :
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

vector<const Square *> Board::getSpecifiedSquares(const vec2<int> startingSquarePosition, const vector<Direction> & directions, bool stopAtFirstPiece) const {
	
	vector<const Square *> squares ;
	
	for (auto i = 0 ; i < directions.size() ; i++) {
		
		vec2<int> offset { directions[i] } ; //directions convert to vectors like (0, 1)
		
		for (vec2<int> next = (startingSquarePosition + offset) ; ; next = (next + offset)) {
			
			bool searchIsStillWithinBoardBounds = isInsideBoardBounds(next) ;
			
			if (searchIsStillWithinBoardBounds) {
				const Square * nextSquare { getSquare(next) } ;
				squares.push_back(nextSquare) ;
			}
			else if (searchIsStillWithinBoardBounds == false) { //we've gone outside the bounds of the board. we can can safely break out of this loop and avoid more pointless searching, since we know there's nothing in this direction
				break ;
			}
			if ((stopAtFirstPiece) && (getSquare(next)->isOccupied())) { //the other way to get out of the loop
				break ;
			}
		}
	}
	
	return squares ;
}

vector<const Square *> Board::getSpecifiedSquares(const vec2<int> startingSquarePosition, const vector<Direction> & directions, int searchDistance) const {
	
	vector<const Square *> squares ;
	
	for (auto i = 0 ; i < directions.size() ; i++) {
		
		vec2<int> offset { directions[i] } ; //directions convert to vectors like (0, 1)
		
		for (vec2<int> next = (startingSquarePosition + offset), end = (startingSquarePosition + (directions[i] * searchDistance)); ; next = (next + offset)) {
			
			bool searchIsStillWithinBoardBounds = isInsideBoardBounds(next) ;
			if (searchIsStillWithinBoardBounds) {
				const Square * nextSquare { getSquare(next) } ;
				squares.push_back(nextSquare) ;
			}
			else if (searchIsStillWithinBoardBounds == false) { //we've gone outside the bounds of the board. we can can safely break out of this loop and avoid more pointless searching, since we know there's nothing in this direction
				break ;
			}
			if (next == end) { //the other way to get out of the loop
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


const short Board::evaluate(const ChessColor callingPlayersColor) const {
	
	short black_sum = 0 ;
	short white_sum = 0 ;
	
	for (auto & i : boardRepresentation) {
		for (auto & j : i) {
			if (j.piece != nullptr) {
				if (j.piece->getColor() == ChessColor::black) {
					black_sum += j.piece->getValue() ;
				}
				else { //if color == white
					white_sum += j.piece->getValue() ;
				}
			}
		}
	}
	
	if (callingPlayersColor == ChessColor::black) {
		constexpr short largestShort = numeric_limits<short>::max() ; //debug variable
		short result = black_sum - white_sum ;
		return result ;
	}
	else /* if (callingPlayersColor == ChessColor::white) */ {
		short result = white_sum - black_sum ;
		return result ;
	}
}








