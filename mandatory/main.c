/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 21:09:00 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/20 14:25:03 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid[2];
	t_info	info;

	set_info(ac, av, &info, env);
	ft_pipe(fd);
	pid[0] = ft_fork();
	if (pid[0] == 0)
		first_child(info, fd, env);
	else
	{
		close(fd[WRITE_END]);
		pid[1] = ft_fork();
		if (pid[1] == 0)
			second_child(info, fd, env);
		else
			close(fd[READ_END]);
	}
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	exit(EXIT_SUCCESS);
}
