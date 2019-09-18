/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:58:24 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/17 23:08:29 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include "math.h"

//DELETE
#include <stdio.h>

# define WINSIZE 1000
# define X_1 200
# define X_2 210
# define Y_1 100
# define Y_2 400
# define SCALE 50
# define START 10

typedef struct		s_fdf
{
	double			x1;
	double			x2;
	double			y1;
	double			y2;
	double			z;
	double			slope;
	double			B;
	int				color;
	struct s_fdf	*next;
}					t_fdf;

/*
**	draw_line.c
*/

void	drawline(t_fdf *line, void *mlx, void *win);
t_fdf	*populate(int x1, int x2, int y1, int y2);

/*
**	build_grid.c
*/

# endif