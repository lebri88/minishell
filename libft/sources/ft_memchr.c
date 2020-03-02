/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 15:21:13 by geliz             #+#    #+#             */
/*   Updated: 2019/09/14 15:24:41 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_tmp;

	i = 0;
	s_tmp = (unsigned char *)s;
	while (i < n)
	{
		if (s_tmp[i] == ((unsigned char)c))
			return (&s_tmp[i]);
		i++;
	}
	return (NULL);
}
