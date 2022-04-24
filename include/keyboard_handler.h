#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

#include <GL/glut.h>

#include "menu_text.h"
#include "generate_tone.h"

void keyboard(unsigned char key, int x, int y);
void special_keyboard(int key, int x, int y);
int get_k_index();
int get_prev_index();
void set_k_index(int x);
void set_display_cb(void *fn);

#endif
