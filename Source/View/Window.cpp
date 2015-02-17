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
}

void ChessWindow::draw(const string & chars) {
	text.setString(chars) ;
	text.setPosition(800, 450) ;
	this->RenderWindow::draw(text) ;
}

void ChessWindow::draw(const wstring & chars) {
	text.setString(chars) ;
	text.setPosition(800, 450) ;
	this->RenderWindow::draw(text) ;
}

