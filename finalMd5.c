// Joseph Griffith - G00350112
// ToA - Md5
//

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>


// ( precomputed table):
//MD5
//constans

const uint32_t K[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	                0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
  		        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
      		        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
		        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};


/* F, G, H and I are basic MD5 functions.
 */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits.
 */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
Rotation is separate from addition to prevent recomputation.
 */


#define FF(a, b, c, d, m, s, t) { a += F(b, c, d) + m + t;  a = b + ROTATE_LEFT(a, s); }
#define GG(a, b, c, d, m, s, t) { a += G(b, c, d) + m + t;  a = b + ROTATE_LEFT(a, s); }
#define HH(a, b, c, d, m, s, t) { a += H(b, c, d) + m + t;  a = b + ROTATE_LEFT(a, s); }
#define II(a, b, c, d, m, s, t) { a += I(b, c, d) + m + t;  a = b + ROTATE_LEFT(a, s); }


//MD5 Hash Constansts
//round 1
#define S11 7 
#define S12 12
#define S13 17
#define S14 22

//round 2
#define S21 5
#define S22 9 
#define S23 14
#define S24 20

//round 3
#define S31 4
#define S32 11
#define S33 16 
#define S34 23

//round 4
#define S41 6
#define S42 10
#define S43 15
#define S44 21

#define FNSZ 128

// A sixty-four byte block of memory, accessed with different types.
 union block {
  uint64_t sixfour[8];
  uint32_t threetwo[16];
  uint8_t eight[64];
  uint8_t eight_padding[64];
};

//functions for md5
typedef struct {
  uint32_t state[4];
} MD5_CONTEX;

// md5 initialization / begins the md5 op writing up a new context
void Md5_initialize(MD5_CONTEX *Md5_contex);
FILE *Md5_hash(MD5_CONTEX *Md5_contex, union block *BL, char *file);


// start MD5 - set state values
void Md5_initialize(MD5_CONTEX *Md5_contex) {
  Md5_contex -> state[0] = 0x67452301;
  Md5_contex -> state[1] = 0xefcdab89;
  Md5_contex -> state[2] = 0x98badcfe;
  Md5_contex -> state[3] = 0x10325476;
}


//padding
const uint8_t PADZERO = 0x00;
const uint8_t PADONE = 0x80;

