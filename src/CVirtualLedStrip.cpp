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
#include <MoveData.h>
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

/*----------------------------------------------------------------------------*/
/*!
	\pre
	None.

	\post
	The whole real LED strip is initialised.

	This function initialises a complete real led strip. This is done so that the virtual LED
	strip can simply access the partial strip by using an offset to the accessed pixel number.
*/
/*----------------------------------------------------------------------------*/
CVirtualLedStrip::CVirtualLedStrip(uint16_t auOffset, uint16_t auLength, uint8_t auPinNumber, neoPixelType atLedType):
m_bIsRunning(false), m_uOffset(auOffset), m_uLength(auLength), Adafruit_NeoPixel(auLength * DF_MVDATA_NUM_VIRTUAL_STRIPS_PER_REAL_STRIP, auPinNumber, atLedType)
{

}

CVirtualLedStrip::~CVirtualLedStrip(void)
{

}

void CVirtualLedStrip::setPixelColor(uint16_t auPixelNumber, uint8_t auRed, uint8_t auGreen, uint8_t auBlue)
{
	Adafruit_NeoPixel::setPixelColor(auPixelNumber + m_uOffset, auRed, auGreen, auBlue);
}

void CVirtualLedStrip::setPixelColor(uint16_t auPixelNumber, uint8_t auRed, uint8_t auGreen, uint8_t auBlue, uint8_t auWhite)
{
	Adafruit_NeoPixel::setPixelColor(auPixelNumber + m_uOffset, auRed, auGreen, auBlue, auWhite);
}

void CVirtualLedStrip::setPixelColor(uint16_t auPixelNumber, uint32_t auColour)
{
	Adafruit_NeoPixel::setPixelColor(auPixelNumber + m_uOffset, auColour);
}

void CVirtualLedStrip::setBrightness(uint8_t auBrightness)
{
	/* I think the most useful method to set the brightness is doing it via CVirtualLedStrip::getPixelColor()
	 * and CVirtualLedStrip::getPixelColor(), in order to avoid that the other virtual strips on the real strip
	 * are affected by the operation. But for now I don't think this is important. */
	Serial.println("CVirtualLedStrip::setBrightness() is currently not implemented!!");
}

void CVirtualLedStrip::clear(void)
{
	/* I think the most useful method to set the brightness is doing it via CVirtualLedStrip::setPixelColor()
	 * in order to avoid that the other virtual strips on the real strip are affected by the operation.
	 * But for now I don't think this is important. */
	Serial.println("CVirtualLedStrip::clear() is currently not implemented!!");
}

void CVirtualLedStrip::updateLength(uint16_t n)
{
	/* I don't think it makes sense to call the base method, since it might very well be possible that the strip
	 * has a "hole", now that the strip length is not equal to the maximum length of the strip. */
	Serial.println("CVirtualLedStrip::updateLength() is currently not implemented!!");
}

uint8_t* CVirtualLedStrip::getPixels(void) const
{
	/* Again I don't know yet how it is possible to get a pointer to the pixels on the real LED strip. */
	Serial.println("CVirtualLedStrip::getPixels() is currently not implemented!!");
}

uint16_t CVirtualLedStrip::numPixels(void) const
{
	return m_uLength;
}

uint32_t CVirtualLedStrip::getPixelColor(uint16_t auPixelNumber) const
{
	return Adafruit_NeoPixel::getPixelColor(auPixelNumber + m_uOffset);
}
