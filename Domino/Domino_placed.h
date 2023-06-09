#pragma once
#include "Player.h"
#include "Domino.h"

struct Tiles_Placed
{
	int l_x;
	int l_y;
	int placed;
	int ilosc_oczek;
	ALLEGRO_COLOR color;

};




typedef struct Tiles_Placed Tiles_Placed;

/// Tworzenie tablicy do uk³adania domino

Tiles_Placed* placing_domino(Tile* first_placed);


void wyswietlanie_lini(Tiles_Placed board[12][20]);

void tab_board_wys(Tiles_Placed board[12][20]);


void checking_placement(Tiles_Placed board[12][20]);

void placing(Tile* current, Tiles_Placed board[][20], Player* gracz, int* currently_selected_index);



