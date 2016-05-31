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
#ifdef DF_NEOPIXEL
#include <Adafruit_NeoPixel.h>
#elif defined(DF_FASTLED)
#include <FastLED.h>
#endif
#include <Arduino_FreeRTOS.h>

#include <CVirtualLedStrip.h>
#include <MoveData.h>
/*----------------------------------------------------------------------------*/
/* defines */
/*----------------------------------------------------------------------------*/
#ifdef DF_FASTLED
#define DF_PIN_STRIP0 6U
#define DF_PIN_STRIP1 9U
#define DF_PIN_STRIP2 10U
#define DF_PIN_STRIP3 11U
#endif
/*----------------------------------------------------------------------------*/
/* forward declarations */
/*----------------------------------------------------------------------------*/
void handleLedStripTask(void* apvLedStrip);

/*----------------------------------------------------------------------------*/
/* globals */
/*----------------------------------------------------------------------------*/
/*! \brief virtual WS2812 strip object */
CVirtualLedStrip* g_ypcVirtPixels[DF_MVDATA_NUM_VIRTUAL_STRIPS];
#ifdef DF_FASTLED
CRGB g_ycPhysPixels[DF_MVDATA_NUM_REAL_STRIPS][DF_MVDATA_NUM_LEDS_PER_REAL_STRIP];
CRGB* g_ypcPhysPixelsForVirtStrips[DF_MVDATA_NUM_VIRTUAL_STRIPS];
#endif

#ifdef DF_NEOPIXEL
Adafruit_NeoPixel* g_ypcPhysPixels[DF_MVDATA_NUM_REAL_STRIPS];
Adafruit_NeoPixel* g_ypcPhysPixelsForVirtStrips[DF_MVDATA_NUM_VIRTUAL_STRIPS];
const uint8_t g_uPins[DF_MVDATA_NUM_REAL_STRIPS] = {6U, 9U, 10U, 11U};
#endif

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
void setup(void)
{
//	char sTaskString[7];

	/* Setup serial communication for debug */
	Serial.begin(9600);
#ifdef DF_NEOPIXEL
	for(uint8_t uStripIndex = 0; uStripIndex < DF_MVDATA_NUM_REAL_STRIPS; uStripIndex++)
	{
		/* Every third strip is the first virtual strip of a physical strip */
		g_ypcPhysPixels[uStripIndex] = new Adafruit_NeoPixel(DF_MVDATA_NUM_LEDS_PER_REAL_STRIP, g_uPins[uStripIndex], NEO_GRB + NEO_KHZ800);
		g_ypcPhysPixels[uStripIndex]->begin();
	}
#endif

#ifdef DF_FASTLED
		FastLED.addLeds<NEOPIXEL, DF_PIN_STRIP0>(g_ycPhysPixels[0], DF_MVDATA_NUM_LEDS_PER_REAL_STRIP);
		FastLED.addLeds<NEOPIXEL, DF_PIN_STRIP1>(g_ycPhysPixels[1], DF_MVDATA_NUM_LEDS_PER_REAL_STRIP);
		FastLED.addLeds<NEOPIXEL, DF_PIN_STRIP2>(g_ycPhysPixels[2], DF_MVDATA_NUM_LEDS_PER_REAL_STRIP);
		FastLED.addLeds<NEOPIXEL, DF_PIN_STRIP3>(g_ycPhysPixels[3], DF_MVDATA_NUM_LEDS_PER_REAL_STRIP);
#endif

	for(uint8_t uRealIndex = 0; uRealIndex < DF_MVDATA_NUM_REAL_STRIPS; uRealIndex++)
	{
		for(uint8_t uVirtIndex = 0; uVirtIndex < DF_MVDATA_NUM_VIRTUAL_STRIPS; uVirtIndex++)
		{
#ifdef DF_NEOPIXEL
			g_ypcPhysPixelsForVirtStrips[(uRealIndex * DF_MVDATA_NUM_VIRTUAL_STRIPS) + uVirtIndex] =
					g_ypcPhysPixels[uRealIndex];
#endif
#ifdef DF_FASTLED
			g_ypcPhysPixelsForVirtStrips[(uRealIndex * DF_MVDATA_NUM_VIRTUAL_STRIPS) + uVirtIndex] =
					g_ycPhysPixels[uRealIndex];
#endif
		}
	}

	for(uint8_t uStripIndex = 0; uStripIndex < DF_MVDATA_NUM_VIRTUAL_STRIPS; uStripIndex++)
	{
		/* Every third strip is the first virtual strip of a physical strip */
		uint8_t uOffset = (uStripIndex % 3U) * 50;
		uint8_t uStripNumber = (uint8_t)(uStripIndex / 3U);
		g_ypcVirtPixels[uStripIndex] = new CVirtualLedStrip(uOffset, DF_MVDATA_NUM_LEDS_PER_VIRTUAL_STRIP, uStripNumber, g_ypcPhysPixelsForVirtStrips[uStripIndex]);

		for(uint8_t uLoop = 0; uLoop < DF_MVDATA_NUM_LEDS_PER_VIRTUAL_STRIP; uLoop++)
		{
			g_ypcVirtPixels[uStripIndex] -> setPixelColor(uLoop, 0, 0, 0);
			g_ypcVirtPixels[uStripIndex] -> show();
		}

//		sprintf(sTaskString, "Handle%u", uStripIndex);
//		uint8_t uTaskErr = 	xTaskCreate(handleLedStripTask, ychTaskString, 1024, g_pcPixels[uStripIndex], 1, g_pvTaskHandles);
//		if(uTaskErr != 1)
//		{
//			Serial.println("Error in task creation!");
//		}

		 // This sends the updated pixel color to the hardware.
	}

	// seed with random analogue noise from unconnected input
	randomSeed(analogRead(0));

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
//	Serial.println("loop");
	for(uint8_t uStripIndex = 0; uStripIndex < DF_MVDATA_NUM_VIRTUAL_STRIPS; uStripIndex++)
	{
		handleLedStripTask(g_ypcVirtPixels[uStripIndex]);
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
			uint8_t uRand = random(100);
			if(uRand < 10)
			{
				pcLedStrip -> startRunning();
			}
		}
		pcLedStrip -> runShootingStar();

//		vTaskDelay(1);
//	}
}
