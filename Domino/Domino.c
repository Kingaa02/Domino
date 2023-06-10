#pragma once
#include"Domino.h"

//losowanie liczby oczek klocka startowegoa
void losowanie_oczek(struct Tile** tiles, int ilosc_domino) {

	for (int i = 0; i < ilosc_domino; i++)
	{
		tiles[i]->ilosc_oczek_lewo = rand() % 7;
		tiles[i]->ilosc_oczek_prawo = rand() % 7;
	}
}

void losowanie_oczek_dobrane(struct Tile** tiles, int ilosc_domino) {

	printf("ilosc dom %d", ilosc_domino);
	tiles[ilosc_domino]->ilosc_oczek_lewo = rand() % 7;
	tiles[ilosc_domino]->ilosc_oczek_prawo = rand() % 7;

}

/// Przypisywanie odpowiednich grafik dla ka¿dej ze stron bloku
void przypisanie_grafik(Tile** tiles, int ilosc_domino) {

	for (int i = 0; i < ilosc_domino; i++)
	{
		switch (tiles[i]->ilosc_oczek_lewo) {
		case 0:
			tiles[i]->lewo = al_load_bitmap("tile_0.png");
			break;
		case 1:
			tiles[i]->lewo = al_load_bitmap("tile_1.png");
			break;
		case 2:
			tiles[i]->lewo = al_load_bitmap("tile_2.png");
			break;
		case 3:
			tiles[i]->lewo = al_load_bitmap("tile_3.png");
			break;
		case 4:
			tiles[i]->lewo = al_load_bitmap("tile_4.png");
			break;
		case 5:
			tiles[i]->lewo = al_load_bitmap("tile_5.png");
			break;
		case 6:
			tiles[i]->lewo = al_load_bitmap("tile_6.png");
			break;
		}

		switch (tiles[i]->ilosc_oczek_prawo) {
		case 0:
			tiles[i]->prawo = al_load_bitmap("tile_0.png");
			break;
		case 1:
			tiles[i]->prawo = al_load_bitmap("tile_1.png");
			break;
		case 2:
			tiles[i]->prawo = al_load_bitmap("tile_2.png");
			break;
		case 3:
			tiles[i]->prawo = al_load_bitmap("tile_3.png");
			break;
		case 4:
			tiles[i]->prawo = al_load_bitmap("tile_4.png");
			break;
		case 5:
			tiles[i]->prawo = al_load_bitmap("tile_5.png");
			break;
		case 6:
			tiles[i]->prawo = al_load_bitmap("tile_6.png");
			break;
		}
	}


}


void przypisanie_grafik_dobrane(Tile** tiles, int ilosc_domino) {


	switch (tiles[ilosc_domino]->ilosc_oczek_lewo) {
	case 0:
		tiles[ilosc_domino]->lewo = al_load_bitmap("tile_0.png");
		break;
	case 1:
		tiles[ilosc_domino]->lewo = al_load_bitmap("tile_1.png");
		break;
	case 2:
		tiles[ilosc_domino]->lewo = al_load_bitmap("tile_2.png");
		break;
	case 3:
		tiles[ilosc_domino]->lewo = al_load_bitmap("tile_3.png");
		break;
	case 4:
		tiles[ilosc_domino]->lewo = al_load_bitmap("tile_4.png");
		break;
	case 5:
		tiles[ilosc_domino]->lewo = al_load_bitmap("tile_5.png");
		break;
	case 6:
		tiles[ilosc_domino]->lewo = al_load_bitmap("tile_6.png");
		break;
	}

	switch (tiles[ilosc_domino]->ilosc_oczek_prawo) {
	case 0:
		tiles[ilosc_domino]->prawo = al_load_bitmap("tile_0.png");
		break;
	case 1:
		tiles[ilosc_domino]->prawo = al_load_bitmap("tile_1.png");
		break;
	case 2:
		tiles[ilosc_domino]->prawo = al_load_bitmap("tile_2.png");
		break;
	case 3:
		tiles[ilosc_domino]->prawo = al_load_bitmap("tile_3.png");
		break;
	case 4:
		tiles[ilosc_domino]->prawo = al_load_bitmap("tile_4.png");
		break;
	case 5:
		tiles[ilosc_domino]->prawo = al_load_bitmap("tile_5.png");
		break;
	case 6:
		tiles[ilosc_domino]->prawo = al_load_bitmap("tile_6.png");
		break;
	}


}

