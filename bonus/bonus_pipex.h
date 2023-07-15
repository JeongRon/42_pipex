/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:30:58 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/15 16:22:13 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_PIPEX_H
# define BONUS_PIPEX_H

# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define BUFFER_SIZE 5000
# define READ_END 0
# define WRITE_END 1

typedef struct s_cmd
{
	char	**cmd;
}	t_cmd;

typedef struct s_info
{
	char	infile[BUFFER_SIZE];
	char	outfile[BUFFER_SIZE];
	char	file_path[BUFFER_SIZE];
	char	limiter[BUFFER_SIZE];
	int		cmd_range[2];
	int		cmd_cnt;
	char	**cmd_path;
	t_cmd	*cmd_all;
}	t_info;

// util (libft, split, pipex)
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_execve(char *filepath, char **av, char **envp);
void	ft_dup2(int old_fd, int new_fd);
pid_t	ft_fork(void);
void	ft_pipe(int *fd);

#endif