//
//  Player.h
//  Chess
//
//  Created by Adam James Leuer on 2/8/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#ifndef __Chess__Player__
#define __Chess__Player__

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <array>
#include <tuple>
#include <iterator>


#include "Chess.h"
#include "Piece.h"
#include "Board.h"


#include "../Util/tree.hh"
#include "../Util/Tree.hpp"
#include "../Util/Random.hpp"

using namespace std;

namespace Chess {


	class Player {

	protected:

		static unsigned long uniqueIDs;

		unsigned long ID;

		string name;

		Chess::Color color;

		Board * board;

		vector <Piece *> findOwnPiecesOnBoard (const Board & workingBoard) const;

		tree <MoveIntent> computeAllMoves (Game_Base & game, vector <Piece *> & piecesToSearchForMoves,
		                                   tree <MoveIntent> * decisionTree,
		                                   tree <MoveIntent>::sibling_iterator & decisionTreePosition,
		                                   tree <MoveIntent> * movesToCheck,
		                                   tree <MoveIntent>::sibling_iterator & currentMove,
		                                   unsigned currentDepth, const unsigned maxSearchDepth) const;

		Tree <MoveIntent> computeAllMoves2 (SimulatedGame & game, Tree <MoveIntent> & moveTree,
		                                    unsigned currentDepth, const unsigned maxDepth) const;


		friend class Game_Base;


		friend class Game;


		friend class SimulatedGame;


	public:

		/* Any other constructors should call this as a delegating constructor */
		explicit Player (Chess::Color color, Board * board);

		Player (const Player & other);

		/**
		 * Move constructor
		 */
		Player (Player && other);

		virtual ~Player ();

		Player & operator = (const Player & other) = delete;

		/**
		 * Move assignment operator
		 */
		Player & operator = (Player && other) = delete;

		Chess::Color getColor () const { return color; }

		void removePiece (Piece * piece);

		void registerForNotifications ();

		const Tree <MoveIntent> findAllMoves () const;

		virtual const MoveIntent decideNextMove () const = 0;

	};


	class Human : public Player {

	public:

		Human (Chess::Color color, Board * board) :
				Player(color, board) {}

		Human (const Player & other) : Player(other) {}

		const MoveIntent decideNextMove () const override;

	};


	class AI : public Player {


	protected:

		const MoveIntent findBestMoveForPiece (Piece * piece) const;


		friend class Game; //debug only

	public:

		AI (Chess::Color color, Board * board) :
				Player(color, board) {}

		AI (const Player & other) : Player(other) {}

		virtual const MoveIntent decideNextMove () const override;

		const MoveIntent chooseBestMove (Board & board) const;

		vector <MoveIntent> computeBestMoves (Board & board) const;
	};


	vector <MoveIntent> extractHighestValueMoves (const vector <MoveIntent> & moves);

	MoveIntent selectMoveAtRandom (const vector <MoveIntent> & moves);


}

#endif /* defined(__Chess__Player__) */






