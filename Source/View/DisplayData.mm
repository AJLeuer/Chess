
#ifdef __APPLE__

#include "../Util/Util.hpp"

#include "DisplayData.h"
#include "Decl_Apple.h"


vec2<unsigned> DisplayData::calculateScreenResolution() {
	NSScreen * screen = [NSScreen mainScreen] ;
	auto vf = [screen visibleFrame] ;
	
	auto x = vf.size.width + vf.origin.x ;
	auto y = vf.size.height + vf.origin.y ;
	return vec2<unsigned>{static_cast<unsigned>(x), static_cast<unsigned>(y)} ;
}

void DisplayData::calculateDisplayScalingFactor() {
	float displayScale = 1.0 ;
	
    if ([[NSScreen mainScreen] respondsToSelector:@selector(backingScaleFactor)]) {
        screens = [NSScreen screens];
        for (int i = 0; i < [screens count]; i++) {
			float s = static_cast<float>([[screens objectAtIndex:i] backingScaleFactor]);
            if (s > displayScale)
                displayScale = s;
        }
    }
    displayScalingFactor_referenceVal = displayScale ;
}


#endif