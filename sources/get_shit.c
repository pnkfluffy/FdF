/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 02:30:25 by jfelty            #+#    #+#             */
/*   Updated: 2019/11/30 17:18:46 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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
	pnt->permcolor = 0;
	if (pnt->z == 0)
		pnt->color = 0xFFFFFF;
	if (above)
		above->down = pnt;
	if ((hexcolor = ft_strchr(z, ',')) != NULL)
	{
		pnt->permcolor = ft_atoi_base(hexcolor + 3, 16);
	}
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
	else if (!(head = populate(x, y, z, above)))
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
