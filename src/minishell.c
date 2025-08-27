/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:53:16 by bpires-r          #+#    #+#             */
/*   Updated: 2025/08/27 18:09:15 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	sig;

void    msh_loop(t_minishell *data)
{
	char *line;

	init_interactive_signals();
	while (1)
	{
		line = readline(data->prompt);
		if (sig)
		{
			init_interactive_signals();
			data->exit_code = 130;
			sig = 0;
		}
		if (!line)
		{
			ft_putendl_fd("exit", 1);
			rl_clear_history();
			exit_msh(data, 0);
		}
		if (*line)
		{
			init_interactive_signals();
			add_history(line);
			data->exit_code = lexer(line, data);
		}
		free(line);
	}
}


int main(int argc, char **argv, char **envp)
{
	t_minishell data;

	(void)argv;
	(void)envp;	
	if (argc != 1)
		return(ft_putendl_fd(WRONG_ARGC, 2), 1);
	data_init(&data, envp);
	msh_loop(&data);
	exit_msh(&data, 0);
	return (0);
}
