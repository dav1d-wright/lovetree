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
#include <avr/pgmspace.h>
#include <MoveData.h>
#ifdef DF_FASTLED
#include <FastLED.h>
#endif
#ifdef DF_NEOPIXEL
#include <Adafruit_NeoPixel.h>
#endif
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
#ifdef DF_FASTLED
CVirtualLedStrip::CVirtualLedStrip(uint16_t auOffset, uint16_t auLength,  uint8_t auStripNumber, CRGB* apcLedStrip):
#elif defined(DF_NEOPIXEL)
CVirtualLedStrip::CVirtualLedStrip(uint16_t auOffset, uint16_t auLength,  uint8_t auStripNumber, Adafruit_NeoPixel* apcLedStrip):
#endif
m_bIsRunning(false), m_eRunStateShootingStar(eRunStateShootingStarIdle), m_uOffset(auOffset), m_uLength(auLength),
m_pcLedStrip(apcLedStrip), m_uStripNumber(auStripNumber)
{
	Serial.println("Constructor");
}

/*----------------------------------------------------------------------------*/
/*!
	\pre
	None.

	\post
	The whole real LED strip is initialised.

	Copy constructor.
	This function initialises a complete real led strip. This is done so that the virtual LED
	strip can simply access the partial strip by using an offset to the accessed pixel number.
*/
/*----------------------------------------------------------------------------*/
CVirtualLedStrip::CVirtualLedStrip(CVirtualLedStrip& acLedStrip)
{

}

/*----------------------------------------------------------------------------*/
/*!
	\pre
	None.

	\post
	None.

	Destructor
*/
/*----------------------------------------------------------------------------*/
CVirtualLedStrip::~CVirtualLedStrip(void)
{

}

/*----------------------------------------------------------------------------*/
/*!
	\pre
	Constructor has been called.

	\post
	Pixel colour is set.

	Changes are only visible after calling CVirtualLedStrip::show().
*/
/*----------------------------------------------------------------------------*/
void CVirtualLedStrip::setPixelColor(uint16_t auPixelNumber, uint8_t auRed, uint8_t auGreen, uint8_t auBlue)
{
#ifdef DF_NEOPIXEL
	m_pcLedStrip->setPixelColor(auPixelNumber + m_uOffset, auRed, auGreen, auBlue);
#elif defined(DF_FASTLED)
	m_pcLedStrip[auPixelNumber + m_uOffset].red = auRed;
	m_pcLedStrip[auPixelNumber + m_uOffset].green = auGreen;
	m_pcLedStrip[auPixelNumber + m_uOffset].blue = auBlue;
#endif

}

#ifdef DF_NEOPIXEL
/*----------------------------------------------------------------------------*/
/*!
	\pre
	Constructor has been called.

	\post
	Pixel colour is set.

	Changes are only visible after calling CVirtualLedStrip::show().
*/
/*----------------------------------------------------------------------------*/
void CVirtualLedStrip::setPixelColor(uint16_t auPixelNumber, uint8_t auRed, uint8_t auGreen, uint8_t auBlue, uint8_t auWhite)
{
	m_pcLedStrip->setPixelColor(auPixelNumber + m_uOffset, auRed, auGreen, auBlue, auWhite);
}

/*----------------------------------------------------------------------------*/
/*!
	\pre
	Constructor has been called.

	\post
	Pixel colour is set.

	Changes are only visible after calling CVirtualLedStrip::show().
*/
/*----------------------------------------------------------------------------*/
void CVirtualLedStrip::setPixelColor(uint16_t auPixelNumber, uint32_t auColour)
{
	m_pcLedStrip->setPixelColor(auPixelNumber + m_uOffset, auColour);
}
#endif


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

void CVirtualLedStrip::show(void) const
{
#ifdef DF_NEOPIXEL
	m_pcLedStrip->show();
#elif defined(DF_FASTLED)
	FastLED[m_uStripNumber].showLeds(0xFFU);
#endif
}

