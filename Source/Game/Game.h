//
//  Game.h
//  Chess
//
//  Created by Adam James Leuer on 2/8/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#ifndef __Chess__Game__
#define __Chess__Game__

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>

#include <SFML/Window/Mouse.hpp>

#include "../Util/Config.h"
#include "../Util/Util.h"
#include "../Util/Random.hpp"

#include "Support.h"
#include "Board.h"
#include "Player.h"

#include "../View/Window.h"

using namespace std;

int main (int, char **);

namespace Chess {

	class Game_Base {

	protected:

		unsigned long gameLoops = 0;

		/** Note: Must be initialized first */
		Board board;

		Player * player0;

		Player * player1;

		virtual void advanceGame (Player * currentPlayer = nullptr, bool overrideMoveDecision = false,
		                          MoveIntent * overridingMove = nullptr) = 0;

		void commitMove (MoveIntent & move, bool recordMove = true);

		vector <GameRecordEntry> gameRecord;


		friend class Player;


		friend class AI;


		friend int::main (int, char **); //for debug only

	public:

		Game_Base ();

		/**
		 * Copy constructor. Right now, the only use is creating temporary games to run simulations
		 */
		Game_Base (const Game_Base & other);

		virtual ~Game_Base ();

		Game_Base & operator = (const Game_Base & other) = delete;

		virtual void playGame () = 0;

		/**
		 * For development and debugging
		 */
		virtual void playDebugGame () = 0;

		Board getBoard () { return this->board; }

		/**
		 * @return The Player with the same color as the Player passed in as an argument
		 */
		Player * getMatchingPlayer (const Player & player) {
			return (player.getColor() == player0->getColor()) ? player0 : player1;
		}

		/**
		 * @return The Player with the color opposite the Player passed in as an argument
		 */
		Player * getOpponentPlayer (const Player & player) {
			return (player.getColor() != player0->getColor()) ? player0 : player1;
		}

		/**
		 * @return A MoveIntent object with the matching Piece found by calling this->board.findMatch(move.piece), such that the returned
		 * MoveIntent could be used to make the same move but in this game
		 */
		MoveIntent tranlateMoveIntent (const MoveIntent & move);

	};


	class Game : public Game_Base {

	protected:

		ChessWindow window;

		void advanceGame (Player * currentPlayer = nullptr, bool overrideMoveDecision = false,
		                  MoveIntent * overridingMove = nullptr) override;


	public:

		Game ();

		Game (const Game_Base & other);

		Game (const Game & other);

		~Game () override {}

		Game & operator = (const Game & other) = delete;

		void playGame () override;

		/**
		 * For development and debugging
		 */
		void playDebugGame () override;

		void display ();

		void monitorMouse ();


	};


	class SimulatedGame : public Game_Base {

	protected:

		void advanceGame (Player * currentPlayer = nullptr, bool overrideMoveDecision = false,
		                  MoveIntent * overridingMove = nullptr) override;

	public:

		SimulatedGame ();

		SimulatedGame (const Game_Base & other);

		SimulatedGame (const SimulatedGame & other);

		~SimulatedGame () override {}

		SimulatedGame & operator = (const SimulatedGame & other) = delete;

		void playGame () override;

		/**
		 * For development and debugging
		 */
		void playDebugGame () override;
	};


}


#endif /* defined(__Chess__Game__) */
