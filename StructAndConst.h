#pragma once
#ifndef _MyStruct_header
#define _MyStruct_header

#define boardW 55 // độ rộng màn hình chơi game
#define boardH 30 // độ dài màn hình chơi game

typedef struct {
	int color;
	char character;
}aCell;

aCell buffer[boardH][boardW + 1];

enum Direction { DOWN, RIGHT, LEFT, UP };
enum Resuit { LOST, WIN };

void drawACell(int row, int col, int character, int color) {
	buffer[row][col].character = character;
	buffer[row][col].color = color;
}

typedef struct {
	int x;
	int y;
}coordinate;

typedef struct {
	coordinate coor;
}Food;

typedef struct {
	coordinate seg[100];
	int length;
	Direction dir;
	int score = 0;
}Snake;


#endif
