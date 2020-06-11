ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

LIB_NAME = libft_malloc_$(HOSTTYPE).so
SYMLINK_NAME = libft_malloc.so

DIR_SRC = ./src/
DIR_OBJ = ./obj/

C_FILES =	malloc.c \
			free.c \
			realloc.c \
			chunk1.c \
			chunk2.c \
			chunk3.c \
			chunk4.c \
			chunk5.c \
			mutex.c \
			show_alloc_mem1.c \
			show_alloc_mem2.c

SRC = $(addprefix $(DIR_SRC), $(C_FILES))
OBJ = $(addprefix $(DIR_OBJ), $(C_FILES:.c=.o))
DEPS = $(addprefix $(DIR_OBJ), $(C_FILES:.c=.d))

FLAGS = -Wall -Werror -Wextra -I inc/
C_FLAGS = -fPIC $(FLAGS)
O_FLAGS = -shared $(FLAGS)


all: $(DIR_OBJ) $(LIB_NAME) $(SYMLINK_NAME)

debug: C_FLAGS += -ggdb
debug: all

-include $(DEPS)

$(SYMLINK_NAME):
	ln -sf $(LIB_NAME) $(SYMLINK_NAME)

$(DIR_OBJ):
	mkdir -p $(DIR_OBJ)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c Makefile
	$(CC) $(C_FLAGS) -MMD -MP -c $< -o $@

$(LIB_NAME): $(OBJ)
	$(CC) $(O_FLAGS) $(OBJ) -o $(LIB_NAME)

clean:
	rm -rf $(DIR_OBJ)

fclean: clean
	rm -f $(LIB_NAME)
	rm -f $(SYMLINK_NAME)

re: fclean all

.PHONY: all clean fclean