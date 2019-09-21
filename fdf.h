/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:58:24 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/20 20:52:10 by jfelty           ###   ########.fr       */
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
# define SCALE 60
# define START 5

typedef struct		s_pnt
{	int				pix_x;
	int				pix_y;
	int				x;
	int				y;
	int				z;
	// double			slope;
	// double			B;
	int				color;
	struct s_pnt	*down;
	struct s_pnt	*next;
}					t_pnt;


typedef struct		s_grid
{
	int				max_x;
	int				max_y;
	void			*mlx;
	void			*win;
}					t_grid;


/*
**	calc_shit.c
*/

t_pnt	*calc_shit(t_pnt *head);
int		deal_key(int key);
t_grid	*initialize_grid();
void	draw_points(t_pnt *head, t_grid *grid);
void	draw_phat_points(t_pnt *head, t_grid *grid);
void	draw_lines(t_pnt *head, t_grid *grid);
void	draw_line(t_pnt *left, t_pnt *right, t_grid *grid);
# endif