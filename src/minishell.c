/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:53:16 by bpires-r          #+#    #+#             */
/*   Updated: 2025/08/17 15:03:18 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	sig;

void    msh_loop(t_minishell *data)
{
	char *line;

	while (1)
	{
		init_interactive_signals();
		line = readline(data->prompt);
		if (sig)
		{
			data->exit_code = 128 + sig;
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
