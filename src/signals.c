/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:18:23 by jomanuel          #+#    #+#             */
/*   Updated: 2025/08/27 18:10:02 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_interactive_signals()
{
	set_handler(SIGINT, handle_sigint_i, 0);
	set_handler(SIGQUIT, SIG_IGN, 0);
}

void	init_interactive_signals2()
{
	set_handler(SIGINT, handle_sigint_i2, 0);
	set_handler(SIGQUIT, SIG_IGN, 0);
}

void	init_child_signals()
{
	set_handler(SIGINT, SIG_DFL, 0);
	set_handler(SIGQUIT, SIG_DFL, 0);
}

void	init_heredoc_signals()
{
	set_handler(SIGINT, handle_sigint_h, 0);
	set_handler(SIGQUIT, SIG_IGN, 0);
}

void	init_ignore_signals()
{
	set_handler(SIGINT, SIG_IGN, 0);
	set_handler(SIGQUIT, SIG_IGN, 0);
}
