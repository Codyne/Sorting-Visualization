#include <stdio.h>
#include <stdlib.h>

#define SWAP_OPT 0
#define SET_VAL_OPT 1

typedef struct swap_t {
	int opt;
	int i, j;
	struct swap_t *next;
} swap_t;

void init_swapt();
void insert_swap(int i, int j);
void set_swap_value(int i, int j);
void print_swaps();
swap_t* get_head();
