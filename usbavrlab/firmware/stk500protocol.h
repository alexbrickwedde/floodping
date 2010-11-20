/************************************************************************************************
 * Project: USB AVR-ISP
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2
 ***********************************************************************************************/

#ifndef __stk500protocol_h_included__
#define __stk500protocol_h_included__

#include <stdint.h>

typedef union{
    uint8_t   bytes[32];
    struct{
        uint16_t  buildVersionLow;
        uint8_t   reserved1[14];
        uint8_t   hardwareVersion;
        uint8_t   softwareVersionMajor;
        uint8_t   softwareVersionMinor;
        uint8_t   reserved2;
        uint8_t   vTarget;
        uint8_t   vRef;
        uint8_t   oscPrescale;
        uint8_t   oscCmatch;
        uint8_t   sckDuration;
        uint8_t   reserved3;
        uint8_t   topcardDetect;
        uint8_t   reserved4;
        uint8_t   status;
        uint8_t   data;
        uint8_t   resetPolarity;
        uint8_t   controllerInit;
    }       s;
} stkParam_t;

typedef struct stkEnterProgIsp{
    uint8_t   timeout;
    uint8_t   stabDelay;
    uint8_t   cmdExeDelay;
    uint8_t   synchLoops;
    uint8_t   byteDelay;
    uint8_t   pollValue;
    uint8_t   pollIndex;
    uint8_t   cmd[4];
}stkEnterProgIsp_t;

typedef struct stkLeaveProgIsp{
    uint8_t   preDelay;
    uint8_t   postDelay;
}stkLeaveProgIsp_t;

typedef struct stkChipEraseIsp{
    uint8_t   eraseDelay;
    uint8_t   pollMethod;
    uint8_t   cmd[4];
}stkChipEraseIsp_t;

typedef struct stkProgramFlashIsp{
    uint8_t   numBytes[2];
    uint8_t   mode;
    uint8_t   delay;
    uint8_t   cmd[3];
    uint8_t   poll[2];
    uint8_t   data[1];    /* actually more data than 1 byte */
}stkProgramFlashIsp_t;

typedef struct stkReadFlashIsp{
    uint8_t  numBytes[2];
    uint8_t   cmd;
}stkReadFlashIsp_t;

typedef struct stkProgramFuseIsp{
    uint8_t   cmd[4];
}stkProgramFuseIsp_t;

typedef struct stkReadFuseIsp{
    uint8_t   retAddr;
    uint8_t   cmd[4];
}stkReadFuseIsp_t;

typedef struct stkMultiIsp{
    uint8_t   numTx;
    uint8_t   numRx;
    uint8_t   rxStartAddr;
    uint8_t   txData[1];  /* actually more than 1 byte */
}stkMultiIsp_t;

/* ------------------------------------------------------------------------- */

#define STK_STX     27
#define STK_TOKEN   14

/* =================== [ STK general command constants ] =================== */

#define STK_CMD_SIGN_ON                         0x01
#define STK_CMD_SET_PARAMETER                   0x02
#define STK_CMD_GET_PARAMETER                   0x03
#define STK_CMD_SET_DEVICE_PARAMETERS           0x04
#define STK_CMD_OSCCAL                          0x05
#define STK_CMD_LOAD_ADDRESS                    0x06
#define STK_CMD_FIRMWARE_UPGRADE                0x07
#define STK_CMD_RESET_PROTECTION                0x0A 

/* =================== [ STK ISP command constants ] =================== */

#define STK_CMD_ENTER_PROGMODE_ISP              0x10
#define STK_CMD_LEAVE_PROGMODE_ISP              0x11
#define STK_CMD_CHIP_ERASE_ISP                  0x12
#define STK_CMD_PROGRAM_FLASH_ISP               0x13
#define STK_CMD_READ_FLASH_ISP                  0x14
#define STK_CMD_PROGRAM_EEPROM_ISP              0x15
#define STK_CMD_READ_EEPROM_ISP                 0x16
#define STK_CMD_PROGRAM_FUSE_ISP                0x17
#define STK_CMD_READ_FUSE_ISP                   0x18
#define STK_CMD_PROGRAM_LOCK_ISP                0x19
#define STK_CMD_READ_LOCK_ISP                   0x1A
#define STK_CMD_READ_SIGNATURE_ISP              0x1B
#define STK_CMD_READ_OSCCAL_ISP                 0x1C
#define STK_CMD_SPI_MULTI                       0x1D