/// Wyœwietlanie domina na ekranie
void wyswietlanie_domino(Tile** tiles, int ilosc_domino)
{
	for (int i = 0; i < ilosc_domino; i++)
	{
		if (i == 0)
		{
			al_draw_bitmap(tiles[i]->lewo, tiles[i]->l_x, tiles[i]->l_y, 0);
			al_draw_bitmap(tiles[i]->prawo, tiles[i]->p_x, tiles[i]->p_y, 0);
		}
		else
		{

			al_draw_bitmap(tiles[i]->lewo, tiles[i]->l_x, tiles[i]->l_y, 0);
			al_draw_bitmap(tiles[i]->prawo, tiles[i]->p_x, tiles[i]->p_y, 0);
		}

	}
}

/// Tworzenie nowych bloków domina
Tile* nowy(int l_x, int l_y, int p_x, int p_y, float rotation_degree)
{
	Tile* n = (Tile*)malloc(sizeof(Tile));
	if (n)
	{
		n->l_x = l_x;
		n->l_y = l_y;
		n->p_x = p_x;
		n->p_y = p_y;
		n->start_l_x = l_x;
		n->start_l_y = l_y;
		n->start_p_x = p_x;
		n->start_p_y = p_y;
		n->moveable = true;
		n->is_placed = false;
		n->rotation_degree = rotation_degree;
		return n;
	}
	return NULL;
}

/// Powiêkszanie tablicy i dodawanie nowych domin do tablicy
Tile** dodawanie_domina(Tile** tab, int index, Tile* domino, unsigned int* length)
{
	const unsigned int powiekszenie = 64;

	if (index >= *length)
	{
		*length += powiekszenie;
		Tile** nowa_tab = realloc(tab, (*length) * sizeof(Tile*));
		if (nowa_tab)
			tab = nowa_tab;
	}
	if (tab)
		tab[index] = domino;
	return tab;
}

