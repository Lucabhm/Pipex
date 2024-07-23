/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:36:19 by lbohm             #+#    #+#             */
/*   Updated: 2024/02/01 17:11:36 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include "../lib/libft/libft.h"
# include "../lib/get_next_line/get_next_line.h"

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

//pipex_bonus

int		main(int argc, char **argv, char **envp);
void	execute_cmds_bonus(t_data data, char **envp);
void	first_cmd_bonus(t_data data, char **cmd, int *pfd, char **envp);
void	next_cmd(t_data data, char **cmd, char **envp);
void	last_cmd(t_data data, char **cmd, int *pfd, char **envp);

// helper_bonus

void	open_in_and_outfile_bonus(int argc, char **argv, t_data *data);
void	parsing_bonus(int argc, char **argv, t_data *data);
void	create_here_doc_file(int argc, char **argv, t_data *data);
void	parsing_here_doc(int argc, char **argv, t_data *data);

// parsing

void	allocat_struct(int argc, t_data *data, int i);
char	*check_for_access(t_data data, char **cmd);
void	parsing_paths(char *env, t_data *data);

//helper

void	search_env_path(char **env, t_data *data);
void	child_process(t_data data, char **cmd, char **envp);
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
# define ERROR_7 "Env path not found !\n"
# define ERROR_8 "access"
# define ERROR_9 "wait"
# define ERROR_10 "Empty String\n"

#endif