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

/// Tworzenie tablicy do uk�adania domino

void board_init(Tiles_Placed board[12][20], Tile* first_placed);

/// Stworzenie obszaru do uk�adania domina
Tiles_Placed* placing_domino(Tile* first_placed);

/// Zaznaczanie obszar�w w ok� po�o�onego domina
void checking_around(Tiles_Placed board[12][20], int i, int j, int rotation_degree);

/// Sprawdzenie czy ilo�� oczek si� zgadza  w zale�no�ci od obrotu danego domina
bool checking_values(Tiles_Placed board[12][20], int i, int j, Tile* current);

/// Dodanie po�o�onego domina do tablicy kafelk�w kt�re zosta�y poprawnie po�o�one
void dodawanie_on_board(Player* gracz, int* current, Tile** tiles_on_board, int ilosc_on_board, int length);

/// Przesuwanie kafelk�w w r�ce do lewej strony
void przesuwanie_do_lewej(Player* gracz, int* current, Tile** tiles_on_board, int ilosc_on_board, int length);

/// G��wna funkcj� do uk�adania domina
void placing(Tile* current, Tiles_Placed board[][20], Player* gracz, int* currently_selected_index, Tile** tiles_on_board, int* ilosc_on_board, int* length, int* current_player);






