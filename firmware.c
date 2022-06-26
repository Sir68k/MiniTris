#ifdef FW_S16
    #include "./firmware/firmware_S1.6.c"
#elif defined FW_S15
    #include "./firmware/firmware_S1.5.c"
#elif defined FW_S14
    #include "./firmware/firmware_S1.4.c"
#elif defined FW_S13
    #include "./firmware/firmware_S1.3.c"
#elif defined FW_S11
    #include "./firmware/firmware_S1.1.c"
#elif defined FW_S10
    #include "./firmware/firmware_S1.1.c"
#endif