/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:58:24 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/20 13:12:50 by jfelty           ###   ########.fr       */
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
# define GRIDSIZE 25
# define SCALE 20
# define START 5

// 	OLD?
// typedef struct		s_pnt
// {
// 	double			x1;
// 	double			x2;
// 	double			y1;
// 	double			y2;
// 	double			z;
// 	double			slope;
// 	double			B;
// 	int				row;
// 	int				col;
// 	int				color;
// 	struct s_pnt	*next;
// 	struct s_pnt	*down;	
// }					t_pnt;

typedef struct		s_pnt
{	int				pix_x;
	int				pix_y;
	int				x;
	int				y;
	int				z;
	// double			slope;
	// double			B;
	int				color;
	// int				max_x;
	// int				max_y;
	struct s_pnt	*down;
	struct s_pnt	*next;
}					t_pnt;


typedef struct		s_grid
{
	int				width;
	int				height;
	int				*numarray;
}					t_grid;


/*
**	build_list.c
*/

t_pnt	*addlist(t_pnt *list, int x, int y, char dir);
//t_pnt	*populate(int x1, int x2, int y1, int y2);
t_pnt	*makelist(t_pnt *list, int x, int y);

/*
**	build_grid.c
*/

# endif