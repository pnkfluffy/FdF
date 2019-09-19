/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 02:30:25 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/19 03:52:56 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char		*readfile(int fd)
{
	char	*tmp;
	char	*gnl;
	char	*str;
	int		i;
	int		ret;

	tmp = NULL;
	str = ft_strnew(0);
	while ((ret = get_next_line(fd, &gnl)) > 0)
	{
		tmp = ft_strjoin(str, gnl);
		free(str);
		str = ft_strjoin(tmp, "\n");
		ft_strdel(&tmp);
	}
	free(gnl);
	return (str);
}

//check that number of points == len * width
int		errorcheck(t_grid *grid)
{
	return (1);
}

//	lenght is i + 1
t_grid	*parse_grid(char *str)
{
	int		i;
	int		x;
	t_grid	*grid;

	printf("string:\n%s\n", str);
	if (!(grid = ft_memalloc(sizeof(t_grid))) || !(grid->numarray =  \
	ft_memalloc(4 * ((ft_strnchr(str, ' ') + ft_strnchr(str, '\n'))))))
		return (NULL);
	grid->width = 1;
	grid->height = 0;
	x = -1;
	i = -1;
	while (str[++i])
	{
		if (grid->height == 0)
			if (str[i] == ' ')
				grid->width += 1;
		if (str[i] == '\n')
			grid->height += 1;
		if (str[i] == '-' || (str[i] >= '0' && str[i] <= '9'))
		{
			grid->numarray[++x] = ft_getnxtnbr(&str[i], ' ');
			while (!ft_isspace(str[i + 1]) && str[i + 1])
				i++;
		}
		if (ft_isspace(str[i]) && ft_isspace(str[i + 1]))
			i++;
	}
	printf("\nwidth:  %d", grid->width);
	printf("\nheight: %d\n", grid->height);
	return(grid);
}

int	main(int ac, char **av)
{
	int		fd;
	t_grid	*grid;
//	int		**numarray;

	fd = open(av[1], O_RDONLY);
	if (!(fd = open(av[1], O_RDONLY)) || ac != 2 || 
	!(grid = parse_grid(readfile(fd))) || !errorcheck(grid))
	{
		if (ac != 2)
			ft_putendl("Usage: ./fillit target_filename");
		else
			ft_putstr("error\n");
		return (0);
	}
	int i = 0;
	int x = 0;
	while (i < grid->height)
	{
		while (x < grid->width)
		{
			printf("%3d ", *grid->numarray++);
			x++;
		}
		printf("\n");
		i++;
		x = 0;
	}
}

// //	lenght is i + 1
// int	**errorcheck(char *str)
// {
// 	int		i;
// 	int		width;
// 	int		thiccness;
// 	int		height;
// 	int		**numarray;

// 	i = -1;
// 	height = ft_strnchr(str, '\n');
// 	thiccness = ((ft_strnchr(str, ' ') + height) / height);
// 	if (!(numarray = (int **)ft_memalloc(height * sizeof(int *))))	//maybe need +1?
// 		return (NULL);
// 	if (!(numarray[0] = (int *)malloc(thiccness * sizeof(int) + 1)))
// 		return (NULL);
// 	height = 0;
// 	width = 0;
// 	while (*str)
// 	{
// 		if (*str == '\n')
// 		{
// 			height++;
// 			width = 0;
// 			str++;
// 			if (!(numarray[height] = (int *)malloc(thiccness * sizeof(int) + 1)))
// 				return (NULL);
// 		}
// 		if (*str == ' ')
// 		{
// 			width++;
// 			str++;
// 		}
// 		if (ft_isdigit(*str))
// 			numarray[height][width] = ft_getnxtnbr(*&str, ' ');	//*str?
// 		while (*str != ' ' && *str != '\n' && *str)
// 			str++;
// 	}
// 	return(numarray);
// }

// int	main(int ac, char **av)
// {
// 	int		fd;
// 	int		**numarray;

// 	fd = open(av[1], O_RDONLY);
// 	if (!(fd = open(av[1], O_RDONLY)) || ac != 2 || 
// 	!(numarray = errorcheck(readfile(fd))))
// 	{
// 		if (ac != 2)
// 			ft_putendl("Usage: ./fillit target_filename");
// 		else
// 			ft_putstr("error\n");
// 		return (0);
// 	}
// 	int i = 0;
// 	int x = 0;
// 	while (i < 10)
// 	{
// 		x = 0;
// 		while (x < 11)
// 		{
// 			ft_putnbr(numarray[i][x]);
// 			printf(" x:%d ", numarray[i][x]);
// 			x++;
// 		}
// 		i++;
// 		printf("i: %d\n", numarray[i][x]);
// 	}
// 	return (0);
// }