

#include "../Util/Util.hpp"

#include "DisplayData.h"

void inspectDisplayConfiguration() {
	auto refreshRate = DisplayData::getScreenRefreshRate() ;
}


bool DisplayData::isInit = false ;

bool DisplayData::hiDPI_referenceVal ;

float DisplayData::displayScalingFactor_referenceVal ;

CGDirectDisplayID DisplayData::displayID = CGMainDisplayID() ;
CGDisplayModeRef DisplayData::displayMode = CGDisplayCopyDisplayMode(displayID) ;

void DisplayData::init() {
	
	/* init displayScalingFactor_referenceVal */
	calculateDisplayScalingFactor() ;
	
	/* init hiDPI_referenceVal */
	hiDPI_referenceVal = ((displayScalingFactor_referenceVal == 2.0) ? true : false) ;
	
	isInit = true ;
	
}

#ifndef __APPLE__

/* non-OS X implementations: */
 
vec2<unsigned> DisplayData::calculateScreenResolution() {
	//todo
}

void DisplayData::calculateDisplayScalingFactor() {
	//todo
}

#endif

double DisplayData::getScreenRefreshRate() {
	return CGDisplayModeGetRefreshRate(displayMode) ;
}

bool DisplayData::hiDPI() {
	
	if (isInit == false) {
		init() ;
		return DisplayData::hiDPI_referenceVal ;
	}
	else {
		return DisplayData::hiDPI_referenceVal ;
	}
	
}



