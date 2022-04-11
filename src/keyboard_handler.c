#include "keyboard_handler.h"

int kIndex = 1;
int prevIndex = 0;
void *displayCallback = NULL;

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 13:
		prevIndex = kIndex;
		kIndex = 1;
		if (displayCallback) glutDisplayFunc(displayCallback);
		break;
	case 27:
		exit(0);
		break;
	}
}


void special_keyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		if (kIndex > 1) kIndex--;
		break;
	case GLUT_KEY_DOWN:
		kIndex++;
		break;
	case 27:
		exit(0);
		break;
	}
}

int get_k_index() {
	return kIndex;
}

int get_prev_index() {
	return prevIndex;
}

void set_k_index(int x) {
	kIndex = x;
}

void set_display_cb(void *fn) {
	displayCallback = fn;
}
