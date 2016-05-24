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
#define DF_MVDATA_NUM_LEDS_PER_VIRTUAL_STRIP 50U
#define DF_MVDATA_NUM_LEDS_PER_REAL_STRIP 150U
#define DF_MVDATA_MAX_AFTERGLOW 20U
#define DF_MVDATA_NUM_VIRTUAL_STRIPS 3U
#define DF_MVDATA_NUM_REAL_STRIPS 1U
#define DF_MVDATA_NUM_VIRTUAL_STRIPS_PER_REAL_STRIP (DF_MVDATA_NUM_VIRTUAL_STRIPS/DF_MVDATA_NUM_REAL_STRIPS)

/*----------------------------------------------------------------------------*/
/*!	\brief Light intensity matrix. The steps increase with increasing x index. The LED pixels increase with increasing y index.
*/
extern const uint8_t g_uLightIntensityMat
		[DF_MVDATA_NUM_LEDS_PER_VIRTUAL_STRIP + DF_MVDATA_MAX_AFTERGLOW][DF_MVDATA_NUM_LEDS_PER_VIRTUAL_STRIP + DF_MVDATA_MAX_AFTERGLOW];

/*----------------------------------------------------------------------------*/
/*!	\brief Step delay array. Contains the delay between the steps for a certain step index.
*/
extern const uint8_t g_uStepDelays[DF_MVDATA_NUM_LEDS_PER_VIRTUAL_STRIP + DF_MVDATA_MAX_AFTERGLOW];




#endif /* INC_MOVEDATA_H */
