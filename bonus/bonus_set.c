/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongron <jeongron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:27:55 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/20 00:11:56 by jeongron         ###   ########.fr       */
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

static void	get_cmd_all(int *cmd_range, int cmd_cnt, char **av, t_info *info)
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

void	here_doc_set(char **av, t_info *info, char **env)
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

void	multi_pipe_set(int ac, char **av, t_info *info, char **env)
{
	ft_strlcpy(info->infile, av[1], ft_strlen(av[1]) + 1);
	ft_strlcpy(info->outfile, av[ac - 1], ft_strlen(av[ac - 1]) + 1);
	info->cmd_range[0] = 2;
	info->cmd_range[1] = ac - 2;
	info->cmd_cnt = info->cmd_range[1] - info->cmd_range[0] + 1;
	info->cmd_path = get_cmd_path(env);
	if (info->cmd_path == NULL)
	{
		write(1, "pipex: PATH not found\n", 22);
		exit(EXIT_FAILURE);
	}
	get_cmd_all(info->cmd_range, info->cmd_cnt, av, info);
}
