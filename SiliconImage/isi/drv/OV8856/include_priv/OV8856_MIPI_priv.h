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
#ifndef __OV8856_PRIV_H__
#define __OV8856_PRIV_H__

#include <ebase/types.h>
#include <common/return_codes.h>
#include <hal/hal_api.h>



#ifdef __cplusplus
extern "C"
{
#endif

/*
*              SILICONIMAGE LIBISP VERSION NOTE
*
*v0.1.0x00 : first version:preview
*v0.2.0 :
*   1). change judgment condition of applying OTP data.
*/


#define CONFIG_SENSOR_DRV_VERSION  KERNEL_VERSION(0, 2, 0)

/*****************************************************************************
 * System control registers
 *****************************************************************************/
//hkw  
#define OV8856_MODE_SELECT                  (0x0100) // rw - Bit[7:1]not used  Bit[0]Streaming set 0: software_standby  1: streaming       
#define OV8856_MODE_SELECT_OFF              (0x00U)
#define OV8856_MODE_SELECT_ON				(0x01U)

#define OV8856_SOFTWARE_RST                 (0x0103) // rw - Bit[7:1]not used  Bit[0]software_reset
#define OV8856_SOFTWARE_RST_VALUE			(0x01)

#define OV8856_CHIP_ID_HIGH_BYTE            (0x300a) // r - 
#define OV8856_CHIP_ID_MIDDLE_BYTE          (0x300b) // r - 
#define OV8856_CHIP_ID_LOW_BYTE             (0x300c) // r -  
#define OV8856_CHIP_ID_HIGH_BYTE_DEFAULT            (0x00) // r - 
#define OV8856_CHIP_ID_MIDDLE_BYTE_DEFAULT          (0x88) // r - 
#define OV8856_CHIP_ID_LOW_BYTE_DEFAULT             (0x5a) //(0x65) // r - 

                                                    //     Bit[3] gain manual enable 0:manual disable use register 0x350a/0x350b   1:manual enable use register 0x3504/0x3505
#define OV8856_AEC_AGC_ADJ_H                (0x3508) // rw- Bit[2:0]gain output to sensor Gain[10:8]
#define OV8856_AEC_AGC_ADJ_L                (0x3509) // rw- Bit[7:0]gain output to sensor Gain[7:0] 

#define OV8856_AEC_EXPO_H                   (0x3500) // rw- Bit[3:0] exposure[19:16]
#define OV8856_AEC_EXPO_M                   (0x3501) // rw- Bit[7:0] exposure[15:8]
#define OV8856_AEC_EXPO_L                   (0x3502) // rw- Bit[7:0] exposure[7:0] low 4 bits are fraction bits which are not supportted and should always be 0.



/*****************************************************************************
 * OV8856 structure
 *****************************************************************************/
typedef struct OV8856_VcmInfo_s                 /* ddl@rock-chips.com: v0.3.0 */
{
    uint32_t StartCurrent;
    uint32_t RatedCurrent;
    uint32_t Step;
    uint32_t StepMode;
} OV8856_VcmInfo_t;
typedef struct OV8856_Context_s
{
    IsiSensorContext_t  IsiCtx;                 /**< common context of ISI and ISI driver layer; @note: MUST BE FIRST IN DRIVER CONTEXT */

    //// modify below here ////

    IsiSensorConfig_t   Config;                 /**< sensor configuration */
    bool_t              Configured;             /**< flags that config was applied to sensor */
    bool_t              Streaming;              /**< flags that sensor is streaming data */
    bool_t              TestPattern;            /**< flags that sensor is streaming test-pattern */

    bool_t              isAfpsRun;              /**< if true, just do anything required for Afps parameter calculation, but DON'T access SensorHW! */

    bool_t              GroupHold;

    float               VtPixClkFreq;           /**< pixel clock */
    uint16_t            LineLengthPck;          /**< line length with blanking */
    uint16_t            FrameLengthLines;       /**< frame line length */

    float               AecMaxGain;
    float               AecMinGain;
    float               AecMaxIntegrationTime;
    float               AecMinIntegrationTime;

    float               AecIntegrationTimeIncrement; /**< _smallest_ increment the sensor/driver can handle (e.g. used for sliders in the application) */
    float               AecGainIncrement;            /**< _smallest_ increment the sensor/driver can handle (e.g. used for sliders in the application) */

    float               AecCurGain;
    float               AecCurIntegrationTime;

    uint16_t            OldGain;               /**< gain multiplier */
    uint32_t            OldCoarseIntegrationTime;
    uint32_t            OldFineIntegrationTime;

    IsiSensorMipiInfo   IsiSensorMipiInfo;
	OV8856_VcmInfo_t    VcmInfo; 
} OV8856_Context_t;

#ifdef __cplusplus
}
#endif

#endif
