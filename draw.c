/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:27:31 by mhromylo          #+#    #+#             */
/*   Updated: 2024/07/05 12:00:09 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*line_with_path(t_game *game, char *str, int len)
{
	char	**map;
	int		i;

	map = game->map_data;
	i = 0;
	while (map[i] && ft_strncmp(map[i], str, len))
		i++;
	if (!map[i])
	{
		printf("Path to texture is missing in the file\n");
		close_game(game);
	}
	return (ft_strdup(map[i]));
}

char	*make_onlypath(char *path)
{
	char	**tmp;
	char	*full_path;

	tmp = NULL;
	if (!path)
		return (NULL);
	else
		tmp = ft_split(path, ' ');
	if (tmp[1])
	{
		full_path = ft_strdupn(tmp[1]);
		free(path);
		arr_str_free(tmp);
		return (full_path);
	}
	if (path)
		free(path);
	return (NULL);
}

static void	texture_error(t_game *game, char *full_path, int i)

{
	if (i == 0)
		printf("Error: There are no path to texture\n");
	else if (i == 1)
		printf("Error: Texture allocation failed\n");
	if (full_path)
		free(full_path);
	close_game(game);
}

void	texture_load(t_game *game, char *path, int i)

{
	t_wall	*wall;
	char	*full_path;

	full_path = make_onlypath(path);
	if (!path || !full_path)
		texture_error(game, full_path, 0);
	wall = &game->wall[i];
	wall->img = malloc(sizeof(t_img));
	if (!wall->img)
		texture_error(game, full_path, 1);
	wall->img->img = mlx_xpm_file_to_image(game->mlx, full_path,
			&wall->width, &wall->height);
	if (!wall->img->img)
		texture_error(game, full_path, 1);
	wall->img->addr = mlx_get_data_addr(wall->img->img,
			&wall->img->bits_per_pixel, &wall->img->line_length,
			&wall->img->endian);
	free(full_path);
}

void	init_facing_direction(t_game *game)
{
	if (game->direction == 'W')
	{
		game->raycast->dir_x = -1;
		game->raycast->view_y = 0.66;
	}
	if (game->direction == 'S')
	{
		game->raycast->dir_y = -1;
		game->raycast->view_x = -0.66;
	}
	if (game->direction == 'E')
	{
		game->raycast->dir_x = 1;
		game->raycast->view_y = -0.66;
	}
	if (game->direction == 'N')
	{
		game->raycast->dir_y = 1;
		game->raycast->view_x = 0.66;
	}
}