#pragma once
#include "Domino.h"

struct Tiles_Placed
{
	int l_x;
	int l_y;

};


typedef struct Tiles_Placed Tiles_Placed;

Tiles_Placed* placing_domino();


void wyswietlanie_lini(Tiles_Placed board[12][20]);

void tab_board_wys(Tiles_Placed board[12][20]);


void placing(Tile* current, Tiles_Placed board[][20]);