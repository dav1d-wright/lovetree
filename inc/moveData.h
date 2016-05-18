/**----------------------------------------------------------------------------
	\file		moveData.h
	\author		D. Wright
	\version	0

	\brief Contains arrays and matrices for move data of LED strip.


  ----------------------------------------------------------------------------*/

#ifndef INC_MOVEDATA_H
#define INC_MOVEDATA_H


/*----------------------------------------------------------------------------*/

/*!	\defgroup moveData.
	\brief Contains arrays and matrices for move data of LED strip..

	\{
*/

/*----------------------------------------------------------------------------*/
/* defines */
/*----------------------------------------------------------------------------*/
#define DF_MVDATA_NUM_LEDS_PER_STRIP 50U
#define DF_MVDATA_MAX_AFTERGLOW 20U
#define DF_MVDATA_NUM_STRIPS 12U

/*----------------------------------------------------------------------------*/
/*!	\brief Light intensity matrix. The steps increase with increasing x index. The LED pixels increase with increasing y index.
*/
extern const uint8_t g_uLightIntensityMat
		[DF_MVDATA_NUM_LEDS_PER_STRIP + DF_MVDATA_MAX_AFTERGLOW][DF_MVDATA_NUM_LEDS_PER_STRIP + DF_MVDATA_MAX_AFTERGLOW];

/*----------------------------------------------------------------------------*/
/*!	\brief Step delay array. Contains the delay between the steps for a certain step index.
*/
extern const uint8_t g_uStepDelays[DF_MVDATA_NUM_LEDS_PER_STRIP + DF_MVDATA_MAX_AFTERGLOW];




#endif /* INC_MOVEDATA_H */
