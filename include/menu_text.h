#include <strings.h>

#define MENU_ROWS 10
#define MENU_COLS 50

typedef struct {
	char text[MENU_ROWS][MENU_COLS];
	int highlight[MENU_ROWS];
} menu_t;

menu_t MENU_TEXT;

#define INIT_MENU_TEXT()										\
	strncpy(MENU_TEXT.text[0], "SELECT SORTING ALGORITHM", 30);	\
	MENU_TEXT.highlight[0] = 0;									\
	strncpy(MENU_TEXT.text[1], "BUBBLE SORT", 30);				\
	MENU_TEXT.highlight[1] = 1;									\
	strncpy(MENU_TEXT.text[2], "QUICK  SORT", 30);				\
	MENU_TEXT.highlight[2] = 0;									\
	strncpy(MENU_TEXT.text[3], "MERGE  SORT", 30);				\
	MENU_TEXT.highlight[3] = 0;									\
	strncpy(MENU_TEXT.text[4], "HEAP   SORT", 30);				\
	MENU_TEXT.highlight[4] = 0;
