/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <qumaujea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:06:55 by qumaujea          #+#    #+#             */
/*   Updated: 2020/02/13 02:32:46 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned char	*ft_ustrnew(size_t size)
{
	unsigned char	*m;
	size_t			c;

	c = 0;
	if (!(m = (unsigned char *)malloc(size + 1)))
		return (NULL);
	while (c != size)
	{
		m[c] = 0;
		c++;
	}
	return (m);
}
