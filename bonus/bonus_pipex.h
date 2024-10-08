/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:30:58 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/22 21:14:50 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_PIPEX_H
# define BONUS_PIPEX_H

# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define _OPEN_MAX 10240
# define BUFFER_SIZE 5000
# define READ_END 0
# define WRITE_END 1
# define INFILE_NAME ".heredoc_file"

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
	int		fd[2];
	int		pre_pipe[2];
	int		heredoc_flag;
}	t_info;

// util_libft
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
// util_split
char	**ft_split(char const *s, char c);
// util_pipex
void	ft_execve(char *filepath, char **av, char **envp);
void	ft_dup2(int old_fd, int new_fd);
pid_t	ft_fork(void);
void	ft_pipe(int *fd);
void	ft_error(char *str);
// get_next_line
char	*get_next_line(int fd);
char	*ft_strdup(const char *src);
void	free_all(char *a, char *b);
int		ft_linelen(const char *s);
char	*ft_strjoin(char *join_buff, char *tmp, int tmp_len);
// bonus_set
void	here_doc_set(int ac, char **av, t_info *info, char **env);
void	multi_pipe_set(int ac, char **av, t_info *info, char **env);
// bonus_exec
void	bonus_pipe_exec(t_info *info, char **env, int index);
// bonus_child
void	child_process(int index, t_info *info, char **env);

#endif