/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_hash_algo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <qumaujea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 03:27:01 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/13 02:21:26 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static void	init_algos(t_hash_algo *algos, char algos_name[10][7])
{
	algos[0] = md5;
	ft_strcpy(algos_name[0], "md5");
	algos[1] = sha256;
	ft_strcpy(algos_name[1], "sha256");
}

static int	which_algo(char *arg, char algos_name[10][7])
{
	int		i;

	i = 0;
	while (i < 10)
	{
		if (!ft_strcmp(arg, algos_name[i]))
			return (i);
		i++;
	}
	return (-1);
}

t_hash_algo	select_hash_algo(char *arg)
{
	t_hash_algo	algos[10];
	char		algos_name[10][7];
	int			index;

	init_algos(algos, algos_name);
	if ((index = which_algo(arg, algos_name)) < 0)
	{
		ft_putstr("\nInvalid hash algorithm choice.\n");
		invalid_hash_algo();
		exit_error("");
	}
	return (algos[index]);
}
