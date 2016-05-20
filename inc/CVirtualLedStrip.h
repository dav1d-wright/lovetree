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

class CVirtualLedStrip: public Adafruit_NeoPixel
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

public:
	CVirtualLedStrip(uint16_t auOffset, uint16_t auLength, uint8_t auPinNumber=6, neoPixelType atPixelType=NEO_GRB + NEO_KHZ800);
	CVirtualLedStrip(CVirtualLedStrip& acLedStrip);
	~CVirtualLedStrip(void);

	/* Overriden members from Adafruit_NeoPixel */
    virtual void setPixelColor(uint16_t auPixelNumber, uint8_t auRed, uint8_t auGreen, uint8_t auBlue);
    virtual void setPixelColor(uint16_t auPixelNumber, uint8_t auRed, uint8_t auGreen, uint8_t auBlue, uint8_t auWhite);
	virtual void setPixelColor(uint16_t auPixelNumber, uint32_t auColour);
	virtual void setBrightness(uint8_t auBrightness);
	virtual void clear(void);
	virtual void updateLength(uint16_t auLength);
    virtual uint8_t *getPixels(void) const;
    virtual uint16_t numPixels(void) const;
    virtual uint32_t getPixelColor(uint16_t auPixelNumber) const;

    /* Programmes */
    virtual void runShootingStar(void);
    virtual bool isRunning(void);
    virtual bool startRunning(void);
};


#endif /* INC_CVIRTUALLEDSTRIP_H_ */
