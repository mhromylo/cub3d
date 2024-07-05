/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:55:13 by mhromylo          #+#    #+#             */
/*   Updated: 2024/06/25 18:11:38 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	str_free(char **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
}

void	arr_str_free(char **arr)
{
	int	i;

	i = -1;
	if (!arr)
		return ;
	while (arr[++i])
		str_free(&arr[i]);
	free(arr);
	arr = NULL;
}

char	*ft_strdupn(const char *s1)

{
	char	*arr;
	int		i;

	i = 0;
	arr = malloc(sizeof(char) * ft_strlen_int(s1) + 1);
	if (!arr)
		return (NULL);
	while (*s1 && *s1 != '\n')
		arr[i++] = *s1++;
	arr[i] = '\0';
	return (arr);
}

static int	error_color(char **color, int i, int *x)

{
	while (color[i][*x] && color[i][*x] != '\n')
	{
		if (!ft_isdigit(color[i][*x]))
			return (1);
		(*x)++;
	}
	return (0);
}

unsigned int	color_handle(char	*color_string)
{
	char			**tmp;
	char			**color;
	unsigned int	int_color[3];
	int				i;
	int				x;

	i = -1;
	tmp = ft_split(color_string, ' ');
	color = ft_split(tmp[1], ',');
	arr_str_free(tmp);
	if (!color[0] || !color[1] || !color[2] || color[0][0] == '\n'
		|| color[1][0] == '\n' || color[2][0] == '\n')
		return (arr_str_free(color), 0);
	while (color[++i] != NULL)
	{
		x = 0;
		if (error_color(color, i, &x))
			return (arr_str_free(color), 0);
		int_color[i] = ft_atoi(color[i]);
	}
	arr_str_free(color);
	return ((int_color[0] << 16) | (int_color[1] << 8) | int_color[2]);
}
