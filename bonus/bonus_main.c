/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 21:09:00 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/22 21:14:42 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

int	main(int ac, char **av, char **env)
{
	t_info	info;

	if (ac < 5)
		ft_error("Incorrect Arguments Count");
	if (ft_strncmp("here_doc", av[1], 9) == 0)
		here_doc_set(ac, av, &info, env);
	else
		multi_pipe_set(ac, av, &info, env);
	bonus_pipe_exec(&info, env, -1);
	exit(EXIT_SUCCESS);
}
