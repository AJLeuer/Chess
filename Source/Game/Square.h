//
//  Square.h
//  Chess
//
//  Created by Adam James Leuer on 3/12/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#ifndef Chess_Square_h
#define Chess_Square_h

using namespace std ;


struct Square {
	
protected:
	
	const RankAndFile rankAndFile ;
	
	const Position position ;
	
	Piece * piece ;
	
	friend class Game ;
	
	friend class Board ;
	
public:
	
	Square(const char file, const unsigned rank) ;
	
	Square(Piece * piece, const char file, const unsigned rank) ;
	
	Square(const string & pieceSymbol, const char file, const unsigned rank) ;
	
	void setCurrentPiece(Piece * piece) { this->piece = piece ; this->piece->setCurrentPosition(& this->position) ;}
	
	void clearCurrentPiece(Piece * ignored = nullptr) { this->piece->setCurrentPosition(nullptr) ; this->piece = nullptr ; }
	
	bool isEmpty() const { return piece == nullptr ; }
	
	const Position & getPosition() const { return this->position ; }
	
	const Piece * getPiece() const { return piece ; }
	
	/**
	 * Registers this Square to be notified when a Piece moves to it
	 * or leaves it.
	 */
	void registerForPieceMovement() ;
	
	friend std::ostream & operator<< (std::ostream & , const Square &) ;
	
	friend basic_ostream<wchar_t> & operator << (basic_ostream<wchar_t> &, const Square &) ;
	
} ;

#endif
