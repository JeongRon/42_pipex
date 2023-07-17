/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 21:09:00 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/17 16:00:07 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

static char	**get_cmd_path(char **env)
{
	int	index;

	index = -1;
	while (env[++index] != NULL)
	{
		if (ft_strncmp(env[index], "PATH=", 5) == 0)
			break ;
	}
	return (ft_split(&env[index][5], ':'));
}	

void	get_cmd_all(int *cmd_range, int cmd_cnt, char **av, t_info *info)
{
	int	index;
	int	cmd_direction;

	index = 0;
	cmd_direction = cmd_range[0];
	info->cmd_all = (t_cmd *)malloc(sizeof(t_cmd) * (cmd_cnt + 1));
	if (!info->cmd_all)
	{
		write(1, "pipex: cmd allocation fail\n", 27);
		exit(EXIT_FAILURE);
	}
	while (cmd_direction <= cmd_range[1])
	{
		info->cmd_all[index].cmd = ft_split(av[cmd_direction], ' ');
		if (!info->cmd_all[index].cmd)
		{
			write(1, "pipex: cmd allocation fail OR cmd not found\n", 44);
			exit(EXIT_FAILURE);
		}
		index++;
		cmd_direction++;
	}
	info->cmd_all[index].cmd = NULL;
}

void	here_doc_set(int ac, char **av, t_info *info, char **env)
{
	ft_strlcpy(info->outfile, av[5], ft_strlen(av[5]) + 1);
	ft_strlcpy(info->limiter, av[2], ft_strlen(av[2]) + 1);
	info->cmd_range[0] = 3;
	info->cmd_range[1] = 4;
	info->cmd_cnt = 2;
	info->cmd_path = get_cmd_path(env);
	if (info->cmd_path == NULL)
	{
		write(1, "pipex: PATH not found\n", 22);
		exit(EXIT_FAILURE);
	}
	get_cmd_all(info->cmd_range, info->cmd_cnt, av, info);
}

void	here_doc_exec(t_info *info)
{
	int		infile;
	char	*line;

	infile = open(".heredoc_file", O_CREAT | O_TRUNC | O_RDWR, 0600);
	if (infile < 0)
	{
		write(1, "pipex: open error\n", 22);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		write(1, ">", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			write(1, "pipex: gnl allocated error\n", 27);
			exit(EXIT_FAILURE);
		}
		if (!ft_strncmp(info->limiter, line, ft_strlen(info->limiter)))
			break ;
		write(infile, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(infile);
}

int	main(int ac, char **av, char **env)
{
	t_info	info;

	if (ft_strncmp("here_doc", av[1], 8) == 0)
	{
		if (ac != 6)
		{
			write(1, "pipex: there are not 5 arguments\n", 33);
			exit(EXIT_FAILURE);
		}
		here_doc_set(ac, av, &info, env);
		here_doc_exec(&info);
	}
	else
	{
		// multi_pipe_set();
		// multi_pipe_exec();
	}
	exit(EXIT_SUCCESS);
}
