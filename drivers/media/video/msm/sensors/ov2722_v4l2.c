#include "msm_sensor.h"
#define SENSOR_NAME "ov2722"
#define PLATFORM_DRIVER_NAME "msm_camera_ov2722"
#define ov2722_obj ov2722_##obj

#ifdef CONFIG_RAWCHIPII
#include "yushanII.h"
#include "ilp0100_ST_api.h"
#include "ilp0100_customer_sensor_config.h"
#endif

DEFINE_MUTEX(ov2722_mut);
DEFINE_MUTEX(ov2722_sensor_init_mut); //CC120902,
static struct msm_sensor_ctrl_t ov2722_s_ctrl;

static struct msm_camera_i2c_reg_conf ov2722_start_settings[] = {
	{0x0100 ,0x01},
{0x301a,0xf0},
};

static struct msm_camera_i2c_reg_conf ov2722_stop_settings[] = {
//	{0x0100 ,0x00},
//{0x301a,0xf1},
};

static struct msm_camera_i2c_reg_conf ov2722_groupon_settings[] = {
};

static struct msm_camera_i2c_reg_conf ov2722_groupoff_settings[] = {
};

static struct msm_camera_i2c_reg_conf ov2722_prev_settings[] = {

};

static struct msm_camera_i2c_reg_conf ov2722_snap_settings[] = {

};



#if defined(CONFIG_MACH_MONARUDO) ||\
    defined(CONFIG_MACH_DELUXE_J) ||\
    defined(CONFIG_MACH_DELUXE_R) ||\
    defined(CONFIG_MACH_IMPRESSION_J) ||\
    defined(CONFIG_MACH_DELUXE_U) ||\
    defined(CONFIG_MACH_DELUXE_UL) ||\
    defined(CONFIG_MACH_DELUXE_UB1)

static struct msm_camera_i2c_reg_conf ov2722_recommend_settings[] = {

{0x0103, 0x01},
{0x3718, 0x10},
{0x3702, 0x24},
{0x373a, 0x60},
{0x3715, 0x01},
{0x3703, 0x2e},
{0x3705, 0x2b},
{0x3730, 0x30},
{0x3704, 0x62},
{0x3f06, 0x3a},
{0x371c, 0x00},
{0x371d, 0xc4},
{0x371e, 0x01},
{0x371f, 0x28},
{0x3708, 0x61},
{0x3709, 0x12},

{0x3800, 0x00},
{0x3801, 0x08},
{0x3802, 0x00},
{0x3803, 0x02},
{0x3804, 0x07},
{0x3805, 0x9b},
{0x3806, 0x04},
{0x3807, 0x45},
{0x3808, 0x07},
{0x3809, 0x80},
{0x380a, 0x04},
{0x380b, 0x38},
{0x380c, 0x08},
{0x380d, 0x5c},
{0x380e, 0x04},
{0x380f, 0x60},
{0x3810, 0x00},
{0x3811, 0x09},
{0x3812, 0x00},
{0x3813, 0x06},

{0x3820, 0x80},
{0x3821, 0x06},
{0x3814, 0x11},
{0x3815, 0x11},
{0x3612, 0x4b},
{0x3618, 0x04},

{0x3a08, 0x01},
{0x3a09, 0x50},
{0x3a0a, 0x01},
{0x3a0b, 0x18},
{0x3a0d, 0x03},
{0x3a0e, 0x03},
{0x4520, 0x00},
{0x4837, 0x1b},
{0x3000, 0xff},
{0x3001, 0xff},
{0x3002, 0xf0},
{0x3600, 0x08},
{0x3621, 0xc0},
{0x3632, 0x53},
{0x3633, 0x63},
{0x3634, 0x24},
{0x3f01, 0x0c},
{0x5001, 0xc1},
{0x3614, 0xf0},
{0x3630, 0x2d},
{0x370b, 0x62},
{0x3706, 0x61},
{0x4000, 0x02},
{0x4002, 0xc5},
{0x4005, 0x08},
{0x404f, 0x84},
{0x4051, 0x00},
{0x5000, 0xff},
{0x3a18, 0x00},
{0x3a19, 0x80},
//{0x3503, 0x00},
{0x3503, 0x07}, // 0->7

{0x4521, 0x00},
{0x5183, 0xb0},
{0x5184, 0xb0},
{0x5185, 0xb0},
{0x370c, 0x0c},

{0x3035, 0x00},
{0x3036, 0x1e},
{0x3037, 0xa1},
{0x303e, 0x19},
{0x3038, 0x06},
{0x3018, 0x04},
{0x3000, 0x00},
{0x3001, 0x00},
{0x3002, 0x00},
{0x3a0f, 0x40},
{0x3a10, 0x38},
{0x3a1b, 0x48},
{0x3a1e, 0x30},
{0x3a11, 0x90},
{0x3a1f, 0x10},

{0x3011, 0x22},

{0x3800, 0x00},
{0x3801, 0x08},
{0x3802, 0x00},
{0x3803, 0x02}, // 00
{0x3804, 0x07},
{0x3805, 0x9b},
{0x3806, 0x04},
{0x3807, 0x45}, // 46
{0x3808, 0x07},
{0x3809, 0x88},
{0x380a, 0x04},
{0x380b, 0x40},
{0x380c, 0x08},
{0x380d, 0x5c},
{0x380e, 0x04},
{0x380f, 0x60+0x10},

{0x3810, 0x00},
{0x3811, 0x05},
{0x3812, 0x00},
{0x3813, 0x02},


{0x3820, 0x86},
{0x3821, 0x00},
{0x3811, 0x06},
{0x3813, 0x03},

//{0x5000,0xcd}, // disable awb
{0x3503,0x07}, // diable ace

#if defined (CONFIG_RAWCHIP)
{0x4009,0x40},  //  Ethan 1003   0x10   /* Black level range */
#else
//{0x4009,0x40},  //  Ethan 1003   0x10   /* Black level range */   /* Do not set this for no rawchip projects */
#endif


//{0x0100, 0x01},
{0x3508,0x00}, // Ethan 1019
{0x3509,0x10}, // Ethan 1019
{0x3501,0x04},//ethan1204//{0x3501,0x03}, // Ethan 1019
{0x3502,0x60},//ethan1204//{0x3502,0x00}, // Ethan 1019

{0x5000,0xcf}, // enable Lens 1023
//R
{0x5800,0x03},
{0x5801,0xcc},
{0x5802,0x02},
{0x5803,0x4b},
{0x5804,0x3e},      // Shading 81%
{0x5805,0x05},
{0x5806,0xc2},
{0x5807,0x08},
//G
{0x5808,0x03},
{0x5809,0xbd},
{0x580a,0x02},
{0x580b,0x57},
{0x580c,0x58},
{0x580d,0x06},
{0x580e,0xc2},
{0x580f,0x08},
//B
{0x5810,0x03},
{0x5811,0xaf},
{0x5812,0x02},
{0x5813,0x4d},
{0x5814,0x4c},
{0x5815,0x06},
{0x5816,0xc2},
{0x5817,0x08},
//{0x3503, 0x00},  // Ethan 1019
{0x4009,0x40},  //  Ethan 1003   0x10
};

