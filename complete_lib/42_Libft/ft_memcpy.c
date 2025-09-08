/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomanuel <jomanuel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:51:22 by bpires-r          #+#    #+#             */
/*   Updated: 2025/09/08 14:06:47 by jomanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*cdest;
	const char	*csrc;

	cdest = (char *)dest;
	csrc = (char *)src;
	if (!dest && !src)
		return (dest);
	i = 0;
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dest);
}

// int	main(void)
// {
// 	char *src = "Ola";
// 	char dest[20];
// 	printf("My Func : %s\n", (char *)ft_memcpy(dest, src, 3));
// 	printf("My Func : %s\n", (char *)ft_memcpy(dest, src, 3));
// 	return (0);
// }