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
#include"Domino.h"
#include"Player.h"
#include"Domino_placed.h"


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960
#define TILE_SIZE 60

float x, y;

///sprawdzanie inicjacji
void sprawdzanie_init(bool test, char* opis)
{
	if (test)
		return;

	printf_s("Nie udalo sie uruchomic %s \n ", opis);
}
 

int main()
{
	///Zainicjowanie potrzebnych funkcji bibliotetki allegro 5
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


	//KURSOR
	ALLEGRO_BITMAP* cursorImage = al_load_bitmap("cursor.png");
	ALLEGRO_MOUSE_STATE mouseState;

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
	sprawdzanie_init(timer, "Zegar");

	ALLEGRO_BITMAP* background = al_load_bitmap("background.png");
	sprawdzanie_init(background, "background");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	sprawdzanie_init(queue, "queue");

	///Przypisanie zródeł zdarzeń do kolejki zdarzeń
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));


	ALLEGRO_EVENT event;
	///Załadowanie czcionki
	ALLEGRO_FONT* font1 = al_load_font("FjallaOne.ttf", 36, 0);
	ALLEGRO_FONT* font2 = al_load_font("FjallaOne.ttf", 100, 0);
	ALLEGRO_FONT* font3 = al_load_font("FjallaOne.ttf", 36, 0);

	al_set_target_bitmap(al_get_backbuffer(display));

	/// Inicjacja flag
	bool done = false;
	bool redraw = true;
	bool zasady = false;
	bool menu = true;
	bool running = true;

	bool button_down = false;
	bool new_game = false;
	bool key_down = false;
	bool button_pressed = false;


	/// Stworzenie tablicy do przechowywania położonych już kafelków
	Tile** tiles_on_board = NULL;
	int ilosc_domino_on_board = 1;
	unsigned int length = 0;
	int start_x = 290;

	tiles_on_board = dodawanie_domina(tiles_on_board, 0, nowy(560, 380, 620, 380, 0), &length);
	losowanie_oczek(tiles_on_board, ilosc_domino_on_board);
	przypisanie_grafik(tiles_on_board, ilosc_domino_on_board);
	
	srand(time(0));

	///Tworzenie graczy oraz ich kafelków
	
	Player gracz_1;
	Player gracz_2;
	int current_player = 1;

	creating_players_domino(&gracz_1);
	creating_players_domino(&gracz_2);

	int current_selected_tile = 0;

	/// Stworzenie miejsca do układania domina
	Tile* placing_space = placing_domino(tiles_on_board[0]);


	int mouse_x, mouse_y;
	float rotation_degree = 0;



	//Odtwarzanie muzyki
	al_play_sample_instance(songInstance);

	al_start_timer(timer);
	/// Uruchomienie kursora
	ALLEGRO_MOUSE_CURSOR* cursor = al_create_mouse_cursor(cursorImage, 0, 0);
	al_set_mouse_cursor(display, cursor);

	while (running)
	{
		al_wait_for_event(queue, &event);

		al_get_mouse_state(&mouseState);

		int windowX, windowY;
		al_get_window_position(display, &windowX, &windowY);

		int mouseX = mouseState.x - windowX;
		int mouseY = mouseState.y - windowY;

		al_set_target_bitmap(al_get_backbuffer(display));
		/// Wyświetlanie menu
		if (menu)
		{
			al_draw_bitmap(background, 0, 0, 0);
			al_draw_text(font2, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 300, ALLEGRO_ALIGN_CENTER, "DOMINO");
			al_draw_text(font1, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 30, ALLEGRO_ALIGN_CENTRE, "Nowa Gra");
			al_draw_text(font1, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 30, ALLEGRO_ALIGN_CENTRE, "Zasady");
			al_draw_text(font1, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 90, ALLEGRO_ALIGN_CENTRE, "Wyjscie");
		}

		switch (event.type)
		{

		case ALLEGRO_EVENT_TIMER:
			redraw = true;
			break;

			///Zamknięcie gry
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = true;
			break;

			///Sprawdzenie czy wciśnięto przycisk myszy
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

		case ALLEGRO_EVENT_MOUSE_AXES:

			x = event.mouse.x;
			y = event.mouse.y;

			/// Poruszanie kafelkami
			if (button_down)
			{
				if (current_player == 1)
				{
					poruszanie(gracz_1.domino_gracza, gracz_1.ilosc_domino, &event, &key_down, &mouse_x, &mouse_y, &current_selected_tile);
				}
				else
				{
					poruszanie(gracz_2.domino_gracza, gracz_2.ilosc_domino, &event, &key_down, &mouse_x, &mouse_y, &current_selected_tile);
				}
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
				/// Uruchomienie funkcji układania w zależności od tego którego gracza jest teraz tura
				if (current_player == 1)
				{
					placing(gracz_1.domino_gracza[current_selected_tile], placing_space, &gracz_1, &current_selected_tile, tiles_on_board, &ilosc_domino_on_board, &length, &current_player);
				}
				else
				{
					placing(gracz_2.domino_gracza[current_selected_tile], placing_space, &gracz_2, &current_selected_tile, tiles_on_board, &ilosc_domino_on_board, &length, &current_player);
				}
				
			}
			if (new_game)
			{
				///Przycisk służący do dobierania nowych kafelków
				if (button_pressed && event.mouse.x >= 0 && event.mouse.x <= 430 &&
					event.mouse.y >= 0 && event.mouse.y <= 50) {
				
					if (current_player == 1)
					{
						dobieranie(&gracz_1);
					}
					else
					{
						dobieranie(&gracz_2);
					}
					break;
				}
				button_pressed = false;
				break;
			}

		case ALLEGRO_EVENT_KEY_CHAR:
		{
			
				///Sprawdzenie czy wciśnięto przycis do oborotu bloku oraz ustawienie jego statusu
				if (event.keyboard.keycode = ALLEGRO_KEY_R)
				{
					key_down = true;
				}
				break;
			
			}
		}

		if (done)
			break;

		if (redraw && al_is_event_queue_empty(queue))
		{
			///Wyświetlanie gry
			if ( new_game)
			{
				if (gracz_1.ilosc_polozonych != gracz_1.ilosc_domino && gracz_2.ilosc_polozonych != gracz_2.ilosc_domino)
				{
					al_clear_to_color(al_map_rgb(0, 64, 0));
					al_draw_rectangle(20, 20, SCREEN_WIDTH - 60, SCREEN_HEIGHT - 220, al_map_rgb(100, 100, 100), 2);


					al_draw_filled_rectangle(0, 0, 430, 50, al_map_rgb(0, 64, 0), 10);
					al_draw_text(font1, al_map_rgb(255, 255, 255), 10, 10, ALLEGRO_ALIGN_LEFT, "Dobierz kafelki tutaj");
					wyswietlanie_domino(tiles_on_board, ilosc_domino_on_board);

				///Wyświetlanie odpowiedniego domina w zależności od tury
					if (current_player == 1)
					{
						wyswietlanie_domino(gracz_1.domino_gracza, gracz_1.ilosc_domino);

					}
					else
					{
						wyswietlanie_domino(gracz_2.domino_gracza, gracz_2.ilosc_domino);
					}
				}
				else
				{
					if (gracz_1.ilosc_polozonych == gracz_1.ilosc_domino)
					{
						al_clear_to_color(al_map_rgb(0, 64, 0));
						//wygrywa gracz 1
					}
					else if (gracz_2.ilosc_polozonych == gracz_2.ilosc_domino)
					{
						al_clear_to_color(al_map_rgb(0, 64, 0));
						// wygrywa gracz 2
						
					}
				}

				al_flip_display();
				redraw = false;
			}
		}
		al_flip_display();
	}


	///Zwolnienie pamięci
	free(gracz_1.domino_gracza);
	free(gracz_2.domino_gracza);
	free(tiles_on_board);


	///Zamknięcie zainicjowanych elementów
	al_destroy_bitmap(background);
	al_destroy_font(font1);
	al_destroy_font(font2);
	al_destroy_event_queue(queue);
	al_destroy_display(display);
	al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);

	return 0;
}