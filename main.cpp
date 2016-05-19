/**----------------------------------------------------------------------------
	\file		Main.cpp
	\author		D. Wright
	\version	0

	\brief Main file

----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/

/*!	\defgroup Main
	\{
*/

/*!	\defgroup Main (MAIN)
 	 * \brief Main File
	\{
*/

/*----------------------------------------------------------------------------*/
/* includes */
/*----------------------------------------------------------------------------*/
#include "stdint.h"
#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

#include "moveData.h"
/*----------------------------------------------------------------------------*/
/* defines */
/*----------------------------------------------------------------------------*/
#define F_CPU 16000000UL

/*----------------------------------------------------------------------------*/
/* forward declarations */
/*----------------------------------------------------------------------------*/
void runningTask(void* apvArgument);

/*----------------------------------------------------------------------------*/
/* globals */
/*----------------------------------------------------------------------------*/
/*! \brief WS2812 strip object */
Adafruit_NeoPixel* g_cPixels[DF_MVDATA_NUM_STRIPS];
/*! \brief WS2812 strip object */
const uint8_t g_uPins[DF_MVDATA_NUM_STRIPS] = {0};
/*! \brief Delay variable */
uint16_t g_uDelayVal = 500U;
/*! \brief task handles */

/*----------------------------------------------------------------------------*/
/*!
	\pre
	None.

	\post
	Arduino is set up.

	Arduino setup function.
*/
/*----------------------------------------------------------------------------*/
void setup(void)
{
	/* Setup LED strips */
	for(uint8_t uStripIndex = 0; uStripIndex < DF_MVDATA_NUM_STRIPS; uStripIndex++)
	{
		g_cPixels[uStripIndex] = new Adafruit_NeoPixel(DF_MVDATA_NUM_LEDS_PER_STRIP, g_uPins[uStripIndex], NEO_GRB + NEO_KHZ800);
		g_cPixels[uStripIndex]->begin();
	}

	/* Setup serial communication for debug */
	Serial.begin(9600);
	Serial.println("Hello World from setup!");
}

/*----------------------------------------------------------------------------*/
/*!
	\pre
	setup() has been called.

	\post
	None.

	Arduino loop function.
*/
/*----------------------------------------------------------------------------*/
void loop(void)
{
  for(uint8_t uLoop = 0; uLoop < DF_MVDATA_NUM_LEDS_PER_STRIP; uLoop++){
	// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
	g_cPixels[0]->setPixelColor(uLoop, g_uLightIntensityMat[0][uLoop], g_uLightIntensityMat[0][uLoop], g_uLightIntensityMat[0][uLoop]);

	g_cPixels[0]->show(); // This sends the updated pixel color to the hardware.

	delay(g_uDelayVal); // Delay for a period of time (in milliseconds).
	Serial.println("Loop is still here.");

  }
}
