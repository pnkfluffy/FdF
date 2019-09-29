/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:23:04 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/29 00:18:49 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	recalc_lines(t_line *line)
{
	t_line	*curr;

	curr = line;
	while (curr)
	{
		curr->len = sqrt(pow(curr->p2->pix_x - curr->p1->pix_x, 2) + pow(curr->p2->pix_y - curr->p1->pix_y, 2));
		curr->dist = 0;
		curr->slope = (curr->p1->pix_x == curr->p2->pix_x ? 1 : (curr->p2->pix_y - curr->p1->pix_y) / (curr->p2->pix_x - curr->p1->pix_x));
		curr->b = (curr->p1->pix_y) - (curr->slope * curr->p1->pix_x);
		curr = curr->next;
	}
}

void	re_translate(t_grid *grid, int x, int y)
{
	t_pnt	*pnt;
	t_line	*line;

	pnt = grid->first_line->p1;
	line = grid->first_line;
	while (pnt)
	{
		pnt->pix_x += x;
		pnt->pix_y += y;
		pnt = pnt->next;
	}
	recalc_lines(grid->first_line);
	draw_lines(grid);
}

void	re_scale(t_grid *grid, double x)
{
	t_pnt	*pnt;

	grid->scale = 1 + x;
	pnt = grid->first_line->p1;
	while (pnt)
	{
		pnt->pix_x *= grid->scale;
		pnt->pix_y *= grid->scale;
		pnt = pnt->next;
	}
	recalc_lines(grid->first_line);
	draw_lines(grid);
}

void	re_height(t_grid *grid, double x)
{
	t_pnt	*pnt;

	grid->heightdrift += x;
	pnt = grid->first_line->p1;
	while (pnt)
	{
		pnt->pix_y -= grid->heightdrift * pnt->z;
		pnt = pnt->next;
	}
	recalc_lines(grid->first_line);
	draw_lines(grid);
}

void	re_set(t_grid *grid)
{
	t_pnt	*head;

	head = grid->first_line->p1;
	grid->height = HEIGHTSCALE;
	grid->heightdrift = HEIGHTDRIFT;
	grid->scale = calc_scale(head, grid);
	adjust_neg_z(head);
	scale_grid(head, grid);
	center_grid(head, grid);
	spoof_height(head, grid);
	spoof_angle(head, grid);
	recalc_lines(grid->first_line);
	draw_lines(grid);
}

int	hook_key(int key, t_grid *grid)
{
	ft_putnbr(key);
	ft_putchar(' ');
	if (key == 53)
		exit(1);
	if (key == 123)
		re_translate(grid, -20, 0);
	if (key == 124)
		re_translate(grid, 20, 0);
	if (key == 125)
		re_translate(grid, 0, 20);
	if (key == 126)
		re_translate(grid, 0, -20);
	if (key == 30)
		re_scale(grid, .01);
	if (key == 33)
		re_scale(grid, -.01);
	if (key == 39)
		re_height(grid, -0.5);
	if (key == 41)
		re_height(grid, 0.5);
	if (key == 15)
		re_set(grid);
	return (key);
}