/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:37:19 by mhromylo          #+#    #+#             */
/*   Updated: 2024/07/05 16:50:18 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_path(char *s2)
{
	char	*s1;
	int		i;
	int		j;

	s1 = ".cub";
	i = ft_strlen_int(s1);
	j = ft_strlen_int(s2);
	while (i >= 0)
	{
		if (s1[i--] == s2[j--])
			continue ;
		else
			return (printf("Error: Wrong path to map\n"), 1);
	}
	return (0);
}

int	close_game(t_game *game)
{	
	int i;

	i = 0;
	if (game->map)
	{
		while (game->map[i])
		{
			free(game->map[i]);
			game->map[i++] = NULL;
		}
		free(game->map);
		game->map = NULL;
	}
	if (game->raycast)
		free(game->raycast);
	if (game->ceiling)
		free(game->ceiling);
	if (game->floor)
		free(game->floor);
	if(game->map_data)
		free(game->map_data);
	free(game);
	exit(0);
	return (0);
}

static void	run_mlx(t_game *game)

{
	game->win = mlx_new_window(game->mlx, S_W, S_H, "CUB 3D");
	game->img.img = mlx_new_image(game->mlx, S_W, S_H);
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	mlx_loop_hook(game->mlx, draw_world, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 1L << 0, close_after_mlx, game);
	mlx_loop(game->mlx);
}

int main(int argc, char *argv[])
{
	t_game	*game;

	if (argc != 2)
		return (printf("ADD please path to map\n"));
	if (check_path(argv[1]) == 1)
		return (0);
	game = ft_calloc(sizeof(t_game), 1);
	game->raycast = ft_calloc(sizeof(t_raycast), 1);
	map_maker(game, argv[1]);
	run_mlx(game);
	return 0;
}

void cleanup(t_game *game)
{
	if (game->north)
		free(game->north);
	if (game->east)
		free(game->east);
	if (game->south)
		free(game->south);
	if (game->west)
		free(game->west);
	
}