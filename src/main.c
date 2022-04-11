#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

#include "sorts.h"
#include "swap_tracker.h"
#include "keyboard_handler.h"
#include "menu_text.h"

char ALGO_TEXT[512];
int *ARR = NULL;
int *GL_ARR = NULL;
int ARR_SIZE = 0;
int FPS = 0;

int selectedSort = 0;
int selectedSize = 0;
int selectedSpeed = 0;

menu_t SORT_MENU_TEXT;
menu_t SIZE_MENU_TEXT;
menu_t SPEED_MENU_TEXT;

swap_t *cur_swap;

void init_arrays() {
	time_t t;

	ARR = (int *)calloc(ARR_SIZE, sizeof(int));
	if (!ARR) exit(1);

	GL_ARR = (int *)calloc(ARR_SIZE, sizeof(int));
	if (!GL_ARR) exit(1);

	srand((unsigned)time(&t));
	for (int i = 0; i < ARR_SIZE; i++) {
		int index = rand() % ARR_SIZE;

		if (ARR[index]) {
			i--;
			continue;
		}

		ARR[index] = i + 1;
		GL_ARR[index] = i + 1;
	}
}

void draw_rect(float x, int i) {
	glBegin(GL_POLYGON);

	glVertex3f(0.0 + i, 0.0, 0.0);
	glVertex3f(0.0 + i, x, 0.0);

	glVertex3f(0.9 + i, x, 0.0);
	glVertex3f(0.9 + i, 0.0, 0.0);

	glEnd();
}

void draw_text(float x, float y, float z, char *text, int highlight) {
	size_t len = strlen(text);
	glPushMatrix();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(3.0);

	glColor3f(0.0 + highlight, 1.0, 0.0);
	glScalef(0.0001 * ARR_SIZE, 0.0001 * ARR_SIZE, 0.0001 * ARR_SIZE);
	glTranslatef(x, y, z);

	for (size_t i = 0; i < len; i++)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, text[i]);

	glPopMatrix();
}

void draw_menu(menu_t *m) {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);

	float ypos = 7500.0f;

	int i = 0;
	for (menu_t *p = m->next; p != NULL; p = p->next) {
		if (i == get_k_index()) {
			p->highlight = 1;
		} else {
			if (!p->next && i < get_k_index()) {
				set_k_index(i);
				p->highlight = 1;
			} else {
				p->highlight = 0;
			}
		}


		draw_text(100.0, ypos, 0.0, p->text, p->highlight);
		ypos -= 500.0f;

		i++;
	}

	glFlush();

	glutSwapBuffers();

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);

	for (int i = 0; i < ARR_SIZE; i++) {
		draw_rect(GL_ARR[i], i);
	}

	draw_text(0.0, 9500.0, 0.0, ALGO_TEXT, 0);
	glFlush();

	if (cur_swap->next) {
		if (cur_swap->opt == SWAP_OPT)
			SWAP(GL_ARR[cur_swap->i], GL_ARR[cur_swap->j]);
		else if (cur_swap->opt == SET_VAL_OPT)
			GL_ARR[cur_swap->i] = cur_swap->j;
		cur_swap = cur_swap->next;
	}

	glutSwapBuffers();
}

int populate_sort_steps(int selectedSort) {
	switch (selectedSort) {
	case 0:
		bubbleSort(ARR, ARR_SIZE);
		strncpy(ALGO_TEXT, "Bubble Sort | ", 20);
		break;
	case 1:
		quickSort(ARR, 0, ARR_SIZE - 1);
		strncpy(ALGO_TEXT, "Quick Sort | ", 20);
		break;
	case 2:
		mergeSort(ARR, 0, ARR_SIZE - 1);
		strncpy(ALGO_TEXT, "Merge Sort | ", 20);
		break;
	case 3:
		heapSort(ARR, ARR_SIZE);
		strncpy(ALGO_TEXT, "Heap Sort | ", 20);
		break;
	default: break;
	}

	sprintf(ALGO_TEXT + strlen(ALGO_TEXT),
			 "Array Size: %d | Speed: %d", ARR_SIZE, FPS);
}