static struct msm_camera_i2c_reg_conf ov2722_recommend_settings_yushanii[] = {

{0x0103, 0x01},
{0x3718, 0x10},
{0x3702, 0x24},
{0x373a, 0x60},
{0x3715, 0x01},
{0x3703, 0x2e},
{0x3705, 0x2b},
{0x3730, 0x30},
{0x3704, 0x62},
{0x3f06, 0x3a},
{0x371c, 0x00},
{0x371d, 0xc4},
{0x371e, 0x01},
{0x371f, 0x28},
{0x3708, 0x61},
{0x3709, 0x12},

{0x3800, 0x00},
{0x3801, 0x08},
{0x3802, 0x00},
{0x3803, 0x02},
{0x3804, 0x07},
{0x3805, 0x9b},
{0x3806, 0x04},
{0x3807, 0x45},
{0x3808, 0x07},
{0x3809, 0x80},
{0x380a, 0x04},
{0x380b, 0x38},
{0x380c, 0x08},
{0x380d, 0x5c},
{0x380e, 0x04},
{0x380f, 0x60},
{0x3810, 0x00},
{0x3811, 0x09},
{0x3812, 0x00},
{0x3813, 0x06},

{0x3820, 0x80},
{0x3821, 0x06},
{0x3814, 0x11},
{0x3815, 0x11},
{0x3612, 0x4b},
{0x3618, 0x04},

{0x3a08, 0x01},
{0x3a09, 0x50},
{0x3a0a, 0x01},
{0x3a0b, 0x18},
{0x3a0d, 0x03},
{0x3a0e, 0x03},
{0x4520, 0x00},
{0x4837, 0x1b},
{0x3000, 0xff},
{0x3001, 0xff},
{0x3002, 0xf0},
{0x3600, 0x08},
{0x3621, 0xc0},
{0x3632, 0x53},
{0x3633, 0x63},
{0x3634, 0x24},
{0x3f01, 0x0c},
{0x5001, 0xc1},
{0x3614, 0xf0},
{0x3630, 0x2d},
{0x370b, 0x62},
{0x3706, 0x61},
{0x4000, 0x02},
{0x4002, 0xc5},
{0x4005, 0x08},
{0x404f, 0x84},
{0x4051, 0x00},
{0x5000, 0xff},
{0x3a18, 0x00},
{0x3a19, 0x80},
//{0x3503, 0x00},
{0x3503, 0x07}, // 0->7

{0x4521, 0x00},
{0x5183, 0xb0},
{0x5184, 0xb0},
{0x5185, 0xb0},
{0x370c, 0x0c},

{0x3035, 0x00},
{0x3036, 0x1e},
{0x3037, 0xa1},
{0x303e, 0x19},
{0x3038, 0x06},
{0x3018, 0x04},
{0x3000, 0x00},
{0x3001, 0x00},
{0x3002, 0x00},
{0x3a0f, 0x40},
{0x3a10, 0x38},
{0x3a1b, 0x48},
{0x3a1e, 0x30},
{0x3a11, 0x90},
{0x3a1f, 0x10},

{0x3011, 0x22},

{0x3800, 0x00},
{0x3801, 0x08},
{0x3802, 0x00},
{0x3803, 0x02}, // 00
{0x3804, 0x07},
{0x3805, 0x9b},
{0x3806, 0x04},
{0x3807, 0x45}, // 46
{0x3808, 0x07},
{0x3809, 0x88},
{0x380a, 0x04},
{0x380b, 0x40},
{0x380c, 0x08},
{0x380d, 0x5c},
{0x380e, 0x04},
{0x380f, 0x60+0x10},

{0x3810, 0x00},
{0x3811, 0x05},
{0x3812, 0x00},
{0x3813, 0x02},


{0x3820, 0x86},
{0x3821, 0x00},
{0x3811, 0x06},
{0x3813, 0x03},

//{0x5000,0xcd}, // disable awb
{0x3503,0x07}, // diable ace

#if defined (CONFIG_RAWCHIP)
{0x4009,0x40},  //  Ethan 1003   0x10   /* Black level range */
#else
//{0x4009,0x40},  //  Ethan 1003   0x10   /* Black level range */   /* Do not set this for no rawchip projects */
#endif


//{0x0100, 0x01},
{0x3508,0x00}, // Ethan 1019
{0x3509,0x10}, // Ethan 1019
{0x3501,0x04},//ethan1204//{0x3501,0x03}, // Ethan 1019
{0x3502,0x60},//ethan1204//{0x3502,0x00}, // Ethan 1019

{0x5000,0xcf}, // enable Lens 1023
//R
{0x5800,0x03},
{0x5801,0xcc},
{0x5802,0x02},
{0x5803,0x4b},
{0x5804,0x3e},      // Shading 81%
{0x5805,0x05},
{0x5806,0xc2},
{0x5807,0x08},
//G
{0x5808,0x03},
{0x5809,0xbd},
{0x580a,0x02},
{0x580b,0x57},
{0x580c,0x58},
{0x580d,0x06},
{0x580e,0xc2},
{0x580f,0x08},
//B
{0x5810,0x03},
{0x5811,0xaf},
{0x5812,0x02},
{0x5813,0x4d},
{0x5814,0x4c},
{0x5815,0x06},
{0x5816,0xc2},
{0x5817,0x08},
//{0x3503, 0x00},  // Ethan 1019
{0x4009,0x40},  //  Ethan 1003   0x10
};
#else
static struct msm_camera_i2c_reg_conf ov2722_recommend_settings[] = {
{0x0103, 0x01},
{0x3718, 0x10},
{0x3702, 0x24},
{0x373a, 0x60},
{0x3715, 0x01},
{0x3703, 0x2e},
{0x3705, 0x2b},
{0x3730, 0x30},
{0x3704, 0x62},
{0x3f06, 0x3a},
{0x371c, 0x00},
{0x371d, 0xc4},
{0x371e, 0x01},
{0x371f, 0x28},
{0x3708, 0x61},
{0x3709, 0x12},

{0x3800, 0x00},
{0x3801, 0x08},
{0x3802, 0x00},
{0x3803, 0x02},
{0x3804, 0x07},
{0x3805, 0x9b},
{0x3806, 0x04},
{0x3807, 0x45},
{0x3808, 0x07},
{0x3809, 0x80},
{0x380a, 0x04},
{0x380b, 0x38},
{0x380c, 0x08},
{0x380d, 0x5c},
{0x380e, 0x04},
{0x380f, 0x60},
{0x3810, 0x00},
{0x3811, 0x09},
{0x3812, 0x00},
{0x3813, 0x06},

{0x3820, 0x80},
{0x3821, 0x06},
{0x3814, 0x11},
{0x3815, 0x11},
{0x3612, 0x4b},
{0x3618, 0x04},

{0x3a08, 0x01},
{0x3a09, 0x50},
{0x3a0a, 0x01},
{0x3a0b, 0x18},
{0x3a0d, 0x03},
{0x3a0e, 0x03},
{0x4520, 0x00},
{0x4837, 0x1b},
{0x3000, 0xff},
{0x3001, 0xff},
{0x3002, 0xf0},
{0x3600, 0x08},
{0x3621, 0xc0},
{0x3632, 0x53},
{0x3633, 0x63},
{0x3634, 0x24},
{0x3f01, 0x0c},
{0x5001, 0xc1},
{0x3614, 0xf0},
{0x3630, 0x2d},
{0x370b, 0x62},
{0x3706, 0x61},
{0x4000, 0x02},
{0x4002, 0xc5},
{0x4005, 0x08},
{0x404f, 0x84},
{0x4051, 0x00},
{0x5000, 0xff},
{0x3a18, 0x00},
{0x3a19, 0x80},
{0x3503, 0x07},

{0x4521, 0x00},
{0x5183, 0xb0},
{0x5184, 0xb0},
{0x5185, 0xb0},
{0x370c, 0x0c},

{0x3035, 0x00},
{0x3036, 0x1e},
{0x3037, 0xa1},
{0x303e, 0x19},
{0x3038, 0x06},
{0x3018, 0x04},
{0x3000, 0x00},
{0x3001, 0x00},
{0x3002, 0x00},
{0x3a0f, 0x40},
{0x3a10, 0x38},
{0x3a1b, 0x48},
{0x3a1e, 0x30},
{0x3a11, 0x90},
{0x3a1f, 0x10},

{0x3011, 0x22},

{0x3800, 0x00},
{0x3801, 0x08},
{0x3802, 0x00},
{0x3803, 0x02},
{0x3804, 0x07},
{0x3805, 0x9b},
{0x3806, 0x04},
{0x3807, 0x45},
{0x3808, 0x07},
{0x3809, 0x88},
{0x380a, 0x04},
{0x380b, 0x40},
{0x380c, 0x08},
{0x380d, 0x5c},
{0x380e, 0x04},
{0x380f, 0x70},

{0x3810, 0x00},
{0x3811, 0x05},
{0x3812, 0x00},
{0x3813, 0x02},


{0x3820, 0x86},
{0x3821, 0x00},
{0x3811, 0x06},
{0x3813, 0x03},

{0x5000,0xcd}, // disable awb
{0x3503,0x07}, // diable ace

#if defined (CONFIG_RAWCHIP)
{0x4009,0x40},  //  Ethan 1003   0x10   /* Black level range */
#else
{0x4009,0x40},  //  Ethan 1003   0x10   /* Black level range */
#endif


//{0x0100, 0x01},
};

