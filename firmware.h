#include <stdint.h>

#if defined FW_S16
    #include "./firmware/firmware_S1.6.h"
#elif defined FW_S15
    #include "./firmware/firmware_S1.5.h"
#elif defined FW_S14
    #include "./firmware/firmware_S1.4.h"
#elif defined FW_S13
    #include "./firmware/firmware_S1.3.h"
#elif defined FW_S12
    #include "./firmware/firmware_S1.2.h"
#elif defined FW_S11
    #include "./firmware/firmware_S1.1.h"
#else //if defined FW_S10
    #include "./firmware/firmware_S1.0.h"
#endif