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
#include <stdint.h>
//#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Arduino_FreeRTOS.h>

#include <CVirtualLedStrip.h>
#include <MoveData.h>
/*----------------------------------------------------------------------------*/
/* defines */
/*----------------------------------------------------------------------------*/
#define F_CPU 16000000UL

/*----------------------------------------------------------------------------*/
/* forward declarations */
/*----------------------------------------------------------------------------*/
void handleLedStripTask(void* apvLedStrip);

/*----------------------------------------------------------------------------*/
/* globals */
/*----------------------------------------------------------------------------*/
/*! \brief WS2812 strip object */
CVirtualLedStrip* g_pcPixels[DF_MVDATA_NUM_VIRTUAL_STRIPS];
/*! \brief WS2812 strip object */
//const uint8_t g_uPins[DF_MVDATA_NUM_VIRTUAL_STRIPS] = {6U, 6U, 6U, 9U, 9U, 9U, 10U, 10U, 10U, 11U, 11U, 11U};
const uint8_t g_uPins[DF_MVDATA_NUM_VIRTUAL_STRIPS] = {6};
/*! \brief Delay variable */
uint16_t g_uDelayVal = 500U;
/*! \brief task handles */
TaskHandle_t g_pvTaskHandles[DF_MVDATA_NUM_VIRTUAL_STRIPS];

/*----------------------------------------------------------------------------*/
/*!
	\pre
	None.

	\post
	Arduino is set up.

	Arduino setup function.
*/
/*----------------------------------------------------------------------------*/
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(DF_MVDATA_NUM_LEDS_PER_REAL_STRIP, 6, NEO_GRB + NEO_KHZ800);
void setup(void)
{
//	char sTaskString[7];

	/* Setup serial communication for debug */
	Serial.begin(9600);
	/* Setup LED strip tasks */
	for(uint8_t uStripIndex = 0; uStripIndex < DF_MVDATA_NUM_VIRTUAL_STRIPS; uStripIndex++)
	{
		/* Every third strip is the first virtual strip of a physical strip */
		uint8_t uOffset = (uStripIndex % 3U) * 50;
		g_pcPixels[uStripIndex] = new CVirtualLedStrip(uOffset, DF_MVDATA_NUM_LEDS_PER_VIRTUAL_STRIP, g_uPins[uStripIndex], NEO_GRB + NEO_KHZ800);
		g_pcPixels[uStripIndex]->begin();

		for(uint8_t uLoop = 1; uLoop < DF_MVDATA_NUM_LEDS_PER_VIRTUAL_STRIP; uLoop++)
		{
			g_pcPixels[uStripIndex] -> setPixelColor(uLoop, 0, 0, 0);
			g_pcPixels[uStripIndex] -> show();
		}

//		sprintf(sTaskString, "Handle%u", uStripIndex);
//		uint8_t uTaskErr = 	xTaskCreate(handleLedStripTask, ychTaskString, 1024, g_pcPixels[uStripIndex], 1, g_pvTaskHandles);
//		if(uTaskErr != 1)
//		{
//			Serial.println("Error in task creation!");
//		}

		 // This sends the updated pixel color to the hardware.
	}
	delay(1000);

	/* Setup tasks */
	Serial.println("Hello world from setup!");

//	vTaskStartScheduler();
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
	Serial.println("loop");
	for(uint8_t uStripIndex = 0; uStripIndex < DF_MVDATA_NUM_VIRTUAL_STRIPS; uStripIndex++)
	{
		handleLedStripTask(g_pcPixels[uStripIndex]);
	}
}

void handleLedStripTask(void* apvLedStrip)
{
	CVirtualLedStrip* pcLedStrip = (CVirtualLedStrip*)apvLedStrip;
//	while(true)
//	{
		if(!apvLedStrip)
		{
			Serial.println("Oooops, null pointer!");
		}

		if(!(pcLedStrip -> isRunning()))
		{
			pcLedStrip -> startRunning();
		}
		pcLedStrip -> runShootingStar();

//		vTaskDelay(1);
//	}
}
