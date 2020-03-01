/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <qumaujea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:07:13 by qumaujea          #+#    #+#             */
/*   Updated: 2020/02/13 02:33:52 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned char	*ft_ustrcpy(unsigned char *dst, unsigned char *src)
{
	size_t	k;

	k = 0;
	while (src[k])
	{
		dst[k] = (unsigned char)src[k];
		k++;
	}
	dst[k] = 0;
	return (dst);
}
