/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:27:57 by jomanuel          #+#    #+#             */
/*   Updated: 2025/08/27 18:10:19 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_handler(int signum, void (*handler)(int), int flags)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = flags;
	sa.sa_handler = handler;
	sigaction(signum, &sa, NULL);
}

void	handle_child_sig(int signo)
{
	int	signal;

	signal = WTERMSIG(signo);
	if (WIFSIGNALED(signo))
	{
		if (signal == SIGINT)
			ft_putstr_fd("\n", 2);
		else if (sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
	}
}

void	handle_sigint_h(int signo)
{
	(void)signo;
	sig = 1;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	handle_sigint_i(int signo)
{
	(void)signo;
	sig = 2;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_i2(int signo)
{
	(void)signo;
	sig = 2;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
