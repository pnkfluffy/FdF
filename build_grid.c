/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:58:27 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/17 23:42:24 by jfelty           ###   ########.fr       */
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
	printf("s: %0.3f\tx: %d\ty: %d\tB: %0.3f\n", line->slope, x, y, line->B);
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
	free(line);
}

int	build_grid(int height, int width)
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;

	if (!(mlx = mlx_init()))
		return (0);
	if (!(win = mlx_new_window(mlx, WINSIZE, WINSIZE, "mlx 42")))
	 	return (0);
	x = -1;
	y = -1;
	while (++y < height + 1)
	{
		while (++x < width + 1)
		{
			if (x != width)
				drawline(populate(x * SCALE, x * SCALE + SCALE, y * SCALE, y * SCALE), mlx, win);
			if (y != height)
				drawline(populate(x * SCALE, x * SCALE, y * SCALE, y * SCALE + SCALE), mlx, win);
		}
		x = -1;
	}
	mlx_key_hook(win, deal_key, (void *)0);
	mlx_loop(mlx);
	return (0);
}

int main()
{
	build_grid(10, 10);
	return (0);
}