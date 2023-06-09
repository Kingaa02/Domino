#pragma once
#include "Domino_placed.h"

void board_init(Tiles_Placed board[12][20], Tile* first_placed)
{
	board[5][9].placed = 1;
	board[5][10].placed = 1;
	board[6][9].placed = 2;
	board[6][10].placed = 2;
	board[6][11].placed = 1;
	board[6][8].placed = 1;
	board[7][9].placed = 1;
	board[7][10].placed = 1;
	board[6][9].ilosc_oczek = first_placed->ilosc_oczek_lewo;
	board[6][10].ilosc_oczek = first_placed->ilosc_oczek_prawo;

	printf("lewo %d prawo %d", board[6][9].ilosc_oczek, board[6][10].ilosc_oczek);

}

Tiles_Placed* placing_domino(Tile* first_placed)
{
	const int rows = 12;
	const int columns = 20;

	int x = 20;
	int y = 20;

	Tiles_Placed* board = malloc(rows * columns * sizeof(Tiles_Placed));
	if (board == NULL)
	{
		///Nie uda³o siê stworzyæ tablicy
		return NULL;
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			int index = i * columns + j;

			board[index].l_x = x;
			board[index].l_y = y;
			board[index].placed = 0;
			board[index].color = al_map_rgb(255, 0, 0);

			x += 60;
		}
		y += 60;
		x = 20;
	}
	board_init(board, first_placed);
	return board;
}

void wyswietlanie_lini(Tiles_Placed board[12][20])
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 20; j++)
		{

			al_draw_filled_circle(board[i][j].l_x, board[i][j].l_y, 5, board[i][j].color);

		}
	}
}

void tab_board_wys(Tiles_Placed board[12][20])
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			printf("i = %d j = %d WYNIK = %d \n", i, j, board[i][j].l_x);


		}
	}
}

void checking_placement(Tiles_Placed board[12][20])
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (board[i][j].placed == 1)
				board[i][j].color = al_map_rgb(0, 255, 0);
			else if (board[i][j].placed == 2)
				board[i][j].color = al_map_rgb(0, 0, 255);
		}
	}
}





/// DOKOÑCZ DLA PIONOWYCH I POZIOMYCH DOMIN
void checking_around(Tiles_Placed board[12][20], int i, int j, int rotation_degree)
{

	if (rotation_degree == 0 || rotation_degree == 180)
	{
		board[i - 1][j].placed = 1; /// jedno w gore
		board[i][j - 1].placed = 1; /// lewa góra
		board[i + 1][j - 1].placed = 1; /// lewa strona dó³
		board[i + 2][j].placed = 1; /// jedno w dó³ 
		board[i][j + 1].placed = 1; /// prawa strona dó³
		board[i + 1][j + 1].placed = 1; /// prawa strona góra
		board[i][j].placed = 2;
		board[i + 1][j].placed = 2;
	}
	else
	{
		board[i - 1][j].placed = 1;
		board[i - 1][j + 1].placed = 1;
		board[i][j - 1].placed = 1;
		board[i + 1][j].placed = 1;
		board[i + 1][j + 1].placed = 1;
		board[i][j + 2].placed = 1;
		board[i][j].placed = 2;
		board[i][j + 1].placed = 2;
	}


}

