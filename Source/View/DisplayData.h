//
//  DisplayData.h
//  SpriteFight
//
//  Created by Adam James Leuer on 6/28/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef DisplayData_h
#define DisplayData_h

#include <CoreGraphics/CoreGraphics.h>

#include "../Util/Vect.h"

/**
 * Only exists for debugging
 */
void inspectDisplayConfiguration() ;

/**
 * Holds information about the resolution and scaling of the current display
 */
struct DisplayData {
	
private:
	
	static bool isInit ;
	
	static bool hiDPI_referenceVal ;
	
	/**
	 * The display scaling factor.
	 * For example, if the system is running in Retina mode,
	 * this value will be 2.0
	 */
	static float displayScalingFactor_referenceVal ;
	
	static CGDirectDisplayID displayID ;
	static CGDisplayModeRef displayMode ;
	
	static void init() ;
	
	static vec2<unsigned> calculateScreenResolution() ;
	
	/**
	 * Used once to initialize displayScalingFactor
	 * For the sake of efficiency, reference displayScalingFactor
	 * instead of calling this.
	 */
	static void calculateDisplayScalingFactor() ; /* should only call this once ideally, just reference displayScalingFactor afterwards */
	
	
public:
	
	template<typename NumericType = unsigned>
	static vec2<NumericType> getScreenResolution() ;
	
	static double getScreenRefreshRate() ;
	
	/**
	 * Checks if running in Retina mode
	 */
	static bool hiDPI() ;
	
	/**
	 * The display scaling factor.
	 * For example, if the system is running in Retina mode,
	 * this value will be 2.0
	 */
	template <typename NumericType = float>
	static NumericType getDisplayScalingFactor() ;
	
} ;

template<typename NumericType>
vec2<NumericType> DisplayData::getScreenResolution() {
	return calculateScreenResolution() ;
}

template <typename NumericType>
NumericType DisplayData::getDisplayScalingFactor() {
	
	if (isInit == false) {
		init() ;
		return DisplayData::displayScalingFactor_referenceVal ;
	}
	else {
		return displayScalingFactor_referenceVal ;
	}
}




#endif
