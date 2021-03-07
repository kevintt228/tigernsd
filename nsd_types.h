#ifndef _NSD_TYPES_H_INCLUDED__
#define _NSD_TYPES_H_INCLUDED__
#include <stdint.h>
#include <unistd.h>
typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

typedef signed long long s64;
typedef unsigned long long u64;

#define  NSD_OK          0
#define  NSD_ERROR      -1
#define  NSD_AGAIN      -2
#define  NSD_BUSY       -3
#define  NSD_DONE       -4
#define  NSD_DECLINED   -5
#define  NSD_ABORT      -6

#endif
