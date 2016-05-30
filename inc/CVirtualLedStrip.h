/**----------------------------------------------------------------------------
	\file		CVirtualLedStrip.h
	\author		D. Wright
	\version	0

	\brief Class that implements a virtual LED strip.

	A virtual strip is a part of an actual LED strip.
	Each LED strip is being divided in multiple virtual substrips.
	Each of those virtual strips can be addressed the same way as the Adafruit_NeoPixel library.
	This class is a wrapper for Adafruit_NeoPixel so it each substrip can be addressed in the same
	fashion as Adafruit_NeoPixel.

  ----------------------------------------------------------------------------*/

#ifndef INC_CVIRTUALLEDSTRIP_H_
#define INC_CVIRTUALLEDSTRIP_H_

/*----------------------------------------------------------------------------*/
/* typedefs */
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*!	\brief Shooting star programme states
*/
typedef enum
{
	/*!	\brief Idle state.*/
	eRunStateShootingStarIdle = 0,
	/*!	\brief Waiting state.*/
	eRunStateShootingStarWaiting,
	/*!	\brief Output state.*/
	eRunStateShootingStarOutput,
	/*!	\brief Calculate next state.*/
	eRunStateShootingStarNextStep
}ERunStateShootingStar;

/*----------------------------------------------------------------------------*/
class CVirtualLedStrip
{
private:
	/*! \brief Offset from pixel number zero of the physical strip. */
	uint16_t m_uOffset;
	/*! \brief TRUE if an LED programme is running. */
	bool m_bIsRunning;
	/*! \brief Length of this virtual strip (number of pixels). */
	uint16_t m_uLength;
	/*! \brief Current step in programme. */
	uint16_t m_uCurrentStep;
	/*! \brief Wait counter between current and next step of programme. */
	uint32_t m_uWaitCounter;
	ERunStateShootingStar m_eRunStateShootingStar;
	uint8_t m_uStripNumber;
#ifdef DF_FASTLED
	CRGB* m_pcLedStrip;
#endif
#ifdef DF_NEOPIXEL
	Adafruit_NeoPixel* m_pcLedStrip;
#endif
public:
#ifdef DF_FASTLED
	CVirtualLedStrip(uint16_t auOffset, uint16_t auLength,  uint8_t auStripNumber, CRGB* apcLedStrip);
#endif
#ifdef DF_NEOPIXEL
	CVirtualLedStrip(uint16_t auOffset, uint16_t auLength,  uint8_t auStripNumber, Adafruit_NeoPixel* apcLedStrip);
#endif
	CVirtualLedStrip(CVirtualLedStrip& acLedStrip);
	~CVirtualLedStrip(void);

	/* Overriden members from Adafruit_NeoPixel */
	/*!	\brief Set pixel colours.
		\param auPixelNumber.
		\param auRed.
		\param auGreen.
		\param auBlue.
		\retval None.
	*/
    virtual void setPixelColor(uint16_t auPixelNumber, uint8_t auRed, uint8_t auGreen, uint8_t auBlue);

#ifdef DF_NEOPIXEL
	/*!	\brief Set pixel colours.
		\param auPixelNumber.
		\param auRed.
		\param auGreen.
		\param auBlue.
		\param auWhite.
		\retval None.
	*/
    virtual void setPixelColor(uint16_t auPixelNumber, uint8_t auRed, uint8_t auGreen, uint8_t auBlue, uint8_t auWhite);

	/*!	\brief Set pixel colours.
		\param auPixelNumber.
		\param auColour.
		\retval None.
	*/
	virtual void setPixelColor(uint16_t auPixelNumber, uint32_t auColour);

	/*!	\brief Set pixel brightness.
		\param auBrightness.
		\retval None.
	*/
#endif
	virtual void setBrightness(uint8_t auBrightness);

	/*!	\brief Clear all pixels.
		\param auLength.
		\retval None.
	*/
	virtual void clear(void);

	/*!	\brief Update strip length.
		\param None.
		\retval None.
	*/
	virtual void updateLength(uint16_t auLength);

    virtual uint8_t* getPixels(void) const;
    virtual uint16_t numPixels(void) const;
    virtual uint32_t getPixelColor(uint16_t auPixelNumber) const;
    virtual void show(void) const;
    virtual void begin(void) const;

    ERunStateShootingStar getState(void);
    /* Programmes */
	/*!	\brief Run shooting star programme.
		\param None.
		\retval None.
	*/
    virtual void runShootingStar(void);

	/*!	\brief Shooting star pixel output handler.
		\param None.
		\retval None.
	*/
    virtual void handleShootingStarOutput(void);

	/*!	\brief Return whether or not a programme is running.
		\param None.
		\return True if a programme is running.
	*/
    virtual bool isRunning(void);

	/*!	\brief Start the programme.
		\param None.
		\retval None.
	*/
    virtual bool startRunning(void);
};


#endif /* INC_CVIRTUALLEDSTRIP_H_ */
