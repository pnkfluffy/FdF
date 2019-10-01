/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 16:04:55 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/30 22:37:11 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	color_pts(t_pnt *head, int colorrand)
{
	t_pnt		*pnt;

	pnt = head;
	if (!(colorrand))
		colorrand = TESTCLR;
	while (pnt)
	{
		pnt->color = (pnt->z == 0 ? 0xFFFFFF : (pnt->z * colorrand) % MAXCOLOR);
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
			pnt->pix_x += grid->height * pnt->z * grid->scale / \
			grid->max_pnt_height / 6;
			pnt->pix_y -= grid->heightdrift * pnt->z * grid->scale / \
			grid->max_pnt_height / 2;
		}
		pnt = pnt->next;
	}
}

void	spoof_cool_angle(t_pnt *head, t_grid *grid)
{
	t_pnt	*pnt;
	t_pnt	*last;

	grid->scale = 500;
	pnt = head;
	last = pnt;
	while (last->next)
		last = last->next;
	while (pnt)
	{
		pnt->pix_x += last->x > 50 ? pnt->x * pnt->y / last->x : \
		pnt->x * pnt->y;
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

void	adjust_neg_z(t_pnt *head)
{
	t_pnt	*pnt;
	int		lowest;

	lowest = 0;
	pnt = head;
	while (pnt)
	{
		if (pnt->z < lowest)
			lowest = pnt->z;
		pnt = pnt->next;
	}
	if (lowest == 0)
		return ;
	pnt = head;
	while (pnt)
	{
		pnt->z -= lowest;
		pnt = pnt->next;
	}
}
