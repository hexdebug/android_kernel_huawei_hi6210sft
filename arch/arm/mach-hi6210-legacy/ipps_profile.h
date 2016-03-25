#include <linux/types.h>
#include "pwrctrl_multi_dfs.h"

const static u8 bus_profile[][8] = {
	{/*[00: 75MHz]*/
		0x00,0x4B,0x00,0x00, /* Freq: 75MHz*/
		0x00,0x00,0x00,0x00, 	},
	{/*[01: 150MHz]*/
		0x00,0x96,0x00,0x00, /* Freq: 150MHz*/
		0x00,0x00,0x00,0x00, 	},
};

const static u32 cpu_profile_all[][CPU_PROFILE_SIZE / BYTES_PER_UINT32] = {
    {208000,   0x381041,  0x003,  0x9b9b0f,   0x07,   0x40000007,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe0f,   0x090001FF,   0x07,   0x4000000C,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe0f,   0x090001FF,
     416000,   0x2C1041,  0x003,  0x9b9b19,   0x07,   0x40000007,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe19,   0x090001FF,   0x07,   0x4000000C,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe19,   0x090001FF,
     624000,   0x281041,  0x003,  0x9b9b19,   0x11,   0x4000000F,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe19,   0x090001FF,   0x0F,   0x40000017,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe19,   0x090001FF,
     798000,   0x2830FA,  0x003,  0x9b9b26,   0x0B,   0x4000000A,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe26,   0x090001FF,   0x11,   0x4000001A,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe26,   0x090001FF,
     1196000,  0x24207D,  0x103,  0x9b9b26,   0x1B,   0x40000016,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe26,   0x090001FF,   0x0D,   0x40000014,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe26,   0x090001FF,
     1596000,  0x2430FA,  0x103,  0x9b9b35,   0x1F,   0x4000001A,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe35,   0x090001FF,   0x0F,   0x40000017,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe35,   0x090001FF},
     {208000,   0x381041,  0x003,  0x9b9b0f,   0x07,   0x40000007,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe0f,   0x090001FF,   0x07,   0x4000000C,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe0f,   0x090001FF,
     416000,   0x2C1041,  0x003,  0x9b9b19,   0x07,   0x40000007,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe19,   0x090001FF,   0x07,   0x4000000C,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe19,   0x090001FF,
     624000,   0x281041,  0x003,  0x9b9b19,   0x11,   0x4000000F,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe19,   0x090001FF,   0x0F,   0x40000017,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe19,   0x090001FF,
     798000,   0x2830FA,  0x003,  0x9b9b26,   0x0B,   0x4000000A,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe26,   0x090001FF,   0x11,   0x4000001A,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe26,   0x090001FF,
     1196000,  0x24207D,  0x103,  0x9b9b26,   0x1B,   0x40000016,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe26,   0x090001FF,   0x0D,   0x40000014,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe26,   0x090001FF,
     1596000,  0x2430FA,  0x103,  0x9b9b35,   0x1F,   0x4000001A,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe35,   0x090001FF,   0x0F,   0x40000017,    0x87654321, 0xFEDCBA9,  0x87654321, 0xFEDCBA9,  0xe35,   0x090001FF},

};