bool checking_values(Tiles_Placed board[12][20], int i, int j, Tile* current)
{

	if (current->rotation_degree == 0)
	{
		if (current->ilosc_oczek_lewo == board[i - 1][j].ilosc_oczek ||
			current->ilosc_oczek_lewo == board[i][j - 1].ilosc_oczek ||
			current->ilosc_oczek_lewo == board[i][j + 1].ilosc_oczek)
		{
			return true;
		}
		else if (current->ilosc_oczek_prawo == board[i + 1][j - 1].ilosc_oczek ||
			current->ilosc_oczek_prawo == board[i + 2][j].ilosc_oczek ||
			current->ilosc_oczek_prawo == board[i + 1][j + 1].ilosc_oczek)
		{
			return true;
		}
	}
	else if (current->rotation_degree == 90)
	{
		if (current->ilosc_oczek_lewo == board[i][j + 2].ilosc_oczek ||
			current->ilosc_oczek_lewo == board[i + 1][j + 1].ilosc_oczek ||
			current->ilosc_oczek_lewo == board[i - 1][j].ilosc_oczek)
		{
			return true;
		}
		else if (current->ilosc_oczek_prawo == board[i - 1][j].ilosc_oczek ||
			current->ilosc_oczek_prawo == board[i + 1][j].ilosc_oczek ||
			current->ilosc_oczek_prawo == board[i][j - 1].ilosc_oczek)
		{
			return true;
		}

	}
	else if (current->rotation_degree == 180)
	{
		if (current->ilosc_oczek_lewo == board[i + 2][j].ilosc_oczek ||
			current->ilosc_oczek_lewo == board[i + 1][j + 1].ilosc_oczek ||
			current->ilosc_oczek_lewo == board[i + 1][j - 1].ilosc_oczek)
		{
			return true;
		}
		else if (current->ilosc_oczek_prawo == board[i - 1][j].ilosc_oczek ||
			current->ilosc_oczek_prawo == board[i][j - 1].ilosc_oczek ||
			current->ilosc_oczek_prawo == board[i][j + 1].ilosc_oczek)
		{
			return true;
		}
	}
	else if (current->rotation_degree == 270)
	{
		if (current->ilosc_oczek_lewo == board[i][j - 1].ilosc_oczek ||
			current->ilosc_oczek_lewo == board[i - 1][j].ilosc_oczek ||
			current->ilosc_oczek_lewo == board[i + 1][j].ilosc_oczek)
		{
			return true;
		}
		else if (current->ilosc_oczek_prawo == board[i - 1][j + 1].ilosc_oczek ||
			current->ilosc_oczek_prawo == board[i][j + 1].ilosc_oczek ||
			current->ilosc_oczek_prawo == board[i + 1][j + 1].ilosc_oczek)
		{
			return true;
		}
	}

	return false;

}



void przesuwanie_do_lewej(Player* gracz, int* current)
{
	printf("ILOSC DOMINO :%d \n", gracz->ilosc_domino);
	printf("CURRENT VALUE %d\n", *current);


	for (int i = gracz->ilosc_domino - 1; i > *current; i--)
	{
		if (gracz->domino_gracza[i]->is_placed == false && gracz->domino_gracza[i - 1]->is_placed == false)
		{
			gracz->domino_gracza[i]->l_x = gracz->domino_gracza[i - 1]->start_l_x;
			gracz->domino_gracza[i]->l_y = gracz->domino_gracza[i - 1]->start_l_y;
			gracz->domino_gracza[i]->p_x = gracz->domino_gracza[i - 1]->start_p_x;
			gracz->domino_gracza[i]->p_y = gracz->domino_gracza[i - 1]->start_p_y;

			gracz->domino_gracza[i]->start_l_x = gracz->domino_gracza[i - 1]->start_l_x;
			gracz->domino_gracza[i]->start_l_y = gracz->domino_gracza[i - 1]->start_l_y;
			gracz->domino_gracza[i]->start_p_x = gracz->domino_gracza[i - 1]->start_p_x;
			gracz->domino_gracza[i]->start_p_y = gracz->domino_gracza[i - 1]->start_p_y;

		}

	}

}




