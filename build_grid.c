/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:58:27 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/18 02:19:01 by jfelty           ###   ########.fr       */
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

void	drawline(t_fdf *line, void *mlx, void *win)
{
	int x;
	int y;
	int prev_y;

	x = line->x1;
	y = line->slope * x + line->B;
	prev_y = y;
	printf("s: %0.3f\tx: %d\ty: %d\t\n", line->slope, x, y);
	if (line->slope == 1)
		while (y < line->y2)
			mlx_pixel_put(mlx, win, x, y++, line->color);
	while (x < line->x2)
	{
		y = line->slope * x + line->B;
		mlx_pixel_put(mlx, win, x, y, line->color);
		if (line->slope > 0)
			while (prev_y < y - 1)
				mlx_pixel_put(mlx, win, x, ++prev_y, line->color);
		if (line->slope < 0)
			while (prev_y > y - 1)
				mlx_pixel_put(mlx, win, x, --prev_y, line->color);
		prev_y = y;
		x++;
	}
}

void	redraw(t_fdf *line, void *mlx, void *win)
{
	while (line)
	{
		drawline(line, mlx, win);
		line = line->next;
	}
}

void	slant(t_fdf *start)
{
	t_fdf *curr;
	int i;
	int row;

	i = 0;
	row = 0;	
	curr = start;
	while (curr)
	{
		if (curr->slope == 1)
			curr->x2 += SCALE / 2;
		else if (curr->slope == 0)
		{
			if (i == GRIDSIZE)
			{
				i = 0;
				row++;
			}
			i++;
		}
		curr->x1 += row * SCALE / 2;
		curr->x2 += row * SCALE / 2;
		curr->slope = (curr->y2 - curr->y1) / (curr->x2 - curr->x1);
		curr->B = curr->y1 - (curr->slope * curr->x1);
		curr = curr->next;
	}
}

int	build_grid(int height, int width)
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	t_fdf	*line;

	line = makelist(line, x, y);
	x = -1;
	y = -1;
	if (!(mlx = mlx_init()))
		return (0);
	if (!(win = mlx_new_window(mlx, WINSIZE, WINSIZE, "mlx 42")))
	 	return (0);
	while (++y < height + 1)
	{
		while (++x < width + 1)
		{
			if (x != width)
				addlist(line, x, y, 'x');
			if (y != height)
				addlist(line, x, y, 'y');
		}
		x = -1;
	}
	slant(line);
	redraw(line, mlx, win);
	mlx_key_hook(win, deal_key, (void *)0);
	mlx_loop(mlx);
	return (0);
}

int main()
{
	build_grid(GRIDSIZE, GRIDSIZE);
	return (0);
}