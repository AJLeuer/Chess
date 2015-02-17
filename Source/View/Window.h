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

using namespace std ;
using namespace sf ;

class ChessWindow : public sf::RenderWindow {
	
protected:
	
	static VideoMode videoMode ;
	
	/**
	 * The Font used for displaying most text onscreen.
	 * Using <a href="http://developer.android.com/design/style/typography.html">Google's Roboto font</a> by default.
	 *
	 * @see <a href="http://developer.android.com/design/style/typography.html"> Google's developer page on Roboto</a>
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
	
	ChessWindow(const string & title = "Chess") ;
	
	void draw(const string & chars) ;
	void draw(const wstring & chars) ;
	
};

#endif /* defined(__Chess__Window__) */
