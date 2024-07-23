/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:13:28 by lbohm             #+#    #+#             */
/*   Updated: 2024/02/02 11:01:13 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/pipex_bonus.h"

void	open_in_and_outfile_bonus(int argc, char **argv, t_data *data)
{
	if (argc > 4)
	{
		if (ft_strncmp(argv[1], "here_doc", 8))
		{
			parsing_bonus(argc, argv, data);
			check_for_empty_str(argc, argv, *data);
			data->infile = open(data->files[0], O_RDONLY);
			if (data->infile == -1)
				error(ERROR_2, *data);
		}
		else
		{
			create_here_doc_file(argc, argv, data);
			check_for_empty_str(argc, argv, *data);
		}
		data->outfile = open(data->files[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data->outfile == -1)
			error(ERROR_2, *data);
	}
	else
		error(ERROR_0, *data);
}

void	parsing_bonus(int argc, char **argv, t_data *data)
{
	int	i;
	int	pos;

	i = 1;
	pos = 0;
	if (argc > 4)
	{
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

void	create_here_doc_file(int argc, char **argv, t_data *data)
{
	int		file;
	char	*str;
	char	*tmp;

	str = "";
	parsing_here_doc(argc, argv, data);
	file = open("here_doc.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file == -1)
		error(ERROR_2, *data);
	tmp = ft_strjoin(data->files[0], "\n");
	while (str)
	{
		str = get_next_line(0);
		if (!(ft_strncmp(str, tmp, ft_strlen(str))))
			break ;
		ft_putstr_fd(str, file);
		free(str);
	}
	free(str);
	free(tmp);
	close(file);
	data->infile = open("here_doc.txt", O_RDONLY);
	if (data->infile == -1)
		error(ERROR_2, *data);
}

void	parsing_here_doc(int argc, char **argv, t_data *data)
{
	int	i;
	int	pos;

	i = 2;
	pos = 0;
	if (argc > 5)
	{
		allocat_struct(argc, data, 3);
		while (argv[i])
		{
			if (i == 2)
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
