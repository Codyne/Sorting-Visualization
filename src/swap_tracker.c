#include "swap_tracker.h"

swap_t *head = NULL;
swap_t *swapt = NULL;

void init_swapt() {
	swapt = (swap_t *)malloc(sizeof(swap_t));
	if (!swapt) exit(1);

	swapt->opt = 0;
	swapt->next = NULL;
	head = swapt;
}

void insert_swap(int i, int j) {
	if (swapt == NULL) {
		init_swapt();
	}

	swapt->opt = SWAP_OPT;
	swapt->i = i;
	swapt->j = j;
	swapt->next = (swap_t *)malloc(sizeof(swap_t));
	if (!swapt->next) exit(1);

	swapt = swapt->next;
}

void set_swap_value(int i, int j) {
	if (swapt == NULL) {
		init_swapt();
	}

	swapt->opt = SET_VAL_OPT;
	swapt->i = i;
	swapt->j = j;
	swapt->next = (swap_t *)malloc(sizeof(swap_t));
	if (!swapt->next) exit(1);

	swapt = swapt->next;
}

void set_swap_highlight(int i) {
	if (swapt == NULL) {
		init_swapt();
	}

	swapt->opt = SET_HL_OPT;
	swapt->i = i;
	swapt->next = (swap_t *)malloc(sizeof(swap_t));
	if (!swapt->next) exit(1);

	swapt = swapt->next;
}

void print_swaps() {
	for (swap_t *p = head; p; p = p->next)
		printf("[%d] - [%d, %d]\n", p->opt, p->i, p->j);
}

swap_t* get_head() {
	return head;
}
