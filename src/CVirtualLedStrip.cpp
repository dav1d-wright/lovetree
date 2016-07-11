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
#elif defined(DF_NEOPIXEL)
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
CVirtualLedStrip::CVirtualLedStrip(uint16_t auOffset, uint16_t auLength,  uint8_t auRealStripNumber, uint8_t auVirtStripNumber, CRGB* apcLedStrip):
#elif defined(DF_NEOPIXEL)
CVirtualLedStrip::CVirtualLedStrip(uint16_t auOffset, uint16_t auLength,  uint8_t auRealStripNumber, uint8_t auVirtStripNumber, Adafruit_NeoPixel* apcLedStrip):
#endif
m_bIsRunning(false), m_eRunStateShootingStar(eRunStateShootingStarIdle), m_uOffset(auOffset), m_uLength(auLength),
m_pcLedStrip(apcLedStrip), m_uRealStripNumber(auRealStripNumber), m_uVirtStripNumber(auVirtStripNumber), m_uHue(0), m_dSaturationPercent(1.0)
{
	Serial.print("C");
	Serial.println(m_uVirtStripNumber);
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
void CVirtualLedStrip::setPixelColorRgb(uint16_t auPixelNumber, uint8_t auRed, uint8_t auGreen, uint8_t auBlue)
{
#ifdef DF_NEOPIXEL
	m_pcLedStrip->setPixelColor(auPixelNumber + m_uOffset, auRed, auGreen, auBlue);
#elif defined(DF_FASTLED)
	m_pcLedStrip[auPixelNumber + m_uOffset].red = auRed;
	m_pcLedStrip[auPixelNumber + m_uOffset].green = auGreen;
	m_pcLedStrip[auPixelNumber + m_uOffset].blue = auBlue;
#endif
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
void CVirtualLedStrip::setPixelColorHsv(uint16_t auPixelNumber, uint8_t auHue, uint8_t auSaturation, uint8_t auValue)
{
#ifdef DF_FASTLED
	m_pcLedStrip[auPixelNumber + m_uOffset] = CHSV(auHue, auSaturation, auValue);
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
	FastLED[m_uRealStripNumber].showLeds(0xFFU);
#endif
}

void CVirtualLedStrip::begin(void) const
{
#ifdef DF_NEOPIXEL
	m_pcLedStrip->begin();
#endif
}

ERunStateShootingStar CVirtualLedStrip::getStateShootingStar(void)
{
	return m_eRunStateShootingStar;
}

ERunStateStrobe CVirtualLedStrip::getStateStrobe(void)
{
	return m_eRunStateStrobe;
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
		if(m_uWaitCounterShootingStar > 0)
		{
			/* This > 0 guard is mainly because erroneous flash reads could (and did) return 0,
			 * which caused underflows. Usually m_uWaitCounterShootingStar should only be zero AFTER this
			 * decrement, because it is only decremented here.
			 */
			m_uWaitCounterShootingStar--;
		}
		if(m_uWaitCounterShootingStar == 0)
		{
			m_eRunStateShootingStar = eRunStateShootingStarOutput;
		}
		break;
	case eRunStateShootingStarOutput:
		this->handleShootingStarOutput();
		m_eRunStateShootingStar = eRunStateShootingStarNextStep;
		break;
	case eRunStateShootingStarNextStep:
		if(m_uCurrentStepShootingStar < (DF_MVDATA_NUM_LEDS_PER_VIRTUAL_STRIP + DF_MVDATA_MAX_AFTERGLOW - 1))
		{
			/* if current step is not last step: wait until countdown has finished */
			m_eRunStateShootingStar = eRunStateShootingStarWaiting;

			m_uCurrentStepShootingStar++;
			m_uWaitCounterShootingStar = (uint32_t)(pgm_read_byte(g_uStepDelays + m_uCurrentStepShootingStar));
		}
		else
		{
			/* if current step is last step: go into idle until a new step is started */
			m_eRunStateShootingStar = eRunStateShootingStarIdle;

			m_bIsRunning = false;
			m_uCurrentStepShootingStar = 0;
			m_uWaitCounterShootingStar = (uint32_t)(pgm_read_byte(g_uStepDelays));
		}
		break;
	default:
		m_eRunStateShootingStar = eRunStateShootingStarIdle;
		break;
	}
}

void CVirtualLedStrip::handleShootingStarOutput(void)
{
	for(uint8_t uLoop = 0; uLoop < m_uLength; uLoop++)
	{
		uint8_t uLightIntensity = pgm_read_byte(g_uLightIntensityMat[m_uCurrentStepShootingStar] + uLoop);
		uint8_t uHue =  m_uHue + (0.2 * (0xFF - uLightIntensity));
		uint8_t uSaturation =  0xFF;

		this->setPixelColorHsv(uLoop, uHue, uSaturation, uLightIntensity);
	}

	this->show(); // This sends the updated pixel color to the hardware.
}

void CVirtualLedStrip::runStrobe(void)
{
	switch(m_eRunStateStrobe)
	{
	case eRunStateStrobeIdle:

		break;
	case eRunStateStrobeWaiting:
		if(m_uWaitCounterStrobe > 0)
		{
			/* This > 0 guard is mainly because erroneous flash reads could (and did) return 0,
			 * which caused underflows. Usually m_uWaitCounterStrobe should only be zero AFTER this
			 * decrement, because it is only decremented here.
			 */
			m_uWaitCounterStrobe--;
		}
		if(m_uWaitCounterStrobe == 0)
		{
			if(m_eLastRunStatetrobe == eRunStateStrobeOn)
			{
				m_eRunStateStrobe = eRunStateStrobeOff;
			}
			else if(m_eLastRunStatetrobe == eRunStateStrobeOff)
			{
				m_eRunStateStrobe = eRunStateStrobeOn;
			}
			m_eLastRunStatetrobe = eRunStateStrobeWaiting;
		}

		break;
	case eRunStateStrobeOn:
		for(uint8_t uLoop = 0; uLoop < m_uLength; uLoop++)
		{
			this->setPixelColorRgb(uLoop, 0xFFU, 0xFFU, 0xFFU);
		}
		this->show();

		m_eRunStateStrobe = eRunStateStrobeWaiting;
		m_eLastRunStatetrobe = eRunStateStrobeOn;
		m_uWaitCounterStrobe = 0;

		break;
	case eRunStateStrobeOff:
		for(uint8_t uLoop = 0; uLoop < m_uLength; uLoop++)
		{
			this->setPixelColorRgb(uLoop, 0, 0, 0);
		}
		this->show();

		m_eRunStateStrobe = eRunStateStrobeWaiting;
		m_eLastRunStatetrobe = eRunStateStrobeOff;
		m_uWaitCounterStrobe = 0;

		break;
	default:
		m_eRunStateStrobe = eRunStateStrobeIdle;
		break;
	}
}

bool CVirtualLedStrip::isRunning(void)
{
	return m_bIsRunning;
}

bool CVirtualLedStrip::startRunning(uint8_t auHue, double adSaturationPercent)
{
	if(!m_bIsRunning)
	{
		m_bIsRunning = true;
		m_uCurrentStepShootingStar = 0;
		m_uWaitCounterShootingStar = (uint32_t)(pgm_read_byte(g_uStepDelays));

		m_uHue = auHue;
		m_dSaturationPercent = adSaturationPercent;

		m_eRunStateShootingStar = eRunStateShootingStarWaiting;
	}
}


uint8_t CVirtualLedStrip::getRealStripIndex(void)
{
	return m_uRealStripNumber;
}

uint8_t CVirtualLedStrip::getVirtStripIndex(void)
{
	return m_uVirtStripNumber;
}
