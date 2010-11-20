/************************************************************************************************
 * Project: USB AVR-ISP
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-09-19
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2 for private use
 *	        commercial use prohibited 
 *
 * Changes:
 ***********************************************************************************************/

#ifndef __usbconfig_h_included__
#define __usbconfig_h_included__

#define USB_CFG_CLOCK_KHZ       (F_CPU/1000)

/* ---------------------------- Hardware Config ---------------------------- */
#if defined(CCCB_COMPATIBLE)
  #define USB_CFG_IOPORTNAME      D
  #define USB_CFG_DMINUS_BIT      6
  #define USB_CFG_DPLUS_BIT       5
#else
  #define USB_CFG_IOPORTNAME      D
  #define USB_CFG_DMINUS_BIT      6
  #define USB_CFG_DPLUS_BIT       5
#endif
/* --------------------------- Functional Range ---------------------------- */

#ifndef BOOTLOADER
 #ifndef ISAVRISPMKII
  #ifndef USB_HID
   #define USB_CFG_HAVE_INTRIN_ENDPOINT    1
   #define USB_CFG_HAVE_INTRIN_ENDPOINT3   1
  #else
   #define USB_CFG_HAVE_INTRIN_ENDPOINT    0
   #define USB_CFG_HAVE_INTRIN_ENDPOINT3   0
  #endif
 #else //AVRISPmkII
   #define USB_CFG_HAVE_INTRIN_ENDPOINT    1
   #define USB_CFG_HAVE_INTRIN_ENDPOINT3   0
   #define USB_CFG_EP3_NUMBER              2
 #endif 
#else
 #define USB_CFG_HAVE_INTRIN_ENDPOINT    0
 #define USB_CFG_HAVE_INTRIN_ENDPOINT3   0
#endif
#define USB_CFG_IMPLEMENT_HALT          0
#define USB_CFG_INTR_POLL_INTERVAL      10
#define USB_CFG_IS_SELF_POWERED         0
#define USB_CFG_MAX_BUS_POWER           120
#define USB_CFG_SAMPLE_EXACT            1
#ifndef ISAVRISPMKII
 #define USB_CFG_IMPLEMENT_FN_WRITE      1
 #ifndef BOOTLOADER
  #define USB_CFG_IMPLEMENT_FN_READ       1
  #ifndef USB_HID
   #define USB_CFG_IMPLEMENT_FN_WRITEOUT   1
  #else
   #define USB_CFG_IMPLEMENT_FN_WRITEOUT   0
  #endif
  #define USB_CFG_HAVE_FLOWCONTROL        1
 #else
  #define USB_CFG_IMPLEMENT_FN_READ       0
 #endif
#else
 #define USB_CFG_IMPLEMENT_FN_WRITE      0
 #define USB_CFG_IMPLEMENT_FN_READ       0
 #define USB_CFG_IMPLEMENT_FN_WRITEOUT   1
 #define USB_CFG_HAVE_FLOWCONTROL        1
 #define USB_COUNT_SOF                   0
#endif

/* -------------------------- Device Description --------------------------- */

#ifndef BOOTLOADER
 #ifndef ISAVRISPMKII
  #define  USB_CFG_VENDOR_ID       0xc0, 0x16
  #ifndef USB_HID
   #define  USB_CFG_DEVICE_ID       0xe1, 0x05
  #else
   #define  USB_CFG_DEVICE_ID       0xdc, 0x05
  #endif
 #else //AVRISPmkII
  #define  USB_CFG_VENDOR_ID  	   0xeb, 0x03
  #define  USB_CFG_DEVICE_ID       0x04, 0x21
 #endif
#endif
#ifndef ISAVRISPMKII
 #define USB_CFG_DEVICE_VERSION  0x00, 0x01
#else
 #define USB_CFG_DEVICE_VERSION  0x02, 0x00
#endif
#ifndef ISAVRISPMKII
 #ifndef ISUSBASP
  #define USB_CFG_VENDOR_NAME     'w', 'w', 'w', '.', 'u', 'l', 'l', 'i', 'h', 'o', 'm', 'e', '.', 'd', 'e'
  #define USB_CFG_VENDOR_NAME_LEN 15
  #define USB_CFG_DEVICE_NAME     'A', 'V', 'R', '-', 'I', 'S', 'P'
  #define USB_CFG_DEVICE_NAME_LEN 7
 #else
  #define	USB_CFG_VENDOR_NAME     'w', 'w', 'w', '.', 'f', 'i', 's', 'c', 'h', 'l', '.', 'd', 'e'
  #define USB_CFG_VENDOR_NAME_LEN 13
  #define	USB_CFG_DEVICE_NAME		'U', 'S', 'B', 'a', 's', 'p'
  #define	USB_CFG_DEVICE_NAME_LEN	6 
 #endif
