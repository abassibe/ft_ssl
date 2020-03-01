/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <qumaujea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:06:04 by qumaujea          #+#    #+#             */
/*   Updated: 2020/02/13 02:33:34 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*m;
	size_t	c;

	c = 0;
	if (!(m = (char *)malloc(size + 1)))
		return (NULL);
	while (c != size)
	{
		m[c] = '\0';
		c++;
	}
	m[c] = '\0';
	return (m);
}
