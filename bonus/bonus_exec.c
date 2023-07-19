/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongron <jeongron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:29:18 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/20 01:22:00 by jeongron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

static void	here_doc_infile(t_info *info)
{
	int		infile;
	char	*line;

	infile = open(INFILE_NAME, O_CREAT | O_TRUNC | O_RDWR, 0600);
	if (infile < 0)
	{
		write(1, "pipex: open error\n", 22);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			break ;
		}
		if (!ft_strncmp(info->limiter, line, ft_strlen(info->limiter)))
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
		first_child_process(info, env);
	else
	{
		close(info->fd[WRITE_END]);
		pid[1] = ft_fork();
		if (pid[1] == 0)
			last_child_process(info, env, 1);
	}
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	unlink(INFILE_NAME);
}

static pid_t	*pid_set(int cmd_cnt)
{
	pid_t	*pid;

	pid = (pid_t *)malloc(sizeof(pid_t) * cmd_cnt);
	if (!pid)
	{
		perror("pid allocated");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

static void	ft_waitpid(pid_t *pid, int cmd_cnt)
{
	int	index;

	index = -1;
	while (++index < cmd_cnt)
	{
		if (waitpid(pid[index], NULL, 0) < 0)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
	}
}

void	multi_pipe_exec(t_info *info, char **env)
{
	pid_t	*pid;
	int		index;

	pid = pid_set(info->cmd_cnt); // pid cmd 개수만큼 만들기
	index = -1;
	while (++index < info->cmd_cnt) // cmd 개수만큼 반복
	{
		if (index != info->cmd_cnt - 1) // 마지막 cmd는 pipe 만들지 않기	
			ft_pipe(info->fd);
		pid[index] = ft_fork(); // fork 복제하기
		if (pid[index] == 0)
			child_process(index, info, env);
		else
		{
			if (index != info->cmd_cnt - 1) // 마지막 fork() 파이프 x
			{
				info->pre_pipe_read = info->fd[READ_END];
				close(info->fd[WRITE_END]);
			}
		}
	}
	ft_waitpid(pid, info->cmd_cnt);
}

// void	first_child_process(t_info *info, char **env)
// {
// 	int	infile;

// 	close(info->fd[READ_END]);
// 	ft_dup2(info->fd[WRITE_END], STDOUT_FILENO);
// 	close(info->fd[WRITE_END]);
// 	infile = open(info->infile, O_RDONLY, 0600);
// 	if (infile < 0)
// 	{
// 		perror("infile open");
// 		exit(EXIT_FAILURE);
// 	}
// 	ft_dup2(infile, STDIN_FILENO);
// 	close(infile);
// 	filepath_search(info, info->cmd_all[0].cmd[0], info->file_path);
// 	ft_execve(info->file_path, info->cmd_all[0].cmd, env);
// }

// void	last_child_process(t_info *info, char **env, int index)
// {
// 	int	outfile;

// 	ft_dup2(info->pre_pipe_read, STDIN_FILENO);
// 	close(info->pre_pipe_read);
// 	outfile = open(info->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0600);
// 	if (outfile < 0)
// 	{
// 		perror("outfile open");
// 		exit(EXIT_FAILURE);
// 	}
// 	ft_dup2(outfile, STDOUT_FILENO);
// 	close(outfile);
// 	filepath_search(info, info->cmd_all[index].cmd[0], info->file_path);
// 	ft_execve(info->file_path, info->cmd_all[index].cmd, env);
// }

// void	parent_process(t_info *info, int index)
// {
// 	if (index != info->cmd_cnt - 1) // 마지막 fork() 파이프 x
// 	{
// 		info->pre_pipe_read = info->fd[READ_END];
// 		close(info->fd[WRITE_END]);
// 	}
// }

// void	middle_child_process(t_info *info, char **env, int index)
// {
// 	close(info->fd[READ_END]);
// 	ft_dup2(info->fd[WRITE_END], STDOUT_FILENO);
// 	close(info->fd[WRITE_END]);
// 	ft_dup2(info->pre_pipe_read, STDIN_FILENO);
// 	close(info->pre_pipe_read);
// 	filepath_search(info, info->cmd_all[index].cmd[0], info->file_path);
// 	ft_execve(info->file_path, info->cmd_all[index].cmd, env);
// }

// void	child_process(int index, t_info *info, char **env)
// {
// 	if (index == 0)
// 		first_child_process(&info, env);
// 	else if (index == info->cmd_cnt - 1)
// 		last_child_process(&info, env, index);
// 	else
// 		middle_child_process(&info, env, index);
// }
