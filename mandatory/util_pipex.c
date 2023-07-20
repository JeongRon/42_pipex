/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:23:55 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/20 14:37:43 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execve(char *filepath, char **av, char **envp)
{
	if (execve(filepath, av, envp) == -1)
	{
		perror("Execve Error");
		exit(EXIT_FAILURE);
	}
}

void	ft_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("Dup2 Error");
		exit(EXIT_FAILURE);
	}
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork Error");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	ft_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("Pipe Error");
		exit(0);
	}
}
