/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:35:58 by lbohm             #+#    #+#             */
/*   Updated: 2024/02/06 12:12:13 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.files = NULL;
	data.cmd = NULL;
	data.path = NULL;
	open_in_and_outfile_bonus(argc, argv, &data);
	search_env_path(envp, &data);
	parsing_paths(envp[data.path_nbr], &data);
	execute_cmds_bonus(data, envp);
	freeall(data);
	return (0);
}

void	execute_cmds_bonus(t_data data, char **envp)
{
	int	pfd[2];
	int	i;

	i = 0;
	if (pipe(pfd) == -1)
		error(ERROR_5, data);
	first_cmd_bonus(data, data.cmd[i], pfd, envp);
	i++;
	while (data.cmd[i + 1])
	{
		next_cmd(data, data.cmd[i], envp);
		i++;
	}
	last_cmd(data, data.cmd[i], pfd, envp);
}

void	first_cmd_bonus(t_data data, char **cmd, int *pfd, char **envp)
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
		child_process(data, cmd, envp);
	}
	else
	{
		if (waitpid(0, &status, 0) == -1)
			error(ERROR_9, data);
		close(pfd[1]);
		if (dup2(pfd[0], STDIN_FILENO) == -1)
			error(ERROR_3, data);
	}
}

void	next_cmd(t_data data, char **cmd, char **envp)
{
	int	pid;
	int	status;
	int	pfd2[2];

	if (pipe(pfd2) == -1)
		error(ERROR_5, data);
	pid = fork();
	if (pid == -1)
		error(ERROR_6, data);
	if (pid == 0)
	{
		close(pfd2[0]);
		if (dup2(pfd2[1], STDOUT_FILENO) == -1)
			error(ERROR_3, data);
		child_process(data, cmd, envp);
	}
	else
	{
		if (waitpid(0, &status, 0) == -1)
			error(ERROR_9, data);
		close(pfd2[1]);
		if (dup2(pfd2[0], STDIN_FILENO) == -1)
			error(ERROR_3, data);
	}
}

void	last_cmd(t_data data, char **cmd, int *pfd, char **envp)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		error(ERROR_6, data);
	if (pid == 0)
	{
		close(pfd[1]);
		if (dup2(data.outfile, STDOUT_FILENO) == -1)
			error(ERROR_3, data);
		child_process(data, cmd, envp);
	}
	else
	{
		close(data.infile);
		close(data.outfile);
		close(pfd[0]);
		close(pfd[1]);
		if (waitpid(0, &status, 0) == -1)
			error(ERROR_9, data);
		unlink("here_doc.txt");
	}
}
