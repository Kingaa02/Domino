#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <time.h>


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960
#define TILE_SIZE 60

float x, y;

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

void losowanie_oczek_dobrane(struct Tile** tiles, int ilosc_domino) {


	tiles[ilosc_domino]->ilosc_oczek_lewo = rand() % 7;
	tiles[ilosc_domino]->ilosc_oczek_prawo = rand() % 7;

}



///sprawdzanie inicjacji
void sprawdzanie_init(bool test, char* opis)
{
	if (test)
		return;

	printf_s("Nie udalo sie uruchomic %s \n ", opis);
}


/// Przypisywanie odpowiednich grafik dla każdej ze stron bloku
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
/// Wyświetlanie domina na ekranie
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

/// Powiększanie tablicy i dodawanie nowych domin do tablicy
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

/// Wyświetlanie zawartości tablicy z domino / Sprawdzanie wartości
void print_array(Tile** array, const unsigned int number_of_values)
{
	if (array) {
		printf("W tablicy znajduje się %u wartości.\n", number_of_values);
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
	sprawdzanie_init(al_init(), "allegro");
	sprawdzanie_init(al_init_primitives_addon(), "primitives addon");
	sprawdzanie_init(al_init_image_addon(), "image addon");
	sprawdzanie_init(al_init_font_addon(), "font addon");
	sprawdzanie_init(al_install_mouse(), "mouse");
	sprawdzanie_init(al_init_ttf_addon(), "ttf addon");
	sprawdzanie_init(al_install_keyboard(), "klawiatura");
	sprawdzanie_init(al_install_audio(), "audio");
	sprawdzanie_init(al_init_acodec_addon(), "acodec");
	srand(time(NULL));

	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	sprawdzanie_init(display, "display");

	//MUZYKA
	al_reserve_samples(1);
	ALLEGRO_SAMPLE* song = al_load_sample("song.wav");
	ALLEGRO_SAMPLE_INSTANCE* songInstance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

	//char tile_a[11] = "tile_0.png", tile_b[11] = "tile_0.png"; //tablice przechowuj¹ce nazwy plików obrazów

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
	sprawdzanie_init(timer, "Zegar");

	ALLEGRO_BITMAP* background = al_load_bitmap("background.png");
	sprawdzanie_init(background, "background");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	sprawdzanie_init(queue, "queue");

	ALLEGRO_USTR* username2 = al_ustr_new("");


	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool done = false;
	bool redraw = true;

	ALLEGRO_EVENT event;

	ALLEGRO_FONT* font1 = al_load_font("FjallaOne.ttf", 36, 0);
	ALLEGRO_FONT* font2 = al_load_font("FjallaOne.ttf", 100, 0);
	ALLEGRO_FONT* font3 = al_load_font("FjallaOne.ttf", 36, 0);

	bool zasady = false;
	al_set_target_bitmap(al_get_backbuffer(display));


	bool menu = true;
	bool running = true;

	Tile** tiles = NULL;
	int ilosc_domino = 8;
	unsigned int length = 0;
	int start_x = 290;


	Tile** tiles_dobrane = NULL;
	unsigned int length_dobrane = 0;
	int i_dobrane = 0;
	int ilosc_dobranych = 0;

	int y_pos = SCREEN_HEIGHT - 200;
	int y2_pos = SCREEN_HEIGHT - 200 + TILE_SIZE;
	srand(time(0));

	///Tworzenie początkowych domino
	for (int i = 0; i < ilosc_domino; i++)
	{
		if (i == 0)
		{
			/// Środkowe domino
			tiles = dodawanie_domina(tiles, i, nowy(SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - TILE_SIZE / 2, 0), &length);
		}
		else if (i == 1)
		{
			tiles = dodawanie_domina(tiles, i, nowy(start_x, y_pos, start_x, y2_pos, 0), &length);
		}
		else
		{
			tiles = dodawanie_domina(tiles, i, nowy(tiles[i - 1]->l_x + 100, y_pos, tiles[i - 1]->p_x + 100, y2_pos, 0), &length);
		}

	}

	losowanie_oczek(tiles, ilosc_domino);
	przypisanie_grafik(tiles, ilosc_domino);
	print_array(tiles, ilosc_domino);

	bool button_down = false;
	bool new_game = false;
	bool username1 = true;

	int mouse_x, mouse_y;

	bool key_down = false;
	float rotation_degree = 0;

	bool button_pressed = false;

	//Odtwarzanie muzyki
	al_play_sample_instance(songInstance);

	al_start_timer(timer);

	while (running)
	{
		al_wait_for_event(queue, &event);

		if (username1)
		{
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(font1, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20, ALLEGRO_ALIGN_CENTRE, "Podaj nazwe uzytkownika");
			al_draw_text(font1, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 20, ALLEGRO_ALIGN_CENTRE, al_cstr(username2));

		}

		if (menu)
		{
			al_draw_bitmap(background, 0, 0, 0);
			al_draw_text(font2, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 450, ALLEGRO_ALIGN_CENTER, "DOMINO");
			al_draw_text(font1, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 30, ALLEGRO_ALIGN_CENTRE, "Nowa Gra");
			al_draw_text(font1, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 30, ALLEGRO_ALIGN_CENTRE, "Zasady");
			al_draw_text(font1, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 90, ALLEGRO_ALIGN_CENTRE, "Wyjscie");
		}

		switch (event.type)
		{

		case ALLEGRO_EVENT_TIMER:
			redraw = true;
			break;


		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = true;
			break;


		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:

			if (event.mouse.button & 1)
			{
				button_down = true;
				mouse_x = event.mouse.x;
				mouse_y = event.mouse.y;
			}
			if (event.mouse.x >= 0 && event.mouse.x <= 430 &&
				event.mouse.y >= 0 && event.mouse.y <= 50) {
				button_pressed = true;

			}

			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:

			if (event.mouse.button & 1)
			{
				button_down = false;
				/// Nowa gra
				if (!zasady && !new_game)
				{
					if (event.mouse.x > SCREEN_WIDTH / 2 - 90 && event.mouse.x < SCREEN_WIDTH / 2 + 90 && event.mouse.y > SCREEN_HEIGHT / 2 - 30 && event.mouse.y < SCREEN_HEIGHT / 2 - 5)
					{
						menu = false;
						new_game = true;
						username1 = true;
					}

					//Wyjście
					if (event.mouse.x > SCREEN_WIDTH / 2 - 70 && event.mouse.x < SCREEN_WIDTH / 2 + 70 && event.mouse.y > SCREEN_HEIGHT / 2 + 90 && event.mouse.y < SCREEN_HEIGHT / 2 + 110)
					{
						menu = false;
						running = false;
					}

					/// Zasady
					if (event.mouse.x > SCREEN_WIDTH / 2 - 70 && event.mouse.x < SCREEN_WIDTH / 2 + 70 && event.mouse.y > SCREEN_HEIGHT / 2 + 30 && event.mouse.y < SCREEN_HEIGHT / 2 + 70)
					{
						zasady = true;
						menu = false;
						username1 = false;

						//al_draw_multiline_text(font, color, x, y, maxWidth, al_get_font_line_height(font), 0, text);
						al_draw_bitmap(background, 0, 0, 0);
						al_draw_multiline_text(font3, al_map_rgb(255, 255, 255), 0, 20, SCREEN_WIDTH, al_get_font_line_height(font3), 0, "1.Gra odbywa sie z uzyciem zestawu kosci domino, skladajacego sie z 28 kamieni");
						al_draw_multiline_text(font3, al_map_rgb(255, 255, 255), 0, 80, SCREEN_WIDTH, al_get_font_line_height(font3), 0, "2.Kazdy kamien sklada sie z dwoch pol, z kazdej strony znajduje sie na nim od 0 do 6 kropek.");
						al_draw_multiline_text(font3, al_map_rgb(255, 255, 255), 0, 140, SCREEN_WIDTH, al_get_font_line_height(font3), 0, "3.Gra zaczyna sie od wylozenia na stol jednego z kamieni (tzw. kostki) z dowolnie wybranym ukladem kropek.");
						al_draw_multiline_text(font3, al_map_rgb(255, 255, 255), 0, 240, SCREEN_WIDTH, al_get_font_line_height(font3), 0, "4.Gracze na przemian dolaczaja do kostki kolejne kamienie, tak aby liczba kropek na jednym polu nowo dolozonej kostki byla rowna liczbie kropek na odpowiadajacym mu polu kostki lezacej na stole.");
						al_draw_multiline_text(font3, al_map_rgb(255, 255, 255), 0, 380, SCREEN_WIDTH, al_get_font_line_height(font3), 0, "5.Jesli gracz nie moze dolozyc zadnego kamienia, przepada swoja kolejke.");
						al_draw_multiline_text(font3, al_map_rgb(255, 255, 255), 0, 440, SCREEN_WIDTH, al_get_font_line_height(font3), 0, "6.Wygrywa gracz, ktory pierwszy pozbyl sie wszystkich swoich kamieni.");
						al_draw_text(font1, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400, ALLEGRO_ALIGN_CENTRE, "Powrot");

					}

				}
				else if (zasady)
				{
					//powrót
					if (event.mouse.x > SCREEN_WIDTH / 2 - 70 && event.mouse.x < SCREEN_WIDTH / 2 + 70 && event.mouse.y < SCREEN_HEIGHT / 2 + 430 && event.mouse.y > SCREEN_HEIGHT / 2 + 400)
					{
						menu = true;
						zasady = false;

					}
				}
			}
			if (new_game)
			{
				if (button_pressed && event.mouse.x >= 0 && event.mouse.x <= 430 &&
					event.mouse.y >= 0 && event.mouse.y <= 50) {
					// Przycisk został kliknięty
					printf("Przycisk dziala");
					tiles_dobrane = dodawanie_domina(tiles_dobrane, i_dobrane, nowy(80, 80, 80, 140, 0), &length_dobrane);

					losowanie_oczek_dobrane(tiles_dobrane, ilosc_dobranych);
					przypisanie_grafik_dobrane(tiles_dobrane, ilosc_dobranych);
					i_dobrane++;
					ilosc_dobranych++;
					break;
				}
				button_pressed = false;
				break;
			}

		case ALLEGRO_EVENT_MOUSE_AXES:

			x = event.mouse.x;
			y = event.mouse.y;

			//Przesuwanie bloków
			if (button_down)
			{
				for (int i = 1; i < ilosc_domino; i++)
				{


					if (tiles[i]->rotation_degree == 0 || tiles[i]->rotation_degree == 180)
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
									tiles[i]->rotation_degree += 90;
									if (tiles[i]->rotation_degree >= 360)
										tiles[i]->rotation_degree = 0;
									key_down = false;
								}

							}
					}
					else
					{
						if (event.mouse.x >= tiles[i]->l_x - 30 && event.mouse.x <= tiles[i]->p_x + 90)
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


				for (int i = 0; i < ilosc_dobranych; i++)
				{
					if (event.mouse.x >= tiles_dobrane[i]->l_x && event.mouse.x <= tiles_dobrane[i]->p_x + TILE_SIZE)
						if (event.mouse.y >= tiles_dobrane[i]->l_y && event.mouse.y <= tiles_dobrane[i]->p_y + TILE_SIZE)
						{
							tiles_dobrane[i]->l_x = tiles_dobrane[i]->l_x + event.mouse.x - mouse_x;
							tiles_dobrane[i]->l_y = tiles_dobrane[i]->l_y + event.mouse.y - mouse_y;

							tiles_dobrane[i]->p_x = tiles_dobrane[i]->p_x + event.mouse.x - mouse_x;
							tiles_dobrane[i]->p_y = tiles_dobrane[i]->p_y + event.mouse.y - mouse_y;

							mouse_x = event.mouse.x;
							mouse_y = event.mouse.y;


							///Obracanie domino
							if (key_down)
							{
								tiles_dobrane[i]->rotation_degree += 90;
								if (tiles_dobrane[i]->rotation_degree >= 360)
									tiles_dobrane[i]->rotation_degree = 0;
								key_down = false;
							}

						}
						else
						{
							if (event.mouse.x >= tiles_dobrane[i]->l_x - 30 && event.mouse.x <= tiles_dobrane[i]->p_x + 90)
								if (event.mouse.y >= tiles_dobrane[i]->l_y + 30 && event.mouse.y <= tiles_dobrane[i]->p_y + 30)
								{
									tiles_dobrane[i]->l_x = tiles_dobrane[i]->l_x + event.mouse.x - mouse_x;
									tiles_dobrane[i]->l_y = tiles_dobrane[i]->l_y + event.mouse.y - mouse_y;

									tiles_dobrane[i]->p_x = tiles_dobrane[i]->p_x + event.mouse.x - mouse_x;
									tiles_dobrane[i]->p_y = tiles_dobrane[i]->p_y + event.mouse.y - mouse_y;

									mouse_x = event.mouse.x;
									mouse_y = event.mouse.y;

									///Obracanie domino
									if (key_down)
									{
										tiles_dobrane[i]->rotation_degree += 90;
										if (tiles_dobrane[i]->rotation_degree >= 360)
											tiles_dobrane[i]->rotation_degree = 0;
										key_down = false;
									}
								}
						}
				}
			}
			break;

		case ALLEGRO_EVENT_KEY_CHAR:
		{
			if (!menu)
			{
				int keycode = event.keyboard.keycode;
				if ((keycode >= ALLEGRO_KEY_A && keycode <= ALLEGRO_KEY_Z) || keycode == ALLEGRO_KEY_SPACE) {
					al_ustr_append_chr(username2, (char)tolower(event.keyboard.unichar));
				}
				else if (keycode == ALLEGRO_KEY_BACKSPACE && al_ustr_length(username2) > 0) {
					al_ustr_remove_chr(username2, al_ustr_length(username2) - 1);
				}
				else if (keycode == ALLEGRO_KEY_ENTER && al_ustr_length(username2) > 0)
				{
					username1 = false;
					break;
				}

				///Sprawdzenie czy wciśnięto przycis do oborotu bloku oraz ustawienie jego statusu
				if (event.keyboard.keycode = ALLEGRO_KEY_R)
				{
					key_down = true;
				}
				break;
			}
			}
		}


		if (done)
			break;
		//GRA

		if (redraw && al_is_event_queue_empty(queue))
		{
			if (!username1 && new_game)
			{
				al_clear_to_color(al_map_rgb(0, 64, 0));

				wyswietlanie_domino(tiles, ilosc_domino);
				wyswietlanie_domino(tiles_dobrane, ilosc_dobranych);
				al_draw_filled_rectangle(0, 0, 430, 50, al_map_rgb(0, 64, 0), 10);
				al_draw_text(font1, al_map_rgb(255, 255, 255), 10, 10, ALLEGRO_ALIGN_LEFT, "Dobierz kafelki tutaj");

				//Narysowane hitboxy
				//al_draw_rectangle(tiles[1]->l_x, tiles[1]->l_y, tiles[1]->p_x + 60, tiles[1]->p_y + 60, al_map_rgb(0, 255, 0), 5);
				//al_draw_rectangle(tiles[1]->l_x-30, tiles[1]->l_y + 30, tiles[1]->p_x + 90, tiles[1]->p_y + 30, al_map_rgb(0, 255, 0), 5)

				al_flip_display();
				redraw = false;
			}
		}
		al_flip_display();
	}


	for (int i = 0; i < ilosc_domino; i++)
	{
		free(tiles[i]);
	}
	free(tiles);


	al_destroy_bitmap(background);
	al_destroy_font(font1);
	al_destroy_font(font2);
	al_destroy_event_queue(queue);
	al_destroy_display(display);
	al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);

	return 0;
}