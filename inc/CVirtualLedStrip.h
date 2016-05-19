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
	uint8_t m_uOffset;

public:
	CVirtualLedStrip(uint8_t auOffset, uint16_t n, uint8_t p=6, neoPixelType t=NEO_GRB + NEO_KHZ800);
	~CVirtualLedStrip(void);

    virtual void begin(void);
    virtual void show(void);
    virtual void setPin(uint8_t p);
    virtual void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
    virtual void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
	virtual void setPixelColor(uint16_t n, uint32_t c);
	virtual void setBrightness(uint8_t);
	virtual void clear(void);
	virtual void updateLength(uint16_t n);
	virtual void updateType(neoPixelType t);

    virtual uint8_t *getPixels(void) const;
    virtual uint8_t getBrightness(void) const;

    virtual uint16_t numPixels(void) const;

    virtual uint32_t Color(uint8_t r, uint8_t g, uint8_t b);
    virtual uint32_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w);

    virtual uint32_t getPixelColor(uint16_t n) const;
};


#endif /* INC_CVIRTUALLEDSTRIP_H_ */
