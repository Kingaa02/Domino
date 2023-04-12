
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define TILE_SIZE 60

struct Tile {
    int a;
    int b;
};

//losowanie liczby oczek klocka startowego
void get_start_piece(struct Tile* tile) {
    srand(time(0));

    tile->a = rand() % 7;
    tile->b = rand() % 7;
}

//przydzielanie obrazka do wyœwietlenia w zale¿noœci od wylosowanej liczby oczek
void draw_start_tile(struct Tile start_tile, char tile_a[], char tile_b[]) {

    switch (start_tile.a) {
    case 0:
        strcpy_s(tile_a, 11, "tile_0.png");
        break;
    case 1:
        strcpy_s(tile_a, 11, "tile_1.png");
        break;
    case 2:
        strcpy_s(tile_a, 11,  "tile_2.png");
        break;
    case 3:
        strcpy_s(tile_a, 11,  "tile_3.png");
        break;
    case 4:
        strcpy_s(tile_a, 11, "tile_4.png");
        break;
    case 5:
        strcpy_s(tile_a, 11,  "tile_5.png");
        break;
    case 6:
        strcpy_s(tile_a, 11, "tile_6.png");
        break;
    }

    switch (start_tile.b) {
    case 0:
        strcpy_s(tile_b, 11, "tile_0.png");
        break;
    case 1:
        strcpy_s(tile_b, 11, "tile_1.png");
        break;
    case 2:
        strcpy_s(tile_b, 11, "tile_2.png");
        break;
    case 3:
        strcpy_s(tile_b, 11, "tile_3.png");
        break;
    case 4:
        strcpy_s(tile_b, 11, "tile_4.png");
        break;
    case 5:
        strcpy_s(tile_b, 11, "tile_5.png");
        break;
    case 6:
        strcpy_s(tile_b, 11, "tile_6.png");
        break;
    }
}

int main() {

    al_init();
    ALLEGRO_DISPLAY* display = NULL; // wskaŸnik na okno gry
    ALLEGRO_EVENT_QUEUE* event_queue = NULL; //wskaŸnik na kolejkê zdarzeñ
    al_init_image_addon();

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));

    char tile_a[11] = "tile_0.png", tile_b[11] = "tile_0.png"; //tablice przechowuj¹ce nazwy plików obrazów
    struct Tile start_tile;
    get_start_piece(&start_tile);
    draw_start_tile(start_tile, tile_a, tile_b);

    ALLEGRO_BITMAP* domino_tile_a = al_load_bitmap(tile_a);
    ALLEGRO_BITMAP* domino_tile_b = al_load_bitmap(tile_b);
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(domino_tile_a, SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE / 2, 0);
    al_draw_bitmap(domino_tile_b, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - TILE_SIZE / 2, 0);
    al_flip_display();

    bool running = true;
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }
    }
    al_destroy_bitmap(domino_tile_a);
    al_destroy_bitmap(domino_tile_b);
    al_destroy_display(display);

    return 0;
}

*/

#include <stdlib.h>
#include <stdio.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<stdbool.h>
#include<time.h>


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1024
#define TILE_SIZE 60



typedef struct Tile Tile;
struct Tile {

	int p_x, p_y;
	int l_x, l_y;


	int ilosc_oczek_lewo, ilosc_oczek_prawo;

	ALLEGRO_BITMAP* lewo;
	ALLEGRO_BITMAP* prawo;

};


//losowanie liczby oczek klocka startowegoa
void get_start_piece(struct Tile* tile) {
	srand(time(0));

	tile->ilosc_oczek_lewo = rand() % 7;
	tile->ilosc_oczek_prawo = rand() % 7;
}



void sprawdznie_init(bool test, char* opis)
{
	if (test)
		return;

	printf_s("Nie udalo sie uruchomic %s \n ", opis);
}



void draw_start_tile(struct Tile start_tile, char tile_a[], char tile_b[]) {

    switch (start_tile.ilosc_oczek_lewo) {
    case 0:
        strcpy_s(tile_a, 11, "tile_0.png");
        break;
    case 1:
        strcpy_s(tile_a, 11, "tile_1.png");
        break;
    case 2:
        strcpy_s(tile_a, 11, "tile_2.png");
        break;
    case 3:
        strcpy_s(tile_a, 11, "tile_3.png");
        break;
    case 4:
        strcpy_s(tile_a, 11, "tile_4.png");
        break;
    case 5:
        strcpy_s(tile_a, 11, "tile_5.png");
        break;
    case 6:
        strcpy_s(tile_a, 11, "tile_6.png");
        break;
    }

    switch (start_tile.ilosc_oczek_prawo) {
    case 0:
        strcpy_s(tile_b, 11, "tile_0.png");
        break;
    case 1:
        strcpy_s(tile_b, 11, "tile_1.png");
        break;
    case 2:
        strcpy_s(tile_b, 11, "tile_2.png");
        break;
    case 3:
        strcpy_s(tile_b, 11, "tile_3.png");
        break;
    case 4:
        strcpy_s(tile_b, 11, "tile_4.png");
        break;
    case 5:
        strcpy_s(tile_b, 11, "tile_5.png");
        break;
    case 6:
        strcpy_s(tile_b, 11, "tile_6.png");
        break;
    }
}






int main()
{
	sprawdznie_init(al_init(), "allegro");
	sprawdznie_init(al_install_keyboard(), "klawiatura");
	sprawdznie_init(al_install_mouse(), "mysz");
	sprawdznie_init(al_init_primitives_addon(), "primitives addon");
	sprawdznie_init(al_init_image_addon(), "zdjecia addon");


	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	sprawdznie_init(display, "Obraz");

    char tile_a[11] = "tile_0.png", tile_b[11] = "tile_0.png"; //tablice przechowuj¹ce nazwy plików obrazów
    struct Tile start_tile;
    get_start_piece(&start_tile);
    draw_start_tile(start_tile, tile_a, tile_b);

    Tile domino_tile;
        domino_tile.lewo= al_load_bitmap(tile_a);
        domino_tile.prawo = al_load_bitmap(tile_b);
  

   



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


	Tile blok1;
	blok1.lewo = al_load_bitmap("tile_1.png");
	blok1.prawo = al_load_bitmap("tile_1.png");


	blok1.l_x = 100;
	blok1.l_y = 100;


	blok1.p_x = 100;
	blok1.p_y = 160;


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
				blok1.l_x = blok1.l_x + event.mouse.x - mouse_x;
				blok1.l_y = blok1.l_y + event.mouse.y - mouse_y;

				blok1.p_x = blok1.p_x + event.mouse.x - mouse_x;
				blok1.p_y = blok1.p_y + event.mouse.y - mouse_y;

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

			al_draw_bitmap(blok1.lewo, blok1.l_x, blok1.l_y, 0);
			al_draw_bitmap(blok1.prawo, blok1.p_x, blok1.p_y, 0);

            al_draw_bitmap(domino_tile.lewo, SCREEN_WIDTH / 2 - TILE_SIZE, SCREEN_HEIGHT / 2 - TILE_SIZE / 2, 0);
            al_draw_bitmap(domino_tile.prawo, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - TILE_SIZE / 2, 0);

			al_flip_display();
			redraw = false;
		}


	}


	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	al_destroy_bitmap(blok1.lewo);
	al_destroy_bitmap(blok1.prawo);


}
