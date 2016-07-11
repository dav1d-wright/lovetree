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

/*!	\brief Shooting star programme states
*/
typedef enum
{
	/*!	\brief Idle state.*/
	eRunStateStrobeIdle = 0,
	/*!	\brief Waiting state.*/
	eRunStateStrobeWaiting,
	/*!	\brief Output on state.*/
	eRunStateStrobeOn,
	/*!	\brief Output off state.*/
	eRunStateStrobeOff
}ERunStateStrobe;


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
	/*! \brief Current step in shooting star programme. */
	uint16_t m_uCurrentStepShootingStar;
	/*! \brief Wait counter between current and next step of shooting star programme. */
	uint32_t m_uWaitCounterShootingStar;
	/*! \brief Current step in strobe programme. */
	uint16_t m_uCurrentStepStrobe;
	/*! \brief Wait counter between current and next step of strobe programme. */
	uint32_t m_uWaitCounterStrobe;
	/*! \brief Current running state in the shooting star programme. */
	ERunStateShootingStar m_eRunStateShootingStar;
	/*! \brief Current running state in the strobe programme. */
	ERunStateStrobe m_eRunStateStrobe;
	/*! \brief Last running state in the strobe programme. */
	ERunStateStrobe m_eLastRunStatetrobe;
	/*! \brief Strip number (physical). */
	uint8_t m_uRealStripNumber;
	/*! \brief Strip number (virtual). */
	uint8_t m_uVirtStripNumber;
	/*! \brief Hue. */
	uint8_t m_uHue;
	/*! \brief Saturation percentage. */
	double m_dSaturationPercent;
#ifdef DF_FASTLED
	CRGB* m_pcLedStrip;
#endif
#ifdef DF_NEOPIXEL
	Adafruit_NeoPixel* m_pcLedStrip;
#endif
public:
#ifdef DF_FASTLED
	CVirtualLedStrip(uint16_t auOffset, uint16_t auLength,  uint8_t auRealStripNumber, uint8_t auVirtStripNumber, CRGB* apcLedStrip);
#endif
#ifdef DF_NEOPIXEL
	CVirtualLedStrip(uint16_t auOffset, uint16_t auLength,  uint8_t auRealStripNumber, uint8_t auVirtStripNumber, Adafruit_NeoPixel* apcLedStrip);
#endif
	CVirtualLedStrip(CVirtualLedStrip& acLedStrip);
	~CVirtualLedStrip(void);

	/* Overriden members from Adafruit_NeoPixel */
	/*!	\brief Set pixel colours using RGB.
		\param auPixelNumber.
		\param auRed.
		\param auGreen.
		\param auBlue.
		\retval None.
	*/
    virtual void setPixelColorRgb(uint16_t auPixelNumber, uint8_t auRed, uint8_t auGreen, uint8_t auBlue);

	/*!	\brief Set pixel colours using HSV.
		\param auPixelNumber.
		\param auHue.
		\param auSaturation.
		\param auValue.
		\retval None.
	*/
    virtual void setPixelColorHsv(uint16_t auPixelNumber, uint8_t auHue, uint8_t auSaturation, uint8_t auValue);

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

    ERunStateShootingStar getStateShootingStar(void);

    ERunStateStrobe getStateStrobe(void);
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

	/*!	\brief Run strobe programme.
		\param None.
		\retval None.
	*/
    virtual void runStrobe(void);

	/*!	\brief Return whether or not a programme is running.
		\param None.
		\return True if a programme is running.
	*/
    virtual bool isRunning(void);

	/*!	\brief Start the programme.
		\param None.
		\retval None.
	*/
    virtual bool startRunning(uint8_t auHue, double adSaturationPercent);

    virtual uint8_t getRealStripIndex(void);

    virtual uint8_t getVirtStripIndex(void);
};


#endif /* INC_CVIRTUALLEDSTRIP_H_ */
