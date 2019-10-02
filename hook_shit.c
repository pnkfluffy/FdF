/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:23:04 by jfelty            #+#    #+#             */
/*   Updated: 2019/10/01 17:21:11 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	re_set(t_grid *grid, int key)
{
	t_pnt	*head;

	head = grid->first_pnt;
	grid->height = HEIGHTSCALE;
	grid->heightdrift = HEIGHTDRIFT;
	grid->scale = calc_scale(head, grid);
	adjust_neg_z(head);
	scale_grid(head, grid);
	center_grid(head, grid);
	spoof_height(head, grid);
	(key == 15) ? spoof_angle(head, grid) : spoof_cool_angle(head);
	recalc_lines(grid->first_line);
	re_draw(grid);
}

void	re_view(t_grid *grid, int key)
{
	t_img	*img;
	t_pnt	*head;

	img = grid->img;
	head = grid->first_pnt;
	if (key == 21 || key == 23)
		key == 21 ? color_pts(head, rand()) : color_pts(head, 5000);
	else
		grid->render = key - 18;
	re_draw(grid);
}

void	re_draw(t_grid *grid)
{
	if (grid->render == 0)
		draw_lines(grid);
	if (grid->render == 1)
		draw_points(grid->first_pnt, grid);
	if (grid->render == 2)
		draw_phat_points(grid->first_pnt, grid);
}

int		hook_key(int key, t_grid *grid)
{
	ft_putnbr(key);
	ft_putchar(' ');
	if (key == 53)
		exit(1);
	if (key == 24 || key == 27)
		key == 24 ? re_angle(grid, 0.5) : re_angle(grid, -0.5);
	if (key == 123 || key == 124)
		key == 123 ? re_translate(grid, -20, 0) : re_translate(grid, 20, 0);
	if (key == 125 || key == 126)
		key == 125 ? re_translate(grid, 0, 20) : re_translate(grid, 0, -20);
	if (key == 30 || key == 33)
		key == 30 ? re_scale(grid, .02) : re_scale(grid, -0.02);
	if (key == 13 || key == 12 || key == 1)
		key == 1 ? re_height(grid, -0.5, 0) : re_height(grid, -(key - 13.5), 0);
	if (key == 2 || key == 0)
		key == 2 ? re_height(grid, 0, 0.5) : re_height(grid, 0, -0.5);
	if (key == 18 || key == 19 || key == 20 || key == 21 || key == 23)
		re_view(grid, key);
	if (key == 15 || key == 17)
		re_set(grid, key);
	return (key);
}
