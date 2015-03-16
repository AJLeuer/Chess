//
//  Config.cpp
//  Chess
//
//  Created by Adam James Leuer on 3/16/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#include "Config.h"

string currentDirectory = "" ;

vec2<unsigned> mainWindowSize = setMainWindowSize() ;

vec2<unsigned> setMainWindowSize() {
	return DisplayData::getScreenResolution() ;
}
