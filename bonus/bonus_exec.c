/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:29:18 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/18 21:48:38 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

void	here_doc_infile(t_info info)
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
		if (!ft_strncmp(info.limiter, line, ft_strlen(info.limiter)))
			break ;
		write(infile, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(infile);
}

void	here_doc_exec(t_info info, char **env)
{
	int		fd[2];
	pid_t	pid[2];

	here_doc_infile(info);
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
	}
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	unlink(INFILE_NAME);
}

// void	multi_pipe_exec(t_info info, char **env)
// {
	
// }