static struct msm_camera_i2c_reg_conf ov2722_recommend_settings_yushanii[] = {
{0x0103, 0x01},
{0x3718, 0x10},
{0x3702, 0x24},
{0x373a, 0x60},
{0x3715, 0x01},
{0x3703, 0x2e},
{0x3705, 0x2b},
{0x3730, 0x30},
{0x3704, 0x62},
{0x3f06, 0x3a},
{0x371c, 0x00},
{0x371d, 0xc4},
{0x371e, 0x01},
{0x371f, 0x28},
{0x3708, 0x61},
{0x3709, 0x12},

{0x3800, 0x00},
{0x3801, 0x08},
{0x3802, 0x00},
{0x3803, 0x02},
{0x3804, 0x07},
{0x3805, 0x9b},
{0x3806, 0x04},
{0x3807, 0x45},
{0x3808, 0x07},
{0x3809, 0x80},
{0x380a, 0x04},
{0x380b, 0x38},
{0x380c, 0x08},
{0x380d, 0x5c},
{0x380e, 0x04},
{0x380f, 0x60},
{0x3810, 0x00},
{0x3811, 0x09},
{0x3812, 0x00},
{0x3813, 0x06},

{0x3820, 0x80},
{0x3821, 0x06},
{0x3814, 0x11},
{0x3815, 0x11},
{0x3612, 0x4b},
{0x3618, 0x04},

{0x3a08, 0x01},
{0x3a09, 0x50},
{0x3a0a, 0x01},
{0x3a0b, 0x18},
{0x3a0d, 0x03},
{0x3a0e, 0x03},
{0x4520, 0x00},
{0x4837, 0x1b},
{0x3000, 0xff},
{0x3001, 0xff},
{0x3002, 0xf0},
{0x3600, 0x08},
{0x3621, 0xc0},
{0x3632, 0x53},
{0x3633, 0x63},
{0x3634, 0x24},
{0x3f01, 0x0c},
{0x5001, 0xc1},
{0x3614, 0xf0},
{0x3630, 0x2d},
{0x370b, 0x62},
{0x3706, 0x61},
{0x4000, 0x02},
{0x4002, 0xc5},
{0x4005, 0x08},
{0x404f, 0x84},
{0x4051, 0x00},
{0x5000, 0xff},
{0x3a18, 0x00},
{0x3a19, 0x80},
{0x3503, 0x07},

{0x4521, 0x00},
{0x5183, 0xb0},
{0x5184, 0xb0},
{0x5185, 0xb0},
{0x370c, 0x0c},

{0x3035, 0x00},
{0x3036, 0x1e},
{0x3037, 0xa1},
{0x303e, 0x19},
{0x3038, 0x06},
{0x3018, 0x04},
{0x3000, 0x00},
{0x3001, 0x00},
{0x3002, 0x00},
{0x3a0f, 0x40},
{0x3a10, 0x38},
{0x3a1b, 0x48},
{0x3a1e, 0x30},
{0x3a11, 0x90},
{0x3a1f, 0x10},

{0x3011, 0x22},

{0x3800, 0x00},
{0x3801, 0x08},
{0x3802, 0x00},
{0x3803, 0x02},
{0x3804, 0x07},
{0x3805, 0x9b},
{0x3806, 0x04},
{0x3807, 0x45},
{0x3808, 0x07},
{0x3809, 0x88},
{0x380a, 0x04},
{0x380b, 0x40},
{0x380c, 0x08},
{0x380d, 0x5c},
{0x380e, 0x04},
{0x380f, 0x70},

{0x3810, 0x00},
{0x3811, 0x05},
{0x3812, 0x00},
{0x3813, 0x02},


{0x3820, 0x86},
{0x3821, 0x00},
{0x3811, 0x06},
{0x3813, 0x03},

{0x5000,0xcd}, // disable awb
{0x3503,0x07}, // diable ace

#if defined (CONFIG_RAWCHIP)
{0x4009,0x40},  //  Ethan 1003   0x10   /* Black level range */
#else
{0x4009,0x40},  //  Ethan 1003   0x10   /* Black level range */
#endif


{0x3508,0x00},//Joy 1218
{0x3509,0x18},//Joy 1218
{0x3501,0x46},//Joy 1218
{0x3502,0x00},//Joy 1218






{0x5000,0xcf}, // enable Lens 1023
//R
{0x5800,0x03},
{0x5801,0xcc},
{0x5802,0x02},
{0x5803,0x4b},
{0x5804,0x40},      // Shading 
{0x5805,0x05},
{0x5806,0xc2},
{0x5807,0x08},
//G
{0x5808,0x03},
{0x5809,0xcd},
{0x580a,0x02},
{0x580b,0x57},
{0x580c,0x5c},
{0x580d,0x06},
{0x580e,0xc2},
{0x580f,0x08},
//B
{0x5810,0x03},
{0x5811,0xd4},
{0x5812,0x02},
{0x5813,0x4d},
{0x5814,0x54},
{0x5815,0x06},
{0x5816,0xc2},
{0x5817,0x08},

//{0x0100, 0x01},
};
#endif


