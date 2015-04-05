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

void Square::clearCurrentPiece(Piece * ignored) {
	if (piece != nullptr) {
		this->piece->setCurrentPosition(nullptr) ;
		this->piece = nullptr ;
	}
}

void Square::registerForPieceMovement() {
	
	using namespace std::placeholders ;
	
	auto setCurrentP = std::bind(&Square::setCurrentPiece, this, _1) ;
	Notification<Piece, size_t> notifyWhenPieceMovesHere (EventType::pieceArriving, setCurrentP, hashTwoVector(this->getPosition())) ;
	
	auto clearCurrentP = std::bind(&Square::clearCurrentPiece, this, _1) ;
	Notification<Piece, size_t> notifyWhenPieceLeaves (EventType::pieceLeaving, clearCurrentP, hashTwoVector(this->getPosition())) ;
	
	notifyWhenPieceMovesHere.registerForCallback() ;
	notifyWhenPieceLeaves.registerForCallback() ;
}

const Square * Board::operator () (unsigned arrIndexX, unsigned arrIndexY) const {
	return & boardRepresentation[arrIndexX][arrIndexY] ;
}

const Square * Board::getSquare(const RankAndFile & rf) const {
	Position pos { rf.convertToPosition() } ;
	return this->operator()(pos.x, pos.y) ; //todo implement properly
}

const Square * Board::getSquare(const Position pos) const {
	return this->operator()(pos.x, pos.y) ;
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
		{{{"♖", 'a', 1, this}, {"♙", 'a', 2, this}, {" ", 'a', 3, this}, {" ", 'a', 4, this}, {" ", 'a', 5, this}, {" ", 'a', 6, this}, {"♟", 'a', 7, this}, {"♜", 'a', 8, this}}},
	
		{{{"♘", 'b', 1, this}, {"♙", 'b', 2, this}, {" ", 'b', 3, this}, {" ", 'b', 4, this}, {" ", 'b', 5, this}, {" ", 'c', 6, this}, {"♟", 'b', 7, this}, {"♞", 'b', 8, this}}},
	
		{{{"♗", 'c', 1, this}, {"♙", 'c', 2, this}, {" ", 'c', 3, this}, {" ", 'c', 4, this}, {" ", 'c', 5, this}, {" ", 'c', 6, this}, {"♟", 'c', 7, this}, {"♝", 'c', 8, this}}},
	
		{{{"♕", 'd', 1, this}, {"♙", 'd', 2, this}, {" ", 'd', 3, this}, {" ", 'd', 4, this}, {" ", 'd', 5, this}, {" ", 'e', 6, this}, {"♟", 'd', 7, this}, {"♛", 'd', 8, this}}},
	
		{{{"♔", 'e', 1, this}, {"♙", 'e', 2, this}, {" ", 'e', 3, this}, {" ", 'e', 4, this}, {" ", 'e', 5, this}, {" ", 'e', 6, this}, {"♟", 'e', 7, this}, {"♚", 'e', 8, this}}},
	
		{{{"♗", 'f', 1, this}, {"♙", 'f', 2, this}, {" ", 'f', 3, this}, {" ", 'f', 4, this}, {" ", 'f', 5, this}, {" ", 'f', 6, this}, {"♟", 'f', 7, this}, {"♝", 'f', 8, this}}},
	
		{{{"♘", 'g', 1, this}, {"♙", 'g', 2, this}, {" ", 'g', 3, this}, {" ", 'g', 4, this}, {" ", 'g', 5, this}, {" ", 'g', 6, this}, {"♟", 'g', 7, this}, {"♞", 'g', 8, this}}},
	
		{{{"♖", 'h', 1, this}, {"♙", 'h', 2, this}, {" ", 'h', 3, this}, {" ", 'h', 4, this}, {" ", 'h', 5, this}, {" ", 'h', 6, this}, {"♟", 'h', 7, this}, {"♜", 'h', 8, this}}}
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

bool Board::isInsideBoardBounds(const Position pos) const {
	if (pos.x < boardRepresentation.size()) {
		if (pos.y < boardRepresentation[pos.x].size()) {
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










