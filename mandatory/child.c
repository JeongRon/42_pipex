/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:22:41 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/22 19:45:56 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	filepath_init(char *path)
{
	int	i;

	i = -1;
	while (++i < BUFFER_SIZE)
	{
		path[i] = 0;
	}
}

static int	filepath_search(t_info info, char *cmd, char *filepath, int i)
{
	if (access(cmd, F_OK) == 0)
		return (0);
	if (info.cmd_path == 0)
	{
		perror("Cmd Not Found");
		exit(EXIT_FAILURE);
	}
	while (info.cmd_path[++i] != NULL)
	{
		filepath_init(filepath);
		ft_strlcat(filepath, info.cmd_path[i], ft_strlen(info.cmd_path[i]) + 1);
		ft_strlcat(filepath, "/", ft_strlen(filepath) + 2);
		ft_strlcat(filepath, cmd, ft_strlen(filepath) + ft_strlen(cmd) + 1);
		if (access(filepath, F_OK) == 0)
			return (1);
	}
	return (0);
}

void	first_child(t_info info, int *fd, char **env)
{
	int	file_fd;
	int	file_flag;

	close(fd[READ_END]);
	ft_dup2(fd[WRITE_END], STDOUT_FILENO);
	close(fd[WRITE_END]);
	file_fd = open(info.infile, O_RDONLY, 0600);
	if (file_fd == -1)
	{
		perror("Infile Open Error");
		exit(EXIT_FAILURE);
	}
	ft_dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	file_flag = filepath_search(info, info.cmd_first[0], info.file_path, -1);
	if (file_flag == 0)
		ft_execve(info.cmd_first[0], info.cmd_first, env);
	else if (file_flag == 1)
		ft_execve(info.file_path, info.cmd_first, env);
}

void	second_child(t_info info, int *fd, char **env)
{
	int	file_fd;
	int	file_flag;

	ft_dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	file_fd = open(info.outfile, O_WRONLY | O_TRUNC | O_CREAT, 0600);
	if (file_fd == -1)
	{
		perror("Outfile Open Error");
		exit(EXIT_FAILURE);
	}
	ft_dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	file_flag = filepath_search(info, info.cmd_second[0], info.file_path, -1);
	if (file_flag == 0)
		ft_execve(info.cmd_second[0], info.cmd_second, env);
	else if (file_flag == 1)
		ft_execve(info.file_path, info.cmd_second, env);
}
