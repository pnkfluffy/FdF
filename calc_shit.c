/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 16:04:55 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/21 19:30:55 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	deal_key(int key)
{
	ft_putnbr(key);
	ft_putchar(' ');
	if (key == 53)
		exit(1);
	return (key);
}

int		calc_scale(t_pnt *head, t_grid *grid)
{
	t_pnt *pnt;
	int scale;

	pnt = head;
	while (pnt->down)
		pnt = pnt->down;
	while (pnt->next)
		pnt = pnt->next;
	scale = grid->max_x * SCALE / pnt->x;
	return (scale);	
}

void	scale_grid(t_pnt *head, t_grid *grid)
{
	t_pnt	*pnt;

	grid->max_pnt_height = 0;
	pnt = head;
	while (pnt)
	{
		if (pnt->z > grid->max_pnt_height)
			grid->max_pnt_height = pnt->z;
		pnt->pix_x = pnt->x * grid->scale;
		pnt->pix_y = pnt->y * grid->scale;
		pnt = pnt->next;
	}
}

//redo to true center, take pix_x and pix_y value and calc to get them 
//same length from center/ boundaries of grid
void	center_grid(t_pnt *head, t_grid *grid)
{
	t_pnt	*pnt;
	double	x_shift;
	double	y_shift;

	pnt = head;
	while (pnt->next)
		pnt = pnt->next;
	x_shift = (WINX - pnt->pix_x) / 2;
	y_shift = (WINY - pnt->pix_y) / 2;
	pnt = head;
	while (pnt)
	{
		pnt->pix_x += x_shift;
		pnt->pix_y += y_shift;
		pnt = pnt->next;
	}
}

void	spoof_height(t_pnt *head, t_grid *grid)
{
	t_pnt	*pnt;

	pnt = head;
	while (pnt)
	{
		if (pnt->z)
		{
			printf("x1: %f y1: %f\n", pnt->pix_x, pnt->pix_y);
			pnt->pix_x += pnt->z * grid->scale / grid->max_pnt_height / 6;
			pnt->pix_y -= pnt->z * grid->scale / grid->max_pnt_height / 2;
			printf("x1: %f y1: %f\n", pnt->pix_x, pnt->pix_y);
		}
		pnt = pnt->next;
	}
}

void	spoof_angle(t_pnt *head, t_grid *grid)
{
	t_pnt	*pnt;

	pnt = head;
	while (pnt)
	{
		pnt->pix_x += pnt->y * grid->scale / 2;
		pnt = pnt->next;
	}
}

//add function to set lowest z value to 0 and increase all others by that amount,
//mlx doesn't handle negatives
t_grid	*initialize_grid(t_pnt	*head)
{
	t_grid	*grid;

	if (!(grid = ft_memalloc(sizeof(t_grid))))
		return (NULL);
	if (!(grid->mlx = mlx_init()))
		return (0);
	if (!(grid->win = mlx_new_window(grid->mlx, WINX, WINY, "mlx 42")))
	 	return (0);
	grid->max_x = WINX;
	grid->max_y = WINY;
	grid->scale = calc_scale(head, grid);
	scale_grid(head, grid);
	center_grid(head, grid);
	// spoof_angle(head, grid);
	spoof_height(head, grid);
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
			(pnt->pix_x > pnt->down->pix_x) ? draw_line(pnt->down, pnt, grid) : draw_line(pnt, pnt->down, grid);
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