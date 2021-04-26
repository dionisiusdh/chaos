#include "../std-header/boolean.h"

// Configuration
// #define LOGO_STRING "1111111111111111100000111111111111111111n1111111111111000111111100011111111111111n1111111111110111111111111100111111111111n1111111111101111111111111111011111111111n1111111111011111111111111111001111111111n1111111111111111111111111111101111111111n1111111110011111111111111111110111111111n1111111110011111111111111111101111111111n1111111110011111111111111111111111111111n1111111110111111111111111001101111111111n1111111110111111111110011111101111111111n1111111111111111111111111111011111111111n1111111111110111101111111100111111111111n1111111111111111111111111111111111111111n1111111111111111101110111111111111111111n1111111111111001111101111011111111111111n1111111111111111101110111111111111111111n1111111111111111111110111111111111111111n1111111111111111111111111111111111111111n1111111111110100101111110100111111111111n1111111111101111001111011111011111111111n1111111111011111111111111111011111111111n1111111111011111111111111111011111111111n1111111111100001000000000000111111111111n";
#define LOGO_STRING "0000000000000000011111000000000000000000n0000000000000111000000011100000000000000n0000000000001000000000000011000000000000n0000000000010000000000000000100000000000n0000000000100000000000000000110000000000n0000000000000000000000000000010000000000n0000000001100000000000000000001000000000n0000000001100000000000000000010000000000n0000000001100000000000000000000000000000n0000000001000000000000000110010000000000n0000000001000000000001100000010000000000n0000000000000000000000000000100000000000n0000000000001000010000000011000000000000n0000000000000000000000000000000000000000n0000000000000000010001000000000000000000n0000000000000110000010000100000000000000n0000000000000000010001000000000000000000n0000000000000000000001000000000000000000n0000000000000000000000000000000000000000n0000000000001011010000001011000000000000n0000000000010000110000100000100000000000n0000000000100000000000000000100000000000n0000000000100000000000000000100000000000n0000000000011110111111111111000000000000n";
// TODO : Extra, Use better technique
// Note : VGA Mode 3 offer 25 lines / row and 80 characters


#define LOADING_X_OFFSET 7
#define LOADING_Y_OFFSET 70

#define LOGO_X_OFFSET 8
#define LOGO_Y_OFFSET 0

// Implemented in assembly
extern int getRawCursorPos();


void charVideoMemoryWrite(int offset, char character);
// putInMemory() wrapper for video memory writing

void clearScreen();
// Wipe entire screen

void setCursorPos(int r, int c);
// Move cursor position
// Note : Row and Column start from 0

int getCursorPos(bool isRow);
// Get cursor position

void drawPixel(int x, int y, int color);
// Change color single pixel on screen,
// (0,0) starting from top left corner
// Right increase x, down increase y

void drawRectangle(int x, int y, int w, int h);
// Draw single white rectangle without fill

void bitDraw(int xs, int ys, int color, char *bitarray);
// Draw from string containing image bit

void drawBootLogo();
// Drawing boot logo

void directCharPrint(char a, int color);
// Direct interrupt to printing colored char

void printColoredString(char *string, char color);
// Generalized version of printString

void enableKeyboardCursor();
// Enabling keyboard cursor

void disableKeyboardCursor();
// Disabling keyboard cursor

void getCursorPosWrapper(int *ptr, bool isrow);
// Wrapper for getCursorPos, changing ptr to row or column cursor position

void scrollScreenSingleRow();
// Scrolling screen 1 row up