#pragma once
#include"Domino.h"

struct Player
{
	Tile** domino_gracza;
	int ilosc_domino;
	int ilosc_polozonych;
	unsigned int length;
	int start_x;

};

typedef struct Player Player;

/// Tworzenie nowego gracza
void creating_players_domino(Player* gracz);

/// Dobieranie domina
void dobieranie(Player* gracz);