static struct msm_sensor_output_info_t ov2722_dimensions[] = {
{
	.x_output = 1928,					// 1928 = 0x788
	.y_output = 1088,				// 1088 = 0x440
	.line_length_pclk = 2140,		// 2140 = 0x85c
	.frame_length_lines = 1136,	// 1136 = 0x470
	.vt_pixel_clk = 72000000,
	.op_pixel_clk = 72000000,
	.binning_factor = 1,
	.x_addr_start = 0,
	.y_addr_start = 0,
	.x_addr_end = 1928-1,
	.y_addr_end = 1088-1,
	.x_even_inc = 1,
	.x_odd_inc = 1,
	.y_even_inc = 1,
	.y_odd_inc = 1,
	.binning_rawchip = 0x11,
	.is_hdr = 0,
},
{
	.x_output = 1928,					// 1928 = 0x788
	.y_output = 1088,				// 1088 = 0x440
	.line_length_pclk = 2140,		// 2140 = 0x85c
	.frame_length_lines = 1136,	// 1136 = 0x470
	.vt_pixel_clk = 72000000,
	.op_pixel_clk = 72000000,

	.binning_factor = 1,
	.x_addr_start = 0,
	.y_addr_start = 0,
	.x_addr_end = 1928-1,
	.y_addr_end = 1088-1,
	.x_even_inc = 1,
	.x_odd_inc = 1,
	.y_even_inc = 1,
	.y_odd_inc = 1,
	.binning_rawchip = 0x11,
	.is_hdr = 0,
},
};

