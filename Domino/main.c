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
