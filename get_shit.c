/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 02:30:25 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/21 20:39:47 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//complete and change to libft function
int		ft_strtohex(char *str)
{
	return (167215);
}

/*
**	
**	
**	
*/

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
	pnt->color = (pnt->z > 0) ? (pnt->z * 500) % 16777215 : (pnt->z * -200) % 16777215;
	if (pnt->z == 0)
		pnt->color = 16777215;
	if (above)
		above->down = pnt;
	if ((hexcolor = ft_strchr(z, ',')) != NULL)
		pnt->color = ft_strtohex(++hexcolor);
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
	{
		head = parse_line(head, ft_strsplit(nextline, ' '), height);
	}
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

int	main(int ac, char **av)
{
	int		fd;
	t_pnt	*head;
	t_grid	*grid;

	fd = open(av[1], O_RDONLY);
	if (!(fd = open(av[1], O_RDONLY)) || ac != 2 || !(head = convert_check(fd)))
	{
		if (ac != 2)
			ft_putendl("Usage: ./fillit target_filename");
		else
			ft_putstr("error\n");
		return (0);
	}
//	calc_shit(head);
	grid = initialize_grid(head);
//	print_params(head);
//	draw_points(head, grid);
//	draw_phat_points(head, grid);
	draw_lines(head, grid);
	mlx_loop(grid->mlx);
	return (0);
}

//cc get_shit.c calc_shit.c minilibx_macos/libmlx.a libft/libft.a -framework OpenGL -framework AppKit