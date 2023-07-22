/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:23:55 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/22 21:08:05 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execve(char *filepath, char **av, char **envp)
{
	if (execve(filepath, av, envp) == -1)
	{
		write(2, "bash : Command not found\n", 25);
		exit(EXIT_FAILURE);
	}
}

void	ft_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		write(2, "Dup2 Error\n", 11);
		exit(EXIT_FAILURE);
	}
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		write(2, "Fork Error\n", 11);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	ft_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		write(2, "Pipe Error", 10);
		exit(EXIT_FAILURE);
	}
}
