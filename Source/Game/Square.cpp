//
//  Square.cpp
//  Chess
//
//  Created by Adam James Leuer on 8/29/15.
//  Copyright © 2015 Adam James Leuer. All rights reserved.
//

#include "Square.h"

using namespace std ;

namespace Chess {
	
	Square::Square(const Square & other) :
		position(other.position),
		/* Don't copy other's board pointer */
		piece((other.piece == nullptr) ? nullptr : Piece::initCopy(*other.piece))
	{
		if (piece != nullptr) {
			this->piece->setSquare(this) ;
		}
	}
	
	Square::Square(const char file, const unsigned rank, Board * board) :
		position(static_cast<vec2<int>>(RankAndFile(file, rank))),
		board(board),
		piece(nullptr)
	{
		
	}
	
	Square::Square(const char file, const unsigned rank, Board * board, Piece * piece) :
		Square(file, rank, board)
	{
		this->piece = piece ;
	}
	
	Square::Square(const char file, const unsigned rank, Board * board, const wchar_t pieceSymbol) :
		Square(file, rank, board)
	{
		this->piece = Piece::init(pieceSymbol, this) ; /* this can't be included in the initializer (i.e. can't pass the call to
														Piece::init() as the piece argument for Square(const char, const unsigned, Board *, Piece *).
														This is because the piece returned from Piece::init() would be created before our position
														was initiialized, and thus the Piece's startingPosition would be created with garbage values.
														So instead we just delegate to Square(const char, const unsigned, Board *) (i.e. no Piece * arg),
														then initialize piece ourself, once it's safe */
		
	}
	
	Square::~Square() {
		destroyCurrentPiece() ; //only deletes if non-null
	}
	
	
	void Square::receiveMovingPiece(Piece * pieceMovingTo) {
		if (this->isOccupied()) {
			destroyCurrentPiece() ;
		}
		clearCurrentPiece(this->piece) ;
		setCurrentPiece(pieceMovingTo) ;
	}
	
	void Square::setCurrentPiece(Piece * pieceMovingTo) {
		this->piece = pieceMovingTo ;
		piece->setSquare(this) ;
	}
	
	void Square::clearCurrentPiece(Piece * toClear) {
		if (this->piece != toClear) { //debug code
			;
		}
		if (this->piece == toClear) {
			if (this->piece != nullptr) {
				this->piece->setSquare(nullptr) ;
			}
			
			this->piece = nullptr ;
		}
	}
	
	void Square::destroyCurrentPiece() {
		
		if ((piece != nullptr) && (piece->isDeleted())) { /* debug code, remove */
			; //set breakpoint
		}
		
		
		if (piece != nullptr) { /* checking if deleted previously is debug code, remove it */
			if (piece->getSquareMutable() != nullptr) { //debug code
				assert(this->piece->getSquareMutable() == this) ;
			}
			this->piece->setSquare(nullptr) ;
			if (piece->isDeleted() == false) { //debug code
				delete this->piece ;
			}
		}
		
		piece = nullptr ;
	}


}