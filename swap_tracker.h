#include <stdio.h>
#include <stdlib.h>

typedef struct swap_t {
	int i, j;
	struct swap_t *next;
} swap_t;

swap_t *swapt = NULL;
swap_t *cur = NULL;

void init_swapt() {
	swapt = (swap_t *)malloc(sizeof(swap_t));
	swapt->next = NULL;
	cur = swapt;
}

void insert_swap(int i, int j) {
	if (cur == NULL) {
		fprintf(stderr, "cur is NULL. Exit failure...\n");
		exit(1);
	}
}
