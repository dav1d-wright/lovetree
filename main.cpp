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
//#include <Arduino_FreeRTOS.h>

#include <CVirtualLedStrip.h>
#include <MoveData.h>
/*----------------------------------------------------------------------------*/
/* defines */
/*----------------------------------------------------------------------------*/
#ifdef DF_FASTLED
#define DF_PIN_STRIP0 6U
#define DF_PIN_STRIP1 8U
#define DF_PIN_STRIP2 4U
#define DF_PIN_STRIP3 10U
#endif
#define DF_PROBABILITY_COUNTER_MAX 0x4096UL
#define DF_PROBABILITY_NOMINAL 30U
#define DF_TASK_WAIT 30U
#define DF_2_PI 6.28
/*----------------------------------------------------------------------------*/
/* forward declarations */
/*----------------------------------------------------------------------------*/
void handleLedStripTask(void* apvLedStrip);
int16_t getStartVariance(uint8_t auStripIndex);
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
/*! \brief Probability variance counter */
uint32_t g_uProbabilityCounter;
/*! \brief task handles */
//TaskHandle_t g_pvTaskHandles[DF_MVDATA_NUM_VIRTUAL_STRIPS];
/*! \brief Time when task was last called */
uint16_t g_uLastCallTime[DF_MVDATA_NUM_VIRTUAL_STRIPS];

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


#ifdef DF_NEOPIXEL
		g_ypcPhysPixelsForVirtStrips[0] = g_ypcPhysPixels[0];
		g_ypcPhysPixelsForVirtStrips[1] = g_ypcPhysPixels[0];
		g_ypcPhysPixelsForVirtStrips[2] = g_ypcPhysPixels[0];
		g_ypcPhysPixelsForVirtStrips[3] = g_ypcPhysPixels[1];
		g_ypcPhysPixelsForVirtStrips[4] = g_ypcPhysPixels[1];
		g_ypcPhysPixelsForVirtStrips[5] = g_ypcPhysPixels[1];
		g_ypcPhysPixelsForVirtStrips[6] = g_ypcPhysPixels[2];
		g_ypcPhysPixelsForVirtStrips[7] = g_ypcPhysPixels[2];
		g_ypcPhysPixelsForVirtStrips[8] = g_ypcPhysPixels[2];
		g_ypcPhysPixelsForVirtStrips[9] = g_ypcPhysPixels[3];
		g_ypcPhysPixelsForVirtStrips[10] = g_ypcPhysPixels[3];
		g_ypcPhysPixelsForVirtStrips[11] = g_ypcPhysPixels[3];
#endif
#ifdef DF_FASTLED
		g_ypcPhysPixelsForVirtStrips[0] = g_ycPhysPixels[0];
		g_ypcPhysPixelsForVirtStrips[1] = g_ycPhysPixels[0];
		g_ypcPhysPixelsForVirtStrips[2] = g_ycPhysPixels[0];
		g_ypcPhysPixelsForVirtStrips[3] = g_ycPhysPixels[1];
		g_ypcPhysPixelsForVirtStrips[4] = g_ycPhysPixels[1];
		g_ypcPhysPixelsForVirtStrips[5] = g_ycPhysPixels[1];
		g_ypcPhysPixelsForVirtStrips[6] = g_ycPhysPixels[2];
		g_ypcPhysPixelsForVirtStrips[7] = g_ycPhysPixels[2];
		g_ypcPhysPixelsForVirtStrips[8] = g_ycPhysPixels[2];
		g_ypcPhysPixelsForVirtStrips[9] = g_ycPhysPixels[3];
		g_ypcPhysPixelsForVirtStrips[10] = g_ycPhysPixels[3];
		g_ypcPhysPixelsForVirtStrips[11] = g_ycPhysPixels[3];
