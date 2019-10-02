/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 00:23:22 by jfelty            #+#    #+#             */
/*   Updated: 2019/10/01 17:20:13 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		initialize_image(t_grid *grid)
{
	t_img	*img;

	if (!(img = ft_memalloc(sizeof(t_img))))
		return ;
	grid->img = img;
	img->image = NULL;
	img->data = NULL;
}

t_grid		*initialize_grid(t_pnt *head)
{
	t_grid	*grid;

	if (!(grid = ft_memalloc(sizeof(t_grid))))
		return (NULL);
	if (!(grid->mlx = mlx_init()))
		return (0);
	if (!(grid->win = mlx_new_window(grid->mlx, WINX, WINY, "mlx 42")))
		return (0);
	grid->first_pnt = head;
	grid->max_x = WINX;
	grid->max_y = WINY;
	grid->height = HEIGHTSCALE;
	grid->heightdrift = HEIGHTDRIFT;
	grid->scale = calc_scale(head, grid);
	grid->render = 0;
	adjust_neg_z(head);
	scale_grid(head, grid);
	center_grid(head, grid);
	spoof_height(head, grid);
	spoof_angle(head, grid);
	color_pts(head, 0);
	initialize_image(grid);
	mlx_hook(grid->win, 2, 0, &hook_key, grid);
	return (grid);
}

int			main(int ac, char **av)
{
	int		fd;
	t_pnt	*head;
	t_grid	*grid;

	fd = open(av[1], O_RDONLY);
	if (!(fd = open(av[1], O_RDONLY)) || ac != 2)
	{
		if (ac != 2)
			ft_putendl("Usage: ./fillit target_filename");
		else
			ft_putstr("error\n");
		return (0);
	}
	if (!(head = convert_check(fd)))
		return (0);
	grid = initialize_grid(head);
	draw_lines(populate_lines(head, grid));
	mlx_loop(grid->mlx);
	return (0);
}
