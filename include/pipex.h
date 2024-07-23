/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:29:38 by lbohm             #+#    #+#             */
/*   Updated: 2024/02/02 10:18:35 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include "../lib/libft/libft.h"

// struct

typedef struct s_data
{
	char	**files;
	char	***cmd;
	char	**path;
	int		path_nbr;
	int		infile;
	int		outfile;
}				t_data;

// pipex

int		main(int argc, char **argv, char **env);
void	open_in_and_outfile(t_data *data);
void	execute_cmds(t_data data, char **envp);
void	first_cmd(t_data data, int *pfd, char **envp);
void	second_cmd(t_data data, int *pfd, char **envp);

// parsing

void	parsing(int argc, char **argv, t_data *data);
void	allocat_struct(int argc, t_data *data, int i);
void	parsing_paths(char *env, t_data *data);

//helper

void	search_env_path(char **env, t_data *data);
void	child_process(t_data data, char **cmd, char **envp);
char	*check_for_access(t_data data, char **cmd);
void	check_for_empty_str(int argc, char **argv, t_data data);

//free

void	freeall(t_data data);
void	freearr(char **arr);
void	freetripplearr(char ***arr);
void	error(char *msg, t_data data);

// error

# define ERROR_0 "Invalid number of arguments\n"
# define ERROR_1 "malloc"
# define ERROR_2 "open"
# define ERROR_3 "dup2"
# define ERROR_4 "execve"
# define ERROR_5 "pipe"
# define ERROR_6 "fork"
# define ERROR_7 "Env path not found\n"
# define ERROR_8 "access: command not found"
# define ERROR_9 "wait"
# define ERROR_10 "Empty String\n"

#endif