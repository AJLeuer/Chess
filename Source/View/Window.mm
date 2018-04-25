//
//  Window.m
//  Chess
//
//  Created by Adam James Leuer on 4/23/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#ifdef __APPLE__


#import <Foundation/Foundation.h>
#import <AppKit/NSWindow.h>
#import <AppKit/NSColor.h>
#import <AppKit/NSOpenGLView.h>
#import <AppKit/NSOpenGL.h>


#include "Window.h"


namespace sf {
	namespace priv {
		class WindowImplCocoa;
	}
}

@class SFSilentResponder;


@interface SFOpenGLView : NSOpenGLView {
	sf::priv::WindowImplCocoa * m_requester;      ///< View's requester
	BOOL m_useKeyRepeat;   ///< Key repeat setting
	BOOL m_mouseIsIn;      ///< Mouse positional state
	NSTrackingArea * m_trackingArea;   ///< Mouse tracking area
	BOOL m_fullscreen;     ///< Indicate whether the window is fullscreen or not
	CGFloat m_scaleFactor;    ///< Display scale factor (e.g. 1x for classic display, 2x for retina)

	// Hidden text view used to convert key event to actual chars.
	// We use a silent responder to prevent sound alerts.
	SFSilentResponder * m_silentResponder;

	NSTextView * m_hiddenTextView;
}

@end


@interface CustomOpenGLView : SFOpenGLView {

}

- (instancetype)initByCopy:(SFOpenGLView *)other;

+ (void)copy:(SFOpenGLView *)other to_self:(CustomOpenGLView *)to_self;

- (BOOL)isOpaque;


//- (void)drawRect:(NSRect)dirtyRect;

@end


@implementation CustomOpenGLView {

}

- (instancetype)initByCopy:(SFOpenGLView *)other {
	self = [super init];

	[CustomOpenGLView copy:other to_self:self];

	auto context = [self openGLContext];
	const int opacity = int(0);
	[context setValues:& opacity forParameter:NSOpenGLCPSurfaceOpacity];
	return self;
}


+ (void)copy:(SFOpenGLView *)other to_self:(CustomOpenGLView *)to_self {
	to_self->m_requester = other->m_requester;
	to_self->m_useKeyRepeat = other->m_useKeyRepeat;
	to_self->m_mouseIsIn = other->m_mouseIsIn;
	to_self->m_trackingArea = other->m_trackingArea;
	to_self->m_fullscreen = other->m_fullscreen;
	to_self->m_scaleFactor = other->m_scaleFactor;
	to_self->m_silentResponder = other->m_silentResponder;
	to_self->m_hiddenTextView = other->m_hiddenTextView;

	[to_self setOpenGLContext:[other openGLContext]];
	[[to_self openGLContext] setView:to_self];
	[to_self setPixelFormat:[other pixelFormat]];
}

- (BOOL)isOpaque {
	return NO;
}

/*
- (void)drawRect:(NSRect)dirtyRect {
	//[[NSColor clearColor] set];
	[super drawRect:dirtyRect] ;
} */

@end


namespace Chess {

	ChessWindow::ChessWindow (const string & title, const TrueColor backgroundColor) :
		RenderWindow(videoMode, title, sf::Style::Default, ContextSettings())
	{

		text.setFont(font);
		text.setCharacterSize(60);

		/* the remaining lines implement window background transparency on OS X */
		NSWindow * this_window = (__bridge NSWindow *) (this->getSystemHandle());
		SFOpenGLView * view = [this_window contentView];
		CustomOpenGLView * replacementView = [[CustomOpenGLView alloc] initByCopy:view];
		this_window.contentView = replacementView;
		this->setBackgroundColor(backgroundColor);
	}

	void ChessWindow::display () {
		/* for some reason we need to call the native update method as well as SFML's */
		NSWindow * this_window = (__bridge NSWindow *) (this->getSystemHandle());
		[this_window displayIfNeeded];

		this->RenderWindow::display();
	}


	void ChessWindow::setBackgroundColor (const TrueColor color) {

		NSWindow * this_window = (__bridge NSWindow *) (this->getSystemHandle());

		NSColor * backgroundColor = [NSColor colorWithDeviceRed:color.R_float() green:color.G_float() blue:color.B_float() alpha:color.A_float()];

		[this_window setOpaque:NO];
		[this_window setBackgroundColor:backgroundColor];
	}

}


#endif
