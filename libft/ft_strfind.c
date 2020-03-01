/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <qumaujea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:03:18 by qumaujea          #+#    #+#             */
/*   Updated: 2020/02/13 02:32:10 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strfind(char *str, char find)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == find)
			return (1);
		i++;
	}
	return (0);
}
