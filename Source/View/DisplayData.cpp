

#include "../Util/Util.hpp"

#include "DisplayData.h"

void inspectDisplayConfiguration ()
{
	auto refreshRate = DisplayData::getScreenRefreshRate();
}


bool DisplayData::isInit = false;

bool DisplayData::displayIsHighDPI;

float DisplayData::displayScalingFactor;

void DisplayData::init ()
{
	/* init displayScalingFactor */
	calculateDisplayScalingFactor();

	/* init displayIsHighDPI */
	displayIsHighDPI = ((displayScalingFactor == 2.0) ? true : false);

	isInit = true;
}

bool DisplayData::IsHighDPI ()
{
	if (isInit == false)
	{
		init();
	}

	return DisplayData::displayIsHighDPI;
}

#ifndef __APPLE__

/* non-OS X implementations: */

double DisplayData::getScreenRefreshRate ()
{
	//todo implement
	return 120;
}
 
vec2<unsigned> DisplayData::calculateScreenResolution()
{
	//todo implement
	return {1280, 720 };
}

void DisplayData::calculateDisplayScalingFactor()
{
	//todo implement
	displayScalingFactor = 2.5;
}

#endif