void CVirtualLedStrip::begin(void) const
{
#ifdef DF_NEOPIXEL
	m_pcLedStrip->begin();
#endif
}

ERunStateShootingStar CVirtualLedStrip::getState(void)
{
	return m_eRunStateShootingStar;
}

/*----------------------------------------------------------------------------*/
/*!
	\pre
	Constructor has been called.

	\post
	None.

*/
/*----------------------------------------------------------------------------*/
uint16_t CVirtualLedStrip::numPixels(void) const
{
	return m_uLength;
}

uint32_t CVirtualLedStrip::getPixelColor(uint16_t auPixelNumber) const
{
#ifdef DF_NEOPIXEL
	return m_pcLedStrip->getPixelColor(auPixelNumber + m_uOffset);
#endif
}

/*----------------------------------------------------------------------------*/
/*!
	\pre
	Constructor has been called.

	\post
	Next step of shooting star programme has been completed.

	The programme is divided in the states defined in \see ERunStateShootingStar.
*/
/*----------------------------------------------------------------------------*/
void CVirtualLedStrip::runShootingStar(void)
{

	switch(m_eRunStateShootingStar)
	{
	case eRunStateShootingStarIdle:
		// do nothing
		break;
	case eRunStateShootingStarWaiting:
		if(m_uWaitCounter > 0)
		{
			/* This > 0 guard is mainly because erroneous flash reads could (and did) return 0,
			 * which caused underflows. Usually m_uWaitCounter should only be zero AFTER this
			 * decrement, because it is only decremented here.
			 */
			m_uWaitCounter--;
		}
		if(m_uWaitCounter == 0)
		{
			m_eRunStateShootingStar = eRunStateShootingStarOutput;
		}

		break;
	case eRunStateShootingStarOutput:
		this->handleShootingStarOutput();
		m_eRunStateShootingStar = eRunStateShootingStarNextStep;
		break;
	case eRunStateShootingStarNextStep:
		if(m_uCurrentStep < (DF_MVDATA_NUM_LEDS_PER_VIRTUAL_STRIP + DF_MVDATA_MAX_AFTERGLOW - 1))
		{
			/* if current step is not last step: wait until countdown has finished */
			m_eRunStateShootingStar = eRunStateShootingStarWaiting;

			m_uCurrentStep++;
			m_uWaitCounter = (uint32_t)(pgm_read_byte(g_uStepDelays + m_uCurrentStep));
		}
		else
		{
			/* if current step is last step: go into idle until a new step is started */
			m_eRunStateShootingStar = eRunStateShootingStarIdle;

			m_bIsRunning = false;
			m_uCurrentStep = 0;
			m_uWaitCounter = (uint32_t)(pgm_read_byte(g_uStepDelays));
		}
		break;
	default:
		m_eRunStateShootingStar = eRunStateShootingStarIdle;
		break;
	}
}

void CVirtualLedStrip::handleShootingStarOutput(void)
{
	for(uint8_t uLoop = 0; uLoop < DF_MVDATA_NUM_LEDS_PER_VIRTUAL_STRIP; uLoop++)
	{
		uint8_t uLightIntensity = pgm_read_byte(g_uLightIntensityMat[m_uCurrentStep] + uLoop);
		this->setPixelColor(uLoop, uLightIntensity, uLightIntensity, uLightIntensity);
	}

	this->show(); // This sends the updated pixel color to the hardware.
}

bool CVirtualLedStrip::isRunning(void)
{
	return m_bIsRunning;
}

bool CVirtualLedStrip::startRunning(void)
{
	if(!m_bIsRunning)
	{
		m_bIsRunning = true;
		m_uCurrentStep = 0;
		m_uWaitCounter = (uint32_t)(pgm_read_byte(g_uStepDelays));

		m_eRunStateShootingStar = eRunStateShootingStarWaiting;
	}
}
