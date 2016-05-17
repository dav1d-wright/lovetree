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
#include "FreeRTOS_AVR.h"
/*----------------------------------------------------------------------------*/
/* defines */
/*----------------------------------------------------------------------------*/
#define DF_NUM_LEDS_PER_STRIP 10U
#define DF_PIN	6U
#define DF_NUM_STRIPS 12

/*----------------------------------------------------------------------------*/
/* forward declarations */
/*----------------------------------------------------------------------------*/
void task(void* apvArgument);

/*----------------------------------------------------------------------------*/
/* globals */
/*----------------------------------------------------------------------------*/
/*! \brief WS2812 strip object */
Adafruit_NeoPixel g_cPixels = Adafruit_NeoPixel(DF_NUM_LEDS_PER_STRIP, DF_PIN, NEO_GRB + NEO_KHZ800);
/*! \brief Delay variable */
uint16_t g_uDelayVal = 500U;
/*! \brief task handles */
TaskHandle_t g_pvTaskHandles[DF_NUM_STRIPS];

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
	g_cPixels.begin();
	xTaskCreate(task, "example task", 1024, 0, 1, g_pvTaskHandles);
	vTaskStartScheduler();

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
  for(uint8_t uLoop = 0; uLoop < DF_NUM_LEDS_PER_STRIP; uLoop++){
	// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
	g_cPixels.setPixelColor(uLoop, g_cPixels.Color(0,150,0)); // Moderately bright green color.

	g_cPixels.show(); // This sends the updated pixel color to the hardware.

	delay(g_uDelayVal); // Delay for a period of time (in milliseconds).

  }
}

void task(void* apvArgument)
{
	while(true)
	{

	}
}
