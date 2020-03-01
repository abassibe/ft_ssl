/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 03:55:21 by abassibe          #+#    #+#             */
/*   Updated: 2019/11/17 05:17:02 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

unsigned int	f0(unsigned int b, unsigned int c, unsigned int d)
{
	return (b & c) | (~b & d);
}

unsigned int	f1(unsigned int b, unsigned int c, unsigned int d)
{
	return (d & b) | (~d & c);
}

unsigned int	f2(unsigned int b, unsigned int c, unsigned int d)
{
	return (b ^ c ^ d);
}

unsigned int	f3(unsigned int b, unsigned int c, unsigned int d)
{
	return (c ^ (b | ~d));
}
