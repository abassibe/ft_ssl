/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_unsigned.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <qumaujea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:03:09 by qumaujea          #+#    #+#             */
/*   Updated: 2020/02/13 02:30:53 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(unsigned long long nbr, int base)
{
	int		ret;

	ret = 0;
	while (nbr != 0)
	{
		nbr /= base;
		ret++;
	}
	return (ret);
}

char		*ft_itoa_base_unsigned(unsigned long long value, int base, int maj)
{
	char	*ret;
	int		nb;
	int		i;
	char	*tab;

	if (maj)
		tab = "0123456789ABCDEF";
	else
		tab = "0123456789abcdef";
	if (value == 0)
		return (ft_strdup("0"));
	nb = count(value, base);
	if (!(ret = (char *)ft_ustrnew(nb)))
		exit_error("An error occured on malloc, exiting...");
	i = 1;
	while (value != 0)
	{
		ret[nb - i] = tab[value % base];
		value /= base;
		i++;
	}
	ret[nb] = '\0';
	return (ret);
}
