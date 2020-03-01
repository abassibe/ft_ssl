/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <qumaujea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:06:26 by qumaujea          #+#    #+#             */
/*   Updated: 2020/02/13 02:31:59 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s1)
{
	char	*s2;

	if (!(s2 = ft_strnew(ft_strlen(s1))))
		exit_error("An error occured on malloc, exiting...");
	return (ft_strcpy(s2, s1));
}
