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
			chunk.c \
			mutex.c \
			show_alloc_mem.c

SRC = $(addprefix $(DIR_SRC),$(C_FILES:.c=.o))
OBJ = $(addprefix $(DIR_OBJ),$(C_FILES:.c=.o))

FLAGS = -Wall -Werror -Wextra -I inc/
C_FLAGS = -fPIC $(FLAGS)
O_FLAGS = -shared $(FLAGS)


all: $(DIR_OBJ) $(LIB_NAME) $(SYMLINK_NAME)

debug: C_FLAGS += -ggdb
debug: all

$(SYMLINK_NAME):
	ln -sf $(LIB_NAME) $(SYMLINK_NAME)

$(DIR_OBJ):
	mkdir -p $(DIR_OBJ)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	gcc $(C_FLAGS) -o $@ -c $<

$(LIB_NAME): $(OBJ)
	gcc $(O_FLAGS) $(OBJ) -o $(LIB_NAME)

clean:
	rm -rf $(DIR_OBJ)

fclean: clean
	rm -rf $(LIB_NAME)
	rm -f $(SYMLINK_NAME)

re: fclean all
