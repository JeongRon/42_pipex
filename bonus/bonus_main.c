/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongron <jeongron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 21:09:00 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/20 01:24:18 by jeongron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

int	main(int ac, char **av, char **env)
{
	t_info	info;

	if (ft_strncmp("here_doc", av[1], 8) == 0)
	{
		if (ac != 6)
		{
			write(1, "pipex: there are not 5 arguments\n", 33);
			exit(EXIT_FAILURE);
		}
		here_doc_set(av, &info, env);
		here_doc_exec(&info, env);
	}
	else
	{
		multi_pipe_set(ac, av, &info, env);
		multi_pipe_exec(&info, env);
	}
	exit(EXIT_SUCCESS);
}
