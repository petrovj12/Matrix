#ifndef C_MATRIX_H
#define C_MATRIX_H

#define MAX_CHRS 120
#define MAX_CHRS_DIS 40
#define MAX_STR 86
#define MIN_STR 4

typedef struct{
	int x;
	int y;
	int passed;
	char string[MAX_STR];
} v_string;

void init_taken();
void free_taken();

void init_v_strings(WINDOW *);
void random_num_str(char *, int);

v_string *generate_rand_v_string();
void print_v_strings();
void fall_v_strings();

#endif
