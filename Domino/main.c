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

	char tile_a[11], tile_b[11];

	int ilosc_oczek_lewo, ilosc_oczek_prawo;
	ALLEGRO_BITMAP* lewo;
	ALLEGRO_BITMAP* prawo;

};


//losowanie liczby oczek klocka startowegoa
void get_start_piece(struct Tile* tile) {

	tile->ilosc_oczek_lewo = rand() % 7;
	tile->ilosc_oczek_prawo = rand() % 7;
}



void sprawdznie_init(bool test, char* opis)
{
	if (test)
		return;

	printf_s("Nie udalo sie uruchomic %s \n ", opis);
}



void draw_start_tile(Tile* start_tile) {

	switch (start_tile->ilosc_oczek_lewo) {
	case 0:
		strcpy_s(start_tile->tile_a, 11, "tile_0.png");
		break;
	case 1:
		strcpy_s(start_tile->tile_a, 11, "tile_1.png");
		break;
	case 2:
		strcpy_s(start_tile->tile_a, 11, "tile_2.png");
		break;
	case 3:
		strcpy_s(start_tile->tile_a, 11, "tile_3.png");
		break;
	case 4:
		strcpy_s(start_tile->tile_a, 11, "tile_4.png");
		break;
	case 5:
		strcpy_s(start_tile->tile_a, 11, "tile_5.png");
		break;
	case 6:
		strcpy_s(start_tile->tile_a, 11, "tile_6.png");
		break;
	}

	switch (start_tile->ilosc_oczek_prawo) {
	case 0:
		strcpy_s(start_tile->tile_b, 11, "tile_0.png");
		break;
	case 1:
		strcpy_s(start_tile->tile_b, 11, "tile_1.png");
		break;
	case 2:
		strcpy_s(start_tile->tile_b, 11, "tile_2.png");
		break;
	case 3:
		strcpy_s(start_tile->tile_b, 11, "tile_3.png");
		break;
	case 4:
		strcpy_s(start_tile->tile_b, 11, "tile_4.png");
		break;
	case 5:
		strcpy_s(start_tile->tile_b, 11, "tile_5.png");
		break;
	case 6:
		strcpy_s(start_tile->tile_b, 11, "tile_6.png");
		break;
	}
}


