#pragma once
#include "Domino_placed.h"

Tiles_Placed* placing_domino()
{
	const int rows = 12;
	const int columns = 20;

	int x = 20;
	int y = 20;

	Tiles_Placed* board = malloc(rows * columns * sizeof(Tiles_Placed));
	if (board == NULL)
	{
		// Obs³u¿ b³¹d alokacji pamiêci
		return NULL;
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			int index = i * columns + j;

			board[index].l_x = x;
			board[index].l_y = y;

			x += 60;
		}
		y += 60;
		x = 20;
	}
	return board;
}

void wyswietlanie_lini(Tiles_Placed board[12][20])
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 20; j++)
		{

			al_draw_filled_circle(board[i][j].l_x, board[i][j].l_y, 3, al_map_rgb(255, 0, 0));

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


void placing(Tile* current, Tiles_Placed board[][20])
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
					if (i != 11)
					{
						current->l_x = board[i][j].l_x;
						current->l_y = board[i][j].l_y;
						current->p_x = board[i + 1][j].l_x;
						current->p_y = board[i + 1][j].l_y;
						found = true;
						break;
					}

				}
			}
			else if (current->rotation_degree == 90)
			{
				if (current->p_x + (2 * TILE_SIZE) < board[i][j].l_x || // prawo z lewym
					current->p_x > board[i][j].l_x + TILE_SIZE || // lewo z prawym
					current->p_y + (2 * TILE_SIZE) < board[i][j].l_y || // dó³ z gór¹
					current->p_y > board[i][j].l_y + (2 * TILE_SIZE) || // góra z do³em
					current->l_x + TILE_SIZE < board[i][j].l_x ||
					current->l_x > board[i][j].l_x + (2 * TILE_SIZE) ||
					current->l_y + (2 * TILE_SIZE) < board[i][j].l_y ||
					current->l_y > board[i][j].l_y + (2 * TILE_SIZE))
				{

				}
				else
				{
					if (j != 19 && i != 11)
					{
						current->l_x = board[i + 1][j + 1].l_x;
						current->l_y = board[i + 1][j + 1].l_y;
						current->p_x = board[i + 1][j].l_x;
						current->p_y = board[i + 1][j].l_y;
						found = true;
						break;
					}

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
					if (i != 11)
					{
						current->l_x = board[i + 1][j].l_x;
						current->l_y = board[i + 1][j].l_y;
						current->p_x = board[i][j].l_x;
						current->p_y = board[i][j].l_y;
						found = true;
						break;
					}

				}
			}
			else if (current->rotation_degree == 270)
			{
				if (current->l_x + (2 * TILE_SIZE) < board[i][j].l_x || // prawo z lewy 
					current->l_x > board[i][j].l_x + TILE_SIZE || // lewo z prawym
					current->l_y + (2 * TILE_SIZE) < board[i][j].l_y ||  // dó³ z gór¹
					current->l_y > board[i][j].l_y + (2 * TILE_SIZE) ||  // góra z do³em
					current->p_x + TILE_SIZE < board[i][j].l_x ||
					current->p_x > board[i][j].l_x + (2 * TILE_SIZE) ||
					current->p_y + (2 * TILE_SIZE) < board[i][j].l_y ||
					current->p_y > board[i][j].l_y + (2 * TILE_SIZE))
				{

				}
				else
				{
					if (j != 19 && i != 11)
					{
						current->l_x = board[i + 1][j].l_x;
						current->l_y = board[i + 1][j].l_y;
						current->p_x = board[i + 1][j + 1].l_x;
						current->p_y = board[i + 1][j + 1].l_y;
						found = true;
						break;
					}

				}
			}


		}

		if (found) {
			break;
		}
	}
}