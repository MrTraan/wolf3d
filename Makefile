NAME = wolf3d

C_DIR = src
C_FILES = src/clock.c  src/keyboard.c src/main.c


O_DIR =	.tmp/obj
O_DIRS = $(C_DIRS:$(C_DIR)%=$(O_DIR)%)
O_FILES = $(C_FILES:$(C_DIR)%.c=$(O_DIR)%.o)

FLAGS = -Wall -Wextra -Werror -fsanitize=address
INCLUDES = -I ./includes -I ./libft/includes -I./minilibx_macos
LIB = -L./minilibx_macos -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit

CC = gcc

all: $(NAME)

$(NAME): $(O_FILES)
	$(CC) $(FLAGS) $^ $(INCLUDES) $(LIB) -o $@

$(O_DIR)%.o: $(C_DIR)%.c
	@mkdir -p $(O_DIRS) $(O_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@rm -Rf $(O_DIR)

fclean: clean
	@rm $(NAME) || true
	@rm -Rf .tmp/

debug:
	$(CC) $(FLAGS) -g $(C_FILES) $(INCLUDES) $(LIB) -o $(NAME)_debug

re: fclean all

.PHONY: clean all fclean re
