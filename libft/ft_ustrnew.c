/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:43:31 by abassibe          #+#    #+#             */
/*   Updated: 2019/09/15 17:14:33 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

unsigned char *ft_ustrnew(size_t size)
{
	unsigned char *m;
	size_t c;

	c = 0;
	if (!(m = (unsigned char *)malloc(size + 1)))
		return (NULL);
	while (c != size)
	{
		m[c] = 0;
		c++;
	}
	m[c] = 0;
	return (m);
}
