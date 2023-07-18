/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:12:56 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/18 20:57:36 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

static void	filepath_init(char *path)
{
	int	i;

	i = -1;
	while (++i < BUFFER_SIZE)
	{
		path[i] = 0;
	}
}

static void	filepath_search(t_info info, char *cmd, char *filepath)
{
	int	i;

	i = -1;
	while (info.cmd_path[++i] != NULL)
	{
		filepath_init(filepath);
		ft_strlcat(filepath, info.cmd_path[i], ft_strlen(info.cmd_path[i]) + 1);
		ft_strlcat(filepath, "/", ft_strlen(filepath) + 2);
		ft_strlcat(filepath, cmd, ft_strlen(filepath) + ft_strlen(cmd) + 1);
		if (access(filepath, F_OK) == 0)
			return ;
	}
	perror("cmd access");
	exit(EXIT_FAILURE);
}

void	first_child(t_info info, int *fd, char **env)
{
	int	file_fd;

	close(fd[READ_END]);
	ft_dup2(fd[WRITE_END], STDOUT_FILENO);
	close(fd[WRITE_END]);
	file_fd = open(INFILE_NAME, O_RDONLY, 0600);
	if (file_fd != -1)
	{
		ft_dup2(file_fd, STDIN_FILENO);
		close(file_fd);
	}
	filepath_search(info, info.cmd_all[0].cmd[0], info.file_path);
	ft_execve(info.file_path, info.cmd_all[0].cmd, env);
}

void	second_child(t_info info, int *fd, char **env)
{
	int	file_fd;

	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	file_fd = open(info.outfile, O_WRONLY | O_TRUNC | O_CREAT, 0600);
	if (file_fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	filepath_search(info, info.cmd_all[1].cmd[0], info.file_path);
	ft_execve(info.file_path, info.cmd_all[1].cmd, env);
	exit(EXIT_SUCCESS);
}
