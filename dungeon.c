#include "dungeon.h"

int main(int argc, char **argv) {
    int option;
    int inFlag = 0;
    int outFlag = 0;
    char *inOptarg;
    FILE *input = NULL;
    FILE *output = NULL;
    FILE *level = NULL;
    while ((option = getopt(argc, argv, "i:o:")) != EOF) {
        switch (option) {
            case 'i': {
                if (inFlag == 0) {
                    inFlag++;
                    input = fopen(optarg, "r");
                    inOptarg = optarg;
                } else {
                    inFlag++;
                }
                break;
            }
            case 'o': {
                if (outFlag == 0) {
                    outFlag++;
                    output = fopen(optarg, "w");
                } else {
                    outFlag++;
                }
                break;
            }
            default: {
                clean(input, output, level);
                fehler_handlung(3);
            }
        }
    }
    char *levelString = argv[optind];
    if (levelString == NULL) {
        level = fopen("level/1.txt", "r");
    } else {
        level = fopen(levelString, "r");
    }
    init_cmd(inFlag, outFlag, &input, &output);
    check_errors(inFlag, outFlag, input, output, level, inOptarg, levelString, argc);
    play(input, level, output);
}






