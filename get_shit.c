/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 02:30:25 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/19 22:13:14 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pnt	*populate(int x, int y, char *z, t_pnt *above, t_pnt *before)
{
	t_pnt	*pnt;

	if (!(pnt = ft_memalloc(sizeof(t_pnt))))
		return (NULL);
	pnt->x = x;
	pnt->y = y;
	pnt->up = NULL;
	pnt->down = NULL;
	pnt->next = NULL;
	if (before)
	
	if (above)
		above->down = pnt;
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
		if (pnt->next)
		{
			if (x == pnt->x)
				above = pnt;
			pnt = pnt->next;
		}
		if (x != 0)
			if (!(pnt->next = populate(x, y, z, above, pnt)))
				return (NULL);
		else
			if (!(head = populate(x, y, z, above, NULL)))
				return (NULL);
	}
	else
		if (!(head = populate(x, y, z, above, NULL)))
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
}

//make a linked list of every variable with connecting pointers
//read files with get next line, then send them one by one into a create_pnt function
//or something FUCK
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
}

int	main(int ac, char **av)
{
	int		fd;
	t_pnt	*head;
	char	*str;

	fd = open(av[1], O_RDONLY);
	if (!(fd = open(av[1], O_RDONLY)) || ac != 2 || !(head = convert_check(fd)))
	{
		if (ac != 2)
			ft_putendl("Usage: ./fillit target_filename");
		else
			ft_putstr("error\n");
		return (0);
	}
	free(str);
	return (0);
}

// // void	array_print(t_grid *grid)
// // {
// // 	int i = 0;
// // 	int x = 0;
// // 	while (i < grid->height)
// // 	{
// // 		while (x < grid->width)
// // 		{
// // 			printf("%3d ", *grid->numarray++);
// // 			x++;
// // 		}
// // 		printf("\n");
// // 		i++;
// // 		x = 0;
// // 	}
// // }

// // char		*readfile(int fd)
// // {
// // 	char	*tmp;
// // 	char	*gnl;
// // 	char	*str;
// // 	int		i;
// // 	int		ret;

// // 	tmp = NULL;
// // 	str = ft_strnew(0);
// // 	while ((ret = get_next_line(fd, &gnl)) > 0)
// // 	{
// // 		tmp = ft_strjoin(str, gnl);
// // 		free(str);
// // 		str = ft_strjoin(tmp, "\n");
// // 		ft_strdel(&tmp);
// // 	}
// // 	free(gnl);
// // 	return (str);
// // }

// // int		str_check(char *str)
// // {
// // 	int i;

// // 	i = 0;
// // 	while (str[i])
// // 	{
// // 		if (str[i] == ',' && str[i + 1] == '0' && str[i + 2] == 'x')
// // 			i += 9;
// // 		if (str[i] != ' ' && str[i] != '\n' && str[i] != '-' && !ft_isdigit(str[i]))
// // 			return (0);
// // 		i++;
// // 	}
// // 	return (1);
// // }

// // int	main(int ac, char **av)
// // {
// // 	int		fd;
// // 	t_grid	*grid;
// // 	char	*str;

// 	fd = open(av[1], O_RDONLY);
// 	if (!(fd = open(av[1], O_RDONLY)) || ac != 2 || !(str = readfile(fd)) ||
// 	!str_check(str) || !(grid = parse_grid(str)))
// 	{
// 		if (ac != 2)
// 			ft_putendl("Usage: ./fillit target_filename");
// 		else
// 			ft_putstr("error\n");
// 		return (0);
// 	}
// 	free(str);
// 	array_print(grid);
// 	return (0);
// }

// TAKES A STR AND OUTPUTS AN ARRAY OF INTS
// t_grid	*parse_grid(char *str)
// {
// 	int		i;
// 	int		x;
// 	t_grid	*grid;

// 	if (!(grid = ft_memalloc(sizeof(t_grid))) || !(grid->numarray = \
// 	ft_memalloc(4 * ((ft_strnchr(str, ' ') + ft_strnchr(str, '\n'))))))
// 		return (NULL);
// 	grid->width = 1;
// 	grid->height = 0;
// 	x = -1;
// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (grid->height == 0)
// 			if (str[i] == ' ')
// 				grid->width += 1;
// 		if (str[i] == '\n')
// 			grid->height += 1;
// 		if (str[i] == '-' || (str[i] >= '0' && str[i] <= '9'))
// 		{
// 			grid->numarray[++x] = ft_getnxtnbr(&str[i], ',');
// 			while (!ft_isspace(str[i + 1]) && str[i + 1])
// 				i++;
// 		}
// 		if (str[i + 1] == ' ' && (str[i] == ' ' || str[i + 2] == '\n'))
// 			i++;
// 	}
// 	printf("string:\n%s\n\nwidth: %d\nheight: %d\n\n", str, grid->width, grid->height);
// 	return(grid);
// }