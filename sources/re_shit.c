/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_shit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 16:44:01 by jfelty            #+#    #+#             */
/*   Updated: 2019/11/30 17:18:54 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	re_translate(t_grid *grid, int x, int y)
{
	t_pnt	*pnt;
	t_line	*line;

	pnt = grid->first_pnt;
	line = grid->first_line;
	while (pnt)
	{
		pnt->pix_x += x;
		pnt->pix_y += y;
		pnt = pnt->next;
	}
	if (!(boundary_check(grid)))
	{
		re_translate(grid, -x, -y);
		return ;
	}
	recalc_lines(grid->first_line);
	re_draw(grid);
}

void	re_scale(t_grid *grid, double x)
{
	t_pnt	*pnt;
	t_pnt	*first;

	first = grid->first_pnt;
	pnt = first;
	while (pnt->next)
		pnt = pnt->next;
	if (x <= 0 && (pnt->pix_x - first->pix_x < WINX / 4))
		return ;
	pnt = first;
	while (pnt)
	{
		pnt->pix_x *= 1 + x;
		pnt->pix_y *= 1 + x;
		pnt = pnt->next;
	}
	if (!(boundary_check(grid)))
	{
		re_scale(grid, -x * 1.1);
		return ;
	}
	recalc_lines(grid->first_line);
	re_draw(grid);
}

void	re_height(t_grid *grid, double height, double drift)
{
	t_pnt	*pnt;

	grid->height += height;
	grid->heightdrift += drift;
	pnt = grid->first_pnt;
	while (pnt)
	{
		if (height)
			pnt->pix_y -= height * pnt->z;
		else if (drift)
			pnt->pix_x += drift * pnt->z;
		pnt = pnt->next;
	}
	if (!(boundary_check(grid)))
	{
		re_height(grid, -(1.01 * height), -(1.01 * drift));
		return ;
	}
	recalc_lines(grid->first_line);
	re_draw(grid);
}

void	re_angle(t_grid *grid, double x)
{
	t_pnt	*pnt;

	pnt = grid->first_pnt;
	while (pnt)
	{
		pnt->pix_x += x * pnt->y;
		pnt = pnt->next;
	}
	if (!(boundary_check(grid)))
	{
		re_angle(grid, -(x * 1.1));
		return ;
	}
	recalc_lines(grid->first_line);
	re_draw(grid);
}