void game_draw(Tile blok1, Tile blok2, Tile blok3, Tile blok4, Tile blok5, Tile blok6, Tile blok7)
{
	al_draw_bitmap(blok1.lewo, 290, SCREEN_HEIGHT - 200, 0);
	al_draw_bitmap(blok1.prawo, 290, SCREEN_HEIGHT - 200 + TILE_SIZE, 0);

	al_draw_bitmap(blok2.lewo, 390, SCREEN_HEIGHT - 200, 0);
	al_draw_bitmap(blok2.prawo, 390, SCREEN_HEIGHT - 200 + TILE_SIZE, 0);

	al_draw_bitmap(blok3.lewo, 490, SCREEN_HEIGHT - 200, 0);
	al_draw_bitmap(blok3.prawo, 490, SCREEN_HEIGHT - 200 + TILE_SIZE, 0);

	al_draw_bitmap(blok4.lewo, 590, SCREEN_HEIGHT - 200, 0);
	al_draw_bitmap(blok4.prawo, 590, SCREEN_HEIGHT - 200 + TILE_SIZE, 0);

	al_draw_bitmap(blok5.lewo, 690, SCREEN_HEIGHT - 200, 0);
	al_draw_bitmap(blok5.prawo, 690, SCREEN_HEIGHT - 200 + TILE_SIZE, 0);

	al_draw_bitmap(blok6.lewo, 790, SCREEN_HEIGHT - 200, 0);
	al_draw_bitmap(blok6.prawo, 790, SCREEN_HEIGHT - 200 + TILE_SIZE, 0);

	al_draw_bitmap(blok7.lewo, 890, SCREEN_HEIGHT - 200, 0);
	al_draw_bitmap(blok7.prawo, 890, SCREEN_HEIGHT - 200 + TILE_SIZE, 0);

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
	struct Tile start_tile;
	get_start_piece(&start_tile);
	draw_start_tile(&start_tile);


	Tile domino_tile;
	domino_tile.lewo = al_load_bitmap(start_tile.tile_a);
	domino_tile.prawo = al_load_bitmap(start_tile.tile_b);





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


	Tile blok;
	blok.lewo = al_load_bitmap("tile_1.png");
	blok.prawo = al_load_bitmap("tile_1.png");

	Tile blok1, blok2, blok3, blok4, blok5, blok6, blok7;

	get_start_piece(&blok1);
	draw_start_tile(&blok1);
	blok1.lewo = al_load_bitmap(blok1.tile_a);
	blok1.prawo = al_load_bitmap(blok1.tile_b);

	get_start_piece(&blok2);
	draw_start_tile(&blok2);
	blok2.lewo = al_load_bitmap(blok2.tile_a);
	blok2.prawo = al_load_bitmap(blok2.tile_b);

	get_start_piece(&blok3);
	draw_start_tile(&blok3);
	blok3.lewo = al_load_bitmap(blok3.tile_a);
	blok3.prawo = al_load_bitmap(blok3.tile_b);


	get_start_piece(&blok4);
	draw_start_tile(&blok4);
	blok4.lewo = al_load_bitmap(blok4.tile_a);
	blok4.prawo = al_load_bitmap(blok4.tile_b);


	get_start_piece(&blok5);
	draw_start_tile(&blok5);
	blok5.lewo = al_load_bitmap(blok5.tile_a);
	blok5.prawo = al_load_bitmap(blok5.tile_b);


	get_start_piece(&blok6);
	draw_start_tile(&blok6);
	blok6.lewo = al_load_bitmap(blok6.tile_a);
	blok6.prawo = al_load_bitmap(blok6.tile_b);


	get_start_piece(&blok7);
	draw_start_tile(&blok7);
	blok7.lewo = al_load_bitmap(blok7.tile_a);
	blok7.prawo = al_load_bitmap(blok7.tile_b);
	blok.l_x = 100;
	blok.l_y = 100;


	blok.p_x = 100;
	blok.p_y = 160;


	bool button_down = false;

	int mouse_x, mouse_y;


	al_start_timer(timer);

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


		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:

			if (event.mouse.button & 1)
			{
				button_down = true;
				mouse_x = event.mouse.x;
				mouse_y = event.mouse.y;
			}

			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:

			if (event.mouse.button & 1)
			{
				button_down = false;
			}

			break;

		case ALLEGRO_EVENT_MOUSE_AXES:

			if (button_down)
			{
				blok.l_x = blok.l_x + event.mouse.x - mouse_x;
				blok.l_y = blok.l_y + event.mouse.y - mouse_y;

				blok.p_x = blok.p_x + event.mouse.x - mouse_x;
				blok.p_y = blok.p_y + event.mouse.y - mouse_y;

				mouse_x = event.mouse.x;
				mouse_y = event.mouse.y;

			}



			break;

		}
		if (done)
			break;

		if (redraw && al_is_event_queue_empty(queue))
		{
			al_clear_to_color(al_map_rgb(255, 255, 255));

			al_draw_bitmap(blok.lewo, blok.l_x, blok.l_y, 0);
			al_draw_bitmap(blok.prawo, blok.p_x, blok.p_y, 0);

			al_draw_bitmap(domino_tile.lewo, SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE / 2, 0);
			al_draw_bitmap(domino_tile.prawo, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - TILE_SIZE / 2, 0);

			game_draw(blok1, blok2, blok3, blok4, blok5, blok6, blok7);

			al_flip_display();
			redraw = false;
		}


	}


	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	al_destroy_bitmap(blok.lewo);
	al_destroy_bitmap(blok.prawo);


}
