#if defined(CONFIG_MACH_COOPER)
#include "synaptics_i2c_rmi4_cooper.c"
#elif defined(CONFIG_MACH_GIOATT)
#include "synaptics_i2c_rmi4_gioatt.c"
#elif defined(CONFIG_MACH_BENI)
#include "synaptics_i2c_rmi4_beni.c"
#elif defined(CONFIG_MACH_TASS)
#include "synaptics_i2c_rmi4_tass.c"
#elif defined(CONFIG_MACH_TASSTMO) && (CONFIG_BOARD_REVISION==0x0)
#include "synaptics_i2c_rmi4_tasstmo.c"
#elif defined(CONFIG_MACH_TASSTMO) && (CONFIG_BOARD_REVISION>=0x1)
#include "synaptics_i2c_rmi4_tasstmo_rev01.c"
#elif defined(CONFIG_MACH_TASSMCT) && (CONFIG_BOARD_REVISION==0x0)
#include "synaptics_i2c_rmi4_tasstmo.c"
#elif defined(CONFIG_MACH_TASSMCT) && (CONFIG_BOARD_REVISION>=0x1)
#include "synaptics_i2c_rmi4_tasstmo_rev01.c"
#elif defined(CONFIG_MACH_TASSVTR) && (CONFIG_BOARD_REVISION==0x0)
#include "synaptics_i2c_rmi4_tasstmo.c"
#elif defined(CONFIG_MACH_TASSVTR) && (CONFIG_BOARD_REVISION>=0x1)
#include "synaptics_i2c_rmi4_tasstmo_rev01.c"
#elif defined(CONFIG_MACH_TASSATT)
#include "synaptics_i2c_rmi4_tassatt.c"
#elif defined(CONFIG_MACH_LUCAS)
#include "synaptics_i2c_rmi4_lucas.c"
#elif defined(CONFIG_MACH_FLIPBOOK)	//ADD_FB TSP
#include "synaptics_i2c_rmi4_flipbook.c"
#else
#endif
