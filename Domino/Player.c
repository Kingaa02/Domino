#pragma once
#include"Player.h"

/// Funkcja do tworzenia nowego gracza i jego kafelków
void creating_players_domino(Player* gracz)
{
	gracz->ilosc_domino = 2;
	gracz->ilosc_polozonych = 0;
	gracz->domino_gracza = NULL;
	gracz->length = 0;
	gracz->start_x = 60;
	int y_pos = SCREEN_HEIGHT - 200;
	int y2_pos = SCREEN_HEIGHT - 200 + TILE_SIZE;

	for (int i = 0; i < gracz->ilosc_domino; i++)
	{
		if (i == 0)
		{
			gracz->domino_gracza = dodawanie_domina(gracz->domino_gracza, i, nowy(gracz->start_x, y_pos, gracz->start_x, y2_pos, 0), &gracz->length);
		}
		else
		{
			gracz->domino_gracza = dodawanie_domina(gracz->domino_gracza, i, nowy(gracz->domino_gracza[i - 1]->l_x + 100, y_pos, gracz->domino_gracza[i - 1]->l_x + 100, y2_pos, 0), &gracz->length);
		}

	}
	losowanie_oczek(gracz->domino_gracza, gracz->ilosc_domino);
	przypisanie_grafik(gracz->domino_gracza, gracz->ilosc_domino);
}

/// Funkcja dobieraj¹ca nowe dominno do rêki gracza
void dobieranie(Player* gracz)
{
	int y_pos = SCREEN_HEIGHT - 200;
	int y2_pos = SCREEN_HEIGHT - 200 + TILE_SIZE;
	gracz->domino_gracza = dodawanie_domina(gracz->domino_gracza, gracz->ilosc_domino, nowy(gracz->domino_gracza[gracz->ilosc_domino - 1]->l_x + 100, y_pos, gracz->domino_gracza[gracz->ilosc_domino - 1]->l_x + 100, y2_pos, 0), &gracz->length);
	losowanie_oczek_dobrane(gracz->domino_gracza, gracz->ilosc_domino);
	przypisanie_grafik_dobrane(gracz->domino_gracza, gracz->ilosc_domino);
	gracz->ilosc_domino += 1;
}
