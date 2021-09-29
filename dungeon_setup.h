#include "libs.h"

bool check_read(FILE *input);

void fehler_handlung(int failure);

void init_output(struct typLevel lvl, FILE *output);

struct typLevel daten_einlesen(FILE *input);

size_t get_col(FILE *input);

size_t get_row(FILE *input);

void clean(FILE *input, FILE *output, FILE *level);

void init_player_coordinates(FILE *input, struct typLevel *level);

struct typLevel init_level(FILE *input);

bool init_cmd(int inFlag, int outFlag, FILE **input, FILE **output);

void check_errors(int inFlag, int outFlag, FILE *input, FILE *output, FILE *level, char *inputName, char *levelName,
                  int argc);

bool check_folder_name_input(char *str);

bool check_folder_name_level(char *str);