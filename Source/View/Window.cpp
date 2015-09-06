//
//  Window.cpp
//  Chess
//
//  Created by Adam James Leuer on 2/13/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#include "Window.h"

using namespace std ;
using namespace sf ;

Font & ChessWindow::font = ChessWindow::initFont() ;

VideoMode ChessWindow::videoMode = setVideoMode() ;

Font & ChessWindow::initFont() {
	static Font storedFont ;
	string mainFontFilePathCopy(mainFontFilePath) ; //debug code
	storedFont.loadFromFile(mainFontFilePath) ;
	return storedFont ;
}

VideoMode & ChessWindow::setVideoMode() {
	const vec2<unsigned> baseWindowSize {mainWindowSize.value.x, mainWindowSize.value.y} ;
	const float dpiScale (DisplayData::getDisplayScalingFactor<float>()) ;
	vec2<unsigned> scaledWindowSize { static_cast<unsigned>(baseWindowSize.value.x * dpiScale), static_cast<unsigned>(baseWindowSize.value.y * dpiScale) } ;
	videoMode = VideoMode(scaledWindowSize.value.x, scaledWindowSize.value.y) ;
	return videoMode ; //self assigns
}


#ifndef __APPLE__

/* Below are the (unfinished) implementations for non-Apple platforms */

ChessWindow::ChessWindow(const string & title, const TrueColor backgroundColor) :
	RenderWindow(videoMode, title, sf::Style::Default, ContextSettings())
{
	text.setFont(font) ;
	text.setCharacterSize(60) ;
	this->setBackgroundColor(backgroundColor) ;
}



void ChessWindow::setBackgroundColor(const TrueColor color) {
	//todo implement for non-Apple unix, win
}





#endif

