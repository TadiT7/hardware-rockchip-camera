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
#include <ebase/types.h>
#include <ebase/trace.h>
#include <ebase/builtins.h>

#include <common/return_codes.h>

#include "isi.h"
#include "isi_iss.h"
#include "isi_priv.h"
#include "NT99252_priv.h"

//#define RK_PUBLIC_SETTING	//(svga)

/*****************************************************************************
 * DEFINES
 *****************************************************************************/


/*****************************************************************************
 * GLOBALS
 *****************************************************************************/

// Image sensor register settings default values taken from data sheet OV8810_DS_1.1_SiliconImage.pdf.
// The settings may be altered by the code in IsiSetupSensor.
const IsiRegDescription_t NT99252_g_aRegDescription[] =
{
	{0x3069, 0x01,"",eReadWrite,},
	{0x306A, 0x03,"",eReadWrite,},

    {0x3290, 0x01,"",eReadWrite,},  //Init WB R gain
    {0x3291, 0x80,"",eReadWrite,},
    {0x3296, 0x01,"",eReadWrite,},  //Init WB B gain
    {0x3297, 0x80,"",eReadWrite,},
	//{0x3025, 0x02,"",eReadWrite,},
	//{0x32F0, 0x01,"",eReadWrite,},
	{0x302A, 0x00,"",eReadWrite,},
	{0x302C, 0x09,"",eReadWrite,},
	{0x302D, 0x01,"",eReadWrite,},
	{0x301F, 0x80,"",eReadWrite,},
    {0x303E, 0x01,"",eReadWrite,},  //DPC off
    {0x3082, 0x02,"",eReadWrite,}, 
    {0x303F, 0x0E,"",eReadWrite,},
    {0x3051, 0xE8,"",eReadWrite,},
    {0x320A, 0x00,"",eReadWrite,},
    {0x302E, 0x01,"",eReadWrite,},
    {0x3100, 0x01,"",eReadWrite,},
    {0x3101, 0x80,"",eReadWrite,},
    {0x3104, 0x03,"",eReadWrite,},
    {0x3105, 0x03,"",eReadWrite,},
    {0x3106, 0x0D,"",eReadWrite,},
    {0x310A, 0x62,"",eReadWrite,},
    {0x310D, 0x60,"",eReadWrite,},
    {0x3111, 0x5B,"",eReadWrite,}, 
    {0x3131, 0x58,"",eReadWrite,},
    {0x3127, 0x01,"",eReadWrite,},
    {0x3112, 0x63,"",eReadWrite,},  
    {0x3133, 0x00,"",eReadWrite,},
    {0x3134, 0x02,"",eReadWrite,},
    {0x3135, 0x5A,"",eReadWrite,},
    {0x3210, 0x1B,"",eReadWrite,},  //Gain0 of R  //Lsc_70 
    {0x3211, 0x1B,"",eReadWrite,},  //Gain1 of R
    {0x3212, 0x1B,"",eReadWrite,},  //Gain2 of R
    {0x3213, 0x1B,"",eReadWrite,},  //Gain3 of R
    {0x3214, 0x14,"",eReadWrite,},  //Gain0 of Gr
    {0x3215, 0x14,"",eReadWrite,},  //Gain1 of Gr
    {0x3216, 0x14,"",eReadWrite,},  //Gain2 of Gr
    {0x3217, 0x14,"",eReadWrite,},  //Gain3 of Gr
    {0x3218, 0x14,"",eReadWrite,},  //Gain0 of Gb
    {0x3219, 0x14,"",eReadWrite,},  //Gain1 of Gb
    {0x321A, 0x14,"",eReadWrite,},  //Gain2 of Gb
    {0x321B, 0x14,"",eReadWrite,},  //Gain3 of Gb
    {0x321C, 0x10,"",eReadWrite,},  //Gain0 of B
    {0x321D, 0x10,"",eReadWrite,},  //Gain1 of B
    {0x321E, 0x10,"",eReadWrite,},  //Gain2 of B
    {0x321F, 0x10,"",eReadWrite,},  //Gain3 of B
    {0x3237, 0x08,"",eReadWrite,},
    {0x3238, 0x20,"",eReadWrite,},
    {0x3239, 0x20,"",eReadWrite,},
    {0x323A, 0x20,"",eReadWrite,},
    {0x3243, 0xC3,"",eReadWrite,},
    {0x3244, 0x00,"",eReadWrite,},
    {0x3245, 0x00,"",eReadWrite,},

	/*
	{0x3302, 0x00,"",eReadWrite,}, //CC
	{0x3303, 0x4C,"",eReadWrite,},
	{0x3304, 0x00,"",eReadWrite,},
	{0x3305, 0x96,"",eReadWrite,},
	{0x3306, 0x00,"",eReadWrite,},
	{0x3307, 0x1D,"",eReadWrite,},
	{0x3308, 0x07,"",eReadWrite,},
	{0x3309, 0xCD,"",eReadWrite,},
	{0x330A, 0x07,"",eReadWrite,},
	{0x330B, 0x51,"",eReadWrite,},
	{0x330C, 0x00,"",eReadWrite,},
	{0x330D, 0xE3,"",eReadWrite,},
	{0x330E, 0x00,"",eReadWrite,},
	{0x330F, 0xC6,"",eReadWrite,},
	{0x3310, 0x07,"",eReadWrite,},
	{0x3311, 0x4A,"",eReadWrite,},
	{0x3312, 0x07,"",eReadWrite,},
	{0x3313, 0xF1,"",eReadWrite,},

	{0x3270, 0x00,"",eReadWrite,}, //GAMMA
	{0x3271, 0x0B,"",eReadWrite,},
	{0x3272, 0x16,"",eReadWrite,},
	{0x3273, 0x2B,"",eReadWrite,},
	{0x3274, 0x3F,"",eReadWrite,},
	{0x3275, 0x51,"",eReadWrite,},
	{0x3276, 0x72,"",eReadWrite,},
	{0x3277, 0x8F,"",eReadWrite,},
	{0x3278, 0xA7,"",eReadWrite,},
	{0x3279, 0xBC,"",eReadWrite,},
	{0x327A, 0xDC,"",eReadWrite,},
	{0x327B, 0xF0,"",eReadWrite,},
	{0x327C, 0xFA,"",eReadWrite,},
	{0x327D, 0xFE,"",eReadWrite,},
	{0x327E, 0xFF,"",eReadWrite,},
	*/
	{0x3302, 0x00,"",eReadWrite,},  //[CC_R1]
	{0x3303, 0x5B,"",eReadWrite,}, 
	{0x3304, 0x00,"",eReadWrite,}, 
	{0x3305, 0x6C,"",eReadWrite,}, 
	{0x3306, 0x00,"",eReadWrite,}, 
	{0x3307, 0x3A,"",eReadWrite,}, 
	{0x3308, 0x07,"",eReadWrite,}, 
	{0x3309, 0xBF,"",eReadWrite,}, 
	{0x330A, 0x06,"",eReadWrite,}, 
	{0x330B, 0xF9,"",eReadWrite,}, 
	{0x330C, 0x01,"",eReadWrite,}, 
	{0x330D, 0x48,"",eReadWrite,}, 
	{0x330E, 0x01,"",eReadWrite,}, 
	{0x330F, 0x0B,"",eReadWrite,}, 
	{0x3310, 0x06,"",eReadWrite,}, 
	{0x3311, 0xFD,"",eReadWrite,}, 
	{0x3312, 0x07,"",eReadWrite,}, 
	{0x3313, 0xFB,"",eReadWrite,},

	{0x3270, 0x08,"",eReadWrite,}, // Gamma5
	{0x3271, 0x14,"",eReadWrite,},
	{0x3272, 0x20,"",eReadWrite,},
	{0x3273, 0x36,"",eReadWrite,},
	{0x3274, 0x4B,"",eReadWrite,},
	{0x3275, 0x5D,"",eReadWrite,},
	{0x3276, 0x7E,"",eReadWrite,},
	{0x3277, 0x98,"",eReadWrite,},
	{0x3278, 0xAC,"",eReadWrite,},
	{0x3279, 0xBD,"",eReadWrite,},
	{0x327A, 0xD4,"",eReadWrite,},
	{0x327B, 0xE5,"",eReadWrite,},
	{0x327C, 0xF0,"",eReadWrite,},
	{0x327D, 0xF9,"",eReadWrite,},
	{0x327E, 0xFF,"",eReadWrite,},
		
	{0x3250, 0x01,"",eReadWrite,},  //Top boundary of R / G
	{0x3251, 0x4A,"",eReadWrite,},  // 
	{0x3252, 0x98,"",eReadWrite,},  //Bottom boundary of R / G
	{0x3253, 0x01,"",eReadWrite,},  //Top boundary of B / G
	{0x3254, 0x2B,"",eReadWrite,},  // 
	{0x3255, 0x70,"",eReadWrite,},  //Bottom boundary of B / G
	{0x3256, 0x70,"",eReadWrite,},  //Top boundary of luminance
	{0x3258, 0x10,"",eReadWrite,},
	{0x329B, 0x01,"",eReadWrite,},
	{0x32A1, 0x01,"",eReadWrite,},
	{0x32A2, 0x00,"",eReadWrite,},
	{0x32A3, 0x01,"",eReadWrite,},
	{0x32A4, 0x67,"",eReadWrite,},
	{0x32A5, 0x01,"",eReadWrite,},
	{0x32A6, 0x48,"",eReadWrite,},
	{0x32A7, 0x01,"",eReadWrite,},
	{0x32A8, 0xD0,"",eReadWrite,},
	//{0x32A9, 0x12,"",eReadWrite,},
	//{0x32AA, 0x01,"",eReadWrite,},

	{0x3326, 0x10,"",eReadWrite,},
	{0x3327, 0x01,"",eReadWrite,},
	{0x3360, 0x08,"",eReadWrite,},
	{0x3361, 0x0E,"",eReadWrite,},
	{0x3362, 0x14,"",eReadWrite,},
	{0x3363, 0xB3,"",eReadWrite,},
	{0x3331, 0x0C,"",eReadWrite,},
	{0x3332, 0x40,"",eReadWrite,},
	{0x3365, 0x10,"",eReadWrite,},
	{0x3366, 0x10,"",eReadWrite,},
	{0x3368, 0x38,"",eReadWrite,},
	{0x3369, 0x28,"",eReadWrite,},
	{0x336A, 0x18,"",eReadWrite,},
	{0x336B, 0x08,"",eReadWrite,},
	{0x336D, 0x14,"",eReadWrite,},
	{0x336E, 0x14,"",eReadWrite,},
	{0x336F, 0x00,"",eReadWrite,},
	{0x3370, 0x00,"",eReadWrite,},
	{0x3379, 0x0A,"",eReadWrite,},
	{0x337A, 0x0A,"",eReadWrite,},
	{0x337B, 0x0A,"",eReadWrite,},
	{0x337C, 0x0A,"",eReadWrite,},
	{0x3371, 0x38,"",eReadWrite,},
	{0x3372, 0x38,"",eReadWrite,},
	{0x3373, 0x3F,"",eReadWrite,},
	{0x3374, 0x3F,"",eReadWrite,},
	{0x33A2, 0x00,"",eReadWrite,},
	{0x33A3, 0x30,"",eReadWrite,},
	{0x33A4, 0x01,"",eReadWrite,},
	{0x33C0, 0x0F,"",eReadWrite,}, //chroma
	{0x33C9, 0xD2,"",eReadWrite,},
	//{0x33CA, 0x38,"",eReadWrite,},
	{0x33CA, 0x33,"",eReadWrite,},

	//{0x33C0, 0x03,"",eReadWrite,},	//chroma
	//{0x33C9, 0xCF,"",eReadWrite,},
	//{0x33CA, 0x36,"",eReadWrite,},
	{0x3290, 0x01,"",eReadWrite,},
	{0x3291, 0x80,"",eReadWrite,},
	{0x3296, 0x01,"",eReadWrite,},
	{0x3297, 0x80,"",eReadWrite,},
	{0x3012, 0x02,"",eReadWrite,},
	{0x3013, 0xC0,"",eReadWrite,},

	{0x32B0, 0x66,"",eReadWrite,}, // Spot
	{0x32B1, 0xAA,"",eReadWrite,},
	{0x32B2, 0x01,"",eReadWrite,},	//0x00

	{0x32F2, 0x88,"",eReadWrite,},	//Contrast
	{0x32FC, 0xF8,"",eReadWrite,},

#if 0
	//[AE_Target : 0x32]
	{0x32B8, 0x39,"",eReadWrite,}, 
	{0x32B9, 0x2B,"",eReadWrite,}, 
	{0x32BC, 0x32,"",eReadWrite,}, 
	{0x32BD, 0x36,"",eReadWrite,}, 
	{0x32BE, 0x2E,"",eReadWrite,}, 
#endif
#if 0
	//[AE_Target : 0x34]
	{0x32B8, 0x3B,"",eReadWrite,}, 
	{0x32B9, 0x2D,"",eReadWrite,}, 
	{0x32BC, 0x34,"",eReadWrite,}, 
	{0x32BD, 0x38,"",eReadWrite,}, 
	{0x32BE, 0x30,"",eReadWrite,}, 
#endif
#if 1
	//[AE_Target : 0x38]
	{0x32B8, 0x3F,"",eReadWrite,}, 
	{0x32B9, 0x31,"",eReadWrite,}, 
	{0x32BC, 0x38,"",eReadWrite,}, 
	{0x32BD, 0x3C,"",eReadWrite,},
	{0x32BE, 0x34,"",eReadWrite,},
#endif

	//MCLK:      24.00MHz 
	//PCLK:      48.00MHz 
	//Size:      1600x1200 
	//FPS:       8.33~10.00 
	//Line:      1980 
	//Frame:     1212 
	//Flicker:   50Hz 
	{0x32BB, 0x87,"",eReadWrite,},	//AE Start
	//{0x32B8, 0x3B,"",eReadWrite,}, 
	//{0x32B9, 0x2D,"",eReadWrite,}, 
	//{0x32BC, 0x34,"",eReadWrite,}, 
	//{0x32BD, 0x38,"",eReadWrite,}, 
	//{0x32BE, 0x30,"",eReadWrite,}, 
	{0x32BF, 0x60,"",eReadWrite,}, 
	{0x32C0, 0x78,"",eReadWrite,}, 
	{0x32C1, 0x78,"",eReadWrite,}, 
	{0x32C2, 0x78,"",eReadWrite,}, 
	{0x32C3, 0x00,"",eReadWrite,}, 
	{0x32C4, 0x17,"",eReadWrite,}, 
	{0x32C5, 0x20,"",eReadWrite,}, 
	{0x32C6, 0x20,"",eReadWrite,}, 
	{0x32C7, 0x00,"",eReadWrite,}, 
	{0x32C8, 0x79,"",eReadWrite,}, 
	{0x32C9, 0x78,"",eReadWrite,}, 
	{0x32CA, 0x98,"",eReadWrite,}, 
	{0x32CB, 0x98,"",eReadWrite,}, 
	{0x32CC, 0x98,"",eReadWrite,}, 
	{0x32CD, 0x98,"",eReadWrite,}, 
	{0x32DB, 0x6E,"",eReadWrite,},	//AE End
	{0x3241, 0x83,"",eReadWrite,}, 
	{0x33A0, 0xAE,"",eReadWrite,}, 
	{0x33A1, 0x48,"",eReadWrite,}, 
	{0x32E0, 0x06,"",eReadWrite,},	//Scale Start
	{0x32E1, 0x40,"",eReadWrite,}, 
	{0x32E2, 0x04,"",eReadWrite,}, 
	{0x32E3, 0xB0,"",eReadWrite,}, 
	{0x32E4, 0x00,"",eReadWrite,}, 
	{0x32E5, 0x00,"",eReadWrite,}, 
	{0x32E6, 0x00,"",eReadWrite,}, 
	{0x32E7, 0x00,"",eReadWrite,},	//Scale End
	{0x3200, 0x3E,"",eReadWrite,},	//Mode Control
	{0x3201, 0x7F,"",eReadWrite,},  //Mode Control
	{0x302A, 0x00,"",eReadWrite,},	//PLL Start
	{0x302C, 0x0C,"",eReadWrite,}, 
	{0x302C, 0x0B,"",eReadWrite,}, 
	{0x302D, 0x02,"",eReadWrite,},	//PLL End
	{0x3022, 0x24,"",eReadWrite,},	//Timing Start
	{0x3023, 0x24,"",eReadWrite,}, 
	{0x3002, 0x00,"",eReadWrite,}, 
	{0x3003, 0x04,"",eReadWrite,}, 
	{0x3004, 0x00,"",eReadWrite,}, 
	{0x3005, 0x04,"",eReadWrite,}, 
	{0x3006, 0x06,"",eReadWrite,}, 
	{0x3007, 0x43,"",eReadWrite,}, 
	{0x3008, 0x04,"",eReadWrite,}, 
	{0x3009, 0xCC,"",eReadWrite,}, 
	{0x300A, 0x07,"",eReadWrite,}, 
	{0x300B, 0xBC,"",eReadWrite,}, 
	{0x300C, 0x04,"",eReadWrite,}, 
	{0x300D, 0xBC,"",eReadWrite,}, 
	{0x300E, 0x06,"",eReadWrite,}, 
	{0x300F, 0x40,"",eReadWrite,}, 
	{0x3010, 0x04,"",eReadWrite,}, 
	{0x3011, 0xB0,"",eReadWrite,},	//Timing End
	{0x325C, 0x03,"",eReadWrite,}, 
	{0x320A, 0x00,"",eReadWrite,}, 
	{0x3021, 0x02,"",eReadWrite,}, 
	{0x3060, 0x01,"",eReadWrite,}, 

    {0x0000, 0x00,"eTableEnd",eTableEnd} //end flag
};