static struct msm_sensor_output_info_t ov2722_dimensions_yushanii[] = {
{
	.x_output = 1928,					// 1928 = 0x788
	.y_output = 1088,				// 1088 = 0x440
	.line_length_pclk = 2140,		// 2140 = 0x85c
	.frame_length_lines = 1136,	// 1136 = 0x470
	.vt_pixel_clk = 72000000,
	.op_pixel_clk = 72000000,
	.binning_factor = 1,
	.x_addr_start = 0,
	.y_addr_start = 0,
	.x_addr_end = 1928-1,
	.y_addr_end = 1088-1,
	.x_even_inc = 1,
	.x_odd_inc = 1,
	.y_even_inc = 1,
	.y_odd_inc = 1,
	.binning_rawchip = 0x11,
	.is_hdr = 0,
},
{
	.x_output = 1928,					// 1928 = 0x788
	.y_output = 1088,				// 1088 = 0x440
	.line_length_pclk = 2140,		// 2140 = 0x85c
	.frame_length_lines = 1136,	// 1136 = 0x470
	.vt_pixel_clk = 72000000,
	.op_pixel_clk = 72000000,

	.binning_factor = 1,
	.x_addr_start = 0,
	.y_addr_start = 0,
	.x_addr_end = 1928-1,
	.y_addr_end = 1088-1,
	.x_even_inc = 1,
	.x_odd_inc = 1,
	.y_even_inc = 1,
	.y_odd_inc = 1,
	.binning_rawchip = 0x11,
	.is_hdr = 0,
},
};

static struct msm_sensor_output_reg_addr_t ov2722_reg_addr = {
	.x_output = 0x3808,
	.y_output = 0x380a,
	.line_length_pclk = 0x380c,
	.frame_length_lines = 0x380e,
};
static struct msm_sensor_exp_gain_info_t ov2722_exp_gain_info = {
	.coarse_int_time_addr = 0x3500,
	.global_gain_addr = 0x3508,
	.vert_offset = 4,
	.min_vert = 4, /* min coarse integration time */ /* HTC Angie 20111019 - Fix FPS */
};


static struct v4l2_subdev_info ov2722_subdev_info[] = {
	{
	.code   = V4L2_MBUS_FMT_SBGGR10_1X10,
	.colorspace = V4L2_COLORSPACE_JPEG,
	.fmt    = 1,
	.order    = 0,
	},
	/* more can be supported, to be added later */
};

static struct msm_camera_i2c_conf_array ov2722_init_conf[] = {
	{&ov2722_recommend_settings[0],
	ARRAY_SIZE(ov2722_recommend_settings), 0, MSM_CAMERA_I2C_BYTE_DATA}
};

