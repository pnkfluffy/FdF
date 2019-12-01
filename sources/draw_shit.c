/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:18:51 by jfelty            #+#    #+#             */
/*   Updated: 2019/11/30 17:15:47 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	img_pixel_put(t_grid *grid, int x, int y, int color)
{
	t_img	*img;

	img = grid->img;
	if (x >= 0 && x < WINX && y >= 0 && y < WINY)
		*(int*)(img->data + ((x + y * WINX) * img->bpp)) = color;
}

void	draw_line(t_line *line, t_grid *grid)
{
	int		x;
	int		y;
	int		pre_y;

	x = line->p1->pix_x - 1;
	y = line->slope * x + line->b;
	pre_y = y;
	while (++x <= line->p2->pix_x + 1 && (y = line->slope * x + line->b))
	{
		if ((int)line->p1->pix_x == (int)line->p2->pix_x)
			while (++pre_y <= line->p2->pix_y)
				if (pre_y >= line->p1->pix_y)
					img_pixel_put(grid, x, pre_y, line->p1->color);
		if (line->slope > -0.03 && line->slope < 0.03)
			img_pixel_put(grid, x, y, line->p1->color);
		if (line->slope > 0)
			while (pre_y <= y)
				if (++pre_y >= line->p1->pix_y && pre_y <= line->p2->pix_y)
					img_pixel_put(grid, x, pre_y, line->p1->color);
		if (line->slope < 0)
			while (pre_y >= y)
				if (--pre_y <= line->p1->pix_y && pre_y >= line->p2->pix_y - 2)
					img_pixel_put(grid, x, pre_y, line->p2->color);
		pre_y = y;
	}
}

void	draw_vert_line(t_line *line, t_grid *grid)
{
	int		smol_y;
	int		big_y;

	smol_y = line->p1->pix_y;
	big_y = line->p2->pix_y;
	if (line->p1->pix_y > line->p2->pix_y)
	{
		smol_y = line->p2->pix_y;
		big_y = line->p1->pix_y;
	}
	while (++smol_y < big_y)
	{
		if (line->p1->pix_y > line->p2->pix_y)
			img_pixel_put(grid, line->p1->pix_x, smol_y, line->p2->color);
		else
			img_pixel_put(grid, line->p1->pix_x, smol_y, line->p1->color);
	}
}

void	draw_phat_points(t_pnt *head, t_grid *grid)
{
	t_pnt	*pnt;
	t_img	*img;

	img = grid->img;
	pnt = head;
	img->image = mlx_new_image(grid->mlx, WINX, WINY);
	img->data = mlx_get_data_addr(img->image, &img->bpp, \
	&img->linesize, &img->end);
	img->bpp = 4;
	pnt = head;
	while (pnt)
	{
		img_pixel_put(grid, pnt->pix_x - 1, pnt->pix_y, pnt->color);
		img_pixel_put(grid, pnt->pix_x, pnt->pix_y - 1, pnt->color);
		img_pixel_put(grid, pnt->pix_x, pnt->pix_y, pnt->color);
		img_pixel_put(grid, pnt->pix_x, pnt->pix_y + 1, pnt->color);
		img_pixel_put(grid, pnt->pix_x + 1, pnt->pix_y, pnt->color);
		pnt = pnt->next;
	}
	mlx_put_image_to_window(grid->mlx, grid->win, img->image, 0, 0);
	mlx_destroy_image(grid->mlx, img->image);
	img->image = NULL;
}

void	draw_points(t_pnt *head, t_grid *grid)
{
	t_pnt	*pnt;
	t_img	*img;

	img = grid->img;
	pnt = head;
	if (!(img->image))
		img->image = mlx_new_image(grid->mlx, WINX, WINY);
	img->data = mlx_get_data_addr(img->image, &img->bpp, \
	&img->linesize, &img->end);
	img->bpp = 4;
	pnt = head;
	while (pnt)
	{
		img_pixel_put(grid, pnt->pix_x, pnt->pix_y, pnt->color);
		pnt = pnt->next;
	}
	mlx_put_image_to_window(grid->mlx, grid->win, img->image, 0, 0);
	mlx_destroy_image(grid->mlx, img->image);
	img->image = NULL;
}
