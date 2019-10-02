/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allign_shit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 00:33:43 by jfelty            #+#    #+#             */
/*   Updated: 2019/10/01 17:21:28 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		calc_scale(t_pnt *head, t_grid *grid)
{
	t_pnt	*pnt;
	int		scale;

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

int		boundary_check(t_grid *grid)
{
	t_pnt	*first;
	t_pnt	*last;
	t_pnt	*highest;
	t_pnt	*lowest;

	first = grid->first_pnt;
	last = first;
	highest = first;
	lowest = first;
	while (last->next)
	{
		if (last->pix_y < highest->pix_y)
			highest = last;
		if (last->pix_y > lowest->pix_y)
			lowest = last;
		last = last->next;
	}
	if (lowest->pix_y > WINY * 0.1 && highest->pix_y < WINY * 0.9 &&
	first->pix_x < WINX * 0.9 && last->pix_x > WINX * 0.1)
		return (1);
	ft_putstr("BOUNDRY CHECK FAILED\n");
	return (0);
}
