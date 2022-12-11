
//typedef unsigned char bool;
#define false 0
#define true 1
#define False false 
#define True true 
#define FALSE False 
#define TRUE True 
typedef unsigned char u8;
typedef signed char s8;
#ifndef NULL 
#define NULL ((void*)0)
#endif 
#define null NULL 
#define Null NULL 
#define bit(n) (1<<n)

#define OPAQUE 0

#define DEBUG 1

#define BPP_16 16
#define BPP_32 32
#define TILESIZE 16
#define PIXELSCALE 2
// 720x360 - 1/2 720p
// 640x400 - 2x vga
// 420x240 - 1/3 720p
#define SCREEN_WIDTH 320*PIXELSCALE//720*PIXELSCALE
#define SCREEN_HEIGHT 200*PIXELSCALE//360*PIXELSCALE

#define FPS_120 ((float)(1000.0f / 120.0f))
#define FPS_90 ((float)(1000.0f / 90.0f))
#define FPS_70 ((float)(1000.0f / 70.0f))
#define FPS_60 ((float)(1000.0f / 60.0f))
#define FPS_30 ((float)(1000.0f / 30.0f))
#define FPS_15 ((float)(1000.0f / 15.0f))

#define JOY_UP bit(0)
#define JOY_DOWN bit(1)
#define JOY_LEFT bit(2)
#define JOY_RIGHT bit(3)
#define JOY_A bit(4)
#define JOY_B bit(5)
