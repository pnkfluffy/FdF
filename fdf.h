/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:58:24 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/18 02:35:30 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <math.h>
# include <fcntl.h>

//DELETE
#include <stdio.h>

# define WINSIZE 1000
# define GRIDSIZE 18
# define SCALE 30
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
**	build_list.c
*/

t_fdf	*addlist(t_fdf *list, int x, int y, char dir);
t_fdf	*populate(int x1, int x2, int y1, int y2);
t_fdf	*makelist(t_fdf *list, int x, int y);

/*
**	build_grid.c
*/

# endif