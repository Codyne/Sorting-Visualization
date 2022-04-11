#include "menu_text.h"

void add_menu_text(menu_t *head, char *str, size_t len, int val, int hl) {
	while (head->next != NULL) head = head->next;
	head->next = (menu_t *)malloc(sizeof(menu_t));
	if (!head->next) exit(1);

	head = head->next;

	head->text = (char *)malloc(sizeof(char) * (len + 1));
	if (!head->text) exit(1);

	strncpy(head->text, str, len);
	head->highlight = hl;
	head->val = val;

	head->next = NULL;
}

int get_menu_val(menu_t *m, int index) {
	int i = 0;

	while (m != NULL && i != index + 1) {
		i++;
		m = m->next;
	}

	if (m) return m->val;

	return 0;
}