const IsiRegDescription_t NT99252_g_svga[] =
{
	{0x334A, 0x00,"",eReadWrite,}, //[GF_Preview]
	{0x334B, 0x7F,"",eReadWrite,},
	{0x334C, 0x1F,"",eReadWrite,},

	//MCLK:      24.00MHz 
	//PCLK:      48.00MHz 
	//Size:      800x600 
	//FPS:       8.33~10.00 
	//Line:      1980 
	//Frame:     1212 
	//Flicker:   50Hz 
	{0x32BB, 0x87,"",eReadWrite,},	//AE Start
	//{0x32B8, 0x3B,"",eReadWrite,}, 
	//{0x32B9, 0x2D,"",eReadWrite,}, 
	//{0x32BC, 0x34,"",eReadWrite,}, 
	//{0x32BD, 0x38,"",eReadWrite,}, 
	//{0x32BE, 0x30,"",eReadWrite,}, 
	{0x32BF, 0x60,"",eReadWrite,}, 
	{0x32C0, 0x78,"",eReadWrite,}, 
	{0x32C1, 0x78,"",eReadWrite,}, 
	{0x32C2, 0x78,"",eReadWrite,}, 
	{0x32C3, 0x00,"",eReadWrite,}, 
	{0x32C4, 0x17,"",eReadWrite,}, 
	{0x32C5, 0x20,"",eReadWrite,}, 
	{0x32C6, 0x20,"",eReadWrite,}, 
	{0x32C7, 0x00,"",eReadWrite,}, 
	{0x32C8, 0x79,"",eReadWrite,}, 
	{0x32C9, 0x78,"",eReadWrite,}, 
	{0x32CA, 0x98,"",eReadWrite,}, 
	{0x32CB, 0x98,"",eReadWrite,}, 
	{0x32CC, 0x98,"",eReadWrite,}, 
	{0x32CD, 0x98,"",eReadWrite,}, 
	{0x32DB, 0x6E,"",eReadWrite,},	//AE End
	{0x3241, 0x83,"",eReadWrite,}, 
	{0x33A0, 0xAE,"",eReadWrite,}, 
	{0x33A1, 0x48,"",eReadWrite,}, 
	{0x32E0, 0x03,"",eReadWrite,},	//Scale Start
	{0x32E1, 0x20,"",eReadWrite,}, 
	{0x32E2, 0x02,"",eReadWrite,}, 
	{0x32E3, 0x58,"",eReadWrite,}, 
	{0x32E4, 0x01,"",eReadWrite,}, 
	{0x32E5, 0x00,"",eReadWrite,}, 
	{0x32E6, 0x01,"",eReadWrite,}, 
	{0x32E7, 0x00,"",eReadWrite,},	//Scale End
	{0x3200, 0x3E,"",eReadWrite,},	//Mode Control
	//{0x3201, 0x7F,"",eReadWrite,},  //Mode Control
	{0x302A, 0x00,"",eReadWrite,},	//PLL Start
	{0x302C, 0x0C,"",eReadWrite,}, 
	{0x302C, 0x0B,"",eReadWrite,}, 
	{0x302D, 0x02,"",eReadWrite,},	//PLL End
	{0x3022, 0x24,"",eReadWrite,},	//Timing Start
	{0x3023, 0x24,"",eReadWrite,}, 
	{0x3002, 0x00,"",eReadWrite,}, 
	{0x3003, 0x04,"",eReadWrite,}, 
	{0x3004, 0x00,"",eReadWrite,}, 
	{0x3005, 0x04,"",eReadWrite,}, 
	{0x3006, 0x06,"",eReadWrite,}, 
	{0x3007, 0x43,"",eReadWrite,}, 
	{0x3008, 0x04,"",eReadWrite,}, 
	{0x3009, 0xCC,"",eReadWrite,}, 
	{0x300A, 0x07,"",eReadWrite,}, 
	{0x300B, 0xBC,"",eReadWrite,}, 
	{0x300C, 0x04,"",eReadWrite,}, 
	{0x300D, 0xBC,"",eReadWrite,}, 
	{0x300E, 0x06,"",eReadWrite,}, 
	{0x300F, 0x40,"",eReadWrite,}, 
	{0x3010, 0x04,"",eReadWrite,}, 
	{0x3011, 0xB0,"",eReadWrite,},	//Timing End
	{0x325C, 0x03,"",eReadWrite,}, 
	{0x320A, 0x6C,"",eReadWrite,}, 
	{0x3021, 0x02,"",eReadWrite,}, 
	{0x3060, 0x01,"",eReadWrite,}, 

    {0x0000 ,0x00,"eTableEnd",eTableEnd}
};

