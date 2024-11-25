#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <stdlib.h>

#define load_level "chapter1.csv"
#define file_bytes 1234567

char infile[file_bytes];
char input_chars[18];
int s[256][256][48];
int ints[256][256];
int unrolled[256][65536];
int counter_row=0;
int counter_column=0;

int difference=0;

int counter=0;

int inc=1;
int dec=2;
int add=3;
int neg=4;
int mul=5;

int increment=1;
int decrement=2;
int negate=4;
int multiply=5;

#include "mersenne_t.h"
#include "util.h"

int main(int argc, char **argv) {
	init_();
	return 0;
}
