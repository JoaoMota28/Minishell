/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:47:07 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/08 14:06:08 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}

// int	main(void)
// {
// 	char s[20] = "Hello :)))";
// 	printf("My Func : %s\n", (char *)ft_memset(s, 'A', 5));
// 	printf("Original Func : %s\n", (char *)ft_memset(s, 'A', 5));
// 	return (0);
// }