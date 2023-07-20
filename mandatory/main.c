/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 21:09:00 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/20 20:35:16 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid;
	t_info	info;
	int		i;

	set_info(ac, av, &info, env);
	ft_pipe(fd);
	pid = ft_fork();
	if (pid == 0)
		first_child(info, fd, env);
	else
	{
		close(fd[WRITE_END]);
		pid = ft_fork();
		if (pid == 0)
			second_child(info, fd, env);
		else
			close(fd[READ_END]);
	}
	i = -1;
	while (++i < 2)
		waitpid(0, NULL, 0);
	exit(EXIT_SUCCESS);
}