static struct msm_camera_i2c_conf_array ov2722_init_conf_yushanii[] = {
	{&ov2722_recommend_settings_yushanii[0],
	ARRAY_SIZE(ov2722_recommend_settings_yushanii), 0, MSM_CAMERA_I2C_BYTE_DATA}
};


static struct msm_camera_i2c_conf_array ov2722_confs[] = {
	{&ov2722_snap_settings[0],
	ARRAY_SIZE(ov2722_snap_settings), 0, MSM_CAMERA_I2C_BYTE_DATA},
	{&ov2722_prev_settings[0],
	ARRAY_SIZE(ov2722_prev_settings), 0, MSM_CAMERA_I2C_BYTE_DATA},
};




static struct msm_camera_csid_vc_cfg ov2722_cid_cfg[] = {
	{0, CSI_RAW10, CSI_DECODE_10BIT},
	{1, CSI_EMBED_DATA, CSI_DECODE_8BIT},
};

static struct msm_camera_csi2_params ov2722_csi_params = {
	.csid_params = {
		.lane_assign = 0xe4,
		.lane_cnt = 1,
		.lut_params = {
			.num_cid = 2,
			.vc_cfg = ov2722_cid_cfg,
		},
	},
	.csiphy_params = {
		.lane_cnt = 1,
		.settle_cnt = 20,
	},
};

static struct msm_camera_csi2_params *ov2722_csi_params_array[] = {
	&ov2722_csi_params,
	&ov2722_csi_params,
};

static struct msm_sensor_id_info_t ov2722_id_info = {
	.sensor_id_reg_addr = 0x300a,
	.sensor_id = 0x2722,
};

static int ov2722_sensor_open_init(const struct msm_camera_sensor_info *data)
{
	if (data->sensor_platform_info)
		ov2722_s_ctrl.mirror_flip = data->sensor_platform_info->mirror_flip;

	return 0;
}

static const char *ov2722Vendor = "Omnivision";
static const char *ov2722NAME = "ov2722";
static const char *ov2722Size = "2.1M";

static ssize_t sensor_vendor_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	ssize_t ret = 0;

	sprintf(buf, "%s %s %s\n", ov2722Vendor, ov2722NAME, ov2722Size);
	ret = strlen(buf) + 1;

	return ret;
}

static DEVICE_ATTR(sensor, 0444, sensor_vendor_show, NULL);

static struct kobject *android_ov2722;

static int ov2722_sysfs_init(void)
{
	int ret ;
	pr_info("ov2722:kobject creat and add\n");
	android_ov2722 = kobject_create_and_add("android_camera2", NULL);
	if (android_ov2722 == NULL) {
		pr_info("ov2722_sysfs_init: subsystem_register " \
		"failed\n");
		ret = -ENOMEM;
		return ret ;
	}
	pr_info("ov2722:sysfs_create_file\n");
	ret = sysfs_create_file(android_ov2722, &dev_attr_sensor.attr);
	if (ret) {
		pr_info("ov2722_sysfs_init: sysfs_create_file " \
		"failed\n");
		kobject_del(android_ov2722);
	}

	return 0 ;
}

static struct msm_camera_i2c_client ov2722_sensor_i2c_client = {
	.addr_type = MSM_CAMERA_I2C_WORD_ADDR,
};

int32_t ov2722_power_up(struct msm_sensor_ctrl_t *s_ctrl)
{
	int rc;
	struct sensor_cfg_data cdata;  //CC140211
	struct msm_camera_sensor_info *sdata = NULL;
	pr_info("%s\n", __func__);

	if (s_ctrl && s_ctrl->sensordata)
		sdata = s_ctrl->sensordata;
	else {
		pr_err("%s: s_ctrl sensordata NULL\n", __func__);
		return (-1);
	}

	if (sdata->camera_power_on == NULL) {
		pr_err("sensor platform_data didnt register\n");
		return -EIO;
	}

	rc = sdata->camera_power_on();
	if (rc < 0) {
		pr_err("%s failed to enable power\n", __func__);
		return rc;
	}

	if (!sdata->use_rawchip && (sdata->htc_image != HTC_CAMERA_IMAGE_YUSHANII_BOARD)) {
		rc = msm_camio_clk_enable(sdata,CAMIO_CAM_MCLK_CLK);
		if (rc < 0) {
			return rc;
		}
	}

#ifdef CONFIG_RAWCHIPII
	Ilp0100_enableIlp0100SensorClock(SENSOR_1);
	mdelay(3);	//h/w comment need to delay 3ms after enable mclock then to send i2c command
#endif

	ov2722_sensor_open_init(sdata);
//CC140211
	if (s_ctrl->func_tbl->sensor_i2c_read_fuseid == NULL) {
		rc = -EFAULT;
		return rc;
	}
	rc = s_ctrl->func_tbl->sensor_i2c_read_fuseid(&cdata, s_ctrl);
	if (rc < 0) {
		return rc;
	}
//CC140211~

	pr_info("%s end\n", __func__);

	return 0;  /*msm_sensor_power_up(sdata)*/
}

