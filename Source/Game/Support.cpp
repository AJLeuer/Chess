//
//  Support.cpp
//  Chess
//
//  Created by Adam James Leuer on 8/29/15.
//  Copyright © 2015 Adam James Leuer. All rights reserved.
//

#include "Support.h"


namespace Chess {


	string RankAndFile::toString () const {
		stringstream ss;
		ss << * this;
		return ss.str();
	}

	wstring RankAndFile::toWString () const {
		wstringstream ss;
		ss << * this;
		return ss.str();
	}


	ostream & operator << (ostream & out, const RankAndFile & rf) {
		out << rf.file << rf.rank;
		return out;
	}

	wostream & operator << (wostream & out, const RankAndFile & rf) {
		out << rf.file << rf.rank;
		return out;
	}


	GameRecordEntry::AlgrebraicNotation::operator wstring () const {

		wstring str {pieceSymbol};
		str += static_cast<wstring>(destination);

		return str;
	}


}