const IsiRegDescription_t NT99252_g_720p[] =
{
	{0x334A, 0x34,"",eReadWrite,}, //[GF_Capture]
	{0x334B, 0x14,"",eReadWrite,},
	{0x334C, 0x10,"",eReadWrite,},

	//[YUYV_1280x720_10.00_15.00_FPS]
	//MCLK: 	 24.00MHz 
	//PCLK: 	 56.00MHz 
	//Size: 	 1280x720 
	//FPS:		 10.00~15.00 
	//Line: 	 1940 
	//Frame:	  962 
	//Flicker:	 50Hz 
	{0x32BB, 0x87,"",eReadWrite,},	//AE Start
	//{0x32B8, 0x3B,"",eReadWrite,}, 
	//{0x32B9, 0x2D,"",eReadWrite,}, 
	//{0x32BC, 0x34,"",eReadWrite,}, 
	//{0x32BD, 0x38,"",eReadWrite,}, 
	//{0x32BE, 0x30,"",eReadWrite,}, 
	{0x32BF, 0x40,"",eReadWrite,}, 
	{0x32C0, 0x74,"",eReadWrite,}, 
	{0x32C1, 0x74,"",eReadWrite,}, 
	{0x32C2, 0x74,"",eReadWrite,}, 
	{0x32C3, 0x00,"",eReadWrite,}, 
	{0x32C4, 0x20,"",eReadWrite,}, 
	{0x32C5, 0x20,"",eReadWrite,}, 
	{0x32C6, 0x20,"",eReadWrite,}, 
	{0x32C7, 0x00,"",eReadWrite,}, 
	{0x32C8, 0x90,"",eReadWrite,}, 
	{0x32C9, 0x74,"",eReadWrite,}, 
	{0x32CA, 0x94,"",eReadWrite,}, 
	{0x32CB, 0x94,"",eReadWrite,}, 
	{0x32CC, 0x94,"",eReadWrite,}, 
	{0x32CD, 0x94,"",eReadWrite,}, 
	{0x32DB, 0x72,"",eReadWrite,},	//AE End
	{0x3241, 0x83,"",eReadWrite,}, 
	{0x33A0, 0xB2,"",eReadWrite,}, 
	{0x33A1, 0x54,"",eReadWrite,}, 
	{0x32E0, 0x05,"",eReadWrite,},	//Scale Start
	{0x32E1, 0x00,"",eReadWrite,}, 
	{0x32E2, 0x02,"",eReadWrite,}, 
	{0x32E3, 0xD0,"",eReadWrite,}, 
	{0x32E4, 0x00,"",eReadWrite,}, 
	{0x32E5, 0x40,"",eReadWrite,}, 
	{0x32E6, 0x00,"",eReadWrite,}, 
	{0x32E7, 0x40,"",eReadWrite,},	//Scale End
	{0x3200, 0x3E,"",eReadWrite,},	//Mode Control
	//{0x3201, 0x7F,"",eReadWrite,},  //Mode Control
	{0x302A, 0x00,"",eReadWrite,},	//PLL Start
	{0x302C, 0x0C,"",eReadWrite,}, 
	{0x302C, 0x1B,"",eReadWrite,}, 
	{0x302D, 0x21,"",eReadWrite,},	//PLL End
	{0x3022, 0x24,"",eReadWrite,},	//Timing Start
	{0x3023, 0x24,"",eReadWrite,}, 
	{0x3002, 0x00,"",eReadWrite,}, 
	{0x3003, 0x04,"",eReadWrite,}, 
	{0x3004, 0x00,"",eReadWrite,}, 
	{0x3005, 0x9A,"",eReadWrite,}, 
	{0x3006, 0x06,"",eReadWrite,}, 
	{0x3007, 0x43,"",eReadWrite,}, 
	{0x3008, 0x04,"",eReadWrite,}, 
	{0x3009, 0xCC,"",eReadWrite,}, 
	{0x300A, 0x07,"",eReadWrite,}, 
	{0x300B, 0x94,"",eReadWrite,}, 
	{0x300C, 0x03,"",eReadWrite,}, 
	{0x300D, 0xC2,"",eReadWrite,}, 
	{0x300E, 0x06,"",eReadWrite,}, 
	{0x300F, 0x40,"",eReadWrite,}, 
	{0x3010, 0x03,"",eReadWrite,}, 
	{0x3011, 0x84,"",eReadWrite,},	//Timing End
	{0x325C, 0x03,"",eReadWrite,}, 
	{0x320A, 0x47,"",eReadWrite,}, 
	{0x3021, 0x02,"",eReadWrite,}, 
	{0x3060, 0x01,"",eReadWrite,}, 
	
	{0x0000 ,0x00,"eTableEnd",eTableEnd}
};

