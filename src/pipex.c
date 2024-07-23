/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:29:25 by lbohm             #+#    #+#             */
/*   Updated: 2024/02/06 10:56:13 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.files = NULL;
	data.cmd = NULL;
	data.path = NULL;
	parsing(argc, argv, &data);
	open_in_and_outfile(&data);
	search_env_path(envp, &data);
	parsing_paths(envp[data.path_nbr], &data);
	execute_cmds(data, envp);
	freeall(data);
	return (0);
}

void	open_in_and_outfile(t_data *data)
{
	data->infile = open(data->files[0], O_RDONLY);
	if (data->infile == -1)
		error(ERROR_2, *data);
	data->outfile = open(data->files[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->outfile == -1)
		error(ERROR_2, *data);
}

void	execute_cmds(t_data data, char **envp)
{
	int		pfd[2];

	if (pipe(pfd) == -1)
		error(ERROR_5, data);
	first_cmd(data, pfd, envp);
	second_cmd(data, pfd, envp);
}

void	first_cmd(t_data data, int *pfd, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		error(ERROR_6, data);
	if (pid == 0)
	{
		close(pfd[0]);
		if (dup2(data.infile, STDIN_FILENO) == -1)
			error(ERROR_3, data);
		if (dup2(pfd[1], STDOUT_FILENO) == -1)
			error(ERROR_3, data);
		child_process(data, data.cmd[0], envp);
	}
	else
	{
		if (waitpid(0, &status, 0) == -1)
			error(ERROR_9, data);
	}
}

void	second_cmd(t_data data, int *pfd, char **envp)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		error(ERROR_6, data);
	if (pid == 0)
	{
		close(pfd[1]);
		if (dup2(pfd[0], STDIN_FILENO) == -1)
			error(ERROR_3, data);
		if (dup2(data.outfile, STDOUT_FILENO) == -1)
			error(ERROR_3, data);
		child_process(data, data.cmd[1], envp);
	}
	else
	{
		close(data.infile);
		close(data.outfile);
		close(pfd[0]);
		close(pfd[1]);
		if (waitpid(0, &status, 0) == -1)
			error(ERROR_9, data);
	}
}
