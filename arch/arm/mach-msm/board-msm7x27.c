#if defined(CONFIG_MACH_CALLISTO)
#include "board-callisto.c"
#elif defined(CONFIG_MACH_EUROPA)
#include "board-europa.c"
#elif defined(CONFIG_MACH_COOPER)
#include "board-cooper.c"
#elif defined(CONFIG_MACH_GIOATT)
#include "board-gioatt.c"
#elif defined(CONFIG_MACH_BENI)
#include "board-beni.c"
#elif defined(CONFIG_MACH_TASS)
#include "board-tass.c"
#elif defined(CONFIG_MACH_TASSTMO)
#include "board-tasstmo.c"
#elif defined(CONFIG_MACH_TASSMCT)
#include "board-tasstmo.c"
#elif defined(CONFIG_MACH_TASSVTR)
#include "board-tasstmo.c"
#elif defined(CONFIG_MACH_TASSATT)

#include "board-tassatt.c"

#elif defined(CONFIG_MACH_GT2)

#include "board-gt2.c"

#elif defined(CONFIG_MACH_FLIPBOOK)

#include "board-flipbook.c"

#elif defined(CONFIG_MACH_LUCAS)
#include "board-lucas.c"
#endif
