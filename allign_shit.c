/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allign_shit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 00:33:43 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/26 01:06:43 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	center_grid(t_pnt *head, t_grid *grid)
{
	t_pnt	*pnt;
	double	x_shift;
	double	y_shift;

	pnt = head;
	while (pnt->next)
		pnt = pnt->next;
	x_shift = (grid->max_x - pnt->pix_x) * SCALE / 2;
	y_shift = (grid->max_y - pnt->pix_y) / 2;
	pnt = head;
	while (pnt)
	{
		pnt->pix_x += x_shift;
		pnt->pix_y += y_shift;
		pnt = pnt->next;
	}
}
