/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:35:11 by lbohm             #+#    #+#             */
/*   Updated: 2024/02/02 14:45:14 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	freeall(t_data data)
{
	if (data.files)
		free(data.files);
	if (data.cmd)
		freetripplearr(data.cmd);
	if (data.path)
		freearr(data.path);
}

void	freearr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	freetripplearr(char ***arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			free(arr[i][j]);
			j++;
		}
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	error(char *msg, t_data data)
{
	if (!(ft_strncmp(msg, "Invalid number of arguments\n", ft_strlen(msg)))
		|| !(ft_strncmp(msg, "Env path not found\n", ft_strlen(msg)))
		|| !(ft_strncmp(msg, "Empty String\n", ft_strlen(msg))))
		write(2, msg, ft_strlen(msg));
	else
		perror(msg);
	freeall(data);
	exit (1);
}
