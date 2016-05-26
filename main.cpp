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
void runningTask(void* apvArgument);
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
	char ychTaskString[7];

	/* Setup serial communication for debug */
	Serial.begin(9600);
	Serial.println("Hello World from setup!");

	/* Setup LED strip tasks */
	for(uint8_t uStripIndex = 0; uStripIndex < DF_MVDATA_NUM_VIRTUAL_STRIPS; uStripIndex++)
	{
		/* Every third strip is the first virtual strip of a physical strip */
		uint8_t uOffset = (uStripIndex % 3U) * 50;
		g_pcPixels[uStripIndex] = new CVirtualLedStrip(uOffset, DF_MVDATA_NUM_LEDS_PER_VIRTUAL_STRIP, g_uPins[uStripIndex], NEO_GRB + NEO_KHZ800);
		g_pcPixels[uStripIndex]->begin();

//		sprintf(ychTaskString, "Handle%u", uStripIndex);
//		uint8_t uTaskErr = 	xTaskCreate(handleLedStripTask, ychTaskString, 1024, g_pcPixels[uStripIndex], 1, g_pvTaskHandles);
//		if(uTaskErr != 1)
//		{
//			Serial.println("Error in task creation!");
//		}

		g_pcPixels[uStripIndex] -> begin();

//		g_cPixels[uStripIndex]->show(); // This sends the updated pixel color to the hardware.
	}
//	Serial.println("begin");
//	pixel.begin();
//	for(uint8_t uLoop = 1; uLoop < DF_MVDATA_NUM_LEDS_PER_VIRTUAL_STRIP; uLoop++)
//	{
//		pixel.setPixelColor(uLoop, 0xff, 0xff, 0xff);
//	}
//
//	pixel.show(); // This sends the updated pixel color to the hardware.
	/* Setup tasks */
//	xTaskCreate(runningTask, "example", 1024, 0, 1, g_pvTaskHandles);

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
//	Serial.println("loop");
	for(uint8_t uStripIndex = 0; uStripIndex < DF_MVDATA_NUM_VIRTUAL_STRIPS; uStripIndex++)
	{
		handleLedStripTask(&uStripIndex);
	}
}

void handleLedStripTask(void* apvLedStrip)
{
	uint8_t uIndex = *((uint8_t*)apvLedStrip);
//	CVirtualLedStrip* pcLedStrip = (CVirtualLedStrip*)apvLedStrip;
//	while(true)
//	{
		if(!apvLedStrip)
		{
			Serial.println("Oooops, null pointer!");
		}

		if(!(g_pcPixels[uIndex] -> isRunning()))
		{
			Serial.println("Start");
			g_pcPixels[uIndex] -> startRunning();
		}
		Serial.println("Run");
		g_pcPixels[uIndex] -> runShootingStar();

//		vTaskDelay(1);
//	}
}

void runningTask(void* apvArgument)
{
	static uint32_t s_uLastEnterTime;
	static TickType_t s_tLastWakeTicks;
	uint32_t uCurrentEnterTime;
	uint32_t uTimeElapsed;
	char cTimeString[256] = {0};
	s_uLastEnterTime = millis();

	while(true)
	{
		s_tLastWakeTicks = xTaskGetTickCount();
		uCurrentEnterTime = millis();
		uTimeElapsed = uCurrentEnterTime - s_uLastEnterTime;
		sprintf(cTimeString, "Timediff: %u ms.", uTimeElapsed);
		Serial.println(cTimeString);
		s_uLastEnterTime = uCurrentEnterTime;
		vTaskDelayUntil(&s_tLastWakeTicks, 1);
	}
}
