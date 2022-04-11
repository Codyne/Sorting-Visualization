#ifndef MENU_TEXT_H
#define MENU_TEXT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct menu_t {
	char *text;
	int val;
	int highlight;
	struct menu_t *next;
} menu_t;

void add_menu_text(menu_t *head, char *str, size_t len, int val, int hl);
int get_menu_val(menu_t *m, int index);

#endif
