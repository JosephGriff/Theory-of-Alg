//Joseph Griffith


#include <stdio.h>
#include <inttypes.h>

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Error: expected single filename as argument\n");
        return 1;
    }

    FILE *inFile = fopen(argv[1], "rb");

    if (!inFile) {
        printf("Error: couldn't open file %s. \n", argv[1]);
        return 1;
    }

    fclose(inFile);
    return 0;
}
