/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:53:16 by bpires-r          #+#    #+#             */
/*   Updated: 2025/06/06 18:54:24 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Sempre que eu me referir a uma variavel de struct 
//como data geralmente significa a struct "principal"
//que interliga a todas as outras structs
/*void    msh_loop(t_minishell *data)
{
	char *line;
	while (1)
	{
		line = readline(data->prompt);
		if (!line)
		{
			ft_putendl_fd("exit", 1);
			rl_clear_history();
			exit_msh(data, 0);
		}
		if (!*line)
		{
			free(line);
			continue ;
		}
		add_history(line);
		data->exit_code = lexer(line);
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
	data_init(&data);
	msh_loop(&data);
	return (0);
}*/
