#include <ebase/types.h>
#include <ebase/trace.h>
#include <ebase/builtins.h>

#include <common/return_codes.h>

#include "isi.h"
#include "isi_iss.h"
#include "isi_priv.h"
#include "SP2509V_MIPI_priv.h"

//AE
#define  SP2509V_P0_0xf7  0x80//78
#define  SP2509V_P0_0xf8  0x74//6e
#define  SP2509V_P0_0xf9  0x80//74
#define  SP2509V_P0_0xfa  0x74//6a
//HEQ
#define  SP2509V_P0_0xdd  0x80
#define  SP2509V_P0_0xde  0x95
//auto lum
#define SP2509V_NORMAL_Y0ffset  	  0x10	//0x0f	 modify by sp_yjp,20120813
#define SP2509V_LOWLIGHT_Y0ffset  0x20

/*****************************************************************************
 * DEFINES
 *****************************************************************************/


/*****************************************************************************
 * GLOBALS
 *****************************************************************************/

const IsiRegDescription_t Sensor_g_aRegDescription[] =
{
	/*1600x1200 init setting*/
/*	{0xfd,0x00,"0x0100",eReadWrite},
	{0x2f,0x04,"0x0100",eReadWrite},
	{0x34,0x00,"0x0100",eReadWrite},
	{0x35,0x00,"0x0100",eReadWrite},
	{0x30,0x1d,"0x0100",eReadWrite},
	{0x33,0x05,"0x0100",eReadWrite},
	{0xfd,0x01,"0x0100",eReadWrite},
	{0x44,0x00,"0x0100",eReadWrite},
	{0x2a,0x4c,"0x0100",eReadWrite},
	{0x2b,0x1e,"0x0100",eReadWrite},	 
	{0x2c,0x60,"0x0100",eReadWrite},
	{0x25,0x11,"0x0100",eReadWrite},
	{0x03,0x01,"0x0100",eReadWrite},
	{0x04,0xfa,"0x0100",eReadWrite},
	{0x09,0x00,"0x0100",eReadWrite},
	{0x0a,0x02,"0x0100",eReadWrite},	 
	{0x06,0x0a,"0x0100",eReadWrite},
	{0x24,0x20,"0x0100",eReadWrite},
	{0x3f,0x00,"0x0100",eReadWrite},
	{0x01,0x01,"0x0100",eReadWrite},
	{0xfb,0x73,"0x0100",eReadWrite},
	{0xfd,0x01,"0x0100",eReadWrite},
	{0x16,0x04,"0x0100",eReadWrite},
	{0x1c,0x09,"0x0100",eReadWrite},
	{0x21,0x46,"0x0100",eReadWrite},
	{0x6c,0x00,"0x0100",eReadWrite},
	{0x6b,0x00,"0x0100",eReadWrite},
	{0x84,0x00,"0x0100",eReadWrite},
	{0x85,0x10,"0x0100",eReadWrite},
	{0x86,0x10,"0x0100",eReadWrite},
	{0x12,0x04,"0x0100",eReadWrite},	 
	{0x13,0x40,"0x0100",eReadWrite},	 
	{0x11,0x20,"0x0100",eReadWrite},
	{0x33,0x40,"0x0100",eReadWrite},	 
	{0xd0,0x03,"0x0100",eReadWrite},
	{0xd1,0x01,"0x0100",eReadWrite},
	{0xd2,0x00,"0x0100",eReadWrite},	 
	{0xd3,0x01,"0x0100",eReadWrite},
	{0xd4,0x20,"0x0100",eReadWrite},	 
	{0x51,0x14,"0x0100",eReadWrite},	 
	{0x52,0x10,"0x0100",eReadWrite},	 
	{0x55,0x30,"0x0100",eReadWrite},
	{0x58,0x10,"0x0100",eReadWrite},
	{0x71,0x10,"0x0100",eReadWrite},
	{0x6f,0x40,"0x0100",eReadWrite},
	{0x75,0x60,"0x0100",eReadWrite},	 
	{0x76,0x10,"0x0100",eReadWrite},	 
	{0x8a,0x22,"0x0100",eReadWrite},
	{0x8b,0x22,"0x0100",eReadWrite},
	{0x19,0x71,"0x0100",eReadWrite},
	{0x29,0x01,"0x0100",eReadWrite},
	{0xfd,0x01,"0x0100",eReadWrite},
	{0x9d,0xea,"0x0100",eReadWrite},
	{0xa0,0x05,"0x0100",eReadWrite},
	{0xa1,0x02,"0x0100",eReadWrite},
	{0xad,0x62,"0x0100",eReadWrite},
	{0xae,0x00,"0x0100",eReadWrite},
	{0xaf,0x85,"0x0100",eReadWrite},
	{0xb1,0x01,"0x0100",eReadWrite},
	{0xfd,0x01,"0x0100",eReadWrite},
	{0xfc,0x10,"0x0100",eReadWrite},
	{0xfe,0x10,"0x0100",eReadWrite},
	{0xf9,0x00,"0x0100",eReadWrite},
	{0xfa,0x00,"0x0100",eReadWrite},
	{0xfd,0x01,"0x0100",eReadWrite},
	{0x8e,0x06,"0x0100",eReadWrite},
	{0x8f,0x40,"0x0100",eReadWrite},
	{0x90,0x04,"0x0100",eReadWrite},
	{0x91,0xb0,"0x0100",eReadWrite},  
	{0x45,0x01,"0x0100",eReadWrite},
	{0x46,0x00,"0x0100",eReadWrite},
	{0x47,0x6c,"0x0100",eReadWrite},
	{0x48,0x03,"0x0100",eReadWrite},
	{0x49,0x8b,"0x0100",eReadWrite},
	{0x4a,0x00,"0x0100",eReadWrite},
	{0x4b,0x07,"0x0100",eReadWrite},
	{0x4c,0x04,"0x0100",eReadWrite},
	{0x4d,0xb7,"0x0100",eReadWrite},
    {0x00,0x00,"eTableEnd",eTableEnd}
*/
	{0xfd,0x00,"0x0100",eReadWrite},
	{0x2f,0x0c,"0x0100",eReadWrite},
	{0x34,0x00,"0x0100",eReadWrite},
	{0x35,0x21,"0x0100",eReadWrite},
	{0x30,0x1d,"0x0100",eReadWrite},
	{0x33,0x05,"0x0100",eReadWrite},
	{0xfd,0x01,"0x0100",eReadWrite},
	{0x44,0x00,"0x0100",eReadWrite},
	{0x2a,0x4c,"0x0100",eReadWrite},
	{0x2b,0x1e,"0x0100",eReadWrite},
	{0x2c,0x60,"0x0100",eReadWrite},
	{0x25,0x11,"0x0100",eReadWrite},
	{0x03,0x04,"0x0100",eReadWrite},
	{0x04,0x74,"0x0100",eReadWrite},
	{0x09,0x00,"0x0100",eReadWrite},
	{0x0a,0x02,"0x0100",eReadWrite},
	{0x06,0x0a,"0x0100",eReadWrite},
	{0x24,0x20,"0x0100",eReadWrite},
	{0x01,0x01,"0x0100",eReadWrite},
	{0xfb,0x73,"0x0100",eReadWrite},
	{0xfd,0x01,"0x0100",eReadWrite},
	{0x16,0x04,"0x0100",eReadWrite},
	{0x1c,0x09,"0x0100",eReadWrite},
	{0x21,0x42,"0x0100",eReadWrite},
	{0x6c,0x00,"0x0100",eReadWrite},
	{0x6b,0x00,"0x0100",eReadWrite},
	{0x84,0x00,"0x0100",eReadWrite},
	{0x85,0x0c,"0x0100",eReadWrite},
	{0x86,0x0c,"0x0100",eReadWrite},
	{0x87,0x00,"0x0100",eReadWrite},
	{0x12,0x04,"0x0100",eReadWrite},
	{0x13,0x40,"0x0100",eReadWrite},
	{0x11,0x20,"0x0100",eReadWrite},
	{0x33,0x40,"0x0100",eReadWrite},
	{0xd0,0x03,"0x0100",eReadWrite},
	{0xd1,0x01,"0x0100",eReadWrite},
	{0xd2,0x00,"0x0100",eReadWrite},
	{0xd3,0x01,"0x0100",eReadWrite},
	{0xd4,0x20,"0x0100",eReadWrite},
	{0x50,0x00,"0x0100",eReadWrite},
	{0x51,0x14,"0x0100",eReadWrite},
	{0x52,0x10,"0x0100",eReadWrite},
	{0x55,0x30,"0x0100",eReadWrite},
	{0x58,0x10,"0x0100",eReadWrite},
	{0x71,0x10,"0x0100",eReadWrite},
	{0x6f,0x40,"0x0100",eReadWrite},
	{0x75,0x60,"0x0100",eReadWrite},
	{0x76,0x34,"0x0100",eReadWrite},
	{0x8a,0x22,"0x0100",eReadWrite},
	{0x8b,0x22,"0x0100",eReadWrite},
	{0x19,0xf1,"0x0100",eReadWrite},
	{0x29,0x01,"0x0100",eReadWrite},
	{0xfd,0x01,"0x0100",eReadWrite},
	{0x9d,0xea,"0x0100",eReadWrite},
	{0xa0,0x29,"0x0100",eReadWrite},
	{0xa1,0x04,"0x0100",eReadWrite},
	{0xad,0x62,"0x0100",eReadWrite},
	{0xae,0x00,"0x0100",eReadWrite},
	{0xaf,0x85,"0x0100",eReadWrite},
	{0xb1,0x01,"0x0100",eReadWrite},
	{0xac,0x01,"0x0100",eReadWrite},
	{0xfd,0x01,"0x0100",eReadWrite},
	{0xf0,0xfd,"0x0100",eReadWrite},
	{0xf1,0xfd,"0x0100",eReadWrite},
	{0xf2,0xfd,"0x0100",eReadWrite},
	{0xf3,0xfd,"0x0100",eReadWrite},
	{0xf4,0x00,"0x0100",eReadWrite},
	{0xf5,0x00,"0x0100",eReadWrite},
	{0xf6,0x00,"0x0100",eReadWrite},
	{0xf7,0x00,"0x0100",eReadWrite},
	{0xfc,0x10,"0x0100",eReadWrite},
	{0xfe,0x10,"0x0100",eReadWrite},
	{0xf9,0x00,"0x0100",eReadWrite},
	{0xfa,0x00,"0x0100",eReadWrite},
	{0x8e,0x06,"0x0100",eReadWrite},
	{0x8f,0x40,"0x0100",eReadWrite},
	{0x90,0x04,"0x0100",eReadWrite},
	{0x91,0xb0,"0x0100",eReadWrite},
	{0x45,0x01,"0x0100",eReadWrite},
	{0x46,0x00,"0x0100",eReadWrite},
	{0x47,0x6c,"0x0100",eReadWrite},
	{0x48,0x03,"0x0100",eReadWrite},
	{0x49,0x8b,"0x0100",eReadWrite},
	{0x4a,0x00,"0x0100",eReadWrite},
	{0x4b,0x07,"0x0100",eReadWrite},
	{0x4c,0x04,"0x0100",eReadWrite},
	{0x4d,0xb7,"0x0100",eReadWrite},
	{0x00,0x00,"eTableEnd",eTableEnd}
};

const IsiRegDescription_t Sensor_g_1600x1200[] =
{
    {0x00,0x00,"eTableEnd",eTableEnd}
};

