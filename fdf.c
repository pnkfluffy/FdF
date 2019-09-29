/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 00:23:22 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/29 00:15:15 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//REMOVE AFTER FIXING COLORS
void	color_pts(t_pnt *head, t_grid *grid)
{
	t_pnt	*pnt;

	pnt = head;
	while (pnt)
	{
		pnt->color = (MAXCOLOR * (double)(pnt->z + 1) / grid->max_pnt_height);
		if (grid->max_pnt_height == 0)
			pnt->color = 0xFFFFFF;
		// else
		// 	pnt->color = (pnt->z * 500) % 16777215;
		pnt = pnt->next;
	}
}

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
	grid->max_x = WINX;
	grid->max_y = WINY;
	grid->height = HEIGHTSCALE;
	grid->heightdrift = HEIGHTDRIFT;
	grid->scale = calc_scale(head, grid);
	adjust_neg_z(head);
	scale_grid(head, grid);
	center_grid(head, grid);
	spoof_height(head, grid);
	spoof_angle(head, grid);
	color_pts(head, grid);
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
	if (!(fd = open(av[1], O_RDONLY)) || ac != 2 || !(head = convert_check(fd)))
	{
		if (ac != 2)
			ft_putendl("Usage: ./fillit target_filename");
		else
			ft_putstr("error\n");
		return (0);
	}
	grid = initialize_grid(head);
	draw_lines(populate_lines(head, grid));
//	print_params(head);
//	draw_points(head, grid);
//	draw_phat_points(head, grid);
	mlx_loop(grid->mlx);
	return (0);
}
