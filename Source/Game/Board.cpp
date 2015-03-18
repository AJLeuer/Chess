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
	piece((other.piece != nullptr) ? Piece::init(other.piece->getSymbol(), & other.position) : nullptr)
{
	
}

Square::Square(const char file, const unsigned rank) :
	rankAndFile(file, rank),
	position(rankAndFile),
	piece(nullptr)
{
	registerForPieceMovement() ;
}

Square::Square(Piece * piece, const char file, const unsigned rank) :
	Square(file, rank)
{
	this->piece = piece ;
}

Square::Square(const string & pieceSymbol, const char file, const unsigned rank) :
	Square(Piece::init(stringConverter.from_bytes(pieceSymbol), & position), file, rank) {}

Square & Square::operator = (const Square & other) {
	if (this != & other) {
		this->rankAndFile = other.rankAndFile ;
		this->position = other.position ;
		
		if (this->piece != nullptr) {
			delete this->piece ;
		}
		
		if (other.piece != nullptr) {
			piece = Piece::init(other.piece->getSymbol(), other.piece->getPosition()) ;
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
	Notification<Piece, Position> notifyWhenPieceMovesHere (EventType::pieceArriving, setCurrentP, this->getPosition()) ;
	
	auto clearCurrentP = std::bind(&Square::clearCurrentPiece, this, _1) ;
	Notification<Piece, Position> notifyWhenPieceLeaves (EventType::pieceLeaving, clearCurrentP, this->getPosition()) ;
	
	notifyWhenPieceMovesHere.registerForCallback() ;
	notifyWhenPieceLeaves.registerForCallback() ;
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

const Square * Board::getSquare(unsigned rank, char file) const {
	return & boardRepresentation[0][0] ; //todo implement properly
}

const Square * Board::getSquare(unsigned arrIndexX, unsigned arrIndexY) const {
	return & boardRepresentation[arrIndexX][arrIndexY] ;
}

Board::Board() :
	boardRepresentation{{
		{{{"♖", 'a', 1}, {"♘", 'b', 1}, {"♗", 'c', 1}, {"♕", 'd', 1}, {"♔", 'e', 1}, {"♗", 'f', 1}, {"♘", 'g', 1}, {"♖", 'h', 1}}},
		
		{{{"♙", 'a', 2}, {"♙", 'b', 2}, {"♙", 'c', 2}, {"♙", 'd', 2}, {"♙", 'e', 2}, {"♙", 'f', 2}, {"♙", 'g', 2}, {"♙", 'h', 2}}},
		
		{{{" ", 'a', 3}, {" ", 'b', 3}, {" ", 'c', 3}, {" ", 'd', 3}, {" ", 'e', 3}, {" ", 'f', 3}, {" ", 'g', 3}, {" ", 'h', 3}}},
		
		{{{" ", 'a', 4}, {" ", 'b', 4}, {" ", 'c', 4}, {" ", 'd', 4}, {" ", 'e', 4}, {" ", 'f', 4}, {" ", 'g', 4}, {" ", 'h', 4}}},
		
		{{{" ", 'a', 5}, {" ", 'b', 5}, {" ", 'c', 5}, {" ", 'd', 5}, {" ", 'e', 5}, {" ", 'f', 5}, {" ", 'g', 5}, {" ", 'h', 5}}},
		
		{{{" ", 'a', 6}, {" ", 'b', 6}, {" ", 'c', 6}, {" ", 'd', 6}, {" ", 'e', 6}, {" ", 'f', 6}, {" ", 'g', 6}, {" ", 'h', 6}}},
		
		{{{"♟", 'a', 7}, {"♟", 'b', 7}, {"♟", 'c', 7}, {"♟", 'd', 7}, {"♟", 'e', 7}, {"♟", 'f', 7}, {"♟", 'g', 7}, {"♟", 'h', 7}}},
		
		{{{"♜", 'a', 8}, {"♞", 'b', 8}, {"♝", 'c', 8}, {"♛", 'd', 8}, {"♚", 'e', 8}, {"♝", 'f', 8}, {"♞", 'g', 8}, {"♜", 'h', 8}}}
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










