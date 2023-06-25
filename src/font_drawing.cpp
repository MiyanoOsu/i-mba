#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "video_blit.h"
#include "font_drawing.h"

static uint8_t n2DLib_font[752] =
{
	0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x40, 0x00,	/* Char 033 (!) */
	0x90, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 034 (") */
	0x50, 0x50, 0xF8, 0x50, 0xF8, 0x50, 0x50, 0x00,	/* Char 035 (#) */
	0x20, 0x78, 0xA0, 0x70, 0x28, 0xF0, 0x20, 0x00,	/* Char 036 ($) */
	0xC8, 0xC8, 0x10, 0x20, 0x40, 0x98, 0x98, 0x00,	/* Char 037 (%) */
	0x70, 0x88, 0x50, 0x20, 0x54, 0x88, 0x74, 0x00,	/* Char 038 (&) */
	0x60, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 039 (') */
	0x20, 0x40, 0x80, 0x80, 0x80, 0x40, 0x20, 0x00,	/* Char 040 (() */
	0x20, 0x10, 0x08, 0x08, 0x08, 0x10, 0x20, 0x00,	/* Char 041 ()  */
	0x00, 0x20, 0xA8, 0x70, 0x70, 0xA8, 0x20, 0x00,	/* Char 042 (*) */
	0x00, 0x00, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x00,	/* Char 043 (+) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x20, 0x40,	/* Char 044 (,) */
	0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00,	/* Char 045 (-) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00,	/* Char 046 (.) */
	0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00,	/* Char 047 (/) */
	0x70, 0x88, 0x98, 0xA8, 0xC8, 0x88, 0x70, 0x00,	/* Char 048 (0) */
	0x40, 0xC0, 0x40, 0x40, 0x40, 0x40, 0xE0, 0x00,	/* Char 049 (1) */
	0x70, 0x88, 0x08, 0x10, 0x20, 0x40, 0xF8, 0x00,	/* Char 050 (2) */
	0x70, 0x88, 0x08, 0x10, 0x08, 0x88, 0x70, 0x00,	/* Char 051 (3) */
	0x08, 0x18, 0x28, 0x48, 0xFC, 0x08, 0x08, 0x00,	/* Char 052 (4) */
	0xF8, 0x80, 0x80, 0xF0, 0x08, 0x88, 0x70, 0x00,	/* Char 053 (5) */
	0x20, 0x40, 0x80, 0xF0, 0x88, 0x88, 0x70, 0x00,	/* Char 054 (6) */
	0xF8, 0x08, 0x10, 0x20, 0x40, 0x40, 0x40, 0x00,	/* Char 055 (7) */
	0x70, 0x88, 0x88, 0x70, 0x88, 0x88, 0x70, 0x00,	/* Char 056 (8) */
	0x70, 0x88, 0x88, 0x78, 0x08, 0x08, 0x70, 0x00,	/* Char 057 (9) */
	0x00, 0x00, 0x60, 0x60, 0x00, 0x60, 0x60, 0x00,	/* Char 058 (:) */
	0x00, 0x00, 0x60, 0x60, 0x00, 0x60, 0x60, 0x20,	/* Char 059 (;) */
	0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x00,	/* Char 060 (<) */
	0x00, 0x00, 0xF8, 0x00, 0xF8, 0x00, 0x00, 0x00,	/* Char 061 (=) */
	0x80, 0x40, 0x20, 0x10, 0x20, 0x40, 0x80, 0x00,	/* Char 062 (>) */
	0x78, 0x84, 0x04, 0x08, 0x10, 0x00, 0x10, 0x00,	/* Char 063 (?) */
	0x70, 0x88, 0x88, 0xA8, 0xB8, 0x80, 0x78, 0x00,	/* Char 064 (@) */
	0x20, 0x50, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x00,	/* Char 065 (A) */
	0xF0, 0x88, 0x88, 0xF0, 0x88, 0x88, 0xF0, 0x00,	/* Char 066 (B) */
	0x70, 0x88, 0x80, 0x80, 0x80, 0x88, 0x70, 0x00,	/* Char 067 (C) */
	0xF0, 0x88, 0x88, 0x88, 0x88, 0x88, 0xF0, 0x00,	/* Char 068 (D) */
	0xF8, 0x80, 0x80, 0xE0, 0x80, 0x80, 0xF8, 0x00,	/* Char 069 (E) */
	0xF8, 0x80, 0x80, 0xE0, 0x80, 0x80, 0x80, 0x00,	/* Char 070 (F) */
	0x70, 0x88, 0x80, 0x80, 0x98, 0x88, 0x78, 0x00,	/* Char 071 (G) */
	0x88, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x88, 0x00,	/* Char 072 (H) */
	0xE0, 0x40, 0x40, 0x40, 0x40, 0x40, 0xE0, 0x00,	/* Char 073 (I) */
	0x38, 0x10, 0x10, 0x10, 0x10, 0x90, 0x60, 0x00,	/* Char 074 (J) */
	0x88, 0x90, 0xA0, 0xC0, 0xA0, 0x90, 0x88, 0x00,	/* Char 075 (K) */
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xF8, 0x00,	/* Char 076 (L) */
	0x82, 0xC6, 0xAA, 0x92, 0x82, 0x82, 0x82, 0x00,	/* Char 077 (M) */
	0x84, 0xC4, 0xA4, 0x94, 0x8C, 0x84, 0x84, 0x00,	/* Char 078 (N) */
	0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00,	/* Char 079 (O) */
	0xF0, 0x88, 0x88, 0xF0, 0x80, 0x80, 0x80, 0x00,	/* Char 080 (P) */
	0x70, 0x88, 0x88, 0x88, 0xA8, 0x90, 0x68, 0x00,	/* Char 081 (Q) */
	0xF0, 0x88, 0x88, 0xF0, 0xA0, 0x90, 0x88, 0x00,	/* Char 082 (R) */
	0x70, 0x88, 0x80, 0x70, 0x08, 0x88, 0x70, 0x00,	/* Char 083 (S) */
	0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00,	/* Char 084 (T) */
	0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00,	/* Char 085 (U) */
	0x88, 0x88, 0x88, 0x50, 0x50, 0x20, 0x20, 0x00,	/* Char 086 (V) */
	0x82, 0x82, 0x82, 0x82, 0x92, 0x92, 0x6C, 0x00,	/* Char 087 (W) */
	0x88, 0x88, 0x50, 0x20, 0x50, 0x88, 0x88, 0x00,	/* Char 088 (X) */
	0x88, 0x88, 0x88, 0x50, 0x20, 0x20, 0x20, 0x00,	/* Char 089 (Y) */
	0xF8, 0x08, 0x10, 0x20, 0x40, 0x80, 0xF8, 0x00,	/* Char 090 (Z) */
	0xE0, 0x80, 0x80, 0x80, 0x80, 0x80, 0xE0, 0x00,	/* Char 091 ([) */
	0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00,	/* Char 092 (\) */
	0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x00,	/* Char 093 (]) */
	0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 094 (^) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00,	/* Char 095 (_) */
	0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 096 (`) */
	0x00, 0x00, 0x70, 0x08, 0x78, 0x88, 0x74, 0x00,	/* Char 097 (a) */
	0x80, 0x80, 0xB0, 0xC8, 0x88, 0xC8, 0xB0, 0x00,	/* Char 098 (b) */
	0x00, 0x00, 0x70, 0x88, 0x80, 0x88, 0x70, 0x00,	/* Char 099 (c) */
	0x08, 0x08, 0x68, 0x98, 0x88, 0x98, 0x68, 0x00,	/* Char 100 (d) */
	0x00, 0x00, 0x70, 0x88, 0xF8, 0x80, 0x70, 0x00,	/* Char 101 (e) */
	0x30, 0x48, 0x40, 0xE0, 0x40, 0x40, 0x40, 0x00,	/* Char 102 (f) */
	0x00, 0x00, 0x34, 0x48, 0x48, 0x38, 0x08, 0x30,	/* Char 103 (g) */
	0x80, 0x80, 0xB0, 0xC8, 0x88, 0x88, 0x88, 0x00,	/* Char 104 (h) */
	0x20, 0x00, 0x60, 0x20, 0x20, 0x20, 0x70, 0x00,	/* Char 105 (i) */
	0x10, 0x00, 0x30, 0x10, 0x10, 0x10, 0x90, 0x60,	/* Char 106 (j) */
	0x80, 0x80, 0x88, 0x90, 0xA0, 0xD0, 0x88, 0x00,	/* Char 107 (k) */
	0xC0, 0x40, 0x40, 0x40, 0x40, 0x40, 0xE0, 0x00,	/* Char 108 (l) */
	0x00, 0x00, 0xEC, 0x92, 0x92, 0x92, 0x92, 0x00,	/* Char 109 (m) */
	0x00, 0x00, 0xB0, 0xC8, 0x88, 0x88, 0x88, 0x00,	/* Char 110 (n) */
	0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70, 0x00,	/* Char 111 (o) */
	0x00, 0x00, 0xB0, 0xC8, 0xC8, 0xB0, 0x80, 0x80,	/* Char 112 (p) */
	0x00, 0x00, 0x68, 0x98, 0x98, 0x68, 0x08, 0x08,	/* Char 113 (q) */
	0x00, 0x00, 0xB0, 0xC8, 0x80, 0x80, 0x80, 0x00,	/* Char 114 (r) */
	0x00, 0x00, 0x78, 0x80, 0x70, 0x08, 0xF0, 0x00,	/* Char 115 (s) */
	0x40, 0x40, 0xE0, 0x40, 0x40, 0x50, 0x20, 0x00,	/* Char 116 (t) */
	0x00, 0x00, 0x88, 0x88, 0x88, 0x98, 0x68, 0x00,	/* Char 117 (u) */
	0x00, 0x00, 0x88, 0x88, 0x88, 0x50, 0x20, 0x00,	/* Char 118 (v) */
	0x00, 0x00, 0x82, 0x82, 0x92, 0x92, 0x6C, 0x00,	/* Char 119 (w) */
	0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88, 0x00,	/* Char 120 (x) */
	0x00, 0x00, 0x88, 0x88, 0x98, 0x68, 0x08, 0x70,	/* Char 121 (y) */
	0x00, 0x00, 0xF8, 0x10, 0x20, 0x40, 0xF8, 0x00,	/* Char 122 (z) */
	0x10, 0x20, 0x20, 0x40, 0x20, 0x20, 0x10, 0x00,	/* Char 123 ({) */
	0x40, 0x40, 0x40, 0x00, 0x40, 0x40, 0x40, 0x00,	/* Char 124 (|) */
	0x40, 0x20, 0x20, 0x10, 0x20, 0x20, 0x40, 0x00,	/* Char 125 (}) */
	0x76, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 126 (~) */
};

extern int32_t screen_width;
//#define setPixel(buffer, x,y,c) 

static inline void setPixel(uint16_t* __restrict__ buffer, uint32_t x, uint32_t y, uint16_t c)
{
	if (x < MENU_WIDTH_RESOLUTION && y < MENU_HEIGHT_RESOLUTION)
	{
		*((uint16_t* )buffer + ((x) + (y) * MENU_WIDTH_RESOLUTION)) = c;
	}
}

static int32_t isOutlinePixel(uint8_t* charfont, uint32_t x, uint32_t y)
{
	uint32_t xis0 = !x, xis7 = x == 7, yis0 = !y, yis7 = y == 7;
	
	if(xis0)
	{
		if (yis0)
		{
			return !(*charfont & 0x80) && ((*charfont & 0x40) || (charfont[1] & 0x80) || (charfont[1] & 0x40));
		}
		else if (yis7)
		{
			return !(charfont[7] & 0x80) && ((charfont[7] & 0x40) || (charfont[6] & 0x80) || (charfont[6] & 0x40));
		}
		else
		{
			return !(charfont[y] & 0x80) && (
				(charfont[y - 1] & 0x80) || (charfont[y - 1] & 0x40) ||
				(charfont[y] & 0x40) ||
				(charfont[y + 1] & 0x80) || (charfont[y + 1] & 0x40));
		}
	}
	else if (xis7)
	{
		if (yis0)
		{
			return !(*charfont & 0x01) && ((*charfont & 0x02) || (charfont[1] & 0x01) || (charfont[1] & 0x02));
		}
		else if (yis7)
		{
			return !(charfont[7] & 0x01) && ((charfont[7] & 0x02) || (charfont[6] & 0x01) || (charfont[6] & 0x02));
		}
		else
		{
			return !(charfont[y] & 0x01) && (
				(charfont[y - 1] & 0x01) || (charfont[y - 1] & 0x02) ||
				(charfont[y] & 0x02) ||
				(charfont[y + 1] & 0x01) || (charfont[y + 1] & 0x02));
		}
	}
	else
	{
		uint32_t b = 1 << (7 - x);
		if (yis0)
		{
			return !(*charfont & b) && (
				(*charfont & (b << 1)) || (*charfont & (b >> 1)) ||
				(charfont[1] & (b << 1)) || (charfont[1] & b) || (charfont[1] & (b >> 1)));
		}
		else if (yis7)
		{
			return !(charfont[7] & b) && (
				(charfont[7] & (b << 1)) || (charfont[7] & (b >> 1)) ||
				(charfont[6] & (b << 1)) || (charfont[6] & b) || (charfont[6] & (b >> 1)));
		}
		else
		{
			return !(charfont[y] & b) && (
				(charfont[y] & (b << 1)) || (charfont[y] & (b >> 1)) ||
				(charfont[y - 1] & (b << 1)) || (charfont[y - 1] & b) || (charfont[y - 1] & (b >> 1)) ||
				(charfont[y + 1] & (b << 1)) || (charfont[y + 1] & b) || (charfont[y + 1] & (b >> 1)));
		}
	}
}

static void drawChar(uint16_t* __restrict__ buffer, uint32_t *x, uint32_t *y, uint32_t margin, char ch, uint16_t fc, uint16_t olc)
{
	uint8_t i, j;
	uint8_t *charSprite;
	if (ch == '\n')
	{
		*x = margin;
		*y += 8;
	}
	else if(*y < (MENU_HEIGHT_RESOLUTION-1))
	{
		charSprite = (ch-33) * 8 + n2DLib_font;
		// Draw charSprite as monochrome 8*8 image using given color
		for(i = 0; i < 8; i++)
		{
			for(j = 7; j; j--)
			{
				if((charSprite[i] >> j) & 1)
				{
					setPixel(buffer, *x + (7 - j), *y + i, fc);
				}
				else if(isOutlinePixel(charSprite, 7 - j, i))
				{
					setPixel(buffer, *x + (7 - j), *y + i, olc);
				}
			}
		}
		*x += 8;
	}
}

static void drawString(uint16_t* __restrict__ buffer, uint32_t *x, uint32_t *y, uint32_t _x, const char *str, uint16_t fc, uint16_t olc)
{
	uint32_t i;
	size_t size_font;

	size_font = strnlen(str, (MENU_WIDTH_RESOLUTION/8)) + 1;
	for(i = 0; i <  size_font; i++)
		drawChar(buffer, x, y, _x, str[i], fc, olc);
}

void print_string(const char *s, const uint16_t fg_color, const uint16_t bg_color, uint32_t x, uint32_t y, uint16_t* __restrict__ buffer) 
{
	if (!s) return;
	
	drawString(buffer, &x, &y, 0, s, fg_color, bg_color);
}
