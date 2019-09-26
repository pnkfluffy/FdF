/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 16:04:55 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/26 00:55:25 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	spoof_height(t_pnt *head, t_grid *grid)
{
	t_pnt	*pnt;

	pnt = head;
	while (pnt)
	{
		if (pnt->z)
		{
			pnt->pix_x += HEIGHTSCALE * pnt->z * grid->scale / grid->max_pnt_height / 6;
			pnt->pix_y -= HEIGHTSCALE * pnt->z * grid->scale / grid->max_pnt_height / 2;
		}
		pnt = pnt->next;
	}
}

void	spoof_cool_angle(t_pnt *head, t_grid *grid)
{
	t_pnt	*pnt;

	grid->scale = 500;
	pnt = head;
	while (pnt)
	{
		pnt->pix_x += pnt->x * pnt->y;
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

void	color_pts(t_pnt *head, t_grid *grid)
{
	t_pnt	*pnt;

	pnt = head;
	while (pnt)
	{
		pnt->color = (MAXCOLOR * (double)(pnt->z + 1) / grid->max_pnt_height);
		if (grid->max_pnt_height == 0)
			pnt->color = 0xFFFFFF;
		//pnt->color = (pnt->z * 500) % 16777215;
		pnt = pnt->next;
	}
}
