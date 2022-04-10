SRC_DIR := src
OBJ_DIR := obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

CC := gcc
CFLAGS := -I include
LDFLAGS := -lglut -lGL

sortvis: $(OBJ_FILES)
	$(CC) $^ $(LDFLAGS) -o $@

debug: export DEBUG=-DDEBUG=1
debug: $(OBJ_FILES)
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $@

clean: FORCE
	@rm -f $(OBJ_DIR)/* sortvis debug
FORCE:
