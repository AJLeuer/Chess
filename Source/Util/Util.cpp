//
//  Util.cpp
//  Chess
//
//  Created by Adam James Leuer on 2/17/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#include "Util.h"

wstring_convert<std::codecvt_utf8<wchar_t>> stringConverter ;

string convertToString(const wstring & wide_string) {
	return stringConverter.to_bytes(wide_string) ;
}