/// Kolizja miêdzy blokami domina
int collision(Tile* domino_r, Tile** tiles, int ilosc_domino, int domino_i)
{
	/// Strony którymi styjak¹ siê domina
	int prawy_z_lewym = 0;
	int lewy_z_prawym = 1;
	int gora_z_dolem = 2;
	int dol_z_gora = 3; 

	for (int i = 0; i < ilosc_domino; i++)
	{
		if (domino_i != i)
		{
			if (domino_r->rotation_degree == 0)
			{
				if (domino_r->l_x + TILE_SIZE < tiles[i]->l_x || // prawo z lewy 
					domino_r->l_x > tiles[i]->l_x + TILE_SIZE || // lewo z prawym
					domino_r->l_y + (2 * TILE_SIZE) < tiles[i]->l_y || // dó³ z gór¹
					domino_r->l_y > tiles[i]->l_y + (2 * TILE_SIZE) || // góra z do³em
					domino_r->p_x + TILE_SIZE < tiles[i]->p_x ||
					domino_r->p_x > tiles[i]->p_x + TILE_SIZE ||
					domino_r->p_y + (2 * TILE_SIZE) < tiles[i]->p_y ||
					domino_r->p_y > tiles[i]->p_y + (2 * TILE_SIZE))
				{
					///Brak kolizji
				}
				else
				{
					///Kolizja

					if (domino_r->l_x >= tiles[i]->l_x + TILE_SIZE && domino_r->p_x >= tiles[i]->p_x + TILE_SIZE)
					{
						printf("LEWO Z PRAWYM\n");
						return lewy_z_prawym;
					}
					else if (domino_r->l_x + TILE_SIZE <= tiles[i]->l_x && domino_r->p_x + TILE_SIZE <= tiles[i]->p_x)
					{
						printf("PRAWY Z LEWYM \n");
						return prawy_z_lewym;
					}
					else if (domino_r->l_y + (2 * TILE_SIZE) <= tiles[i]->l_y && domino_r->p_y + (2 * TILE_SIZE) <= tiles[i]->p_y)
					{
						printf("DOL Z GORA \n");
						return dol_z_gora;
					}
					else if (domino_r->l_y >= tiles[i]->l_y + (2 * TILE_SIZE) && domino_r->p_y >= tiles[i]->p_y + (2 * TILE_SIZE))
					{
						printf("GORA Z DOEM \n");
						return gora_z_dolem;
					}

				}
			}
			else if (domino_r->rotation_degree == 90)
			{
				if (domino_r->p_x + (2 * TILE_SIZE) < tiles[i]->l_x || // prawo z lewym
					domino_r->p_x > tiles[i]->l_x + TILE_SIZE || // lewo z prawym
					domino_r->p_y + (2 * TILE_SIZE) < tiles[i]->l_y || // dó³ z gór¹
					domino_r->p_y > tiles[i]->l_y + (2 * TILE_SIZE) || // góra z do³em
					domino_r->l_x + TILE_SIZE < tiles[i]->p_x ||
					domino_r->l_x > tiles[i]->p_x + (2 * TILE_SIZE) ||
					domino_r->l_y + (2 * TILE_SIZE) < tiles[i]->p_y ||
					domino_r->l_y > tiles[i]->p_y + (2 * TILE_SIZE))
				{
					///Brak kolizji
				}
				else
				{
					///Kolizja
					if (domino_r->p_x >= tiles[i]->l_x + TILE_SIZE && domino_r->l_x >= tiles[i]->p_x + (2 * TILE_SIZE))
					{
						printf("LEWO Z PRAWYM\n");
						return lewy_z_prawym;
					}
					else if (domino_r->p_x + (2 * TILE_SIZE) <= tiles[i]->l_x && domino_r->l_x + TILE_SIZE <= tiles[i]->p_x)
					{
						printf("PRAWY Z LEWYM \n");
						return prawy_z_lewym;
					}
					else if (domino_r->p_y + (2 * TILE_SIZE) <= tiles[i]->l_y && domino_r->l_y + (2 * TILE_SIZE) <= tiles[i]->p_y)
					{
						printf("DOL Z GORA \n");
						return dol_z_gora;
					}
					else if (domino_r->p_y >= tiles[i]->l_y + (2 * TILE_SIZE) && domino_r->l_y >= tiles[i]->p_y + (2 * TILE_SIZE))
					{
						printf("GORA Z DOEM \n");
						return gora_z_dolem;
					}
					printf("Kolizja\n");
				}
			}
			else if (domino_r->rotation_degree == 180)
			{
				if (domino_r->p_x + TILE_SIZE < tiles[i]->l_x || // prawo z lewy 
					domino_r->p_x > tiles[i]->l_x + TILE_SIZE || // lewo z prawym
					domino_r->p_y + (2 * TILE_SIZE) < tiles[i]->l_y || // dó³ z gór¹
					domino_r->p_y > tiles[i]->l_y + (2 * TILE_SIZE) || // góra z do³em
					domino_r->l_x + TILE_SIZE < tiles[i]->p_x ||
					domino_r->l_x > tiles[i]->p_x + TILE_SIZE ||
					domino_r->l_y + (2 * TILE_SIZE) < tiles[i]->p_y ||
					domino_r->l_y > tiles[i]->p_y + (2 * TILE_SIZE))
				{
					///Brak kolizji
				}
				else
				{
					///Kolizja
					if (domino_r->p_x >= tiles[i]->l_x + TILE_SIZE && domino_r->l_x > tiles[i]->p_x + TILE_SIZE)
					{
						printf("LEWO Z PRAWYM\n");
						return lewy_z_prawym;
					}
					else if (domino_r->p_x + TILE_SIZE <= tiles[i]->l_x && domino_r->l_x + TILE_SIZE <= tiles[i]->p_x)
					{
						printf("PRAWY Z LEWYM \n");
						return prawy_z_lewym;
					}
					else if (domino_r->p_y + (2 * TILE_SIZE) <= tiles[i]->l_y && domino_r->l_y + (2 * TILE_SIZE) <= tiles[i]->p_y)
					{
						printf("DOL Z GORA \n");
						return dol_z_gora;
					}
					else if (domino_r->p_y >= tiles[i]->l_y + (2 * TILE_SIZE) && domino_r->l_y > tiles[i]->p_y + (2 * TILE_SIZE))
					{
						printf("GORA Z DOEM \n");
						return gora_z_dolem;
					}
					printf("Kolizja\n");
				}
			}
			else if (domino_r->rotation_degree == 270)
			{
				if (domino_r->l_x + (2 * TILE_SIZE) < tiles[i]->l_x || // prawo z lewy 
					domino_r->l_x > tiles[i]->l_x + TILE_SIZE ||		// lewo z prawym
					domino_r->l_y + (2 * TILE_SIZE) < tiles[i]->l_y ||  // dó³ z gór¹
					domino_r->l_y > tiles[i]->l_y + (2 * TILE_SIZE) ||  // góra z do³em
					domino_r->p_x + TILE_SIZE < tiles[i]->p_x ||
					domino_r->p_x > tiles[i]->p_x + (2 * TILE_SIZE) ||
					domino_r->p_y + (2 * TILE_SIZE) < tiles[i]->p_y ||
					domino_r->p_y > tiles[i]->p_y + (2 * TILE_SIZE))
				{
					///Brak kolizji
				}
				else
				{
					///Kolizja
					if (domino_r->l_x >= tiles[i]->l_x + TILE_SIZE && domino_r->p_x >= tiles[i]->p_x + (2 * TILE_SIZE))
					{
						printf("LEWO Z PRAWYM\n");
						return lewy_z_prawym;
					}
					else if (domino_r->l_x + (2 * TILE_SIZE) <= tiles[i]->l_x && domino_r->p_x + TILE_SIZE <= tiles[i]->p_x)
					{
						printf("PRAWY Z LEWYM \n");
						return prawy_z_lewym;
					}
					else if (domino_r->l_y + (2 * TILE_SIZE) <= tiles[i]->l_y && domino_r->p_y + (2 * TILE_SIZE) <= tiles[i]->p_y)
					{
						printf("DOL Z GORA \n");
						return dol_z_gora;
					}
					else if (domino_r->l_y >= tiles[i]->l_y + (2 * TILE_SIZE) && domino_r->p_y >= tiles[i]->p_y + (2 * TILE_SIZE))
					{
						printf("GORA Z DOEM \n");
						return gora_z_dolem;
					}
					printf("Kolizja\n");
				}
			}
		}

	}

	return -1;


}
/// Funkcja do obracania domina
void obracanie(Tile* current)
{
	current->rotation_degree += 90;
	if (current->rotation_degree == 90)
	{
		current->l_x += TILE_SIZE;
		current->l_y += TILE_SIZE;
	}
	else if (current->rotation_degree == 180)
	{
		current->l_x -= TILE_SIZE;
		current->l_y += TILE_SIZE;
	}
	else if (current->rotation_degree == 270)
	{
		current->l_x -= TILE_SIZE;
		current->l_y -= TILE_SIZE;
	}
	else if (current->rotation_degree == 360)
	{
		current->l_x += TILE_SIZE;
		current->l_y -= TILE_SIZE;
		current->rotation_degree = 0;
	}



}
/// Funkcja do poruszania domina 
/// Current - indeks w tablicy obecnie ruszanego elemntu
/// key_down - sprawdzenie czy obróciæ domino
void poruszanie(Tile** tiles, int ilosc_domino, ALLEGRO_EVENT* event, bool* key_down, int* mouse_x, int* mouse_y, int* current)
{
	for (int i = 0; i < ilosc_domino; i++)
	{
		if (tiles[i]->moveable == true)
		{
			if (tiles[i]->rotation_degree == 0 || tiles[i]->rotation_degree == 270)
			{

				if (event->mouse.x >= tiles[i]->l_x && event->mouse.x <= tiles[i]->p_x + TILE_SIZE)
					if (event->mouse.y >= tiles[i]->l_y && event->mouse.y <= tiles[i]->p_y + TILE_SIZE)
					{
						*current = i;


						tiles[i]->l_x = tiles[i]->l_x + event->mouse.x - *mouse_x;
						tiles[i]->l_y = tiles[i]->l_y + event->mouse.y - *mouse_y;

						tiles[i]->p_x = tiles[i]->p_x + event->mouse.x - *mouse_x;
						tiles[i]->p_y = tiles[i]->p_y + event->mouse.y - *mouse_y;

						*mouse_x = event->mouse.x;
						*mouse_y = event->mouse.y;

						///Obracanie domino
						if (*key_down)
						{
							obracanie(tiles[i]);
							*key_down = false;

						}

					}
			}
			else
			{
				*current = i;

				tiles[i]->l_x = tiles[i]->l_x + event->mouse.x - *mouse_x;
				tiles[i]->l_y = tiles[i]->l_y + event->mouse.y - *mouse_y;

				tiles[i]->p_x = tiles[i]->p_x + event->mouse.x - *mouse_x;
				tiles[i]->p_y = tiles[i]->p_y + event->mouse.y - *mouse_y;

				*mouse_x = event->mouse.x;
				*mouse_y = event->mouse.y;

				if (*key_down)
				{
					obracanie(tiles[i]);
					*key_down = false;
				}

			}


		}
	}
}


