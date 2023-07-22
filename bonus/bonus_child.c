/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:12:56 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/22 21:21:13 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

static int	filepath_search(t_info *info, char *cmd, char *filepath)
{
	int	i;
	int	j;
	int	length;

	if (access(cmd, F_OK) == 0)
		return (0);
	if (info->cmd_path == 0)
		ft_error("Cmd Not Found");
	i = -1;
	while (info->cmd_path[++i] != NULL)
	{
		j = -1;
		while (++j < BUFFER_SIZE)
			filepath[j] = 0;
		length = ft_strlen(info->cmd_path[i]) + 1;
		ft_strlcat(filepath, info->cmd_path[i], length);
		ft_strlcat(filepath, "/", ft_strlen(filepath) + 2);
		ft_strlcat(filepath, cmd, ft_strlen(filepath) + ft_strlen(cmd) + 1);
		if (access(filepath, F_OK) == 0)
			return (1);
	}
	write(2, "Cmd Access Error\n", 17);
	exit(EXIT_FAILURE);
}

static void	first_child_process(t_info *info, char **env)
{
	int	infile;
	int	file_flag;

	close(info->fd[READ_END]);
	ft_dup2(info->fd[WRITE_END], STDOUT_FILENO);
	close(info->fd[WRITE_END]);
	if (info->heredoc_flag == 1)
		infile = open(INFILE_NAME, O_RDONLY, 0600);
	else
		infile = open(info->infile, O_RDONLY, 0600);
	if (infile == -1)
		ft_error("Infile Open Error");
	ft_dup2(infile, STDIN_FILENO);
	close(infile);
	file_flag = filepath_search(info, info->cmd_all[0].cmd[0], info->file_path);
	if (file_flag == 0)
		ft_execve(info->cmd_all[0].cmd[0], info->cmd_all[0].cmd, env);
	else
		ft_execve(info->file_path, info->cmd_all[0].cmd, env);
}

static void	middle_child_process(t_info *info, char **env, int i)
{
	int	file_flag;

	close(info->fd[READ_END]);
	ft_dup2(info->fd[WRITE_END], STDOUT_FILENO);
	close(info->fd[WRITE_END]);
	ft_dup2(info->pre_pipe[0], STDIN_FILENO);
	close(info->pre_pipe[0]);
	close(info->pre_pipe[1]);
	file_flag = filepath_search(info, info->cmd_all[i].cmd[0], info->file_path);
	if (file_flag == 0)
		ft_execve(info->cmd_all[i].cmd[0], info->cmd_all[i].cmd, env);
	else
		ft_execve(info->file_path, info->cmd_all[i].cmd, env);
}

static void	last_child_process(t_info *info, char **env, int i)
{
	int	outfile;
	int	file_flag;

	ft_dup2(info->pre_pipe[0], STDIN_FILENO);
	close(info->pre_pipe[0]);
	close(info->pre_pipe[1]);
	if (info->heredoc_flag == 1)
		outfile = open(info->outfile, O_WRONLY | O_APPEND | O_CREAT, 0600);
	else
		outfile = open(info->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0600);
	if (outfile == -1)
		ft_error("Outfile Open Error");
	ft_dup2(outfile, STDOUT_FILENO);
	close(outfile);
	file_flag = filepath_search(info, info->cmd_all[i].cmd[0], info->file_path);
	if (file_flag == 0)
		ft_execve(info->cmd_all[i].cmd[0], info->cmd_all[i].cmd, env);
	else
		ft_execve(info->file_path, info->cmd_all[i].cmd, env);
}

void	child_process(int i, t_info *info, char **env)
{
	if (i == 0)
		first_child_process(info, env);
	else if (i == info->cmd_cnt - 1)
		last_child_process(info, env, i);
	else
		middle_child_process(info, env, i);
}
