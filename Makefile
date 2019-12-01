# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/25 23:24:55 by jfelty            #+#    #+#              #
#    Updated: 2019/11/30 17:26:21 by jfelty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MLXFLAGS = -framework OpenGL -framework AppKit

MLXLIB = minilibx_macos/libmlx.a

LIBFT = sources/libft/libft.a

SRC =	sources/fdf.c \
		sources/get_shit.c \
		sources/allign_shit.c \
		sources/start_shit.c \
		sources/draw_shit.c \
		sources/hook_shit.c \
		sources/line_shit.c \
		sources/re_shit.c

all: $(NAME)

$(NAME): lib mlx out

mlx:
	@make -C minilibx_macos

lib:
	@make -C sources/libft
	@echo "libft complete"
#uses make command in library

out:
	@$(CC) $(CFLAGS) $(SRC) $(MLXLIB) $(LIBFT) $(MLXFLAGS) -o fdf
	@echo "FdF Generation Complete"

clean:
	@rm -f $(OBJ)
	@make -C sources/libft/ clean
	@make -C minilibx_macos/ clean

fclean: clean
	@rm -f $(NAME)
	@make -C sources/libft/ fclean

re: fclean all

.PHONY: lib out clean all fclean re fdf mlx