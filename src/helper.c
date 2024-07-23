/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:30:07 by lbohm             #+#    #+#             */
/*   Updated: 2024/02/06 12:57:51 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	search_env_path(char **env, t_data *data)
{
	int	i;

	i = 0;
	data->path_nbr = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			data->path_nbr = i;
			break ;
		}
		i++;
	}
	if (!(env[i]))
		error(ERROR_7, *data);
}

void	child_process(t_data data, char **cmd, char **envp)
{
	char	*path;

	path = check_for_access(data, cmd);
	if (!(path))
		error(ERROR_8, data);
	else
		if (execve(path, cmd, envp) == -1)
			error(ERROR_4, data);
}

char	*check_for_access(t_data data, char **cmd)
{
	int		i;
	char	*newpath;
	char	*tmp;

	i = 0;
	while (data.path[i])
	{
		tmp = ft_strjoin(data.path[i], "/");
		newpath = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(newpath, X_OK) == -1)
		{
			i++;
			free(newpath);
		}
		else
			return (newpath);
	}
	return (NULL);
}

void	check_for_empty_str(int argc, char **argv, t_data data)
{
	int	i;
	int	j;
	int	space;

	i = 0;
	while (argc > i)
	{
		j = 0;
		space = 0;
		if (!(ft_strncmp(argv[i], "", ft_strlen(argv[i]))))
			error(ERROR_10, data);
		while (argv[i][j])
		{
			if (argv[i][j] == ' ')
				space++;
			j++;
		}
		if (space == (int)ft_strlen(argv[i]))
			error(ERROR_10, data);
		i++;
	}
}
