/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:53:16 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/11 22:28:51 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig;

void	msh_loop(t_minishell *data)
{
	char	*line;

	while (1)
	{
		line = readline(data->prompt);
		if (g_sig)
		{
			init_interactive_signals('i');
			data->exit_code = 130;
			g_sig = 0;
		}
		if (!line)
		{
			ft_putendl_fd("exit", 1);
			rl_clear_history();
			exit_msh(data, 0);
		}
		if (*line)
		{
			init_interactive_signals('i');
			add_history(line);
			data->exit_code = lexer(line, data);
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;

	(void)argv;
	(void)envp;
	if (argc != 1)
		return (ft_putendl_fd(WRONG_ARGC, 2), 1);
	data_init(&data, envp);
	init_interactive_signals('i');
	msh_loop(&data);
	exit_msh(&data, 0);
	return (0);
}
