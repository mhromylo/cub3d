/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:54:31 by mhromylo          #+#    #+#             */
/*   Updated: 2024/07/04 16:55:59 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	count_rows(int fd)
{
	int		i;
	char	*str;

	i = 1;
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		i++;
	}
	free(str);
	return (i);
}

static void	error_read(t_game *game)
{
	printf("Error: cant read\n");
	close_game(game);
}

void	map_load(t_game *game, char *map)
{
	int		fd;
	char	*str;
	int		i;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		error_read(game);
	game->map_height = (count_rows(fd));
	game->map_data = ft_calloc((sizeof(char *)) * (game->map_height + 1), 1);
	if (!game->map_data)
		return ;
	close(fd);
	i = 0;
	fd = open(map, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		game->map_data[i++] = ft_strdup(str);
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	close(fd);
	game->map_data[i] = NULL;
}

void	map_fix(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (game->map_data[++y])
	{
		x = -1;
		while (game->map_data[y][++x])
		{
			if (game->map_data[y][x] == '\t')
				game->map_data[y][x] = ' ';
		}
	}
}

void	map_alloc(t_game *game)

{
	game->north = line_with_path(game, "NO ", 3);
	texture_load(game, game->north, 0);
	game->south = line_with_path(game, "SO ", 3);
	texture_load(game, game->south, 1);
	game->west = line_with_path(game, "WE ", 3);
	texture_load(game, game->west, 2);
	game->east = line_with_path(game, "EA ", 3);
	texture_load(game, game->east, 3);
	game->floor = line_with_path(game, "F ", 2);
	game->ceiling = line_with_path(game, "C ", 2);
	game->floor_bit = color_handle(game->floor);
	game->ceiling_bit = color_handle(game->ceiling);
	game->map = map_create(game);
}
