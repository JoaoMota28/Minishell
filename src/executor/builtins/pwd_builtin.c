/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:19:11 by jomanuel          #+#    #+#             */
/*   Updated: 2025/08/16 17:46:30 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// feito com getcwd mas supostamente o bash usa um array de variáveis interno para este efeito
// vai buscar a variável PWD interna atualizada quando o working directory muda
// export só muda no env dos uusers e não no interno
// getcwd deveria falhar se o working directory for eliminado enquanto o user está dentro dele, mas o env não muda por isso pwd funciona
// testar se o getcwd falha ou não depois de criar o cd e de poder executar rm


#include "minishell.h"

int	pwd_builtin(t_minishell *data, t_tree *leaf)
{
	char	*pwd;

	(void)data;
	(void)leaf;
	pwd = data->pwd;
	if (!pwd)
		pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		if (data->exec.pipeline_child)
      		exit_msh(data, EXIT_FAILURE);
		ft_putstr_fd(PWD_ERROR, 2);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(pwd, 1);
	free (pwd);
	return (EXIT_SUCCESS);
}