/* =================== [ STK PP command constants ] =================== */

#define STK_CMD_ENTER_PROGMODE_PP               0x20
#define STK_CMD_LEAVE_PROGMODE_PP               0x21
#define STK_CMD_CHIP_ERASE_PP                   0x22
#define STK_CMD_PROGRAM_FLASH_PP                0x23
#define STK_CMD_READ_FLASH_PP                   0x24
#define STK_CMD_PROGRAM_EEPROM_PP               0x25
#define STK_CMD_READ_EEPROM_PP                  0x26
#define STK_CMD_PROGRAM_FUSE_PP                 0x27
#define STK_CMD_READ_FUSE_PP                    0x28
#define STK_CMD_PROGRAM_LOCK_PP                 0x29
#define STK_CMD_READ_LOCK_PP                    0x2A
#define STK_CMD_READ_SIGNATURE_PP               0x2B
#define STK_CMD_READ_OSCCAL_PP                  0x2C    

#define STK_CMD_SET_CONTROL_STACK               0x2D

/* =================== [ STK HVSP command constants ] =================== */

#define STK_CMD_ENTER_PROGMODE_HVSP             0x30
#define STK_CMD_LEAVE_PROGMODE_HVSP             0x31
#define STK_CMD_CHIP_ERASE_HVSP                 0x32
#define STK_CMD_PROGRAM_FLASH_HVSP              0x33
#define STK_CMD_READ_FLASH_HVSP                 0x34
#define STK_CMD_PROGRAM_EEPROM_HVSP             0x35
#define STK_CMD_READ_EEPROM_HVSP                0x36
#define STK_CMD_PROGRAM_FUSE_HVSP               0x37
#define STK_CMD_READ_FUSE_HVSP                  0x38
#define STK_CMD_PROGRAM_LOCK_HVSP               0x39
#define STK_CMD_READ_LOCK_HVSP                  0x3A
#define STK_CMD_READ_SIGNATURE_HVSP             0x3B
#define STK_CMD_READ_OSCCAL_HVSP                0x3C

/* =================== [ STK status constants ] =================== */

/* Success */
#define STK_STATUS_CMD_OK                       0x00

/* Warnings */
#define STK_STATUS_CMD_TOUT                     0x80
#define STK_STATUS_RDY_BSY_TOUT                 0x81
#define STK_STATUS_SET_PARAM_MISSING            0x82

/* Errors */
#define STK_STATUS_CMD_FAILED                   0xC0
#define STK_STATUS_CKSUM_ERROR                  0xC1
#define STK_STATUS_CMD_UNKNOWN                  0xC9

/* =================== [ STK parameter constants ] =================== */
#define STK_PARAM_BUILD_NUMBER_LOW              0x80
#define STK_PARAM_BUILD_NUMBER_HIGH             0x81
#define STK_PARAM_HW_VER                        0x90
#define STK_PARAM_SW_MAJOR                      0x91
#define STK_PARAM_SW_MINOR                      0x92
#define STK_PARAM_VTARGET                       0x94
#define STK_PARAM_VADJUST                       0x95
#define STK_PARAM_OSC_PSCALE                    0x96
#define STK_PARAM_OSC_CMATCH                    0x97
#define STK_PARAM_SCK_DURATION                  0x98
#define STK_PARAM_TOPCARD_DETECT                0x9A
#define STK_PARAM_STATUS                        0x9C
#define STK_PARAM_DATA                          0x9D
#define STK_PARAM_RESET_POLARITY                0x9E
#define STK_PARAM_CONTROLLER_INIT               0x9F

/* =================== [ STK answer constants ] =================== */

#define STK_ANSWER_CKSUM_ERROR                  0xB0

#define PGM_STATUS_PROGRAMMING 1
#define PGM_STATUS_IDLE        2    

extern uint8_t    	STK500_Status;
extern uint32_t  	STK500_Address;
extern stkParam_t   STK500_Param;
extern uint8_t        STK500_Buffer[];
extern uint16_t       STK500_rxPos;
extern uint16_t  	  STK500_rxLen;
extern uint16_t  	  STK500_txLen;

void (*PGM_statuschanged)(uint8_t); 
void STK500_byterecived(uint8_t data);
void STK500_init();
void STK500_save();
void STK500_processmessage();

#endif /* __stk500protocol_h_included__ */
