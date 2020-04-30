//Joseph Griffith


#include <stdio.h>
#include <inttypes.h>

uint64_t no_zeros_bytes(uint64_t no_bits) {
    uint64_t result = 512 - (no_bits % 512ULL);

    if (result < 65) {
        result += 512;
    }

    result -= 72;

    return (result / 8ULL);
}

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

    uint64_t noBits;
   
    uint8_t i;

    for (noBits = 0, i = 0; fread(&i, 1, 1, inFile) == 1; noBits += 8) {
        printf("%02" PRIx8 ,i );
    }

    printf("%02" PRIx8, 0x80); // Bits: 1000 000
    
    for (uint64_t i = (no_zeros_bytes(noBits)); i > 0; i--) {
        printf("%02" PRIx8, 0x00);
    }0

    printf("%016" PRIx64 "\n", noBits);


    fclose(inFile);
    return 0;
}
