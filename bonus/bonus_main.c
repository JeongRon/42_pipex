/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 21:09:00 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/20 20:04:19 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

int	main(int ac, char **av, char **env)
{
	t_info	info;

	if (ft_strncmp("here_doc", av[1], 9) == 0)
	{
		if (ac != 6)
			ft_perror("Incorrect Arguments Count");
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
