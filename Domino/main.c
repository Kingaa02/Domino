#include <stdlib.h>
#include <stdio.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<stdbool.h>
#include<time.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960
#define TILE_SIZE 60


typedef struct Tile Tile;
struct Tile {

	int p_x, p_y;
	int l_x, l_y;
	int ilosc_oczek_lewo, ilosc_oczek_prawo;
	float rotation_degree;
	ALLEGRO_BITMAP* lewo;
	ALLEGRO_BITMAP* prawo;

};


//losowanie liczby oczek klocka startowegoa
void losowanie_oczek(struct Tile** tiles, int ilosc_domino) {

	for (int i = 0; i < ilosc_domino; i++)
	{
		tiles[i]->ilosc_oczek_lewo = rand() % 7;
		tiles[i]->ilosc_oczek_prawo = rand() % 7;
	}
}


///Sprawdzanie inicjacji
void sprawdznie_init(bool test, char* opis)
{
	if (test)
		return;

	printf_s("Nie udalo sie uruchomic %s \n ", opis);
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

/// Wyœwietlanie domina na ekranie
void wyswietlanie_domino(Tile** tiles, int ilosc_domino)
{
	for (int i = 0; i < ilosc_domino; i++)
	{
		if (i == 0)
		{
			al_draw_bitmap(tiles[i]->lewo, tiles[i]->l_x, tiles[i]->l_y,0);
			al_draw_bitmap(tiles[i]->prawo, tiles[i]->p_x, tiles[i]->p_y,0);
		}
		else
		{

			al_draw_rotated_bitmap(tiles[i]->lewo, TILE_SIZE / 2, TILE_SIZE, tiles[i]->l_x + TILE_SIZE / 2, tiles[i]->p_y, tiles[i]->rotation_degree * 3.14159 / 180, 0);
			al_draw_rotated_bitmap(tiles[i]->prawo, TILE_SIZE / 2, 0, tiles[i]->p_x + TILE_SIZE / 2, tiles[i]->p_y, tiles[i]->rotation_degree * 3.14159 / 180, 0);

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
		n->rotation_degree = rotation_degree;
		return n;
	}
	return NULL;
}

/// Powiêkszanie tablicy i dodawanie nowych domin do tablicy
Tile** dodawanie_domina(Tile** tab, int index, Tile* domino, unsigned int* length)
{
	const unsigned int powiekszenie = 10;

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
/// Wyœwietlanie zawartoœci tablicy z domino / Sprawdzanie wartoœci
void print_array(Tile** array, const unsigned int number_of_values)
{
	if (array) {
		printf("W tablicy znajduje siê %u wartoœci.\n", number_of_values);
		for (int i = 0; i < number_of_values; i++)
		{
			printf("l_x %d \n", array[i]->l_x);
			printf("l_y %d \n", array[i]->l_y);
			printf("p_x %d \n", array[i]->p_x);
			printf("p_y %d \n", array[i]->p_y);
			printf("ilosc_oczek_lewo %d \n", array[i]->ilosc_oczek_lewo);
			array[i]->lewo;

		}
		puts("");
	}
}



int main()
{
	sprawdznie_init(al_init(), "allegro");
	sprawdznie_init(al_install_keyboard(), "klawiatura");
	sprawdznie_init(al_install_mouse(), "mysz");
	sprawdznie_init(al_init_primitives_addon(), "primitives addon");
	sprawdznie_init(al_init_image_addon(), "zdjecia addon");

	srand(time(NULL));

	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	sprawdznie_init(display, "Obraz");

	//char tile_a[11] = "tile_0.png", tile_b[11] = "tile_0.png"; //tablice przechowuj¹ce nazwy plików obrazów



	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
	sprawdznie_init(timer, "Zegar");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	sprawdznie_init(queue, "Kolejka");


	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));


	bool done = false;
	bool redraw = true;

	ALLEGRO_EVENT event;

	Tile** tiles = NULL;
	int ilosc_domino = 8;
	unsigned int length = 0;
	int start_x = 290;

	int y_pos = SCREEN_HEIGHT - 200;
	int y2_pos = SCREEN_HEIGHT - 200 + TILE_SIZE;
	srand(time(0));


	///Tworzenie pocz¹tkowych domino
	for (int i = 0; i < ilosc_domino; i++)
	{
		if (i == 0)
		{
			/// Œrodkowe domino
			tiles = dodawanie_domina(tiles, i, nowy(SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - TILE_SIZE / 2,0	), &length);
		}
		else if (i == 1)
		{
			tiles = dodawanie_domina(tiles, i, nowy(start_x, y_pos, start_x, y2_pos,0), &length);
		}
		else
		{
			tiles = dodawanie_domina(tiles, i, nowy(tiles[i - 1]->l_x + 100, y_pos, tiles[i - 1]->p_x + 100, y2_pos,0), &length);
		}

	}

	losowanie_oczek(tiles, ilosc_domino);
	przypisanie_grafik(tiles, ilosc_domino);
	print_array(tiles, ilosc_domino);



	bool mouse_button_down = false;
	int mouse_x, mouse_y;


	bool key_down = false;

	float rotation_degree = 0;

	al_start_timer(timer);
	///Funkcja g³ówna
	while (true)
	{
		al_wait_for_event(queue, &event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			redraw = true;
			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = true;
			break;
			///Sprawdzenie czy wciœniêto przycis do oborotu bloku oraz ustawienie jego statusu
		case ALLEGRO_EVENT_KEY_CHAR:
			if (event.keyboard.keycode = ALLEGRO_KEY_R)
			{
				key_down = true;
			}
			break;
			///Sprawdzenie czy wciœniêto przyscisk myszy
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:

			if (event.mouse.button & 1)
			{
				mouse_button_down = true;
				mouse_x = event.mouse.x;
				mouse_y = event.mouse.y;
			}

			break;
			///Sprawdzenie czy przycisk myszy zosta³ puszczony
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:

			if (event.mouse.button & 1)
			{
				mouse_button_down = false;
			}

			break;

		case ALLEGRO_EVENT_MOUSE_AXES:

			//Przesuwanie bloków
			if (mouse_button_down)
			{
				for (int i = 1; i < ilosc_domino; i++)
				{


					if(tiles[i]->rotation_degree == 0 || tiles[i]->rotation_degree == 180 )
					{
						if (event.mouse.x >= tiles[i]->l_x && event.mouse.x <= tiles[i]->p_x + TILE_SIZE)
							if (event.mouse.y >= tiles[i]->l_y && event.mouse.y <= tiles[i]->p_y + TILE_SIZE)
							{
								tiles[i]->l_x = tiles[i]->l_x + event.mouse.x - mouse_x;
								tiles[i]->l_y = tiles[i]->l_y + event.mouse.y - mouse_y;

								tiles[i]->p_x = tiles[i]->p_x + event.mouse.x - mouse_x;
								tiles[i]->p_y = tiles[i]->p_y + event.mouse.y - mouse_y;

								mouse_x = event.mouse.x;
								mouse_y = event.mouse.y;


								///Obracanie domino
								if (key_down)
								{
									tiles[i]->rotation_degree +=90;
									if (tiles[i]->rotation_degree >= 360)
										tiles[i]->rotation_degree = 0;
									key_down = false;
								}
								
							}
					}
					else
					{
						if(event.mouse.x >= tiles[i]->l_x - 30 && event.mouse.x <= tiles[i]->p_x + 90)
							if (event.mouse.y >= tiles[i]->l_y + 30 && event.mouse.y <= tiles[i]->p_y + 30)
							{
								tiles[i]->l_x = tiles[i]->l_x + event.mouse.x - mouse_x;
								tiles[i]->l_y = tiles[i]->l_y + event.mouse.y - mouse_y;

								tiles[i]->p_x = tiles[i]->p_x + event.mouse.x - mouse_x;
								tiles[i]->p_y = tiles[i]->p_y + event.mouse.y - mouse_y;

								mouse_x = event.mouse.x;
								mouse_y = event.mouse.y;

								///Obracanie domino
								if (key_down)
								{
									tiles[i]->rotation_degree += 90;
									if (tiles[i]->rotation_degree >= 360)
										tiles[i]->rotation_degree = 0;
									key_down = false;
								}
							}
					}
				



				}

			}

			break;

		}
		if (done)
			break;

		if (redraw && al_is_event_queue_empty(queue))
		{
			al_clear_to_color(al_map_rgb(255, 255, 255));

			wyswietlanie_domino(tiles, ilosc_domino);

			//Narysowane hitboxy
			//al_draw_rectangle(tiles[1]->l_x, tiles[1]->l_y, tiles[1]->p_x + 60, tiles[1]->p_y + 60, al_map_rgb(0, 255, 0), 5);
			//al_draw_rectangle(tiles[1]->l_x-30, tiles[1]->l_y + 30, tiles[1]->p_x + 90, tiles[1]->p_y + 30, al_map_rgb(0, 255, 0), 5);


			al_flip_display();
			redraw = false;
		}


	}

	for (int i = 0; i < ilosc_domino; i++)
	{
		free(tiles[i]);
	}
	free(tiles);

	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);



}
