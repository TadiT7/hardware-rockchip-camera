/******************************************************************************
 *
 * The copyright in this software is owned by Rockchip and/or its licensors.
 * This software is made available subject to the conditions of the license 
 * terms to be determined and negotiated by Rockchip and you.
 * THIS SOFTWARE IS PROVIDED TO YOU ON AN "AS IS" BASIS and ROCKCHP AND/OR 
 * ITS LICENSORS DISCLAIMS ANY AND ALL WARRANTIES AND REPRESENTATIONS WITH 
 * RESPECT TO SUCH SOFTWARE, WHETHER EXPRESS,IMPLIED, STATUTORY OR OTHERWISE, 
 * INCLUDING WITHOUT LIMITATION, ANY IMPLIED WARRANTIES OF TITLE, NON-INFRINGEMENT, 
 * MERCHANTABILITY, SATISFACTROY QUALITY, ACCURACY OR FITNESS FOR A PARTICULAR PURPOSE. 
 * Except as expressively authorized by Rockchip and/or its licensors, you may not 
 * (a) disclose, distribute, sell, sub-license, or transfer this software to any third party, 
 * in whole or part; (b) modify this software, in whole or part; (c) decompile, reverse-engineer, 
 * dissemble, or attempt to derive any source code from the software.
 *
 *****************************************************************************/
/**
 * @file cam_calibdb_types.h
 *
 * @brief
 *   Interface description of the CamEngine.
 *
 *****************************************************************************/
/**
 *
 * @defgroup cam_calibdb_types CamCalibDb Types
 * @{
 */

#ifndef __CAM_CALIBDB_TYPES_H__
#define __CAM_CALIBDB_TYPES_H__

#include <ebase/types.h>

