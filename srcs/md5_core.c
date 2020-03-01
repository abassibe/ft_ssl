/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 03:46:34 by abassibe          #+#    #+#             */
/*   Updated: 2019/11/17 05:16:36 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static unsigned int	*subdivide_block(unsigned char *block)
{
	int				i;
	int				j;
	unsigned int	*sub_divided;

	i = 0;
	j = 0;
	if (!(sub_divided = (unsigned int *)malloc(16 * sizeof(unsigned int))))
		exit_error("An error occured on malloc, exiting...");
	while (j < 16)
	{
		sub_divided[j] = ((block[i] << 24) | (block[i + 1] << 16) |
				(block[i + 2] << 8) | block[i + 3]);
		i += 4;
		j++;
	}
	return (sub_divided);
}

void				maj_env(t_md5 **env, unsigned int *h, unsigned char *buffer,
		int curr_block)
{
	(*env)->a = h[0];
	(*env)->b = h[1];
	(*env)->c = h[2];
	(*env)->d = h[3];
	(*env)->g = 0;
	(*env)->f = 0;
	if ((*env)->sub_block)
		free((*env)->sub_block);
	(*env)->sub_block = subdivide_block(&buffer[curr_block]);
}

static void			update_values(int i, t_md5 **env)
{
	if (i < 16)
	{
		(*env)->f = f0((*env)->b, (*env)->c, (*env)->d);
		(*env)->g = i;
	}
	else if (i < 32)
	{
		(*env)->f = f1((*env)->b, (*env)->c, (*env)->d);
		(*env)->g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		(*env)->f = f2((*env)->b, (*env)->c, (*env)->d);
		(*env)->g = (3 * i + 5) % 16;
	}
	else
	{
		(*env)->f = f3((*env)->b, (*env)->c, (*env)->d);
		(*env)->g = (7 * i) % 16;
	}
}

void				hash_main_loop(t_md5 **env, uint32_t *word, unsigned int *k)
{
	int		i;

	i = 0;
	while (i < 64)
	{
		update_values(i, env);
		(*env)->f = (*env)->f + (*env)->a + k[i] + word[(*env)->g];
		(*env)->a = (*env)->d;
		(*env)->d = (*env)->c;
		(*env)->c = (*env)->b;
		(*env)->b = (*env)->b + (((*env)->f << g_md5_r[i]) |
				((*env)->f >> (32 - g_md5_r[i])));
		i++;
	}
}
