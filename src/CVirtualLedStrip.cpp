/**----------------------------------------------------------------------------
	\file		CVirtualLedStrip.cpp
	\author		D. Wright
	\version	0

	\brief Class that implements a virtual LED strip.

	A virtual strip is a part of an actual LED strip.
	Each LED strip is being divided in multiple virtual substrips.
	Each of those virtual strips can be addressed the same way as the Adafruit_NeoPixel library.
	This class is a wrapper for Adafruit_NeoPixel so it each substrip can be addressed in the same
	fashion as Adafruit_NeoPixel.

  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* includes */
/*----------------------------------------------------------------------------*/
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include <CVirtualLedStrip.h>

/*----------------------------------------------------------------------------*/
/* definitions */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* global variables */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* forward declarations */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* implementations */
/*----------------------------------------------------------------------------*/
CVirtualLedStrip::CVirtualLedStrip(uint8_t auOffset, uint16_t n, uint8_t p, neoPixelType t)
{

}
CVirtualLedStrip::~CVirtualLedStrip(void)
{

}

void CVirtualLedStrip::begin(void)
{

}

void CVirtualLedStrip::show(void)
{

}

void CVirtualLedStrip::setPin(uint8_t p)
{

}

void CVirtualLedStrip::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
{

}

void CVirtualLedStrip::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{

}

void CVirtualLedStrip::setPixelColor(uint16_t n, uint32_t c)
{

}

void CVirtualLedStrip::setBrightness(uint8_t)
{

}

void CVirtualLedStrip::clear(void)
{

}

void CVirtualLedStrip::updateLength(uint16_t n)
{

}

void CVirtualLedStrip::updateType(neoPixelType t)
{

}

uint8_t* CVirtualLedStrip::getPixels(void) const
{

}

uint8_t CVirtualLedStrip::getBrightness(void) const
{

}

uint16_t CVirtualLedStrip::numPixels(void) const
{

}

uint32_t CVirtualLedStrip::Color(uint8_t r, uint8_t g, uint8_t b)
{

}

uint32_t CVirtualLedStrip::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{

}

uint32_t CVirtualLedStrip::getPixelColor(uint16_t n) const
{

}
