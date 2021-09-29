#include "dungeon_setup.h"

//check if the file has been successfully opened
bool check_read(FILE *input) {
    return input != NULL;
}


//check if an input file starts with eingabe/
bool check_folder_name_input(char *str) {
    char *txt = "eingabe/";
    if (strlen(str) <= strlen(txt)) return false;
    if(!strncmp(str, txt, strlen(txt))) return true;
    return false;
}

//check if a level file starts with level/
bool check_folder_name_level(char *str) {
    char *txt = "level/";
    if (strlen(str) <= strlen(txt)) return false;
    if(!strncmp(str, txt, strlen(txt))) return true;
    return false;
}

//check all the error cases
void check_errors(int inFlag, int outFlag, FILE *input, FILE *output, FILE *level, char *inputName, char *levelName,
                  int argc) {

    //if multiple arguments
    if (inFlag > 1 || outFlag > 1 || argc - (2 * inFlag + 2 * outFlag) > 2) {
        clean(input, output, level);
        fehler_handlung(3);
    }

    //if input file can't be read
    if (!check_read(input) && inFlag == 1) {
        clean(input, output, level);
        fehler_handlung(1);
    }
    //if the file doesn't start with "eingabe/" -> unreadable
    if (inFlag == 1 && !check_folder_name_input(inputName)) {
        clean(input, output, level);
        fehler_handlung(2);
    }

    //if level file can't be read or it doesn't start with "level/" -> unreadable
    if (!check_read(level)) {
        clean(input, output, level);
        fehler_handlung(1);
    } else if (levelName != NULL && !check_folder_name_level(levelName)) {
        clean(input, output, level);
        fehler_handlung(2);
    }

    //in case you tried to access an unwritable output file
    if (!check_read(output)) {
        clean(input, output, level);
        fehler_handlung(1);
    }
}

//get input and/or output from cmd
bool init_cmd(int inFlag, int outFlag, FILE **input, FILE **output) {
    bool cond = false;
    if (outFlag == 0) {
        (*output) = stdout;
        cond = true;
    }
    if (inFlag == 0) {
        (*input) = stdin;
        cond = true;
    }
    return cond;
}

//print error and exit with state 'failure'
void fehler_handlung(int failure) {
    fprintf(stderr, "%s\n", "Fehler");
    exit(failure);
}


//generate the initial field in output
void init_output(struct typLevel lvl, FILE *output) {
    for (int i = 0; i < lvl.row; i++) {
        for (int j = 0; j < lvl.col; j++) {
            if (getElement(&lvl, i, j) != '\0')
                fputc(getElement(&lvl, i, j), output);
        }
        fputc('\n', output);
    }
}

//setter for the element
void setElement(struct typLevel *level, size_t row, size_t col, char value) {
    level->state[level->col * row + col] = value;
}

//getter for the element
char getElement(struct typLevel *level, size_t row, size_t col) {
    return level->state[level->col * row + col];
}

//get the rows of the level
size_t get_row(FILE *fp) {
    int ch;
    size_t lines = 0;
    while (!feof(fp)) {
        ch = fgetc(fp);
        if (ch == '\n') {
            lines++;
        }
    }
    rewind(fp);
    return lines;
}

//get the columns needed for the level
size_t get_col(FILE *fp) {
    int ch;
    size_t cols = 0;
    size_t max = 0;
    while (!feof(fp)) {
        ch = fgetc(fp);
        if (ch == '\n') {
            if (cols > max) max = cols;
            cols = 0;
        } else {
            cols++;
        }
    }
    rewind(fp);
    return max + 1;
}


//store the level in a typLevel variable and initializes the row and col variables
struct typLevel daten_einlesen(FILE *input) {
    struct typLevel lvl = {NULL, get_row(input), get_col(input)};
    lvl.state = calloc(lvl.row * lvl.col, 1);
    for (int i = 0; i < lvl.row; i++) {
        for (int j = 0; j < lvl.col; j++) {
            char c;
            fscanf(input, "%c", &c);
            if (c == '\n') break;
            setElement(&lvl, i, j, c);
        }
    }
    rewind(input);
    return lvl;
}

//initialize the player's coordinates
void init_player_coordinates(FILE *input, struct typLevel *level) {
    get_s_position(input, level);
}


//initialize the very first level
struct typLevel init_level(FILE *input) {
    struct typLevel level = daten_einlesen(input);
    init_player_coordinates(input, &level);
    level.playerState = 1;
    level.anzahl_monsters = anzahl_monsters(input);
    level.monsters = init_monster(&level);
    return level;
}

//free the level from the allocated memory
void free_level(struct typLevel *lvl) {
    free(lvl->state);
    free(lvl->monsters);
}


//clean everything and close all the files
void clean(FILE *input, FILE *output, FILE *level) {
    if (input)
        fclose(input);
    if (output)
        fclose(output);
    if (level)
        fclose(level);
}

//start the game
void play(FILE *input, FILE *level, FILE *output) {
    struct typLevel lvl = init_level(level);
    init_output(lvl, output);
    movePlayer(input, output, &lvl);
    free_level(&lvl);
    clean(input, output, level);
}

