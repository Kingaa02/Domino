#pragma once
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

#define TILE_SIZE 60
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960

typedef struct Tile Tile;
struct Tile {

	int p_x, p_y;
	int l_x, l_y;

	int start_p_x, start_p_y;
	int start_l_x, start_l_y;

	bool moveable;
	bool is_placed;
	int ilosc_oczek_lewo, ilosc_oczek_prawo;
	float rotation_degree;
	ALLEGRO_BITMAP* lewo;
	ALLEGRO_BITMAP* prawo;

};

//losowanie liczby oczek klocka startowegoa
void losowanie_oczek(struct Tile** tiles, int ilosc_domino);

void losowanie_oczek_dobrane(struct Tile** tiles, int ilosc_domino);

/// Przypisywanie odpowiednich grafik dla ka¿dej ze stron bloku
void przypisanie_grafik(Tile** tiles, int ilosc_domino);

/// Przypisywanie odpowiednich grafik dla ka¿dej ze stron bloku dobranych
void przypisanie_grafik_dobrane(Tile** tiles, int ilosc_domino);


/// Wyœwietlanie domina na ekranie
void wyswietlanie_domino(Tile** tiles, int ilosc_domino);

/// Tworzenie nowych bloków domina
Tile* nowy(int l_x, int l_y, int p_x, int p_y, float rotation_degree);

/// Powiêkszanie tablicy i dodawanie nowych domin do tablicy
Tile** dodawanie_domina(Tile** tab, int index, Tile* domino, unsigned int* length);

/// Wyœwietlanie zawartoœci tablicy z domino / Sprawdzanie wartoœci
void print_array(Tile** array, const unsigned int number_of_values);

/// Kolizja pomiêdzy blokami
int collision(Tile* domino_r, Tile** tiles, int ilosc_domino, int domino_i);

/// Obracanie blokow domino
void obracanie(Tile* current);

/// Poruszanie blokami przy pomocy myszki
void poruszanie(Tile** tiles, int ilosc_domino, ALLEGRO_EVENT* event, bool* key_down, int* mouse_x, int* mouse_y, int* current);

void dobieranie(Tile** tiles);

