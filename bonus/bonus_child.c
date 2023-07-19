/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongron <jeongron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:12:56 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/20 01:24:10 by jeongron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

static void	filepath_search(t_info *info, char *cmd, char *filepath)
{
	int	index;
	int	i;

	index = -1;
	while (info->cmd_path[++index] != NULL)
	{
		i = -1;
		while (++i < BUFFER_SIZE)
			filepath[i] = 0;
		ft_strlcat(filepath, info->cmd_path[index], ft_strlen(info->cmd_path[index]) + 1);
		ft_strlcat(filepath, "/", ft_strlen(filepath) + 2);
		ft_strlcat(filepath, cmd, ft_strlen(filepath) + ft_strlen(cmd) + 1);
		if (access(filepath, F_OK) == 0)
			return ;
	}
	perror("cmd access");
	exit(EXIT_FAILURE);
}

void	first_child_process(t_info *info, char **env)
{
	int	infile;

	close(info->fd[READ_END]);
	ft_dup2(info->fd[WRITE_END], STDOUT_FILENO);
	close(info->fd[WRITE_END]);
	infile = open(info->infile, O_RDONLY, 0600);
	if (infile < 0)
	{
		perror("infile open");
		exit(EXIT_FAILURE);
	}
	ft_dup2(infile, STDIN_FILENO);
	close(infile);
	filepath_search(info, info->cmd_all[0].cmd[0], info->file_path);
	ft_execve(info->file_path, info->cmd_all[0].cmd, env);
}

void	last_child_process(t_info *info, char **env, int index)
{
	int	outfile;

	ft_dup2(info->pre_pipe_read, STDIN_FILENO);
	close(info->pre_pipe_read);
	outfile = open(info->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0600);
	if (outfile == -1)
	{
		perror("outfile open");
		exit(EXIT_FAILURE);
	}
	ft_dup2(outfile, STDOUT_FILENO);
	close(outfile);
	filepath_search(info, info->cmd_all[index].cmd[0], info->file_path);
	ft_execve(info->file_path, info->cmd_all[index].cmd, env);
}

void	middle_child_process(t_info *info, char **env, int index)
{
	close(info->fd[READ_END]);
	ft_dup2(info->fd[WRITE_END], STDOUT_FILENO);
	close(info->fd[WRITE_END]);
	ft_dup2(info->pre_pipe_read, STDIN_FILENO);
	close(info->pre_pipe_read);
	filepath_search(info, info->cmd_all[index].cmd[0], info->file_path);
	ft_execve(info->file_path, info->cmd_all[index].cmd, env);
}

void	child_process(int index, t_info *info, char **env)
{
	if (index == 0)
		first_child_process(info, env);
	else if (index == info->cmd_cnt - 1)
		last_child_process(info, env, index);
	else
		middle_child_process(info, env, index);
}
