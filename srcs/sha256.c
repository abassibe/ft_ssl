/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 04:33:15 by abassibe          #+#    #+#             */
/*   Updated: 2020/03/04 04:22:40 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static t_sha256	*sha256_init_env(unsigned int *h, unsigned char *input)
{
	t_sha256	*env;

	if (!(env = ft_memalloc(sizeof(t_sha256))))
		exit_error("An error occured on malloc, exiting...");
	env->a = h[0];
	env->b = h[1];
	env->c = h[2];
	env->d = h[3];
	env->e = h[4];
	env->f = h[5];
	env->g = h[6];
	env->h = h[7];
	env->input_len = ft_strlen((char *)input);
	return (env);
}

static void		sha256_init_hash(unsigned int *k, unsigned int *h)
{
	int		i;

	i = 0;
	while (i < 64)
	{
		k[i] = g_sha256_r[i];
		i++;
	}
	i = 0;
	while (i < 8)
	{
		h[i] = g_sha256_h[i];
		i++;
	}
}

static void		sha256_fill_input(t_sha256 **env, unsigned char *input)
{
	unsigned long int	len_bits;
	int					i;

	i = -1;
	len_bits = (*env)->input_len * 8;
	(*env)->filled_input_len = (448 - (len_bits + 1)) % 512;
	(*env)->filled_input_len += len_bits + 64 + 1;
	(*env)->filled_input_len /= 8;
	if (!((*env)->filled_input = ft_ustrnew((*env)->filled_input_len)))
		exit_error("An error occured on malloc, exiting...");
	ft_bzero((*env)->filled_input, sizeof(uint8_t) * (*env)->filled_input_len);
	ft_memcpy((*env)->filled_input, input, (*env)->input_len);
	(*env)->filled_input[(*env)->input_len] = 0x80;
	while (++i < 8)
		(*env)->filled_input[(*env)->filled_input_len - 8 + i] =
			((uint8_t *)&(len_bits))[7 - i];
}

void			sha256(t_ssl *ssl, t_command *command, unsigned char *input)
{
	t_sha256		*env;
	unsigned int	h[8];
	unsigned int	k[64];
	size_t			curr_block;
	uint32_t		*chunk;

	sha256_init_hash(k, h);
	env = sha256_init_env(h, input);
	sha256_fill_input(&env, input);
	curr_block = 0;
	while (curr_block < env->filled_input_len)
	{
		if (!(chunk = (uint32_t *)ft_memalloc(sizeof(uint32_t) * 16)))
			exit_error("An error occured on malloc, exiting...");
		sha256_process_hash(env, chunk, h, curr_block);
		curr_block += 64;
		free(chunk);
	}
	display_hash_sha256(ssl, h, command);
}
