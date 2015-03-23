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

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Config.h"
#include "Position.h"
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
	static Font font ;
	
	/**
	 * @note Need to create a quick initialization function
	 * for the SFML Font type here, since their constructors don't
	 * allow creating directly from a file, and we need to statically
	 * initialize font
	 */
	static Font & initFont() ;
	
	Text text ;
	
public:
	
	ChessWindow(const ChessWindow & other) :
		text(other.text)
	{
		
	}
	
	ChessWindow(const string & title = "Chess") ;
	
	~ChessWindow() {}
	
	ChessWindow & operator = (const ChessWindow & other) ;
	
	template<class StringType>
	void displayText(const StringType & chars, const Position where) ;
	
};

template<class StringType>
void ChessWindow::displayText(const StringType & chars, const Position where) {
	
	text.setString(chars) ;
	text.setColor(sf::Color(173, 255, 0)) ;
	
	auto textSize = text.getLocalBounds() ;
	
	Position middle = {static_cast<int>((textSize.width / 2)), static_cast<int>((textSize.height / 2)) } ;
	
	Position adjustedPos = where - middle ;
	
	text.setPosition(convertToSFMLVectorType<float, int>(adjustedPos)) ;
	
	this->RenderWindow::draw(text) ;
}

#endif /* defined(__Chess__Window__) */
