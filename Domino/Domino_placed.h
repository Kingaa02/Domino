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

void board_init(Tiles_Placed board[12][20], Tile* first_placed);

/// Stworzenie obszaru do uk³adania domina
Tiles_Placed* placing_domino(Tile* first_placed);

/// Zaznaczanie obszarów w okó³ po³o¿onego domina
void checking_around(Tiles_Placed board[12][20], int i, int j, int rotation_degree);

/// Sprawdzenie czy iloœæ oczek siê zgadza  w zale¿noœci od obrotu danego domina
bool checking_values(Tiles_Placed board[12][20], int i, int j, Tile* current);

/// Dodanie po³o¿onego domina do tablicy kafelków które zosta³y poprawnie po³o¿one
void dodawanie_on_board(Player* gracz, int* current, Tile** tiles_on_board, int ilosc_on_board, int length);

/// Przesuwanie kafelków w rêce do lewej strony
void przesuwanie_do_lewej(Player* gracz, int* current, Tile** tiles_on_board, int ilosc_on_board, int length);

/// G³ówna funkcj¹ do uk³adania domina
void placing(Tile* current, Tiles_Placed board[][20], Player* gracz, int* currently_selected_index, Tile** tiles_on_board, int* ilosc_on_board, int* length, int* current_player);






