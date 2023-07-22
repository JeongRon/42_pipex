/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:29:18 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/22 21:14:34 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

static void	ft_wait_free(pid_t *pid, int cmd_cnt)
{
	int	cnt;

	cnt = 0;
	while (cnt < cmd_cnt)
	{
		wait(NULL);
		cnt++;
	}
	free(pid);
}

static pid_t	*pid_set(int cmd_cnt)
{
	pid_t	*pid;

	pid = (pid_t *)malloc(sizeof(pid_t) * cmd_cnt);
	if (!pid)
		ft_error("PID Allocation Error");
	return (pid);
}

static void	here_doc_infile(t_info *info)
{
	int		infile;
	char	*line;

	infile = open(INFILE_NAME, O_CREAT | O_TRUNC | O_RDWR, 0600);
	if (infile == -1)
		ft_error("Infile Open Error");
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			break ;
		}
		if (!ft_strncmp(info->limiter, line, ft_strlen(info->limiter)) \
		&& (!ft_strncmp(info->limiter, line, ft_strlen(line) - 1)))
			break ;
		write(infile, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(infile);
}

static void	close_pre_pipe(t_info *info)
{
	close(info->pre_pipe[READ_END]);
	close(info->pre_pipe[WRITE_END]);
}

void	bonus_pipe_exec(t_info *info, char **env, int index)
{
	pid_t	*pid;

	if (info->heredoc_flag == 1)
		here_doc_infile(info);
	pid = pid_set(info->cmd_cnt);
	while (++index < info->cmd_cnt)
	{
		if (index > 1)
			close_pre_pipe(info);
		info->pre_pipe[0] = info->fd[READ_END];
		info->pre_pipe[1] = info->fd[WRITE_END];
		if (index != info->cmd_cnt - 1)
			ft_pipe(info->fd);
		pid[index] = ft_fork();
		if (pid[index] == 0)
			child_process(index, info, env);
	}
	close_pre_pipe(info);
	ft_wait_free(pid, info->cmd_cnt);
	if (info->heredoc_flag == 1)
		unlink(INFILE_NAME);
}
