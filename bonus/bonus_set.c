/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:27:55 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/22 21:15:04 by jeongrol         ###   ########.fr       */
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
			return (ft_split(&env[index][5], ':'));
	}
	return (0);
}	

static void	get_cmd_all(int *cmd_range, int cmd_cnt, char **av, t_info *info)
{
	int	index;
	int	cmd_direction;

	index = 0;
	cmd_direction = cmd_range[0];
	info->cmd_all = (t_cmd *)malloc(sizeof(t_cmd) * (cmd_cnt + 1));
	if (!info->cmd_all)
		ft_error("cmd Allocation Error");
	while (cmd_direction <= cmd_range[1])
	{
		info->cmd_all[index].cmd = ft_split(av[cmd_direction], ' ');
		if (!info->cmd_all[index].cmd)
			ft_error("cmd Split Error");
		index++;
		cmd_direction++;
	}
	info->cmd_all[index].cmd = NULL;
}

void	here_doc_set(int ac, char **av, t_info *info, char **env)
{
	ft_strlcpy(info->limiter, av[2], ft_strlen(av[2]) + 1);
	ft_strlcpy(info->outfile, av[ac - 1], ft_strlen(av[ac - 1]) + 1);
	info->cmd_range[0] = 3;
	info->cmd_range[1] = ac - 2;
	info->cmd_cnt = info->cmd_range[1] - info->cmd_range[0] + 1;
	info->cmd_path = get_cmd_path(env);
	get_cmd_all(info->cmd_range, info->cmd_cnt, av, info);
	info->heredoc_flag = 1;
}

void	multi_pipe_set(int ac, char **av, t_info *info, char **env)
{
	ft_strlcpy(info->infile, av[1], ft_strlen(av[1]) + 1);
	ft_strlcpy(info->outfile, av[ac - 1], ft_strlen(av[ac - 1]) + 1);
	info->cmd_range[0] = 2;
	info->cmd_range[1] = ac - 2;
	info->cmd_cnt = info->cmd_range[1] - info->cmd_range[0] + 1;
	info->cmd_path = get_cmd_path(env);
	get_cmd_all(info->cmd_range, info->cmd_cnt, av, info);
	info->heredoc_flag = 0;
}
