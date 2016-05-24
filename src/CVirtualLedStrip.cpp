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
#include <string.h>
using namespace std;
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
m_bIsRunning(false), m_eRunStateShootingStar(eRunStateShootingStarIdle), m_uOffset(auOffset), m_uLength(auLength),
Adafruit_NeoPixel(auLength * DF_MVDATA_NUM_VIRTUAL_STRIPS_PER_REAL_STRIP, auPinNumber, atLedType)
{

	Serial.println("Constructor");
}

CVirtualLedStrip::CVirtualLedStrip(CVirtualLedStrip& acLedStrip)
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

void CVirtualLedStrip::runShootingStar(void)
{

	switch(m_eRunStateShootingStar)
	{
	case eRunStateShootingStarIdle:
		// do nothing
		break;
	case eRunStateShootingStarWaiting:

		m_uWaitCounter--;
		if(m_uWaitCounter == 0)
		{
			m_eRunStateShootingStar = eRunStateShootingStarOutput;
		}
		char sWait[64];
		sprintf(sWait, "Waiting%u: %u %d", this, m_uWaitCounter, m_bIsRunning);
		Serial.println(sWait);

		break;
	case eRunStateShootingStarOutput:
		this->handleShootingStarOutput();
		m_eRunStateShootingStar = eRunStateShootingStarNextStep;
		char sOut[64];
		sprintf(sOut, "Output%u", this);
		Serial.println(sOut);

		break;
	case eRunStateShootingStarNextStep:

		char sNext[64];
		sprintf(sNext, "NextStep%u", this);
		Serial.println(sNext);

		if(m_uCurrentStep < (DF_MVDATA_NUM_LEDS_PER_VIRTUAL_STRIP + DF_MVDATA_MAX_AFTERGLOW - 1))
		{
			/* if current step is not last step: wait until countdown has finished */
			m_eRunStateShootingStar = eRunStateShootingStarWaiting;

			m_uCurrentStep++;
			m_uWaitCounter = g_uStepDelays[m_uCurrentStep];
		}
		else
		{
			/* if current step is last step: go into idle until a new step is started */
			m_eRunStateShootingStar = eRunStateShootingStarIdle;

			m_bIsRunning = false;
			m_uCurrentStep = 0;
			m_uWaitCounter = g_uStepDelays[0];
		}
		break;
	}
}

void CVirtualLedStrip::handleShootingStarOutput(void)
{
	for(uint8_t uLoop = 0; uLoop < DF_MVDATA_NUM_LEDS_PER_VIRTUAL_STRIP; uLoop++)
	{
		// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
		this->setPixelColor(uLoop, g_uLightIntensityMat[m_uCurrentStep][uLoop], g_uLightIntensityMat[m_uCurrentStep][uLoop], g_uLightIntensityMat[m_uCurrentStep][uLoop]);

//		m_pcLpd->setPixelColor(uLoop, g_uLightIntensityMat[m_uCurrentStep][uLoop], g_uLightIntensityMat[m_uCurrentStep][uLoop], g_uLightIntensityMat[m_uCurrentStep][uLoop]);
	}

	this->show(); // This sends the updated pixel color to the hardware.
//	m_pcLpd->show();
}

bool CVirtualLedStrip::isRunning(void)
{
	return m_bIsRunning;
}

bool CVirtualLedStrip::startRunning(void)
{
//	if(!m_bIsRunning)
//	{
		m_bIsRunning = true;
		char sRun[32];
		sprintf(sRun, "StarRunning%u %u", this, m_bIsRunning);
		Serial.println(sRun);
		m_uCurrentStep = 0;
		m_uWaitCounter = 100;//g_uStepDelays[0];
		m_eRunStateShootingStar = eRunStateShootingStarWaiting;
//	}


}