#else
 #define USB_CFG_VENDOR_NAME     'A', 't', 'm', 'e', 'l'
 #define USB_CFG_VENDOR_NAME_LEN 5
 #define USB_CFG_DEVICE_NAME     'A', 'V', 'R', 'I', 'S', 'P', ' ', 'm', 'k', 'I', 'I'
 #define USB_CFG_DEVICE_NAME_LEN 11
#endif

#ifndef ISAVRISPMKII
 #define USB_CFG_SERIAL_NUMBER_LENGTH  0
#else
 #define USB_CFG_SERIAL_NUMBER       'U', 'L', 'L', 'I', 'H', 'O', 'M', 'E', '.', 'D', 'E', '0', '1'
 #define USB_CFG_SERIAL_NUMBER_LEN   13
#endif

#if defined(BOOTLOADER) || defined(USB_HID) 
 #define USB_CFG_DEVICE_CLASS    	0xff
 #define USB_CFG_DEVICE_SUBCLASS 	0
 #define USB_CFG_INTERFACE_CLASS    0
 #define USB_CFG_INTERFACE_SUBCLASS 0
 #define USB_CFG_INTERFACE_PROTOCOL 0 
#else
 #ifndef ISAVRISPMKII
  #define USB_CFG_DEVICE_CLASS        2
  #define USB_CFG_DEVICE_SUBCLASS     0
  #define USB_CFG_INTERFACE_CLASS     0x02    /* CDC class */
  #define USB_CFG_INTERFACE_SUBCLASS  2       /* Abstract (Modem) */
  #define USB_CFG_INTERFACE_PROTOCOL  1       /* AT-Commands */
 #else
  #define USB_CFG_DEVICE_CLASS    	  0xff
  #define USB_CFG_DEVICE_SUBCLASS 	  0
  #define USB_CFG_INTERFACE_CLASS     0xff    /* Vendor specific */
  #define USB_CFG_INTERFACE_SUBCLASS  0       /* none */
  #define USB_CFG_INTERFACE_PROTOCOL  0       /* none */
 #endif
#endif
#define USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH 0
#ifndef ISAVRISPMKII
 #ifndef BOOTLOADER
  #ifndef USB_HID
   #define USB_CFG_DESCR_PROPS_DEVICE                  USB_PROP_IS_DYNAMIC
   #define USB_CFG_DESCR_PROPS_CONFIGURATION           USB_PROP_IS_DYNAMIC
   #define USB_CFG_DESCR_PROPS_STRINGS                 0
   #define USB_CFG_DESCR_PROPS_STRING_0                0
   #define USB_CFG_DESCR_PROPS_STRING_VENDOR           0
   #define USB_CFG_DESCR_PROPS_STRING_PRODUCT          0
   #define USB_CFG_DESCR_PROPS_STRING_SERIAL_NUMBER    0
   #define USB_CFG_DESCR_PROPS_HID                     USB_PROP_IS_DYNAMIC
   #define USB_CFG_DESCR_PROPS_HID_REPORT              0
   #define USB_CFG_DESCR_PROPS_UNKNOWN                 0
  #endif
 #endif
#else
 #define USB_CFG_DESCR_PROPS_DEVICE                  0
 #define USB_CFG_DESCR_PROPS_CONFIGURATION           USB_PROP_IS_DYNAMIC
 #define USB_CFG_DESCR_PROPS_STRINGS                 0
 #define USB_CFG_DESCR_PROPS_STRING_0                0
 #define USB_CFG_DESCR_PROPS_STRING_VENDOR           0
 #define USB_CFG_DESCR_PROPS_STRING_PRODUCT          0
 #define USB_CFG_DESCR_PROPS_STRING_SERIAL_NUMBER    0
 #define USB_CFG_DESCR_PROPS_HID                     0
 #define USB_CFG_DESCR_PROPS_HID_REPORT              0
 #define USB_CFG_DESCR_PROPS_UNKNOWN                 0
#endif

#endif
