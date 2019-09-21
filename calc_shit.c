/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 16:04:55 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/20 20:49:05 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pnt	*calc_shit(t_pnt *head)
{
	t_pnt	*pnt;
	int		random;
	
	random = rand();
	pnt = head;
	while (pnt)
	{
		pnt->pix_x = pnt->x * SCALE + START;
		pnt->pix_y = pnt->y * SCALE + START;
		pnt->color = (pnt->z == 0) ? 115550 : pnt->z * random;
		pnt = pnt->next;
	}
	return (head);
}

int	deal_key(int key)
{
	ft_putnbr(key);
	ft_putchar(' ');
	if (key == 53)
		exit(1);
	return (key);
}

t_grid	*initialize_grid()
{
	t_grid	*grid;

	if (!(grid = ft_memalloc(sizeof(t_grid))))
		return (NULL);
	if (!(grid->mlx = mlx_init()))
		return (0);
	if (!(grid->win = mlx_new_window(grid->mlx, WINSIZE, WINSIZE, "mlx 42")))
	 	return (0);
	mlx_key_hook(grid->win, &deal_key, (void *)0);
	return (grid);
}

void	draw_line(t_pnt *left, t_pnt *right, t_grid *grid)
{
	int		x;
	int		y;
	int		prev_y;
	double	slope;
	double	b;

	x = left->pix_x;
	slope = (left->pix_x == right->pix_x ? 1 : (double)(right->pix_y - left->pix_y) / (double)(right->pix_x - left->pix_x));
	b = (double)(left->pix_y) - (slope * (double)left->pix_x);
	y = slope * x + b;
	prev_y = y;
	if (slope == 1)
		while (y < right->pix_y)
			mlx_pixel_put(grid->mlx, grid->win, x, y++, left->color);
	while (x < right->pix_x)
	{
		y = slope * x + b;
		mlx_pixel_put(grid->mlx, grid->win, x, y, left->color);
		if (slope >= 0)
			while (prev_y < y - 1)
				mlx_pixel_put(grid->mlx, grid->win, x, ++prev_y, left->color);
		if (slope < 0)
			while (prev_y > y - 1)
				mlx_pixel_put(grid->mlx, grid->win, x, --prev_y, left->color);
		prev_y = y;
		x++;
	}
}

void	draw_lines(t_pnt *head, t_grid *grid)
{
	t_pnt	*pnt;

	pnt = head;
	while (pnt->next)
	{
		if (pnt->next->x != 0 && pnt->next)
			(pnt->pix_x >= pnt->next->pix_x) ? draw_line(pnt->next, pnt, grid) : draw_line(pnt, pnt->next, grid);
		if (pnt->down)
			(pnt->pix_x >= pnt->down->pix_x) ? draw_line(pnt, pnt->down, grid) : draw_line(pnt->down, pnt, grid);
		pnt = pnt->next;
	}
}

void	draw_phat_points(t_pnt *head, t_grid *grid)
{
	t_pnt	*pnt;

	pnt = head;
	while (pnt)
	{
		mlx_pixel_put(grid->mlx, grid->win, pnt->pix_x - 1, pnt->pix_y - 1, pnt->color);
		mlx_pixel_put(grid->mlx, grid->win, pnt->pix_x - 1, pnt->pix_y, pnt->color);
		mlx_pixel_put(grid->mlx, grid->win, pnt->pix_x - 1, pnt->pix_y + 1, pnt->color);
		mlx_pixel_put(grid->mlx, grid->win, pnt->pix_x, pnt->pix_y - 1, pnt->color);
		mlx_pixel_put(grid->mlx, grid->win, pnt->pix_x, pnt->pix_y, pnt->color);
		mlx_pixel_put(grid->mlx, grid->win, pnt->pix_x, pnt->pix_y + 1, pnt->color);
		mlx_pixel_put(grid->mlx, grid->win, pnt->pix_x + 1, pnt->pix_y - 1, pnt->color);
		mlx_pixel_put(grid->mlx, grid->win, pnt->pix_x + 1, pnt->pix_y, pnt->color);
		mlx_pixel_put(grid->mlx, grid->win, pnt->pix_x + 1, pnt->pix_y + 1, pnt->color);
		pnt = pnt->next;
	}
}

void	draw_points(t_pnt *head, t_grid *grid)
{
	t_pnt	*pnt;

	pnt = head;
	while (pnt)
	{
		mlx_pixel_put(grid->mlx, grid->win, pnt->pix_x, pnt->pix_y, pnt->color);
		pnt = pnt->next;
	}
}

// void	pass_lines(t_pnt *head, t_grid *grid)
// {
// 	t_pnt	*pnt;

// 	pnt = head;
// 	while (pnt)
// 	{
// 		if (pnt->next->x != 0)
		
// 		pnt = pnt->next;
// 	}
// 	return (head);
// }