int32_t ov2722_power_down(struct msm_sensor_ctrl_t *s_ctrl)//(const struct msm_camera_sensor_info *sdata)
{
	int rc;
	struct msm_camera_sensor_info *sdata = NULL;
	pr_info("%s\n", __func__);

	if (s_ctrl && s_ctrl->sensordata)
		sdata = s_ctrl->sensordata;
	else {
		pr_err("%s: s_ctrl sensordata NULL\n", __func__);
		return (-1);
	}

	if (sdata->camera_power_off == NULL) {
		pr_err("sensor platform_data didnt register\n");
		return -EIO;
	}

	if (!sdata->use_rawchip && (sdata->htc_image != HTC_CAMERA_IMAGE_YUSHANII_BOARD)) {
		msm_camio_clk_disable(sdata,CAMIO_CAM_MCLK_CLK);
	}
	rc = sdata->camera_power_off();
	if (rc < 0) {
		pr_err("%s failed to disable power\n", __func__);
		return rc;
	}
	return 0;  /*msm_sensor_power_down(sdata);*/
}

void ov2722_write_exp_line(struct msm_sensor_ctrl_t *s_ctrl, uint16_t line)
{
	if (line>1112) {
		msm_camera_i2c_write(s_ctrl->sensor_i2c_client, 0x350c, line-1112, MSM_CAMERA_I2C_WORD_DATA);
	}
	// 3500[3:0]+3501[7:0]+3502[7:4]
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client, 0x3500, line>>12, MSM_CAMERA_I2C_BYTE_DATA);
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client, 0x3501, (line>>4)&0xff, MSM_CAMERA_I2C_BYTE_DATA);
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client, 0x3502, (line<<4)&0xff, MSM_CAMERA_I2C_BYTE_DATA);
}


int32_t ov2722_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	int	rc = 0;
	/* Retry mechanism for sensor probe fail. Disable by default in CC stage */
	/* int max_probe_count = 5; */
	int max_probe_count = 1;
	int probe_count = 0;

	pr_info("%s\n", __func__);

sensor_probe_retry:
	rc = msm_sensor_i2c_probe(client, id);
	if(rc >= 0)
		ov2722_sysfs_init();
	else {
		/* Retry mechanism for sensor probe fail. Disable by default in CC stage */
		probe_count++;
		if(probe_count < max_probe_count) {
			pr_info("%s  apply sensor probe retry mechanism , probe_count=%d\n", __func__, probe_count);
			goto sensor_probe_retry;
		}
	}

	pr_info("%s: rc(%d)\n", __func__, rc);
	return rc;
}

static const struct i2c_device_id ov2722_i2c_id[] = {
	{SENSOR_NAME, (kernel_ulong_t)&ov2722_s_ctrl},
	{ }
};

static struct i2c_driver ov2722_i2c_driver = {
	.id_table = ov2722_i2c_id,
	.probe  = ov2722_i2c_probe,//msm_sensor_i2c_probe,
	.driver = {
		.name = SENSOR_NAME,
	},
};

static int ov2722_read_fuseid(struct sensor_cfg_data *cdata,
	struct msm_sensor_ctrl_t *s_ctrl)
{
	int32_t rc = 0;
	int i;
	uint16_t read_data = 0;
	uint16_t id_addr[4] = {0x3d09,0x3d0a,0x3d0b,0x3d0c};
	static uint16_t id_data[4] = {0,0,0,0};
	static int first=true;
	
	pr_info("%s called\n", __func__);
	if (!first) {
		cdata->cfg.fuse.fuse_id_word1 = id_data[0];
		cdata->cfg.fuse.fuse_id_word2 = id_data[1];
		cdata->cfg.fuse.fuse_id_word3 = id_data[2];
		cdata->cfg.fuse.fuse_id_word4 = id_data[3];
	
		pr_info("ov2722: catched fuse->fuse_id : 0x%x 0x%x 0x%x 0x%x\n", 
			cdata->cfg.fuse.fuse_id_word1,
			cdata->cfg.fuse.fuse_id_word2,
			cdata->cfg.fuse.fuse_id_word3,
			cdata->cfg.fuse.fuse_id_word4);
		return 0;	
	}
	first = false;

	rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client, 0x100, 1, MSM_CAMERA_I2C_BYTE_DATA);
	if (rc < 0) {
		pr_err("%s: msm_camera_i2c_write failed\n", __func__);
		return rc;
	}
	// clear
	for (i = 0x3d00; i <= 0x3d1f; i++) {
		rc = msm_camera_i2c_write(s_ctrl->sensor_i2c_client, i, 0, MSM_CAMERA_I2C_BYTE_DATA);
		if (rc < 0) {
			pr_err("%s: msm_camera_i2c_write failed\n", __func__);
			return rc;
		}
	}
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client, 0x3d81, 1, MSM_CAMERA_I2C_BYTE_DATA);
    msleep(10);
    
	for (i = 0; i < 4; i++) {
		rc = msm_camera_i2c_read(s_ctrl->sensor_i2c_client, id_addr[i], &read_data, MSM_CAMERA_I2C_BYTE_DATA);
		if (rc < 0) {
			pr_err("%s: msm_camera_i2c_read 0x%x failed\n", __func__,  i);
			return rc;
		}
		id_data[i] = read_data & 0xff;
	}
	
	if (i==4) {
		cdata->cfg.fuse.fuse_id_word1 = id_data[0];
		cdata->cfg.fuse.fuse_id_word2 = id_data[1];
		cdata->cfg.fuse.fuse_id_word3 = id_data[2];
		cdata->cfg.fuse.fuse_id_word4 = id_data[3];
	
		pr_info("ov2722: fuse->fuse_id : 0x%x 0x%x 0x%x 0x%x\n", 
			cdata->cfg.fuse.fuse_id_word1,
			cdata->cfg.fuse.fuse_id_word2,
			cdata->cfg.fuse.fuse_id_word3,
			cdata->cfg.fuse.fuse_id_word4);
	}
	return rc;

}
/* HTC_END*/