#endif


	for(uint8_t uStripIndex = 0; uStripIndex < DF_MVDATA_NUM_VIRTUAL_STRIPS; uStripIndex++)
	{
		/* Every third strip is the first virtual strip of a physical strip */
		uint8_t uOffset = (uStripIndex % 3U) * DF_MVDATA_NUM_LEDS_PER_VIRTUAL_STRIP;
		uint8_t uRealStripNumber = (uint8_t)(uStripIndex / 3U);
		g_ypcVirtPixels[uStripIndex] = new CVirtualLedStrip(uOffset, DF_MVDATA_NUM_LEDS_PER_VIRTUAL_STRIP, uRealStripNumber, uStripIndex, g_ypcPhysPixelsForVirtStrips[uStripIndex]);

		for(uint8_t uLoop = 0; uLoop < DF_MVDATA_NUM_LEDS_PER_VIRTUAL_STRIP; uLoop++)
		{
			g_ypcVirtPixels[uStripIndex] -> setPixelColorRgb(uLoop, 0, 0, 0);
			g_ypcVirtPixels[uStripIndex] -> show();
		}

		g_uLastCallTime[uStripIndex] = millis();
//		Serial.print("Create  task ");
//		Serial.println(uStripIndex);
//		sprintf(sTaskString, "Handle%u", uStripIndex);
//		uint8_t uTaskErr = 	xTaskCreate(handleLedStripTask, sTaskString, 1024, g_ypcVirtPixels[uStripIndex], 1, 0);
//		uint8_t uTaskErr = 	xTaskCreate(handleLedStripTask, sTaskString, 1024, 0, 1, 0);
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
		uint16_t uThisCallTime = millis();
		uint16_t uTimeDiff = uThisCallTime - g_uLastCallTime[uStripIndex];

		if(uTimeDiff > DF_TASK_WAIT)
		{
			if(uStripIndex == 0)
			{
				/* decrement probability counter for sinusodial behaviour of starting a new task */
				if(g_uProbabilityCounter == 0)
				{
					g_uProbabilityCounter = DF_PROBABILITY_COUNTER_MAX;
				}

				g_uProbabilityCounter--;
			}

			g_uLastCallTime[uStripIndex] = millis();
			handleLedStripTask(g_ypcVirtPixels[uStripIndex]);
		}
	}
}

void handleLedStripTask(void* apvLedStrip)
{
	CVirtualLedStrip* pcLedStrip = (CVirtualLedStrip*)apvLedStrip;
	uint8_t uStripIndex = pcLedStrip->getVirtStripIndex();
//	static uint16_t s_uLastMillis = 0;
//	uint16_t uThisMillis = millis();
//	uint16_t uTimeDiff = uThisMillis - s_uLastMillis;
//
//	if(uStripIndex == 0)
//	{
//		Serial.println(uTimeDiff);
//		s_uLastMillis = uThisMillis;
//	}

//	while(true)
//	{
		if(!apvLedStrip)
		{
			Serial.println("Oooops, null pointer!");
		}

		/* check if task is running */
		if(!(pcLedStrip -> isRunning()))
		{
			int16_t uRand = (int16_t)random(1000);
			int16_t uProb = (((int16_t)(DF_PROBABILITY_NOMINAL)) + getStartVariance(uStripIndex));

			if(uStripIndex == 0)
			{
				Serial.print(uProb);
				Serial.print(" ");
				Serial.println(uRand);
			}

			if(uRand < uProb)
			{
				if(uStripIndex == 0)
				{
					Serial.println("S");
				}
				double dSaturationPercent;
				double dHuePercent = ((double)random(50))/100.0;
				if(random(100) > 15)
				{
					dSaturationPercent = 1.0;
				}
				else
				{
					dSaturationPercent = 0.0;
				}
				pcLedStrip -> startRunning(dHuePercent, dSaturationPercent);
			}
		}
		pcLedStrip -> runShootingStar();

//		vTaskDelay(10);
//	}
}

int16_t getStartVariance(uint8_t auStripIndex)
{
	int16_t iVariance = 0U;

	/* Amplitude = DF_PROBABILITY_NOMINAL + 2 so that we fall below 0 sometimes */
	iVariance = (int8_t)((double)DF_PROBABILITY_NOMINAL + 0.5) * sin(
			((double)g_uProbabilityCounter) / ((double)DF_PROBABILITY_COUNTER_MAX) * DF_2_PI);
	return iVariance;
}
