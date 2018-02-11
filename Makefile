# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/10 15:53:21 by ngrasset          #+#    #+#              #
#    Updated: 2018/02/11 16:55:20 by ngrasset         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

C_DIR = src
C_FILES = src/clock.c  src/keyboard.c src/main.c src/parse_map_file.c \
		  src/init.c src/free.c src/movement.c src/drawing.c

O_DIR =	.tmp/obj
O_DIRS = $(C_DIRS:$(C_DIR)%=$(O_DIR)%)
O_FILES = $(C_FILES:$(C_DIR)%.c=$(O_DIR)%.o)

FLAGS = -Wall -Wextra -Werror -O3
INCLUDES = -I ./includes -I ./libft/includes -I./minilibx_macos
LIB = -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit -L./libft -lft

CC = clang

all: $(NAME)

$(NAME): $(O_FILES)
	make -C ./libft
	$(CC) $(FLAGS) $^ $(INCLUDES) $(LIB) -o $@

$(O_DIR)%.o: $(C_DIR)%.c
	@mkdir -p $(O_DIRS) $(O_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	make clean -C ./libft
	@rm -Rf $(O_DIR)

fclean: clean
	make fclean -C ./libft
	@rm -f $(NAME)
	@rm -Rf .tmp/

re: fclean all

infer: clean
	infer -- make

.PHONY: clean all fclean re
