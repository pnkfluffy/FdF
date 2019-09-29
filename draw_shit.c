/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:18:51 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/28 22:19:26 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		color_line(t_line *line)
{
	double	old_rgb[3];
	int		new_rgb[3];

	old_rgb[0] = (double)((R(line->p2->color)) - (R(line->p1->color)) / line->len);
	old_rgb[1] = (double)((G(line->p2->color)) - (G(line->p1->color)) / line->len);
	old_rgb[2] = (double)((B(line->p2->color)) - (B(line->p1->color)) / line->len);
	new_rgb[0] = (R(line->p1->color)) + (line->dist * old_rgb[0]);
	new_rgb[1] = (R(line->p1->color)) + (line->dist * old_rgb[1]);
	new_rgb[2] = (R(line->p1->color)) + (line->dist * old_rgb[2]);
	printf("dist: %2d\ttotal: %f\n", line->dist, line->len);
	line->dist++;
	return (COMBINE(new_rgb[0], new_rgb[1], new_rgb[2]));
}

void	img_pixel_put(t_grid *grid, int x, int y, int color)
{
	t_img	*img;

	img = grid->img;
	if (x >= 0 && x <= WINX && y >= 0 && y < WINY)
		img->data[(x * img->bpp * 4) / (img->bpp * sizeof(*img->data)) + (y * img->linesize / sizeof(*img->data))] = mlx_get_color_value(grid->mlx, color);
}

void	draw_line(t_line *line, t_grid *grid)
{
	int		x;
	int		y;
	int		prev_y;

	x = line->p1->pix_x;
	y = line->slope * x + line->b;
	prev_y = y;
	if (line->slope == 1)
		while (y <= line->p2->pix_y)
			img_pixel_put(grid, x, y++, line->p1->color);
	while (x <= line->p2->pix_x + 1)
	{
		y = line->slope * x + line->b;
		if (line->slope == 0)
			img_pixel_put(grid, x, y, line->p1->color);
		if (line->slope > 0)
			while (prev_y <= y)
				if (++prev_y >= line->p1->pix_y && prev_y <= line->p2->pix_y)
					img_pixel_put(grid, x, prev_y, line->p1->color);
		if (line->slope < 0)
			while (prev_y >= y)
				if (--prev_y <= line->p1->pix_y && prev_y >= line->p2->pix_y - 2)
					img_pixel_put(grid, x, prev_y, line->p2->color);
		prev_y = y;
		x++;
	}
}

void	draw_lines(t_grid *grid)
{
	t_line	*line;
	t_img	*img;

	img = grid->img;
	if (!(img->image))
		img->image = mlx_new_image(grid->mlx, WINX, WINY);
	img->data = mlx_get_data_addr(img->image, &img->bpp, &img->linesize, &img->end);
	line = grid->first_line;
	while (line)
	{
		draw_line(line, grid);
		line = line->next;
	}
	mlx_put_image_to_window(grid->mlx, grid->win, img->image, 0, 0);
	mlx_destroy_image(grid->mlx, img->image);
	img->image = NULL;
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
