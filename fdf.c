#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include "math.h"

//DELETE
#include <stdio.h>

int g_winsize = 500;
int g_x1 = 200;
int g_x2 = 300;
int g_y1 = 100;
int g_y2 = 150;

typedef struct		s_fdf
{
	void			*mlx;
	void			*win;
	int				x1;
	int				x2;
	int				y1;
	int				y2; 
	int				color;
	struct s_fdf	*next;
}					t_fdf;

int	deal_key(int key)
{
	ft_putnbr(key);
	ft_putchar(' ');
	if (key == 53)
		exit(1);
	return (key);
}

int horizontal(t_fdf *line)
{

}

int drawline(t_fdf *line)
{
	int dx;
	int dy;
	int x;
	int y;
	int D;

	x = line->x1;
	y = line->y1;
	dx = line->x2 - line->x1;
	dy = line->y2 - line->y1;
	D = 2 * dy - dx;
	printf("dy: %d\tdx: %d", dy, dx);
	if (dx > dy && dy > 0)
		draw_lowslope(line);
	else if (dx < dy && dy > 0)
		draw_highslope(line);
	else if (dy == 0)
		draw_horizontal(line);
	else if (dx == 0)
		draw_vertical(line);
	// if (dy >= 0)
	// {
	// 	while(x < line->x2)
	// 	{
	// 		printf("D: %d\n", D);
	// 		mlx_pixel_put(line->mlx, line->win, x, y, line->color);
	// 		if (D > 0)
	// 		{
	// 			y++;
	// 			D = D - (2 * dx);
	// 		}
	// 		D = D + (2 * dy);
	// 		x++;
	// 	}
	// }
	return (1);
}

t_fdf	*populate(int x1, int x2, int y1, int y2)
{
	t_fdf	*line;

	if (!(line = ft_memalloc(sizeof(t_fdf))))
		return (NULL);
	if (!(line->mlx = mlx_init()))
		return (0);
	if (!(line->win = mlx_new_window(line->mlx, g_winsize, g_winsize, "mlx 42")))
		return (0);
	line->x1 = x1;
	line->x2 = x2;
	line->y1 = y1;
	line->y2 = y2;
	line->color = 1677215;
	line->next = NULL;
	return (line);
}

int main()
{
	t_fdf	*line;

	line = populate(g_x1, g_x2, g_y1, g_y2);
	drawline(line);
	// mlx_string_put(line->mlx, line->win, 200, 400, 0xFFFFFF, "hello");
	mlx_key_hook(line->win, deal_key, (void *)0);
	mlx_loop(line->mlx);
	return (0);
}

// cc fdf.c minilibx_macos/libmlx.a libft/libft.a -framework OpenGL -framework AppKit

