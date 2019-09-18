/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 02:30:25 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/18 06:57:54 by jfelty           ###   ########.fr       */
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
		//free(str);
		str = ft_strjoin(tmp, "\n");
		ft_strdel(&tmp);
	}
	//free(gnl);
	return (str);
}

//	lenght is i + 1
int	**errorcheck(char *str)
{
	int		i;
	int		width;
	int		thiccness;
	int		height;
	int		**numarray;

	i = -1;
	height = ft_strnchr(str, '\n');
	thiccness = ((ft_strnchr(str, ' ') + height) / height);
	if (!(numarray = (int **)ft_memalloc(height * sizeof(int *))))	//maybe need +1?
		return (NULL);
	if (!(numarray[0] = (int *)malloc(thiccness * sizeof(int) + 1)))
		return (NULL);
	height = 0;
	width = 0;
	while (*str)
	{
		if (*str == '\n')
		{
			height++;
			width = 0;
			str++;
			if (!(numarray[height] = (int *)malloc(thiccness * sizeof(int) + 1)))
				return (NULL);
		}
		if (*str == ' ')
		{
			width++;
			str++;
		}
		if (ft_isdigit(*str))
			numarray[height][width] = ft_getnxtnbr(*&str, ' ');	//*str?
		while (*str != ' ' && *str != '\n' && *str)
			str++;
	}
	return(numarray);
}

int	main(int ac, char **av)
{
	int		fd;
	int		**numarray;

	fd = open(av[1], O_RDONLY);
	if (!(fd = open(av[1], O_RDONLY)) || ac != 2 || 
	!(numarray = errorcheck(readfile(fd))))
	{
		if (ac != 2)
			ft_putendl("Usage: ./fillit target_filename");
		else
			ft_putstr("error\n");
		return (0);
	}
	int i = 0;
	int x = 0;
	while (i < 10)
	{
		x = 0;
		while (x < 11)
		{
			ft_putnbr(numarray[i][x]);
			printf(" x:%d ", numarray[i][x]);
			x++;
		}
		i++;
		printf("i: %d\n", numarray[i][x]);
	}
	return (0);
}
