#include "libs.h"

//get the number of monsters
size_t anzahl_monsters(FILE *input) {
    rewind(input);
    int result = 0;
    while (!feof(input)) {
        int c = fgetc(input);
        if (c == '^' || c == 'v' || c == '<' || c == '>') {
            ++result;
        }
    }
    rewind(input);
    return result;
}


//initialize the monster array
Monster *init_monster(struct typLevel *level) {
    Monster *monster = calloc(level->anzahl_monsters, sizeof(Monster));
    int k = 0;
    for (size_t i = 0; i < level->row; ++i) {
        for (size_t j = 0; j < level->col; ++j) {
            if (check_if_monster(*level, i, j)) {
                monster[k].dir = getElement(level, i, j);
                monster[k].x = i;
                monster[k].y = j;
                ++k;
            }
        }
    }
    return monster;
}

//moves the monster to the left or to the right
void update_field_horizontally(struct typLevel level, size_t row, size_t col, int operator, int i) {
    bool cond = false;
    for (int j = 0; j < level.anzahl_monsters; ++j) {
        if (i != j && level.monsters[j].x == row && level.monsters[j].y == col) cond = true;
    }
    if (!cond) setElement(&level, row, col, ' ');
    if (operator == -1)
        setElement(&level, row, col + operator, '<');
    else
        setElement(&level, row, col + operator, '>');
}

//moves the monster up or down
void update_level_vertically(struct typLevel level, size_t row, size_t col, int operator, int i) {
    bool cond = false;
    for (int j = 0; j < level.anzahl_monsters; ++j) {
        if (i != j && level.monsters[j].x == row && level.monsters[j].y == col) cond = true;
    }
    if (!cond) setElement(&level, row, col, ' ');

    if (operator == -1)
        setElement(&level, row + operator, col, '^');
    else
        setElement(&level, row + operator, col, 'v');
}

//move the monster
void move_monster(struct typLevel *level) {
    for (int i = (int) level->anzahl_monsters - 1; i >= 0; --i) {
        switch (level->monsters[i].dir) {
            case '>': {
                if (!check_if_wall(*level, level->monsters[i].x, level->monsters[i].y + 1) &&
                    !check_if_exit(*level, level->monsters[i].x, level->monsters[i].y + 1)) {
                    update_field_horizontally(*level, level->monsters[i].x, level->monsters[i].y, 1, i);
                    level->monsters[i].y = level->monsters[i].y + 1;
                } else {
                    setElement(level, level->monsters[i].x, level->monsters[i].y, '<');
                    level->monsters[i].dir = '<';
                }
                break;
            }
            case '<': {
                if (!check_if_wall(*level, level->monsters[i].x, level->monsters[i].y - 1) &&
                    !check_if_exit(*level, level->monsters[i].x, level->monsters[i].y - 1)) {
                    update_field_horizontally(*level, level->monsters[i].x, level->monsters[i].y, -1, i);
                    level->monsters[i].y = level->monsters[i].y - 1;
                } else {
                    setElement(level, level->monsters[i].x, level->monsters[i].y, '>');
                    level->monsters[i].dir = '>';
                }
                break;
            }
            case '^': {
                if (!check_if_wall(*level, level->monsters[i].x - 1, level->monsters[i].y) &&
                    !check_if_exit(*level, level->monsters[i].x - 1, level->monsters[i].y)) {
                    update_level_vertically(*level, level->monsters[i].x, level->monsters[i].y, -1, i);
                    level->monsters[i].x = level->monsters[i].x - 1;
                } else {
                    setElement(level, level->monsters[i].x, level->monsters[i].y, 'v');
                    level->monsters[i].dir = 'v';
                }
                break;
            }
            case 'v': {
                if (!check_if_wall(*level, level->monsters[i].x + 1, level->monsters[i].y) &&
                    !check_if_exit(*level, level->monsters[i].x + 1, level->monsters[i].y)) {
                    update_level_vertically(*level, level->monsters[i].x, level->monsters[i].y, 1, i);
                    level->monsters[i].x = level->monsters[i].x + 1;
                } else {
                    setElement(level, level->monsters[i].x, level->monsters[i].y, '^');
                    level->monsters[i].dir = '^';
                }
                break;
            }
            default: {
                break;
            }
        }
    }
}