// Message Digit - File Pointer
FILE *Md5_hashed(MD5_CONTEX *Md5_contex, union block *BL, char *file) {
    FILE *filepointer;
    uint32_t a, b, c, d; // Stores the prev hash values
    uint64_t counter = 0; // counts the PADS
    size_t size;
    bool keepAlive = true;
    int i = 0;
    int padding = 0;

    // temporary variable values
    a = Md5_contex -> state[0];
    b = Md5_contex -> state[1];
    c = Md5_contex -> state[2];
    d = Md5_contex -> state[3];

    // the file pointer opens the file
    filepointer = fopen(file, "r");

    printf("\nFILE: %s\n", file);
    printf("OUTPUT HASHED STRING: ");

    // checks if files exist
    if (filepointer == NULL) {
        fprintf(stderr, "ERROR: Sorry but FILE %s does not seem to exist", file);
    }


    // Padding cont.
    while (keepAlive) {
    size = fread(&BL -> eight, 1, 64, filepointer);

        // if size is = 64 no padding is needed
        if (size == 64) {
            counter += 512;
        // No space at the end of file if the size > 56 and <64
      } else if (size > 56 && size < 64) {
            counter += (size * 8);
            padding = 1;

        BL -> eight_padding[size] = PADONE;
        for (i = size + 1; i < 64; i++) {
            BL -> eight_padding[i] = PADZERO;
        }
      } else if(size > 0 && size < 56) {
            counter += (size * 8);

        BL -> eight_padding[size] = PADONE;

        for (i = size + 1; i < 56; i++) {
            BL -> eight_padding[i] = PADZERO;
        }

        BL -> sixfour[7] = counter;

        keepAlive = false;
      } else if (size == 0 && padding == 0) {
        BL -> eight_padding[0] = PADONE;

        for(i = 1; i < 56; i++) {
            BL -> eight_padding[i] = PADZERO;
        }

        BL -> sixfour[7] = counter;

        keepAlive = false;
      } else if (size == 0 && padding == 1) {
            BL -> eight_padding[0]=PADZERO;

      for(i = 1; i < 56; i++) {
            BL -> eight_padding[i] = PADZERO;
      }

        BL -> sixfour[7] = counter;

        keepAlive = false;
      }
      

      // start of imp of rounds
    // Round 1 - FF
    FF(a, b, c, d, BL -> threetwo[0], S11, K[0]);
    FF(d, a, b, c, BL -> threetwo[1], S12, K[1]);
    FF(c, d, a, b, BL -> threetwo[2], S13, K[2]);
    FF(b, c, d, a, BL -> threetwo[3], S14, K[3]);
    FF(a, b, c, d, BL -> threetwo[4], S11, K[4]);
    FF(d, a, b, c, BL -> threetwo[5], S12, K[5]);
    FF(c, d, a, b, BL -> threetwo[6], S13, K[6]);
    FF(b, c, d, a, BL -> threetwo[7], S14, K[7]);
    FF(a, b, c, d, BL -> threetwo[8], S11, K[8]);
    FF(d, a, b, c, BL -> threetwo[9], S12, K[9]);
    FF(c, d, a, b, BL -> threetwo[10], S13, K[10]);
    FF(b, c, d, a, BL -> threetwo[11], S14, K[11]);
    FF(a, b, c, d, BL-> threetwo[12], S11, K[12]);
    FF(d, a, b, c, BL -> threetwo[13], S12, K[13]);
    FF(c, d, a, b, BL -> threetwo[14], S13, K[14]);
    FF(b, c, d, a, BL-> threetwo[15], S14, K[15]);

    // Round 2 - GG
    GG(a, b, c, d, BL -> threetwo[1], S21, K[16]);
    GG(d, a, b, c, BL -> threetwo[6], S22, K[17]);
    GG(c, d, a, b, BL -> threetwo[11], S23, K[18]);
    GG(b, c, d, a, BL -> threetwo[0], S24, K[19]);
    GG(a, b, c, d, BL -> threetwo[5], S21, K[20]);
    GG(d, a, b, c, BL -> threetwo[10], S22, K[21]);
    GG(c, d, a, b, BL -> threetwo[15], S23, K[22]);
    GG(b, c, d, a, BL -> threetwo[4], S24, K[23]);
    GG(a, b, c, d, BL -> threetwo[9], S21, K[24]);
    GG(d, a, b, c, BL -> threetwo[14], S22, K[25]);
    GG(c, d, a, b, BL -> threetwo[3], S23, K[26]);
    GG(b, c, d, a, BL -> threetwo[8], S24, K[27]);
    GG(a, b, c, d, BL -> threetwo[13], S21, K[28]);
    GG(d, a, b, c, BL -> threetwo[2], S22, K[29]);
    GG(c, d, a, b, BL -> threetwo[7], S23, K[30]);
    GG(b, c, d, a, BL -> threetwo[12], S24, K[31]);

    // Round 3 - HH
    HH(a, b, c, d, BL -> threetwo[5], S31, K[32]);
    HH(d, a, b, c, BL-> threetwo[8], S32, K[33]);
    HH(c, d, a, b, BL -> threetwo[11], S33, K[34]);
    HH(b, c, d, a, BL -> threetwo[14], S34, K[35]);
    HH(a, b, c, d, BL -> threetwo[1], S31, K[36]);
    HH(d, a, b, c, BL -> threetwo[4], S32, K[37]);
    HH(c, d, a, b, BL -> threetwo[7], S33, K[38]);
    HH(b, c, d, a, BL -> threetwo[10], S34, K[39]);
    HH(a, b, c, d, BL -> threetwo[13], S31, K[40]);
    HH(d, a, b, c, BL -> threetwo[0], S32, K[41]);
    HH(c, d, a, b, BL -> threetwo[3], S33, K[42]);
    HH(b, c, d, a, BL -> threetwo[6], S34, K[43]);
    HH(a, b, c, d, BL -> threetwo[9], S31, K[44]);
    HH(d, a, b, c, BL -> threetwo[12], S32, K[45]);
    HH(c, d, a, b, BL -> threetwo[15], S33, K[46]);
    HH(b, c, d, a, BL -> threetwo[2], S34, K[47]);

    // Round 4 - II
    II(a, b, c, d, BL -> threetwo[0], S41, K[48]);
    II(d, a, b, c, BL -> threetwo[7], S42, K[49]);
    II(c, d, a, b, BL -> threetwo[14], S43, K[50]);
    II(b, c, d, a, BL -> threetwo[5], S44, K[51]);
    II(a, b, c, d, BL -> threetwo[12], S41, K[52]);
    II(d, a, b, c, BL -> threetwo[3], S42, K[53]);
    II(c, d, a, b, BL -> threetwo[10], S43, K[54]);
    II(b, c, d, a, BL -> threetwo[1], S44, K[55]);
    II(a, b, c, d, BL -> threetwo[8], S41, K[56]);
    II(d, a, b, c, BL -> threetwo[15], S42, K[57]);
    II(c, d, a, b, BL -> threetwo[6], S43, K[58]);
    II(b, c, d, a, BL -> threetwo[13], S44, K[59]);
    II(a, b, c, d, BL -> threetwo[4], S41, K[60]);
    II(d, a, b, c, BL -> threetwo[11], S42, K[61]);
    II(c, d, a, b, BL -> threetwo[2], S43, K[62]);
    II(b, c, d, a, BL -> threetwo[9], S44, K[63]);
}
}




int main(int argc, char *argv[]) {


  MD5_CONTEX Md5_contex_VAL;
  FILE *file = NULL;
  union block BL;
  FILE *pointer;
  bool keepAlive = true;
  int i ;
  int gui;
  char filename[FNSZ] = {0};
  char userfiler[50] = "user-entry.txt"; //file that stores users input
  char string[100];// user input

  // Command Line Arguments
  // GUI - Title
  printf("\n- JOSEPH GRIFFITH - G00350112 -\n");
  printf("\n- MD5 ALGORITHM - HASH GENERATOR -\n");
  printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#\n\n");

  // GUI - Options
  printf("PRESS (1) TO BEGIN HASHING A FILE e.g:(file_name_here.txt)\n");
  printf("PRESS (2) TO BEGIN HASHING A STRING \n");
  printf("PRESS (4) TO EXIT HASHING\n");
  printf("Please choose one of the above options: ");
  scanf("%d", &gui);













  fclose(file);
  return 0; 
}
