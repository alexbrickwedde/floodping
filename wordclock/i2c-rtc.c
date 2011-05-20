/*------------------------------------------------------------------------------------------------------------------------------------------------*//**
 * @file i2c-rtc.c
 * 
 *  Handling of an DS1307 I2C real time clock
 *
 * \version $Id: i2c-rtc.c 285 2010-03-24 21:43:24Z vt $
 * 
 * \author Copyright (c) 2010 Frank Meyer - frank(at)fli4l.de
 * 
 * \remarks
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 */
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/

#include <avr/io.h>
#include <util/delay.h>

#include "i2c-master.h"
#include "i2c-rtc.h"
#include "uart.h"
#include "stdio.h"

#define DEVRTC                0xD0                                              // device address of RTC DS1307
static volatile uint8_t i2c_rtc_pulsetype;
static volatile uint8_t i2c_rtc_pulselen;

static uint8_t rtc_initialized = 0;
static uint8_t i2c_rtc_status;

void
save_byte(uint8_t var, uint8_t value)
{
  i2c_rtc_sram_write(0x10 + var, &value, 1);
}

void
read_byte(uint8_t var, uint8_t *value)
{
  i2c_rtc_sram_read(0x10 + var, value, 1);
}

int8_t rtc_offset = 0;

void
set_offset(uint8_t newoffset)
{
  if (newoffset != rtc_offset)
  {
    rtc_offset = newoffset;
    save_byte(cRTCOffset, rtc_offset);
    char s[100];
    sprintf(s, "rtc offset now: %d\r\n", rtc_offset);
    uartPuts(s);
  }
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * bits of control register:
 *
 * NAME     PURPOSE             REMARK
 * OUT      output control      if SQWE=0, the logic level on the SQW/OUT pin is 1 if OUT=1 and is 0 if OUT=0
 * SQWE     square wave enable  enable the oscillator output, rate see below
 * RS1/RS0  rate select         rate select
 *
 * RS1  RS0    SQW output frequency
 *  0    0      1 Hz
 *  0    1      4.096 kHz
 *  1    0      8.192 kHz
 *  1    0      32.768 kHz
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */

#define CTRL_REG_OUT          0x80                                              // output control
#define CTRL_REG_SQWE         0x10                                              // square wave enable
#define CTRL_REG_RS1          0x02                                              // rate select RS1
#define CTRL_REG_RS0          0x01                                              // rate select RS0
static volatile uint8_t ctrlreg;

static inline uint8_t
div10(uint8_t x, uint8_t* o_remaind)
{
  // seems to produce bug in byteToStrLessHundred, but why?
  //uint8_t y;
  //register uint8_t hilf;
  //asm(
  //   "ldi %[temp], 205     \n"
  //   "mul %[temp], %[input]   \n"
  //   "lsr R1             \n"
  //   "lsr R1             \n"
  //   "lsr R1             \n"
  //   "mov %[result], R1  \n"
  //    : [result] "=d" (y), [temp]"=d" (hilf)
  //    : [input]"d" (x)
  //    : "r1","r0"
  // );
  //*o_remaind = x-(10*y);
  //return y;
  uint8_t y = (((uint16_t) x) * 205) >> 11;
  *o_remaind = x - (y * 10);
  return y;
}

uint8_t
bcdtoi(uint8_t bcd)
{
  uint8_t i = 10 * (bcd >> 4) + (bcd & 0x0F);
  return (i);
}

uint8_t
itobcd(uint8_t i)
{
  uint8_t bcd;

#if 0
  bcd = (i / 10) << 4;
  bcd |= (i % 10);
#else
  uint8_t r;

  bcd = div10(i, &r) << 4;
  bcd |= r;
#endif

  return (bcd);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 *  Get I2C status
 *  @details  Returns I2C status
 *  @return    i2c rtc status
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */

uint8_t
i2c_rtc_get_status(void)
{
  return i2c_rtc_status;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 *  Write date & time
 *  @details  Writes date & time into RTC
 *  @param    date & time
 *  @return    TRUE = successful, FALSE = failed
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
uint8_t
i2c_rtc_write(const DATETIME * datetime)
{
  uint8_t rtcbuf[7];
  uint8_t rtc = false;

  if (rtc_initialized)
  {
    rtcbuf[0] = itobcd(datetime->ss); // seconds    00-59
    rtcbuf[1] = itobcd(datetime->mm); // minutes    00-59
    rtcbuf[2] = itobcd(datetime->hh); // hours    00-23
    rtcbuf[3] = itobcd(datetime->wd) + 1; // weekday     1-7
    rtcbuf[4] = itobcd(datetime->DD); // day of month  00-31
    rtcbuf[5] = itobcd(datetime->MM); // month    00-12
    rtcbuf[6] = itobcd(datetime->YY); // year      00-99

    if (i2c_rtc_sram_write(0x00, rtcbuf, 7))
    {
      rtc = true;
    }
  }
  return rtc;
}

void
add_year(DATETIME * datetime)
{
  datetime->YY++;
}

void
sub_year(DATETIME * datetime)
{
  datetime->YY--;
}

void
add_month(DATETIME * datetime)
{
  datetime->MM++;
  if (datetime->MM > 12)
  {
    datetime->MM = 1;
    add_year(datetime);
  }
}

void
sub_month(DATETIME * datetime)
{
  datetime->MM--;
  if (datetime->MM < 1)
  {
    datetime->MM = 12;
    sub_year(datetime);
  }
}

void
add_day(DATETIME * datetime)
{
  datetime->DD++;
  uint8_t days = 31;
  switch (datetime->MM)
  {
  case 4:
  case 6:
  case 9:
  case 11:
    days = 30;
    break;
  case 2:
    days = ((datetime->YY % 4 == 0) && (!(datetime->YY % 100 == 0))) ? 29 : 28;
    break;
  }
  if (datetime->DD > days)
  {
    datetime->DD = 1;
    add_month(datetime);
  }
}

void
sub_day(DATETIME * datetime)
{
  datetime->DD--;
  uint8_t days = 31;
  switch (datetime->MM - 1)
  {
  case 4:
  case 6:
  case 9:
  case 11:
    days = 30;
    break;
  case 2:
    days = ((datetime->YY % 4 == 0) && (!(datetime->YY % 100 == 0))) ? 29 : 28;
    break;
  }
  if (datetime->DD < 1)
  {
    datetime->DD = days;
    sub_month(datetime);
  }
}

void
add_hour(DATETIME * datetime)
{
  datetime->hh++;
  if (datetime->hh > 23)
  {
    datetime->hh = 0;
    add_day(datetime);
  }
}

void
sub_hour(DATETIME * datetime)
{
  if (datetime->hh < 1)
  {
    datetime->hh = 23;
    sub_day(datetime);
  }
  else
  {
    datetime->hh--;
  }
}

void
add_minute(DATETIME * datetime)
{
  datetime->mm++;
  if (datetime->mm > 59)
  {
    datetime->mm = 0;
    add_hour(datetime);
  }
}

void
sub_minute(DATETIME * datetime)
{
  if (datetime->mm < 1)
  {
    datetime->mm = 59;
    sub_hour(datetime);
  }
  else
  {
    datetime->mm--;
  }
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 *  Read date & time
 *  @details  Reads date & time from rtc
 *  @param    date & time
 *  @return    TRUE = successful, FALSE = failed
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */

const uint8_t amziffer[12] =
{ 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };

#define XY2CL(x,y) (x*100 + ((y*6)/10))

#define RISE(x,y) (XY2CL(x,y) - XY2CL(1,15))
#define FALL(x,y) (XY2CL(x,y) - XY2CL(1,30))

//
// Sunset-Timing in local time (non-dst!) / adjust utc-offset in RISE/FALL macro
//
//                       JAN          FEB          MAR          APR          MAI          JUN          JUL          AUG          SEP          OKT          NOV          DEZ          JAN
const int arise[] = { 0, RISE( 8,37), RISE( 8,12), RISE( 7,20), RISE( 6,11), RISE( 5, 8), RISE( 4,52), RISE( 4,20), RISE( 4,55), RISE( 5,43), RISE( 6,31), RISE( 7,23), RISE( 8,12), RISE( 8,37) };
const int afall[] = { 0, FALL(16,34), FALL(17,21), FALL(18,11), FALL(18,50), FALL(19,32), FALL(20,20), FALL(20,52), FALL(20,22), FALL(19,21), FALL(18,13), FALL(17, 9), FALL(16,29), FALL(16,34) };

uint8_t
i2c_rtc_read(DATETIME * datetime, uint8_t bLocal)
{
  uint8_t rtcbuf[7];
  uint8_t rtc = 0;

  if (rtc_initialized)
  {
    if (i2c_rtc_sram_read(0x00, rtcbuf, 7))
    {
      datetime->YY = bcdtoi(rtcbuf[6]); // year
      datetime->MM = bcdtoi(rtcbuf[5]); // month
      datetime->DD = bcdtoi(rtcbuf[4]); // day of month
      //       = bcdtoi(rtcbuf[3]) - 1; // weekday 0-6
      datetime->hh = bcdtoi(rtcbuf[2]); // hours
      datetime->mm = bcdtoi(rtcbuf[1]); // minutes
      datetime->ss = bcdtoi(rtcbuf[0]); // seconds

      uint8_t tziffer = datetime->DD % 7;
      uint8_t mziffer = amziffer[datetime->MM - 1];
      uint8_t jziffer = (datetime->YY + (datetime->YY / 4)) % 7;
      if (datetime->YY % 4 == 0 && datetime->MM < 3)
      {
        jziffer += 6;
      }
      datetime->wd = (tziffer + mziffer + jziffer + 6) % 7;

      rtc = 1;
    }

    if (bLocal != 0)
    {
      int riseduration = 100;

      int mrise = arise[(int) datetime->MM];
      int mfall = afall[(int) datetime->MM];

      int nmrise = arise[datetime->MM + 1];
      int nmfall = afall[datetime->MM + 1];

      int rise = mrise + (((nmrise - mrise) * datetime->DD) / 31);
      int fall = mfall + (((nmfall - mfall) * datetime->DD) / 31);

      datetime->sunrisehh = rise / 100;
      datetime->sunfallhh = fall / 100;
      datetime->sunrisemm = (rise % 100) * 60 / 100;
      datetime->sunfallmm = (fall % 100) * 60 / 100;

      int now = (datetime->hh * 100) + ((datetime->mm * 100) / 60);

      if (now < rise)
      {
        datetime->sunrise = 0;
      }
      else if (now >= rise && now < rise + riseduration)
      {
        datetime->sunrise = ((now - rise) * 100 / riseduration);
      }
      else if (now >= rise + riseduration && now < fall)
      {
        datetime->sunrise = 100;
      }
      else if (now >= fall && now < fall + riseduration)
      {
        datetime->sunrise = 100 - ((now - fall) * 100 / riseduration);
      }
      else
      {
        datetime->sunrise = 0;
      }

      for (int x = 0; x != rtc_offset;)
      {
        if (rtc_offset > 0)
        {
          add_hour(datetime);
          datetime->sunrisehh++;
          datetime->sunfallhh++;
          x++;
        }
        else
        {
          sub_hour(datetime);
          datetime->sunrisehh--;
          datetime->sunfallhh--;
          x--;
        }
      }
      if (datetime->MM < 3 || datetime->MM > 10)
      {
        datetime->dst = 0;
      }
      else if (datetime->MM > 3 && datetime->MM < 10)
      {
        datetime->sunrisehh++;
        datetime->sunfallhh++;
        add_hour(datetime);
        datetime->dst = 1;
      }
      else
      {
        if (datetime->DD - datetime->wd >= 25 && (datetime->wd || datetime->hh > 2))
        {
          if (datetime->MM == 10)
          {
            datetime->dst = 0;
          }
          else
          {
            datetime->sunrisehh++;
            datetime->sunfallhh++;
            add_hour(datetime);
            datetime->dst = 1;
          }
        }
        else
        {
          if (datetime->MM == 3)
          {
            datetime->dst = 0;
          }
          else
          {
            datetime->sunrisehh++;
            datetime->sunfallhh++;
            add_hour(datetime);
            datetime->dst = 1;
          }
        }
      }
    }
  }
  return rtc;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 *  Write data into SRAM
 *  @details  Writes data into SRAM
 *  @param    address
 *  @param    pointer to buffer
 *  @param    length
 *  @return    TRUE = successful, FALSE = failed
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
uint8_t
i2c_rtc_sram_write(uint8_t addr, void * void_valuep, uint8_t length)
{
  unsigned char * valuep = void_valuep;
  uint8_t rtc = 0;

  if (rtc_initialized)
  {
    if (length && addr + length <= 64)
    {
      i2c_master_start_wait(DEVRTC + I2C_WRITE); // set device address and write mode

      if (i2c_master_write(addr, &i2c_rtc_status) == 0) // write address
      {
        rtc = true; // indicate success

        while (length--)
        {
          if (i2c_master_write(*valuep++, &i2c_rtc_status) != 0) // write value
          {
            rtc = false; // indicate errror
            break;
          }
        }
      }

      i2c_master_stop(); // set stop conditon = release bus
    }
  }
  return rtc;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 *  Read data into SRAM
 *  @details  Reads data into SRAM
 *  @param    address
 *  @param    pointer to buffer
 *  @param    length
 *  @return   TRUE = successful, FALSE = failed
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
uint8_t
i2c_rtc_sram_read(uint8_t addr, void * void_valuep, uint8_t length)
{
  unsigned char * valuep = void_valuep;
  uint8_t rtc = false;

  if (rtc_initialized)
  {
    if (length && addr + length <= 64)
    {
      i2c_master_start_wait(DEVRTC + I2C_WRITE); // set device address and write mode

      if (i2c_master_write(addr, &i2c_rtc_status) == 0) // write address
      {
        if (i2c_master_rep_start(DEVRTC + I2C_READ, &i2c_rtc_status) == 0) // set device address and read mode
        {
          rtc = true; // indicate success

          while (--length)
          {
            *valuep++ = i2c_master_read_ack(); // read n'th byte
          }
          *valuep++ = i2c_master_read_nak(); // read last byte
        }
      }

      i2c_master_stop(); // set stop conditon = release bus
    }
  }
  return rtc;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 *  Write control register
 *  @details    Writes control register
 *  @return     TRUE = successful, FALSE = failed
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
static uint8_t
i2c_write_ctrlreg(void)
{
  uint8_t value[1];
  uint8_t rtc = 0;

  value[0] = ctrlreg;

  if (i2c_rtc_sram_write(0x07, value, 1))
  {
    rtc = 1;
  }
  return rtc;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 *  Initialize RTC
 *  @details  Initializes & configures RTC
 *  @param    pointer to byte in order to store errorcode
 *  @param    pointer to byte in order to store I2C status
 *  @return   TRUE = successful, FALSE = failed
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
uint8_t
i2c_rtc_init(uint8_t * errorcode_p, uint8_t * status_p)
{
  uint8_t rtc = false;
  uint8_t seconds;

  *status_p = 0xFF;
  *errorcode_p = i2c_master_init(); // init I2C interface


  if (*errorcode_p == 0)
  {
    rtc_initialized = true;
    ctrlreg = CTRL_REG_OUT; // set SQWE pin to output and set it to high (deactivated, active low!)

    if (i2c_write_ctrlreg())
    {
      rtc = true;

      if (i2c_rtc_sram_read(0x00, &seconds, 1))
      {
        if (seconds & 0x80) // clock stopped?
        {
          seconds &= ~0x80;
          (void) i2c_rtc_sram_write(0x00, &seconds, 1);
        }
      }
      read_byte(cRTCOffset, (uint8_t*)&rtc_offset);
    }
    else
    {
      *errorcode_p = I2C_ERROR_SLAVE_NOT_FOUND;
      *status_p = i2c_rtc_status;
    }
  }

  return rtc;
}

