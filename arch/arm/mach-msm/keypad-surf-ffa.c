#if defined(CONFIG_MACH_COOPER)
#include "keypad-cooper.c"
#elif defined(CONFIG_MACH_BENI)
#include "keypad-beni.c"
#elif defined(CONFIG_MACH_TASS)
#include "keypad-tass.c"
#elif defined(CONFIG_MACH_TASSTMO)
#include "keypad-tasstmo.c"
#elif defined(CONFIG_MACH_TASSMCT)
#include "keypad-tasstmo.c"
#elif defined(CONFIG_MACH_TASSVTR)
#include "keypad-tasstmo.c"
#elif defined(CONFIG_MACH_TASSATT)
#include "keypad-tassatt.c"
#elif defined(CONFIG_MACH_GT2)
#include "keypad-gt2.c"
#elif defined(CONFIG_MACH_FLIPBOOK)
#include "keypad-flipbook.c"
#elif defined(CONFIG_MACH_GIOATT)
#include "keypad-gioatt.c"
#elif defined(CONFIG_MACH_LUCAS)
#include "keypad-lucas.c"
#else
#endif