static int __init msm_sensor_init_module(void)
{
	pr_info("ov2722 %s\n", __func__);
	return i2c_add_driver(&ov2722_i2c_driver);
}

static struct v4l2_subdev_core_ops ov2722_subdev_core_ops = {
	.ioctl = msm_sensor_subdev_ioctl,
	.s_power = msm_sensor_power,
};

static struct v4l2_subdev_video_ops ov2722_subdev_video_ops = {
	.enum_mbus_fmt = msm_sensor_v4l2_enum_fmt,
};

static struct v4l2_subdev_ops ov2722_subdev_ops = {
	.core = &ov2722_subdev_core_ops,
	.video  = &ov2722_subdev_video_ops,
};

static struct msm_sensor_fn_t ov2722_func_tbl = {
	.sensor_start_stream = msm_sensor_start_stream,
	.sensor_stop_stream = msm_sensor_stop_stream,
	.sensor_group_hold_on = msm_sensor_group_hold_on,
	.sensor_group_hold_off = msm_sensor_group_hold_off,
	.sensor_set_fps = msm_sensor_set_fps,
	.sensor_write_exp_gain_ex = msm_sensor_write_exp_gain1_ex,
	.sensor_write_snapshot_exp_gain_ex = msm_sensor_write_exp_gain1_ex,
	//.sensor_setting = msm_sensor_setting_parallel, //CC120902
	.sensor_setting = msm_sensor_setting_parallel_ov, //CC120902
	.sensor_set_sensor_mode = msm_sensor_set_sensor_mode,
	.sensor_mode_init = msm_sensor_mode_init,
	.sensor_get_output_info = msm_sensor_get_output_info,
	.sensor_config = msm_sensor_config,//ov2722_sensor_config,
	.sensor_power_up = ov2722_power_up,
	.sensor_power_down = ov2722_power_down,
	.sensor_ov2722_write_exp_line=ov2722_write_exp_line,
	.sensor_i2c_read_fuseid = ov2722_read_fuseid,
};

static struct msm_sensor_reg_t ov2722_regs = {
	.default_data_type = MSM_CAMERA_I2C_BYTE_DATA,
	.start_stream_conf = ov2722_start_settings,
	.start_stream_conf_size = ARRAY_SIZE(ov2722_start_settings),
	.stop_stream_conf = ov2722_stop_settings,
	.stop_stream_conf_size = ARRAY_SIZE(ov2722_stop_settings),
	.group_hold_on_conf = ov2722_groupon_settings,
	.group_hold_on_conf_size = ARRAY_SIZE(ov2722_groupon_settings),
	.group_hold_off_conf = ov2722_groupoff_settings,
	.group_hold_off_conf_size =
		ARRAY_SIZE(ov2722_groupoff_settings),
	.init_settings = &ov2722_init_conf[0],
	.init_size = ARRAY_SIZE(ov2722_init_conf),

	.init_settings_yushanii = &ov2722_init_conf_yushanii[0],
	.init_size_yushanii = ARRAY_SIZE(ov2722_init_conf_yushanii),

	.mode_settings = &ov2722_confs[0],
	.output_settings = &ov2722_dimensions[0],
	.num_conf = ARRAY_SIZE(ov2722_confs),

	.output_settings_yushanii = &ov2722_dimensions_yushanii[0],
};

static struct msm_sensor_ctrl_t ov2722_s_ctrl = {
	.msm_sensor_reg = &ov2722_regs,
	.sensor_i2c_client = &ov2722_sensor_i2c_client,
	.sensor_i2c_addr = 0x6c,
	.sensor_output_reg_addr = &ov2722_reg_addr,
	.sensor_id_info = &ov2722_id_info,
	.sensor_exp_gain_info = &ov2722_exp_gain_info,
	.cam_mode = MSM_SENSOR_MODE_INVALID,
	.csi_params = &ov2722_csi_params_array[0],
	.msm_sensor_mutex = &ov2722_mut,
	.sensor_i2c_driver = &ov2722_i2c_driver,
	.sensor_v4l2_subdev_info = ov2722_subdev_info,
	.sensor_v4l2_subdev_info_size = ARRAY_SIZE(ov2722_subdev_info),
	.sensor_v4l2_subdev_ops = &ov2722_subdev_ops,
	.func_tbl = &ov2722_func_tbl,
	.sensor_first_mutex = &ov2722_sensor_init_mut,  //CC120902,
};

module_init(msm_sensor_init_module);
MODULE_DESCRIPTION("OV 2.0 MP Bayer sensor driver");
MODULE_LICENSE("GPL v2");