void predisp() {
	selectedSpeed = get_prev_index();

	ARR_SIZE = get_menu_val(&SIZE_MENU_TEXT, selectedSize);
	FPS = get_menu_val(&SPEED_MENU_TEXT, selectedSpeed);

	init_arrays();
	populate_sort_steps(selectedSort);

	cur_swap = get_head();

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, ARR_SIZE, 0.0, ARR_SIZE, -1.0, 1.0);
	glutDisplayFunc(display);
}

void speed_menu() {
	selectedSize = get_prev_index();
	draw_menu(&SPEED_MENU_TEXT);
	set_display_cb(predisp);
}

void size_menu() {
	selectedSort = get_prev_index() - 1;
	draw_menu(&SIZE_MENU_TEXT);
	set_display_cb(speed_menu);
}

void sort_menu() {
	draw_menu(&SORT_MENU_TEXT);
}

void timer() {
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer, 0);
}

int main(int argc, char **argv) {
	ARR_SIZE = 50;
	FPS = 60;
	add_menu_text(&SORT_MENU_TEXT, "SELECT SORTING ALGORITHM", 30, 0, 0);
	add_menu_text(&SORT_MENU_TEXT, "BUBBLE SORT", 30, 0, 0);
	add_menu_text(&SORT_MENU_TEXT, "QUICK  SORT", 30, 1, 0);
	add_menu_text(&SORT_MENU_TEXT, "MERGE  SORT", 30, 2, 0);
	add_menu_text(&SORT_MENU_TEXT, "HEAP   SORT", 30, 3, 0);

	add_menu_text(&SIZE_MENU_TEXT, "SELECT ARRAY SIZE", 30, 0, 0);
	add_menu_text(&SIZE_MENU_TEXT, "10", 10, 10, 0);
	add_menu_text(&SIZE_MENU_TEXT, "50", 10, 50, 0);
	add_menu_text(&SIZE_MENU_TEXT, "100", 10, 100, 0);
	add_menu_text(&SIZE_MENU_TEXT, "250", 10, 250, 0);
	add_menu_text(&SIZE_MENU_TEXT, "500", 10, 500, 0);
	add_menu_text(&SIZE_MENU_TEXT, "1000", 10, 1000, 0);
	add_menu_text(&SIZE_MENU_TEXT, "5000", 10, 5000, 0);

	add_menu_text(&SPEED_MENU_TEXT, "SELECT SPEED (FPS)", 30, 0, 0);
	add_menu_text(&SPEED_MENU_TEXT, "5", 10, 5, 0);
	add_menu_text(&SPEED_MENU_TEXT, "20", 10, 20, 0);
	add_menu_text(&SPEED_MENU_TEXT, "30", 10, 30, 0);
	add_menu_text(&SPEED_MENU_TEXT, "60", 10, 60, 0);
	add_menu_text(&SPEED_MENU_TEXT, "100", 10, 100, 0);
	add_menu_text(&SPEED_MENU_TEXT, "200", 10, 200, 0);
	add_menu_text(&SPEED_MENU_TEXT, "500", 10, 500, 0);
	add_menu_text(&SPEED_MENU_TEXT, "1000", 10, 1000, 0);
	add_menu_text(&SPEED_MENU_TEXT, "5000", 10, 5000, 0);

	glutInit(&argc, argv);
	glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(100,100);
	glutInitWindowSize(300,300);
	glutCreateWindow(argv[0]);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, ARR_SIZE, 0.0, ARR_SIZE, -1.0, 1.0);

	glutDisplayFunc(sort_menu);
	set_display_cb(size_menu);

	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keyboard);
	glutMainLoop();

	return 0;
}
