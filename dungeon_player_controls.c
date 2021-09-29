#include "dungeon_player_controls.h"

//write the step and the command in the output file
void update_step(FILE *output, int i, char c) {
    if (output == stdin)
        output = stdout;
    char *temp = malloc(256);
    memset(temp, '\0', 256);
    sprintf(temp, "%d %c\n", i, c);
    fputs(temp, output);
    free(temp);
}

//write the updated level in the output file
void update_output(struct typLevel level, FILE *output) {
    if (output == stdin)
        output = stdout;
    for (int k = 0; k < level.row; k++) {
        for (int j = 0; j < level.col; j++) {
            if (getElement(&level, k, j) != '\0') {
                fputc(getElement(&level, k, j), output);
            }
        }
        fputc('\n', output);
    }
}

//check if the char at position [row][col] is a wall (#)
bool check_if_wall(struct typLevel lvl, size_t row, size_t col) {
    return (getElement(&lvl, row, col) == '#');
}

//check if the char at position [row][col] is an exit (A)
bool check_if_exit(struct typLevel lvl, size_t row, size_t col) {
    return (getElement(&lvl, row, col) == 'A');
}

//check if the char at position [row][col] is a monster
bool check_if_monster(struct typLevel level, size_t row, size_t col) {
    char c = getElement(&level, row, col);
    return c == '^' || c == 'v' || c == '>' || c == '<';
}


//get the position (row and col) of S in the current level
void get_s_position(FILE *input, struct typLevel *level) {
    int row = -1;
    int col = -1;
    while (!feof(input)) {
        int c = fgetc(input);
        col++;
        if (c == '\n') {
            row++;
            col = -1;
        } else if (c == 'S') {
            row++;
            break;
        }
    }
    level->playerX = row;
    level->playerY = col;
    rewind(input);
}

/* move player horizontally depending on operator
 * if operator = -1 -> move left
 * if operator =  1 -> move right
 */
void move_horizontally(struct typLevel *level, int operator) {
    for (int i = 0; i < level->anzahl_monsters; ++i) {
        if (level->monsters[i].x == level->playerX && level->monsters[i].y == level->playerY &&
            !check_if_wall(*level, level->playerX, level->playerY + operator)) {
            setElement(level, level->playerX, level->playerY + operator, 'S');
            level->playerY = level->playerY + operator;
            return;
        }
    }
    //if the next character isn't a wall or an exit, move S forward to the right
    if (!check_if_wall(*level, level->playerX, level->playerY + operator) &&
        !check_if_exit(*level, level->playerX, level->playerY + operator)) {
        setElement(level, level->playerX, level->playerY, ' ');
        setElement(level, level->playerX, level->playerY + operator, 'S');
        level->playerY = level->playerY + operator;
    }
        //if the next character is an exit, remove S
    else if (check_if_exit(*level, level->playerX, level->playerY + operator)) {
        setElement(level, level->playerX, level->playerY, ' ');
        level->playerY = level->playerY + operator;
        level->playerState = -1;
    }
}

/* move player vertically depending on operator
 * if operator = -1 -> move upwards
 * if operator =  1 -> move downwards
 */
void move_vertically(struct typLevel *level, int operator) {
    //if the player and the monster are at the same position and the monster didn't eat the player
    for (int i = 0; i < level->anzahl_monsters; ++i) {
        if (level->monsters[i].x == level->playerX && level->monsters[i].y == level->playerY &&
            !check_if_wall(*level, level->playerX + operator, level->playerY)) {
            setElement(level, level->playerX + operator, level->playerY, 'S');
            level->playerX = level->playerX + operator;
            return;
        }
    }
    //if the next character isn't a wall or an exit, move S forward to the right or left depends on operator
    if (!check_if_wall(*level, level->playerX + operator, level->playerY) &&
        !check_if_exit(*level, level->playerX + operator, level->playerY)) {
        setElement(level, level->playerX, level->playerY, ' ');
        setElement(level, level->playerX + operator, level->playerY, 'S');
        level->playerX = level->playerX + operator;
    }
        //if the next character is an exit, remove S
    else if (check_if_exit(*level, level->playerX + operator, level->playerY)) {
        setElement(level, level->playerX, level->playerY, ' ');
        level->playerX = level->playerX + operator;
        level->playerState = -1;
    }
}

//checks if you won or lost
bool check_status(struct typLevel *level, FILE *output) {
    if (output == stdin)
        output = stdout;
    //if exit -> end the game and add winner message to the output file
    if (getElement(level, level->playerX, level->playerY) == 'A') {
        update_output(*level, output);
        level->playerState = -1;
        fputs("Gewonnen!\n", output);
        return 1;
        //if monster -> end the game and add loser message to the output file
    } else {
        for (int i = 0; i < level->anzahl_monsters; ++i) {
            if (level->monsters[i].x == level->playerX && level->monsters[i].y == level->playerY) {
                setElement(level, level->playerX, level->playerY, level->monsters[i].dir);
                update_output(*level, output);
                level->playerState = -1;
                fputs("Du wurdest von einem Monster gefressen.\n", output);
                return 1;
            }
        }
    }
    return 0;
}


//controls the player movement
void movePlayer(FILE *input, FILE *output, struct typLevel *level) {
    int i = 0;
    int c;
    while (level->playerState != -1) {
        c = fgetc(input);
        if(c == EOF) break;
        switch (c) {
            case 'd': {
                i++;
                move_monster(level);
                move_horizontally(level, 1);
                break;
            }
            case 'a': {
                i++;
                move_monster(level);
                move_horizontally(level, -1);
                break;
            }
            case 's': {
                i++;
                move_monster(level);
                move_vertically(level, 1);
                break;
            }
            case 'w': {
                i++;
                move_monster(level);
                move_vertically(level, -1);
                break;
            }
            default:{
                break;
            }
        }
        if (c != '\n') {
            update_step(output, i, c);
            bool status = check_status(level, output);
            if (status == 0) {
                update_output(*level, output);
            }
        }
    }
}