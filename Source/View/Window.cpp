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

ChessWindow & ChessWindow::operator = (const ChessWindow & other) {
	if (this != & other) {
		this->text = other.text ;
	}
	return * this ;
}

VideoMode ChessWindow::videoMode = setVideoMode() ;

VideoMode ChessWindow::setVideoMode() {
	vec2<float> baseWindowSize {static_cast<float>(mainWindowSize.x), static_cast<float>(mainWindowSize.y)} ;
	float dpiScale = DisplayData::getDisplayScalingFactor<float>() ;
	vec2<float> scaledWindowSize = baseWindowSize * dpiScale ;
	VideoMode vm(scaledWindowSize.x, scaledWindowSize.y) ;
	return vm ;
}

Font ChessWindow::font = ChessWindow::initFont() ;

Font & ChessWindow::initFont() {
	font.loadFromFile("Menlo-Regular.ttf") ;
	return font ;
}


ChessWindow::ChessWindow(const string & title) :
	RenderWindow(videoMode, title, Style::Default, ContextSettings())
{
	text.setFont(font) ;
	text.setCharacterSize(60) ;
}



