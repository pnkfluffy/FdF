/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 02:30:25 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/26 00:23:30 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pnt	*populate(int x, int y, char *z, t_pnt *above)
{
	t_pnt	*pnt;
	char	*hexcolor;

	if (!(pnt = ft_memalloc(sizeof(t_pnt))))
		return (NULL);
	pnt->x = x;
	pnt->y = y;
	pnt->z = ft_atoi(z);
	pnt->down = NULL;
	pnt->next = NULL;
	pnt->color = (int)NULL;
	if (pnt->z == 0)
		pnt->color = 0xFFFFFF;
	if (above)
		above->down = pnt;
	if ((hexcolor = ft_strchr(z, ',')) != NULL)
		pnt->color = ft_atoi_base(hexcolor + 3, 16);
	return (pnt);
}

t_pnt	*add_pnt(t_pnt *head, int x, int y, char *z)
{
	t_pnt	*pnt;
	t_pnt	*above;

	above = NULL;
	pnt = head;
	if (pnt)
	{
		while (pnt->y < y - 1)
			pnt = pnt->down;
		while (pnt->next)
		{
			if (x == pnt->x)
				above = pnt;
			pnt = pnt->next;
		}
		if (!(pnt->next = populate(x, y, z, above)))
			return (NULL);
	}
	else
		if (!(head = populate(x, y, z, above)))
			return (NULL);
	return (head);
}

t_pnt	*parse_line(t_pnt *head, char **linearray, int height)
{
	int		i;

	i = -1;
	while (linearray[++i])
	{
		if (!(head = add_pnt(head, i, height - 1, linearray[i])))
			return (NULL);
	}
	return (head);
}

t_pnt	*convert_check(int fd)
{
	t_pnt	*head;
	char	*nextline;
	int		height;

	head = NULL;
	height = 0;
	nextline = ft_strnew(0);
	while (get_next_line(fd, &nextline) > 0 && ++height)
		head = parse_line(head, ft_strsplit(nextline, ' '), height);
	return (head);
}

void	print_params(t_pnt	*head)
{
	t_pnt	*pnt;

	pnt = head;
	while (pnt->next)
	{
		printf("x: %d  y: %d  z: %d  pix_x: %3f  pix_y: %3f\n", pnt->x, pnt->y, pnt->z, pnt->pix_x, pnt->pix_y);
		pnt = pnt->next;
	}
}
