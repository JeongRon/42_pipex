/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:45:16 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/20 14:36:43 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_cmd_path(char **env)
{
	int	index;

	index = -1;
	while (env[++index] != NULL)
	{
		if (ft_strncmp(env[index], "PATH=", 5) == 0)
			break ;
	}
	return (ft_split(&env[index][5], ':'));
}	

static void	input_info(char **av, t_info *info, char **env)
{
	ft_strlcpy(info->infile, av[1], ft_strlen(av[1]) + 1);
	info->cmd_first = ft_split(av[2], ' ');
	info->cmd_second = ft_split(av[3], ' ');
	ft_strlcpy(info->outfile, av[4], ft_strlen(av[4]) + 1);
	if (info->cmd_first[0] == NULL || info->cmd_second[0] == NULL)
	{
		perror("Command Not Found");
		exit(EXIT_FAILURE);
	}
	info->cmd_path = get_cmd_path(env);
	if (info->cmd_path == NULL)
	{
		perror("Path Not Found");
		exit(EXIT_FAILURE);
	}
}

static void	validate_ac_av(int ac, char **av)
{
	int	fd;

	if (ac != 5)
	{
		perror("Incorrect Arguments Count");
		exit(EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Can Not Read Infile");
		exit(EXIT_FAILURE);
	}
	else
		close(fd);
}

void	set_info(int ac, char **av, t_info *info, char **env)
{
	validate_ac_av(ac, av);
	input_info(av, info, env);
}
