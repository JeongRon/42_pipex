/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:29:18 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/22 16:07:43 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

static void	ft_waitpid(pid_t *pid, int cmd_cnt)
{
	int	index;

	index = -1;
	while (++index < cmd_cnt)
	{
		if (waitpid(0, NULL, 0) < 0)
			ft_perror("waitpid Error");
	}
	free(pid);
}

static pid_t	*pid_set(int cmd_cnt)
{
	pid_t	*pid;

	pid = (pid_t *)malloc(sizeof(pid_t) * cmd_cnt);
	if (!pid)
		ft_perror("PID Allocation Error");
	return (pid);
}

static void	here_doc_infile(t_info *info)
{
	int		infile;
	char	*line;

	infile = open(INFILE_NAME, O_CREAT | O_TRUNC | O_RDWR, 0600);
	if (infile == -1)
		ft_perror("Infile Open Error");
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

void	here_doc_exec(t_info *info, char **env)
{
	pid_t	pid[2];

	here_doc_infile(info);
	ft_pipe(info->fd);
	pid[0] = ft_fork();
	if (pid[0] == 0)
		first_child_process(info, env, 0);
	else
	{
		close(info->fd[WRITE_END]);
		pid[1] = ft_fork();
		if (pid[1] == 0)
			last_child_process(info, env, 1, 0);
		else
			close(info->fd[READ_END]);
	}
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	unlink(INFILE_NAME);
}

void	multi_pipe_exec(t_info *info, char **env)
{
	pid_t	*pid;
	int		index;

	pid = pid_set(info->cmd_cnt);
	index = -1;
	while (++index < info->cmd_cnt)
	{
		if (index != info->cmd_cnt - 1)
			ft_pipe(info->fd);
		pid[index] = ft_fork();
		if (pid[index] == 0)
			child_process(index, info, env);
		else
		{
			if (index != info->cmd_cnt - 1)
			{
				info->pre_pipe_read = info->fd[READ_END];
				close(info->fd[WRITE_END]);
			}
		}
	}
	close(info->fd[READ_END]);
	ft_waitpid(pid, info->cmd_cnt);
}
