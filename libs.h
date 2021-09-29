#ifndef DUNGEON_C_LIBS_H
#define DUNGEON_C_LIBS_H

#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct monster {
    size_t x;
    size_t y;
    char dir;
} Monster;

struct typLevel {
    char *state;
    size_t row;
    size_t col;
    size_t playerX; //x coordinate of the player
    size_t playerY; //y coordinate of the player
    int playerState; //-1 if there is no player
    Monster *monsters; //array of monsters
    size_t anzahl_monsters; //length of the array
};

void move_monster(struct typLevel *level);

bool check_if_exit(struct typLevel lvl, size_t row, size_t col);

bool check_if_wall(struct typLevel lvl, size_t row, size_t col);

void play(FILE *input, FILE *level, FILE *output);

bool check_if_monster(struct typLevel level, size_t row, size_t col);

void get_s_position(FILE *input, struct typLevel *level);

void update_field_horizontally(struct typLevel level, size_t row, size_t col, int operator, int index);

void update_level_vertically(struct typLevel level, size_t row, size_t col, int operator, int index);

void free_level(struct typLevel *level);

Monster *init_monster(struct typLevel *level);

void movePlayer(FILE *input, FILE *output, struct typLevel *level);

bool check_status(struct typLevel *level, FILE *output);

void setElement(struct typLevel *level, size_t row, size_t col, char value);

char getElement(struct typLevel *level, size_t row, size_t col);

size_t anzahl_monsters(FILE *input);

#endif //DUNGEON_C_LIBS_H