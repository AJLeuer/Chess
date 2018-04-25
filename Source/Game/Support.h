//
//  Support.hpp
//  Chess
//
//  Created by Adam James Leuer on 8/29/15.
//  Copyright © 2015 Adam James Leuer. All rights reserved.
//

#ifndef Support_h
#define Support_h

#include "Piece.h"

#include "../Util/Vect.h"

using namespace std;

namespace Chess {

/**
 * Used to represents a position on the chess board in algebraic notation, where the first square
 * is a1, etc. Can be explicitely and implicitely converted to a simd_vector_2<int> (where a1 would equal the 2-vector (0, 0)), and vice versa.
 *
 * @see Wikipedia's article on <a href="http://en.wikipedia.org/wiki/Algebraic_notation_(chess)">Algebraic notation (chess)</a>
 */
	struct RankAndFile {

	protected:

		static constexpr char FILE_FIRST {'a'};

		static constexpr char FILE_LAST {'h'};

		static constexpr unsigned short RANK_FIRST {1};

		static constexpr unsigned short RANK_LAST {8};

		static constexpr char convertToFile (const unsigned x) {
			char c = static_cast<char>(x + lowerCaseA);
			return c;
		}

		static constexpr unsigned convertToRank (const unsigned y) {
			auto ret = y + 1;
			return ret;
		}

		char file;

		unsigned rank;

		friend struct Square;

		friend void runChessGameTests ();

	public:

		RankAndFile () {}

		constexpr RankAndFile (const char & file, const unsigned rank) : file(file), rank(rank) {}

		constexpr RankAndFile (const vec2 <int> & pos) : RankAndFile(convertToFile(pos[0]), convertToRank(pos[1])) {}

		constexpr RankAndFile (const RankAndFile & other) : RankAndFile(other.file, other.rank) {}

		/* User-provided destructors not allowed for literal types */
		constexpr RankAndFile & operator = (const RankAndFile & rhs) {
			if (this != & rhs) {
				this->file = rhs.file;
				this->rank = rhs.rank;
			}
			return * this;
		}

		constexpr RankAndFile & operator = (const vec2 <int> & pos) {
			RankAndFile other(pos);
			* this = other;
			return * this;
		}

		constexpr operator vec2 <int> () const {
			return convertToPosition();
		}

		operator string () const { return toString(); }

		operator wstring () const { return toWString(); }

		constexpr vec2 <int> convertToPosition () const {

			/* Chess ranks start with 1 at the bottom and increase as we move up the board,
			 but window coordinates start with y = 0 at the top, and y increases with descent.
			 So to convert our rank to a y-coordinate, we'll need to essentially swap each rank
			 value across the horizontal axis, and subtract 1 from it (rank values start at 1, but
			 vec2<int> values start at 0)

			 Chess files can be converted from x-coordinates by subtracting the Unicode decimal value for 'a' -
			 97 - from the decimal value of the char representing the rank. Applied to 'a', this gives an x-coord
			 of 0, 'b' outputs as 1, 'c' is 2, etc.
			 */

			//convert rank to y:
			int y = this->getRank();
			y = (RANK_LAST - y) % RANK_LAST;

			//convert file to x:
			int x = static_cast<int>(getFile() - lowerCaseA);

			return vec2 <int> {x, y};
		}

		string toString () const;

		wstring toWString () const;

		constexpr const char getFile () const { return file; }

		constexpr const unsigned & getRank () const { return rank; }

		friend std::ostream & operator << (ostream &, const RankAndFile &);

		friend std::wostream & operator << (wostream &, const RankAndFile &);

	};


	struct GameRecordEntry {

		struct AlgrebraicNotation {

			const wchar_t pieceSymbol;

			const RankAndFile destination;

			AlgrebraicNotation (const Piece & piece, const RankAndFile & destination) :
					pieceSymbol(piece.getSymbol()), destination(destination) {}

			operator wstring () const;

		} algrebraicNotation;


		RankAndFile startingPosition;

		GameRecordEntry (const Piece & piece, const RankAndFile & destination) :
				algrebraicNotation(piece, destination), startingPosition(* piece.getPosition()) {}

	};


}

#endif /* Support_hpp */
