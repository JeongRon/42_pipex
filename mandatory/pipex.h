/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:30:58 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/20 19:37:21 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define BUFFER_SIZE 5000
# define READ_END 0
# define WRITE_END 1

typedef struct s_info
{
	char	infile[BUFFER_SIZE];
	char	outfile[BUFFER_SIZE];
	char	file_path[BUFFER_SIZE];
	char	**cmd_path;
	char	**cmd_first;
	char	**cmd_second;
}	t_info;

// util (libft, split, pipex)
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
void	ft_execve(char *filepath, char **av, char **envp);
void	ft_dup2(int old_fd, int new_fd);
pid_t	ft_fork(void);
void	ft_pipe(int *fd);

// set_info.c
void	set_info(int ac, char **av, t_info *info, char **env);

// child.c
void	first_child(t_info info, int *fd, char **env);
void	second_child(t_info info, int *fd, char **env);

#endif