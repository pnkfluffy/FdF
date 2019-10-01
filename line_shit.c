/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:46:38 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/30 22:36:26 by jfelty           ###   ########.fr       */
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
	line->len = sqrt(pow(pnt2->pix_x - pnt1->pix_x, 2) + \
	pow(pnt2->pix_y - pnt1->pix_y, 2));
	line->dist = 0;
	line->slope = (line->p1->pix_x == line->p2->pix_x ? INT_MAX : \
	(line->p2->pix_y - line->p1->pix_y) / (line->p2->pix_x - line->p1->pix_x));
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
			line = line->next;
		}
		if (pnt->down)
		{
			line->next = add_line(line, pnt, pnt->down);
			line = line->next;
		}
		pnt = pnt->next;
	}
	return (grid);
}

void	recalc_lines(t_line *line)
{
	t_line	*curr;
	t_pnt	*tmp;

	tmp = NULL;
	curr = line;
	while (curr)
	{
		if (curr->p1->pix_x > curr->p2->pix_x)
		{
			tmp = curr->p1;
			curr->p1 = curr->p2;
			curr->p2 = tmp;
		}
		curr->len = sqrt(pow(curr->p2->pix_x - curr->p1->pix_x, 2) + \
		pow(curr->p2->pix_y - curr->p1->pix_y, 2));
		curr->dist = 0;
		curr->slope = (curr->p1->pix_x == curr->p2->pix_x ? INT_MAX : \
		(curr->p2->pix_y - curr->p1->pix_y) / (curr->p2->pix_x - \
		curr->p1->pix_x));
		curr->b = (curr->p1->pix_y) - (curr->slope * curr->p1->pix_x);
		curr = curr->next;
	}
}

void	draw_lines(t_grid *grid)
{
	t_line	*line;
	t_img	*img;

	img = grid->img;
	if (!(img->image))
		img->image = mlx_new_image(grid->mlx, WINX, WINY);
	img->data = mlx_get_data_addr(img->image, &img->bpp, \
	&img->linesize, &img->end);
	img->bpp = 4;
	line = grid->first_line;
	while (line)
	{
		if (line->slope != INT_MAX)
			draw_line(line, grid);
		else
			draw_vert_line(line, grid);
		line = line->next;
	}
	mlx_put_image_to_window(grid->mlx, grid->win, img->image, 0, 0);
	mlx_destroy_image(grid->mlx, img->image);
	img->image = NULL;
}
