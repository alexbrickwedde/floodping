#ifndef BUFFER_H
#define BUFFER_H

#include <inttypes.h>

#define Buf_Size 8

typedef struct
{
    uint8_t get;			//Pointer to the next char
    uint8_t put;			//Pointer to the next empty Position
    uint16_t n;				
	uint16_t size;
    uint8_t *buf;
} BUF_t;


#define BUF_newpos(i,size) (i+1) == size ? 0 : i+1
uint8_t BUF_add(uint8_t);
void    BUF_flush(BUF_t *buffer);
int     BUF_get(BUF_t *buffer);
void    BUF_put(uint8_t val, BUF_t *buffer);
void 	BUF_init(BUF_t *buffer,unsigned char *buf,uint16_t size);


#endif
