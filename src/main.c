#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

#include "sorts.h"
#include "swap_tracker.h"

char ALGO_TEXT[50];
int *ARR = NULL;
int *GL_ARR = NULL;
int ARR_SIZE = 0;
int FPS = 0;
swap_t *cur_swap;

void init_arrays() {
	time_t t;

	ARR = (int *)malloc(sizeof(int) * ARR_SIZE);
	GL_ARR = (int *)malloc(sizeof(int) * ARR_SIZE);

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

void draw_algo_text() {
	size_t len = strlen(ALGO_TEXT);
	glPushMatrix();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(3.0);

	glColor3f(0.0, 1.0, 0.0);
	glScalef(0.0001 * ARR_SIZE, 0.0001 * ARR_SIZE, 0.0001 * ARR_SIZE);
	glTranslatef(0.0, 9500.0, 0.0);

	for (size_t i = 0; i < len; i++) {
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, ALGO_TEXT[i]);
	}
	glPopMatrix();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);

	for (int i = 0; i < ARR_SIZE; i++) {
		draw_rect(GL_ARR[i], i);
	}

	draw_algo_text();
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

void timer() {
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer, 0);
}

int select_sort() {
	char input[5];
	printf("1 - Bubble Sort\n");
	printf("2 - Quick Sort\n");
	printf("3 - Merge Sort\n");
	printf("4 - Heap Sort\n");
	printf("Select Sorting Algorithm (1 - 4): ");
	fflush(stdout);

	fgets(input, 3, stdin);
	fflush(stdin);

	return atoi(input) - 1;
}

int select_array_size() {
	char input[15];
	printf("Select Array Size (3 or more): ");

	fflush(stdout);
	fgets(input, 10, stdin);
	fflush(stdin);

	return atoi(input);
}

int select_fps() {
	char input[15];
	printf("Select Swaps Per Second (1 or more): ");

	fflush(stdout);
	fgets(input, 10, stdin);
	fflush(stdin);

	return atoi(input);
}

int populate_sort_steps(int selectedSort) {
	switch (selectedSort) {
	case 0:
		bubbleSort(ARR, ARR_SIZE);
		strncpy(ALGO_TEXT, "Bubble Sort", 20);
		break;
	case 1:
		quickSort(ARR, 0, ARR_SIZE - 1);
		strncpy(ALGO_TEXT, "Quick Sort", 20);
		break;
	case 2:
		mergeSort(ARR, 0, ARR_SIZE - 1);
		strncpy(ALGO_TEXT, "Merge Sort", 20);
		break;
	case 3:
		heapSort(ARR, ARR_SIZE);
		strncpy(ALGO_TEXT, "Heap Sort", 20);
		break;
	default: break;
	}
}

int main(int argc, char **argv) {
	int selectedSort = -1;
	while (selectedSort < 0 || selectedSort > 3) selectedSort = select_sort();
	while (ARR_SIZE < 3) ARR_SIZE = select_array_size();
	while (FPS < 1) FPS = select_fps();

	init_arrays();
	populate_sort_steps(selectedSort);

	//print_swaps();
	cur_swap = get_head();

	glutInit(&argc, argv);
	glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(100,100);
	glutInitWindowSize(300,300);
	glutCreateWindow(argv[0]);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, ARR_SIZE, 0.0, ARR_SIZE, -1.0, 1.0);

	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();

	return 0;
}
