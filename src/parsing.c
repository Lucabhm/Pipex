/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:05:53 by lbohm             #+#    #+#             */
/*   Updated: 2024/02/01 17:06:50 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	parsing(int argc, char **argv, t_data *data)
{
	int	i;
	int	pos;

	i = 1;
	pos = 0;
	if (argc == 5)
	{
		check_for_empty_str(argc, argv, *data);
		allocat_struct(argc, data, 2);
		while (i < argc)
		{
			if (i == 1)
				data->files[0] = argv[i];
			else if (i + 1 == argc)
				data->files[1] = argv[i];
			else
			{
				data->cmd[pos] = ft_split(argv[i], ' ');
				pos++;
			}
			i++;
		}
	}
	else
		error(ERROR_0, *data);
}

void	allocat_struct(int argc, t_data *data, int i)
{
	data->files = (char **)malloc (3 * sizeof(char *));
	if (!(data->files))
		error(ERROR_1, *data);
	data->files[2] = NULL;
	data->cmd = (char ***)malloc ((argc - i) * sizeof(char **));
	if (!(data->cmd))
		error(ERROR_1, *data);
	data->cmd[argc - (i + 1)] = NULL;
}

void	parsing_paths(char *env, t_data *data)
{
	int	i;

	i = 0;
	while (env[i] != '/')
		i++;
	data->path = ft_split(env + i, ':');
}
