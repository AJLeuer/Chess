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


VideoMode ChessWindow::videoMode = VideoMode::getDesktopMode() ;

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

void ChessWindow::draw(const string & chars, const Position where) {
	text.setString(chars) ;
	text.setPosition(convertToSFMLVectorType<float, unsigned>(where)) ;
	this->RenderWindow::draw(text) ;
}

void ChessWindow::draw(const wstring & chars, const Position where) {
	text.setString(chars) ;
	text.setPosition(convertToSFMLVectorType<float, unsigned>(where)) ;
	this->RenderWindow::draw(text) ;
}

