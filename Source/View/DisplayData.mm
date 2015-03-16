
#ifdef __APPLE__


#include "../Util/Util.hpp"

#include "DisplayData.h"
#include "Decl_Apple.h"


vec2<unsigned> DisplayData::calculateScreenResolution() {
	NSScreen * screen = [NSScreen mainScreen] ;
	auto vf = [screen visibleFrame] ;
	
	unsigned x = vf.size.width + vf.origin.x ;
	unsigned y = vf.size.height + vf.origin.y ;
	return vec2<unsigned>{x, y} ;
}

void DisplayData::calculateDisplayScalingFactor() {
	float displayScale = 1.0 ;
	
    if ([[NSScreen mainScreen] respondsToSelector:@selector(backingScaleFactor)]) {
        screens = [NSScreen screens];
        for (int i = 0; i < [screens count]; i++) {
            float s = [[screens objectAtIndex:i] backingScaleFactor];
            if (s > displayScale)
                displayScale = s;
        }
    }
    displayScalingFactor_referenceVal = displayScale ;
}

#endif