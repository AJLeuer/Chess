//
//  Window.h
//  Chess
//
//  Created by Adam James Leuer on 2/13/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#ifndef __Chess__Window__
#define __Chess__Window__

#include <iostream>
#include <string>

#include <OpenGL/gl.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../Game/Chess.h"

#include "../Util/Vect.h"
#include "../Util/Color.h"

#include "Config.h"
#include "DisplayData.h"

using namespace std ;
using namespace sf ;

class ChessWindow : public sf::RenderWindow {
	
protected:
	
	static VideoMode videoMode ;
	
	static VideoMode & setVideoMode() ;
	
	/**
	 * The Font used for displaying most text onscreen.
	 * 
	 * Currently using Apple's menlo font (which is based on Bitstream Vera Sans
	 * mono), until I can find something better suited for chess
	 */
	static Font & font ;
	
	/**
	 * @note Need to create a quick initialization function
	 * for the SFML Font type here, since their constructors don't
	 * allow creating directly from a file, and we need to statically
	 * initialize font
	 */
	static Font & initFont() ;
	
	Text text ;
	
public:
	
	ChessWindow(const ChessWindow & other) = delete ;
	
	ChessWindow(const string & title = "Chess", const TrueColor backgroundColor = Chess::windowBackgroundColor) ;
	
	~ChessWindow() {}
	
	ChessWindow & operator = (const ChessWindow & other) = delete ;

	void display() ;
	
	void setBackgroundColor(const TrueColor color) ;
	
	template<class StringType>
	void displayText(const StringType & chars, const TrueColor color, const vec2<int> where) ;
	
};

template<class StringType>
void ChessWindow::displayText(const StringType & chars, const TrueColor color, const vec2<int> where) {
	
	text.setString(chars) ;
	text.setColor(color) ;
	
	auto textSize = text.getLocalBounds() ;
	
	vec2<int> middle = {static_cast<int>((textSize.width / 2)), static_cast<int>((textSize.height / 2)) } ;
	
	vec2<int> adjustedPos = where - middle ;
	
	text.setPosition(convertToSFMLVectorType<float, int>(adjustedPos)) ;
	
	this->RenderWindow::draw(text) ;
}

#endif /* defined(__Chess__Window__) */
