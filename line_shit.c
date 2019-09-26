/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:46:38 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/25 23:36:10 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_line	*add_line(t_line *line, t_pnt *pnt1, t_pnt *pnt2)
{
	if (!(line = ft_memalloc(sizeof(t_line))))
		return (NULL);
	if (pnt1->pix_x <= pnt2->pix_x)
	{
		line->p1 = pnt1;
		line->p2 = pnt2;
	}
	else
	{
		line->p1 = pnt2;
		line->p2 = pnt1;
	}
	line->len = sqrt(pow(pnt2->pix_x - pnt1->pix_x, 2) + pow(pnt2->pix_y - pnt1->pix_y, 2));
	line->dist = 0;
	line->slope = (line->p1->pix_x == line->p2->pix_x ? 1 : (line->p2->pix_y - line->p1->pix_y) / (line->p2->pix_x - line->p1->pix_x));
	line->b = (line->p1->pix_y) - (line->slope * line->p1->pix_x);
	line->next = NULL;
	return (line);
}

t_grid	*populate_lines(t_pnt *head, t_grid *grid)
{
	t_pnt	*pnt;
	t_line	*line;

	line = NULL;
	pnt = head;
	line = add_line(line, pnt, pnt->next);
	grid->first_line = line;
	while (pnt->next)
	{
		if (pnt->next->x != 0 && pnt->next)
		{
			line->next = add_line(line, pnt, pnt->next);	
//			printf("pnt1: (%3.1f, %3.1f)\t pnt2: (%3.1f, %3.1f)\t linelen: %f\n", pnt->pix_x, pnt->pix_y, pnt->next->pix_x, pnt->next->pix_y, line->len);
			line = line->next;
		}
		if (pnt->down)
		{
			line->next = add_line(line, pnt, pnt->down);
//			printf("pnt1: (%3.1f, %3.1f)\t pnt2: (%3.1f, %3.1f)\t linelen: %f\n", pnt->pix_x, pnt->pix_y, pnt->next->pix_x, pnt->next->pix_y, line->len);
			line = line->next;
		}
		pnt = pnt->next;
	}
	return (grid);
}