const static u32 ddr_profile_all[][DDR_PROFILE_SIZE / BYTES_PER_UINT32] = {
   {75000,    0x2,     0x0,    0x00000000, 0x04147, 0x19, 0x01,0x40000003,0x87654321,0x0FEDCBA9,0x87654321,0x0FEDCBA9,0xF19,0x090001FF,0x6318C805,0x12358011,0x43009008,0xAF44C035,0x5F2000,0x11130B08,0x55,1,
    150000,   0x2,     0x0,    0x00000000, 0x01143, 0x19, 0x03,0x40000006,0x87654321,0x0FEDCBA9,0x87654321,0x0FEDCBA9,0xF19,0x090001FF,0x63290D08,0x22458021,0x4300A01A,0xAF497035,0x5F2000,0x11140F08,0x55,1,
    266000,   0x1,     0x0,    0x00000000, 0x31141, 0x19, 0x05,0x40000009,0x87654321,0x0FEDCBA9,0x87654321,0x0FEDCBA9,0xF19,0x090001FF,0x6441950D,0x3C758039,0x53011036,0xAF50B035,0x5f2000,0x12171908,0x55,1,
    360000,   0x0,     0x0,    0x0524104B, 0x10541, 0x19, 0x07,0x4000000C,0x87654321,0x0FEDCBA9,0x87654321,0x0FEDCBA9,0xF19,0x090001FF,0x65521B11,0x5195804D,0x7401704D,0xAF569046,0x5f2000,0x12192208,0x55,1,
    533000,   0x1,     0x1,   0x00000000, 0x30441, 0x19, 0x0D,0x40000014,0x87654321,0x0FEDCBA9,0x87654321,0x0FEDCBA9,0xF19,0x090001FF,0x677B2718,0x77C58071,0x95021077,0xAF616057,0x5f2000,0x132C3108,0x55,0,
    533000,   0x1,     0x1,   0x00000000, 0x30441, 0x19, 0x11,0x4000001A,0x87654321,0x0FEDCBA9,0x87654321,0x0FEDCBA9,0xF26,0x090001FF,0x677B2718,0x77C58071,0x95021077,0xAF616057,0x5f2000,0x132C3108,0x55,0},
   {75000,    0x2,     0x0,    0x00000000, 0x04147, 0x19, 0x01,0x40000003,0x87654321,0x0FEDCBA9,0x87654321,0x0FEDCBA9,0xF19,0x090001FF,0x6318C805,0x12358011,0x43009008,0xAF44C035,0x5F2000,0x11130B08,0x55,1,
    150000,   0x2,     0x0,    0x00000000, 0x01143, 0x19, 0x03,0x40000006,0x87654321,0x0FEDCBA9,0x87654321,0x0FEDCBA9,0xF19,0x090001FF,0x63290D08,0x22458021,0x4300A01A,0xAF497035,0x5F2000,0x11140F08,0x55,1,
    266000,   0x1,     0x0,    0x00000000, 0x31141, 0x19, 0x05,0x40000009,0x87654321,0x0FEDCBA9,0x87654321,0x0FEDCBA9,0xF19,0x090001FF,0x6441950D,0x3C758039,0x53011036,0xAF50B035,0x5f2000,0x12171908,0x55,1,
    360000,   0x0,     0x0,    0x0524104B, 0x10541, 0x19, 0x07,0x4000000C,0x87654321,0x0FEDCBA9,0x87654321,0x0FEDCBA9,0xF19,0x090001FF,0x65521B11,0x5195804D,0x7401704D,0xAF569046,0x5f2000,0x12192208,0x55,1,
    533000,   0x1,     0x1,   0x00000000, 0x30441, 0x19, 0x0D,0x40000014,0x87654321,0x0FEDCBA9,0x87654321,0x0FEDCBA9,0xF19,0x090001FF,0x677B2718,0x77C58071,0x95021077,0xAF616057,0x5f2000,0x132C3108,0x55,0,
    533000,   0x1,     0x1,   0x00000000, 0x30441, 0x19, 0x11,0x4000001A,0x87654321,0x0FEDCBA9,0x87654321,0x0FEDCBA9,0xF26,0x090001FF,0x677B2718,0x77C58071,0x95021077,0xAF616057,0x5f2000,0x132C3108,0x55,0},
};

const static u32 gpu_profile_all[][GPU_PROFILE_SIZE / BYTES_PER_UINT32] = {
    {160000,                                         \
     266000,                                         \
     355000,                                         \
     533000},                                        \
    {160000,                                         \
     266000,                                         \
     355000,                                         \
     533000},                                        \
};

