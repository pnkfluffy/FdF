/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:58:24 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/21 20:37:45 by jfelty           ###   ########.fr       */
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

# define WINX 1000
# define WINY 1000
# define SCALE 0.6
# define START 5

typedef struct		s_pnt
{
	double			pix_x;
	double			pix_y;
	int				x;
	int				y;
	int				z;
	int				color;
	struct s_pnt	*down;
	struct s_pnt	*next;
}					t_pnt;


typedef struct		s_grid
{
	double			max_x;
	double			max_y;
	double			max_pnt_height;
	double			scale;
	void			*mlx;
	void			*win;
}					t_grid;


void	print_params(t_pnt	*head);

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