#ifdef __cplusplus
extern "C"
{
#endif



/*******************************************************************************
 * @brief The standard calibration database parameter values
 *
 * This enumeration lists the possible standard calibration values. 
 */
typedef enum CamCalibDbParameterId_e
{
    CAM_CALIBDB_ID_INVALID                          = 0,    /**< invalid id to avoid an uninitialized id */
    CAM_CALIBDB_ID_CREATION_DATE                    = 1,    /**< creation date */
    CAM_CALIBDB_ID_CREATOR                          = 2,    /**< nick of creator */
    CAM_CALIBDB_ID_CREATOR_VERSION                  = 3,    /**< creator/generator version */
    CAM_CALIBDB_ID_SENSOR_NAME                      = 4,    /**< sensor name */
    CAM_CALIBDB_ID_SENSOR_SAMPLE                    = 5,    /**< sensor sample identifier */
    CAM_CALIBDB_ID_RESOLUTION                       = 6,

    /* white balnace parameter */
    CAM_CALIBDB_ID_AWB_BASE                         = 100,
    CAM_CALIBDB_ID_AWB_SVDMEANVALUE                 = ( CAM_CALIBDB_ID_AWB_BASE + 0 ),
    CAM_CALIBDB_ID_AWB_PCAMATRIX                    = ( CAM_CALIBDB_ID_AWB_BASE + 1 ),
    CAM_CALIBDB_ID_AWB_CENTERLINE                   = ( CAM_CALIBDB_ID_AWB_BASE + 2 ),
    CAM_CALIBDB_ID_AWB_KFACTOR                      = ( CAM_CALIBDB_ID_AWB_BASE + 3 ),
    CAM_CALIBDB_ID_AWB_RG1                          = ( CAM_CALIBDB_ID_AWB_BASE + 4 ),
    CAM_CALIBDB_ID_AWB_MAXDIST1                     = ( CAM_CALIBDB_ID_AWB_BASE + 5 ),
    CAM_CALIBDB_ID_AWB_RG2                          = ( CAM_CALIBDB_ID_AWB_BASE + 6 ),
    CAM_CALIBDB_ID_AWB_MAXDIST2                     = ( CAM_CALIBDB_ID_AWB_BASE + 7 ),
    CAM_CALIBDB_ID_AWB_GLOBALFADE1                  = ( CAM_CALIBDB_ID_AWB_BASE + 8 ),
    CAM_CALIBDB_ID_AWB_GLOBALGAINDISTANCE1          = ( CAM_CALIBDB_ID_AWB_BASE + 9 ),
    CAM_CALIBDB_ID_AWB_GLOBALFADE2                  = ( CAM_CALIBDB_ID_AWB_BASE + 10 ),
    CAM_CALIBDB_ID_AWB_GLOBALGAINDISTANCE2          = ( CAM_CALIBDB_ID_AWB_BASE + 11 ),
    CAM_CALIBDB_ID_AWB_GLOBALS_FADE2                = ( CAM_CALIBDB_ID_AWB_BASE + 12 ),   
    CAM_CALIBDB_ID_AWB_GLOBALS_CB_MIN_REGIONMAX     = ( CAM_CALIBDB_ID_AWB_BASE + 13 ),
    CAM_CALIBDB_ID_AWB_GLOBALS_CR_MIN_REGIONMAX     = ( CAM_CALIBDB_ID_AWB_BASE + 14 ),
    CAM_CALIBDB_ID_AWB_GLOBALS_MAX_CSUM_REGIONMAX   = ( CAM_CALIBDB_ID_AWB_BASE + 15 ),
    CAM_CALIBDB_ID_AWB_GLOBALS_CB_MIN_REGIONMIN     = ( CAM_CALIBDB_ID_AWB_BASE + 16 ),
    CAM_CALIBDB_ID_AWB_GLOBALS_CR_MIN_REGIONMIN     = ( CAM_CALIBDB_ID_AWB_BASE + 17 ),
    CAM_CALIBDB_ID_AWB_GLOBALS_MAX_CSUM_REGIONMIN   = ( CAM_CALIBDB_ID_AWB_BASE + 18 ),
    CAM_CALIBDB_ID_AWB_GLOBALS_RGPROJ_INDOOR_MIN    = ( CAM_CALIBDB_ID_AWB_BASE + 19 ),
    CAM_CALIBDB_ID_AWB_GLOBALS_RGPROJ_OUTDOOR_MIN   = ( CAM_CALIBDB_ID_AWB_BASE + 20 ),
    CAM_CALIBDB_ID_AWB_GLOBALS_RGPROJ_MAX           = ( CAM_CALIBDB_ID_AWB_BASE + 21 ),
    CAM_CALIBDB_ID_AWB_GLOBALS_RGPROJ_MAX_SKY       = ( CAM_CALIBDB_ID_AWB_BASE + 22 ),
    CAM_CALIBDB_ID_AWB_ILLUMINATION_PROFILE         = ( CAM_CALIBDB_ID_AWB_BASE + 23 ),

    CAM_CALIBDB_ID_MAX
} CamCalibDbParameterId_t;



#define CREATION_DATE_SIZE          ( 15U )
typedef char                        creation_date_t[CREATION_DATE_SIZE];

#define CREATOR_NAME_SIZE           ( 10U )
typedef char                        creator_name_t[CREATOR_NAME_SIZE];

#define CREATOR_VERSION_SIZE        ( 20U )
typedef char                        creator_version_t[CREATOR_VERSION_SIZE];

#define SENSOR_NAME_SIZE            ( 20U )
typedef char                        sensor_name_t[SENSOR_NAME_SIZE];

#define SENSOR_SAMPLE_ID_SIZE       ( 20U )
typedef char                        sensor_sample_id_t[SENSOR_SAMPLE_ID_SIZE];


/*****************************************************************************/
/**
 * @brief   Global AWB calibration structure
 */
/*****************************************************************************/
typedef struct OTPInfo_s
{
    uint16_t				nRG_Ratio_Typical;                  /**wb rg value*/
    uint16_t				nBG_Ratio_Typical;                  /**wb bg value*/
} OTPInfo_t;

typedef struct CamCalibDbMetaData_s
{
    creation_date_t         cdate;                  /**< creation date */
    creator_name_t          cname;                  /**< name/id of creator */
    creator_version_t       cversion;               /**< version of creation tool (matlab generator) */
    sensor_name_t           sname;                  /**< sensor name */
    sensor_sample_id_t      sid;                    /**< sensor sample id */
	OTPInfo_t				OTPInfo;
} CamCalibDbMetaData_t;



#ifdef __cplusplus
}
#endif


/* @} cam_calibdb_types */


#endif /* __CAM_CALIBDB_TYPES_H__ */