const IsiRegDescription_t NT99252_g_1600x1200[] =
//const IsiRegDescription_t NT99252_g_2592x1944[] =
{
	{0x334A, 0x34,"",eReadWrite,}, //[GF_Capture]
	{0x334B, 0x14,"",eReadWrite,},
	{0x334C, 0x10,"",eReadWrite,},

    //MCLK:      24.00MHz 
	//PCLK:      48.00MHz 
	//Size:      1600x1200 
	//FPS:       8.33~10.00 
	//Line:      1980 
	//Frame:     1212 
	//Flicker:   50Hz 
    {0x32BB, 0x87,"",eReadWrite,},  //AE Start
	//{0x32B8, 0x3B,"",eReadWrite,}, 
	//{0x32B9, 0x2D,"",eReadWrite,}, 
	//{0x32BC, 0x34,"",eReadWrite,}, 
	//{0x32BD, 0x38,"",eReadWrite,}, 
	//{0x32BE, 0x30,"",eReadWrite,}, 
    {0x32BF, 0x60,"",eReadWrite,}, 
    {0x32C0, 0x78,"",eReadWrite,}, 
    {0x32C1, 0x78,"",eReadWrite,}, 
    {0x32C2, 0x78,"",eReadWrite,}, 
    {0x32C3, 0x00,"",eReadWrite,}, 
    {0x32C4, 0x17,"",eReadWrite,}, 
    {0x32C5, 0x20,"",eReadWrite,}, 
    {0x32C6, 0x20,"",eReadWrite,}, 
    {0x32C7, 0x00,"",eReadWrite,}, 
    {0x32C8, 0x79,"",eReadWrite,}, 
    {0x32C9, 0x78,"",eReadWrite,}, 
    {0x32CA, 0x98,"",eReadWrite,}, 
    {0x32CB, 0x98,"",eReadWrite,}, 
    {0x32CC, 0x98,"",eReadWrite,}, 
    {0x32CD, 0x98,"",eReadWrite,}, 
    {0x32DB, 0x6E,"",eReadWrite,},  //AE End
    {0x3241, 0x83,"",eReadWrite,}, 
    {0x33A0, 0xAE,"",eReadWrite,}, 
    {0x33A1, 0x48,"",eReadWrite,}, 
    {0x32E0, 0x06,"",eReadWrite,},  //Scale Start
    {0x32E1, 0x40,"",eReadWrite,}, 
    {0x32E2, 0x04,"",eReadWrite,}, 
    {0x32E3, 0xB0,"",eReadWrite,}, 
    {0x32E4, 0x00,"",eReadWrite,}, 
    {0x32E5, 0x00,"",eReadWrite,}, 
    {0x32E6, 0x00,"",eReadWrite,}, 
    {0x32E7, 0x00,"",eReadWrite,},  //Scale End
    {0x3200, 0x38,"",eReadWrite,},  //Mode Control
    {0x3200, 0x3E,"",eReadWrite,},  //Mode Control
    //{0x3201, 0x7F,"",eReadWrite,},  //Mode Control    
    {0x302A, 0x00,"",eReadWrite,},  //PLL Start
    {0x302C, 0x0C,"",eReadWrite,}, 
    {0x302C, 0x0B,"",eReadWrite,}, 
    {0x302D, 0x02,"",eReadWrite,},  //PLL End
    {0x3022, 0x24,"",eReadWrite,},  //Timing Start
    {0x3023, 0x24,"",eReadWrite,}, 
    {0x3002, 0x00,"",eReadWrite,}, 
    {0x3003, 0x04,"",eReadWrite,}, 
    {0x3004, 0x00,"",eReadWrite,}, 
    {0x3005, 0x04,"",eReadWrite,}, 
    {0x3006, 0x06,"",eReadWrite,}, 
    {0x3007, 0x43,"",eReadWrite,}, 
    {0x3008, 0x04,"",eReadWrite,}, 
    {0x3009, 0xCC,"",eReadWrite,}, 
    {0x300A, 0x07,"",eReadWrite,}, 
    {0x300B, 0xBC,"",eReadWrite,}, 
    {0x300C, 0x04,"",eReadWrite,}, 
    {0x300D, 0xBC,"",eReadWrite,}, 
    {0x300E, 0x06,"",eReadWrite,}, 
    {0x300F, 0x40,"",eReadWrite,}, 
    {0x3010, 0x04,"",eReadWrite,}, 
    {0x3011, 0xB0,"",eReadWrite,},  //Timing End
    {0x325C, 0x03,"",eReadWrite,}, 
    {0x320A, 0x00,"",eReadWrite,}, 
    {0x3021, 0x02,"",eReadWrite,}, 
    {0x3060, 0x01,"",eReadWrite,},  

    {0x0000 ,0x00,"eTableEnd",eTableEnd}
};
