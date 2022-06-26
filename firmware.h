#ifndef FIRMWARE_H
#define FIRMWARE_H

#ifdef FW_S16
    #include "./firmware/firmware_S1.6.h"
#elif defined FW_S14
    #include "./firmware/firmware_S1.4.h"
#elif defined FW_S13
    #include "./firmware/firmware_S1.3.h"
#elif defined FW_S11
    #include "./firmware/firmware_S1.1.h"
#elif defined FW_S10
    #include "./firmware/firmware_S1.1.h"
#endif

#endif