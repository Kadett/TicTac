#pragma once
#include <iostream>
#include <vector>
#include <limits>
#include <chrono>
#include <random>

using namespace std;

struct Coord {
    int x, y;
};

enum Cell { EMPTY = '-', CROSS = 'X', ZERO = 'O', null = 0 };



int getFieldSizeFromHuman();
int getSizeLineForWin(const int sizeField);

void initField(Cell** arr, int size);

void printField(Cell** arr, int size);
void deInitField(Cell** arr, int size);
bool isEmptyCell(Cell** arr, int x, int y);
bool changeField(Cell** arr, Cell c, int x, int y);
Coord getCoordFromHuman(Cell** arr, int size);
Coord getCoordFromAI(Cell** arr, int size, int sizeLineForWin, int& countTurn, Cell cell);
Cell checkWin(Cell** arr, int size, int sizeLineForWin, Cell cell);
void whoFirst(Cell& hum, Cell& AI);