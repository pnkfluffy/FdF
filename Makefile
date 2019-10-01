# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/25 23:24:55 by jfelty            #+#    #+#              #
#    Updated: 2019/09/30 16:46:45 by jfelty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MLXFLAGS = -framework OpenGL -framework AppKit

MLXLIB = minilibx_macos/libmlx.a

LIBFT = libft/libft.a

SRC =	fdf.c \
		get_shit.c \
		allign_shit.c \
		start_shit.c \
		draw_shit.c \
		hook_shit.c \
		line_shit.c \
		re_shit.c

all: $(NAME)

$(NAME): lib out

lib:
	@make -C libft
	@echo "libft complete"
#uses make command in library

out:
	@$(CC) $(CFLAGS) $(SRC) $(MLXLIB) $(LIBFT) $(MLXFLAGS) -fsanitize=address -g -o fdf
	@echo "FdF Generation Complete"

clean:
	@rm -f $(OBJ)
	@make -C libft/ clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all

.PHONY: lib out clean all fclean re fdf