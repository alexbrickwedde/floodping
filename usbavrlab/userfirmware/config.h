#define HASBOOTLOADER
//#define USBASP_COMPATIBLE //uncomment this for USBasp hardware compatibility
//#define CCCB_COMPATIBLE

//#define HAS_ISP_SPEEDSETTING
#if defined(__AVR_ATmega8__)||defined(__AVR_ATmega168__)
#define HAS_DEBUGPORT
#endif

#if defined(__AVR_ATmega168__)||defined(__AVR_ATmega16__)||defined(__AVR_ATmega32__)
  #define HAS_ISP_SPEEDSETTING //uncomment this if you want an isp speed menue in terminal mode (dont fits in atmega8)
  #define HAS_AVR910_PROTOCOL //uncomment this if you want an isp speed menue in terminal mode (dont fits in atmega8)
  #define HAS_INFO
#else
 #ifdef HAS_STK500_PROTOCOL
  #ifndef ISAVRISPMKII
   #ifndef HASBOOTLOADER
    #define HASMENUE
   #endif
  #endif
 #endif
 #ifdef HAS_AVR910_PROTOCOL
  #ifndef HASBOOTLOADER
   #define HASMENUE
   #define HAS_INFO
  #endif
 #endif
#endif

