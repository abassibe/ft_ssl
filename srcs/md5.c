/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 03:31:45 by abassibe          #+#    #+#             */
/*   Updated: 2019/11/17 05:15:01 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static void		init_hash(unsigned int *k, unsigned int *h)
{
	int		i;

	i = 0;
	while (i < 64)
	{
		k[i] = (unsigned int)floor(fabs(sin(i + 1)) * pow(2, 32));
		i++;
	}
	i = 0;
	while (i < 4)
	{
		h[i] = g_md5_h[i];
		i++;
	}
}

static void		fill_input(t_md5 **env, unsigned char *input)
{
	unsigned long int	len_bits;
	unsigned long int	block_count;

	(*env)->input_len = ft_strlen((char *)input);
	block_count = (((*env)->input_len + 8) / 64) + 1;
	(*env)->filled_input_len = block_count * 64;
	if (!((*env)->filled_input = ft_ustrnew((*env)->filled_input_len)))
		exit_error("An error occured on malloc, exiting...");
	(*env)->filled_input = ft_ustrcpy((*env)->filled_input,
			(unsigned char *)input);
	(*env)->filled_input[(*env)->input_len] = 0x80;
	len_bits = 8 * (*env)->input_len;
	ft_memcpy((*env)->filled_input + ((*env)->filled_input_len - 8),
			&len_bits, 8);
}

void			md5(t_ssl *ssl, t_command *command, unsigned char *input)
{
	t_md5			*env;
	unsigned int	h[4];
	unsigned int	k[64];
	size_t			curr_block;
	uint32_t		*word;

	init_hash(k, h);
	if (!(env = (t_md5 *)ft_memalloc(sizeof(t_md5))))
		exit_error("An error occured on malloc, exiting...");
	fill_input(&env, input);
	curr_block = 0;
	while (curr_block < env->filled_input_len)
	{
		maj_env(&env, h, env->filled_input, curr_block);
		word = (uint32_t *)(env->filled_input + curr_block);
		hash_main_loop(&env, word, k);
		h[0] += env->a;
		h[1] += env->b;
		h[2] += env->c;
		h[3] += env->d;
		curr_block += 64;
	}
	display_hash_md5(ssl, h, command);
}
