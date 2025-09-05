/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:18:23 by jomanuel          #+#    #+#             */
/*   Updated: 2025/09/05 19:23:24 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_interactive_signals(char flag)
{
	if (flag == 'i')
	{
		set_handler(SIGINT, handle_sigint_i, 0);
		set_handler(SIGQUIT, SIG_IGN, 0);
	}
	else
	{
		set_handler(SIGINT, handle_sigint_i_h, 0);
		set_handler(SIGQUIT, SIG_IGN, 0);
	}
}

void	init_child_signals(void)
{
	set_handler(SIGINT, SIG_DFL, 0);
	set_handler(SIGQUIT, SIG_DFL, 0);
}

void	init_heredoc_signals(void)
{
	set_handler(SIGINT, handle_sigint_h, 0);
	set_handler(SIGQUIT, SIG_IGN, 0);
}

void	init_ignore_signals(void)
{
	set_handler(SIGINT, SIG_IGN, 0);
	set_handler(SIGQUIT, SIG_IGN, 0);
}
