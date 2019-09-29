/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:58:24 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/29 00:15:53 by jfelty           ###   ########.fr       */
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
# define SCALE 0.5
# define START 20
# define HEIGHTSCALE 6
# define HEIGHTDRIFT 4
# define MAXCOLOR 16777215

# define R(a) (a) >> 16
# define G(a) ((a) >> 8) & 0xFF
# define B(a) (a) & 0xFF
# define COMBINE(a, b, c) ((a) << 16) + ((b) << 8) + (c)

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

typedef struct		s_line
{
	struct s_pnt	*p1;
	struct s_pnt	*p2;
	struct s_line	*next;
	double			len;
	int				dist;
	double 			slope;
	double			b;
}					t_line;

typedef struct		s_img
{
	int				end;
	int				bpp;
	int				linesize;
	char			*data;	
	void			*image;
}					t_img;


typedef struct		s_grid
{
	double			max_x;
	double			max_y;
	double			max_pnt_height;
	double			scale;
	double			pos;
	double			height;
	double			heightdrift;
	void			*mlx;
	void			*win;
	struct s_line	*first_line;
	struct s_img	*img;
}					t_grid;

/*
**	fdf.c
*/

t_grid	*initialize_grid(t_pnt	*head);

/*
**	get_shit.c
*/

t_pnt	*populate(int x, int y, char *z, t_pnt *above);
t_pnt	*add_pnt(t_pnt *head, int x, int y, char *z);
t_pnt	*parse_line(t_pnt *head, char **linearray, int height);
t_pnt	*convert_check(int fd);
void	print_params(t_pnt	*head);

/*
**	allign_shit.c
*/

int		calc_scale(t_pnt *head, t_grid *grid);
void	scale_grid(t_pnt *head, t_grid *grid);
void	center_grid(t_pnt *head, t_grid *grid);

/*
**	calc_shit.c
*/

void	spoof_height(t_pnt *head, t_grid *grid);
void	spoof_cool_angle(t_pnt *head, t_grid *grid);
void	spoof_angle(t_pnt *head, t_grid *grid);
void	adjust_neg_z(t_pnt *head);

/*
**	line_shit.c
*/

t_line	*add_line(t_line *line, t_pnt *pnt1, t_pnt *pnt2);
t_grid	*populate_lines(t_pnt *head, t_grid *grid);

/*
**	draw_shit.c
*/

int		color_line(t_line *line);
void	draw_line(t_line *line, t_grid *grid);
void	draw_lines(t_grid *grid);
void	draw_phat_points(t_pnt *head, t_grid *grid);
void	draw_points(t_pnt *head, t_grid *grid);

/*
**	hook_shit.c
*/

int		hook_key(int key, t_grid *grid);

# endif