void placing(Tile* current, Tiles_Placed board[][20], Player* gracz, int* currently_selected_index)
{

	// 0 jest puste
	// 1 zaznaczenie pol dooko³a
	// 2 nie mozna polozyc
	if (current->moveable)
	{
		for (int i = 0; i < 12; i++)
		{
			bool found = false;
			for (int j = 0; j < 20; j++)
			{
				if (current->rotation_degree == 0)
				{
					if (current->l_x + TILE_SIZE < board[i][j].l_x ||
						current->l_x > board[i][j].l_x + TILE_SIZE ||
						current->l_y + (2 * TILE_SIZE) < board[i][j].l_y ||
						current->l_y > board[i][j].l_y + (2 * TILE_SIZE) ||
						current->p_x + TILE_SIZE < board[i][j].l_x ||
						current->p_x > board[i][j].l_x + TILE_SIZE ||
						current->p_y + (2 * TILE_SIZE) < board[i][j].l_y ||
						current->p_y > board[i][j].l_y + (2 * TILE_SIZE))
					{


					}
					else
					{
						if (i != 12 && board[i][j].placed != 2 && board[i + 1][j].placed != 2 && current->is_placed == false)
						{
							if (board[i][j].placed == 1 || board[i + 1][j].placed == 1)
							{

								if (checking_values(board, i, j, current))
								{
									board[i][j].ilosc_oczek = current->ilosc_oczek_lewo;
									board[i + 1][j].ilosc_oczek = current->ilosc_oczek_prawo;
									current->l_x = board[i][j].l_x;
									current->l_y = board[i][j].l_y;
									current->p_x = board[i + 1][j].l_x;
									current->p_y = board[i + 1][j].l_y;
									current->moveable = false;
									przesuwanie_do_lewej(gracz, currently_selected_index);
									current->is_placed = true;
									board[i][j].placed = 2;
									board[i + 1][j].placed = 2;

									checking_around(board, i, j, current->rotation_degree);
									checking_placement(board);

									printf("i = %d, j = %d , %d\n", i, j, board[i][j].placed);

									found = true;
									break;
								}




							}
						}
						current->l_x = current->start_l_x;
						current->l_y = current->start_l_y;
						current->p_x = current->start_p_x;
						current->p_y = current->start_p_y;
						current->rotation_degree = 0;

					}
				}
				else if (current->rotation_degree == 90)
				{
					if (current->p_x + (2 * TILE_SIZE) < board[i - 1][j].l_x || // prawo z lewym
						current->p_x > board[i - 1][j].l_x + TILE_SIZE ||		// lewo z prawym
						current->p_y + (2 * TILE_SIZE) < board[i - 1][j].l_y || // dó³ z gór¹
						current->p_y > board[i - 1][j].l_y + (2 * TILE_SIZE) || // góra z do³em
						current->l_x + TILE_SIZE < board[i - 1][j].l_x ||
						current->l_x > board[i - 1][j].l_x + (2 * TILE_SIZE) ||
						current->l_y + (2 * TILE_SIZE) < board[i - 1][j].l_y ||
						current->l_y > board[i - 1][j].l_y + (2 * TILE_SIZE))
					{

					}
					else
					{
						if (j != 20 && i != 12 && board[i][j].placed != 2 && board[i][j + 1].placed != 2 && current->is_placed == false)
						{
							if (board[i][j].placed == 1 || board[i][j + 1].placed == 1)
							{
								if (checking_values(board, i, j, current))
								{
									board[i][j].ilosc_oczek = current->ilosc_oczek_prawo;
									board[i][j + 1].ilosc_oczek = current->ilosc_oczek_lewo;
									current->l_x = board[i][j + 1].l_x;
									current->l_y = board[i][j + 1].l_y;
									current->p_x = board[i][j].l_x;
									current->p_y = board[i][j].l_y;
									board[i][j + 1].placed = 2;
									board[i][j].placed = 2;
									current->moveable = false;
									przesuwanie_do_lewej(gracz, currently_selected_index);
									current->is_placed = true;
									checking_around(board, i, j, current->rotation_degree);
									checking_placement(board);
									printf("i = %d, j = %d , %d\n", i, j, board[i][j].placed);
									found = true;
									break;
								}

							}

						}
						current->l_x = current->start_l_x;
						current->l_y = current->start_l_y;
						current->p_x = current->start_p_x;
						current->p_y = current->start_p_y;
						current->rotation_degree = 0;
					}
				}
				else if (current->rotation_degree == 180)
				{
					if (current->p_x + TILE_SIZE < board[i][j].l_x || // prawo z lewy 
						current->p_x > board[i][j].l_x + TILE_SIZE || // lewo z prawym
						current->p_y + (2 * TILE_SIZE) < board[i][j].l_y || // dó³ z gór¹
						current->p_y > board[i][j].l_y + (2 * TILE_SIZE) || // góra z do³em
						current->l_x + TILE_SIZE < board[i][j].l_x ||
						current->l_x >board[i][j].l_x + TILE_SIZE ||
						current->l_y + (2 * TILE_SIZE) < board[i][j].l_y ||
						current->l_y > board[i][j].l_y + (2 * TILE_SIZE))
					{

					}
					else
					{

						if (i != 12 && board[i][j].placed != 2 && board[i + 1][j].placed != 2 && current->is_placed == false)
						{
							if (board[i][j].placed == 1 || board[i + 1][j].placed == 1)
							{

								if (checking_values(board, i, j, current))
								{
									board[i][j].ilosc_oczek = current->ilosc_oczek_prawo;
									board[i + 1][j].ilosc_oczek = current->ilosc_oczek_lewo;
									current->l_x = board[i + 1][j].l_x;
									current->l_y = board[i + 1][j].l_y;
									current->p_x = board[i][j].l_x;
									current->p_y = board[i][j].l_y;
									current->moveable = false;
									przesuwanie_do_lewej(gracz, currently_selected_index);
									current->is_placed = true;
									board[i][j].placed = 2;
									board[i + 1][j].placed = 2;
									checking_around(board, i, j, current->rotation_degree);
									checking_placement(board);
									printf("i = %d, j = %d , %d\n", i, j, board[i][j].placed);

									found = true;
									break;
								}




							}
						}
						current->l_x = current->start_l_x;
						current->l_y = current->start_l_y;
						current->p_x = current->start_p_x;
						current->p_y = current->start_p_y;
						current->rotation_degree = 0;
					}
				}
				else if (current->rotation_degree == 270)
				{
					if (current->l_x + (2 * TILE_SIZE) < board[i - 1][j].l_x || // prawo z lewy 
						current->l_x > board[i - 1][j].l_x + TILE_SIZE || // lewo z prawym
						current->l_y + (2 * TILE_SIZE) < board[i - 1][j].l_y ||  // dó³ z gór¹
						current->l_y > board[i - 1][j].l_y + (2 * TILE_SIZE) ||  // góra z do³em
						current->p_x + TILE_SIZE < board[i - 1][j].l_x ||
						current->p_x > board[i - 1][j].l_x + (2 * TILE_SIZE) ||
						current->p_y + (2 * TILE_SIZE) < board[i - 1][j].l_y ||
						current->p_y > board[i - 1][j].l_y + (2 * TILE_SIZE))
					{

					}
					else
					{
						if (j != 20 && i != 12 && board[i][j].placed != 2 && board[i][j + 1].placed != 2 && current->is_placed == false)
						{
							if (board[i][j].placed == 1 || board[i][j + 1].placed == 1)
							{
								if (checking_values(board, i, j, current))
								{
									board[i][j].ilosc_oczek = current->ilosc_oczek_lewo;
									board[i][j + 1].ilosc_oczek = current->ilosc_oczek_prawo;
									current->l_x = board[i][j].l_x;
									current->l_y = board[i][j].l_y;
									current->p_x = board[i][j + 1].l_x;
									current->p_y = board[i][j + 1].l_y;
									board[i][j + 1].placed = 2;
									board[i][j].placed = 2;
									current->moveable = false;
									przesuwanie_do_lewej(gracz, currently_selected_index);
									current->is_placed = true;
									checking_around(board, i, j, current->rotation_degree);
									checking_placement(board);
									printf("i = %d, j = %d , %d\n", i, j, board[i][j].placed);
									found = true;
									break;
								}

							}

						}
						current->l_x = current->start_l_x;
						current->l_y = current->start_l_y;
						current->p_x = current->start_p_x;
						current->p_y = current->start_p_y;
						current->rotation_degree = 0;
					}
				}


			}

			if (found) {
				break;
			}
		}
	}

}


