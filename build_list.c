/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:58:32 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/19 12:55:05 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pnt	*populate(int x1, int x2, int y1, int y2)
{
	t_pnt	*line;

	if (!(line = ft_memalloc(sizeof(t_pnt))))
		return (NULL);
	line->x1 = (double)x1 + SCALE;
	line->x2 = (double)x2 + SCALE;
	line->y1 = (double)y1 + SCALE;
	line->y2 = (double)y2 + SCALE;
	if (x1 == x2)
		line->slope = 1;
	else
		line->slope = (line->y2 - line->y1) / (line->x2 - line->x1);
	line->B = line->y1 - (line->slope * line->x1);
	line->color = 1677215;
	line->next = NULL;
	return (line);
}

t_pnt	*addlist(t_pnt *list, int x, int y, char dir)
{
	t_pnt	*curr;

	curr = list;
	while (curr->next)
		curr = curr->next;
	if (dir == 'x')
		curr->next = populate(x * SCALE, x * SCALE + SCALE, y * SCALE, y * SCALE);
	else if (dir == 'y')
		curr->next = populate(x * SCALE, x * SCALE, y * SCALE, y * SCALE + SCALE);
	return(list);
}

t_pnt	*makelist(t_pnt *list, int x, int y)
{
	list = populate(x * SCALE, x * SCALE, y * SCALE, y * SCALE);
	return (list);
}

// int main()
// {
// 	t_pnt	*line;

// 	line = populate(X_1, X_2, Y_1, Y_2);
// 	drawline(line);
// 	mlx_key_hook(line->win, deal_key, (void *)0);
// 	mlx_loop(line->mlx);
// 	return (0);
// }

// cc build_list.c build_grid.c minilibx_macos/libmlx.a libft/libft.a -framework OpenGL -framework AppKit

