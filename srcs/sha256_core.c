/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 03:56:11 by abassibe          #+#    #+#             */
/*   Updated: 2020/03/04 03:58:28 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static unsigned int	right(unsigned int x, unsigned int n)
{
	return (x >> n % 32) | (x << (32 - n) % 32);
}

static uint32_t		*create_words(uint32_t *chunk)
{
	int			i;
	uint32_t	*words;
	uint32_t	s0;
	uint32_t	s1;

	if (!(words = (uint32_t *)ft_memalloc(sizeof(uint32_t) * 65)))
		exit_error("An error occured on malloc, exiting...");
	ft_bzero(words, sizeof(uint32_t) * 65);
	i = -1;
	while (++i < 16)
	{
		ft_memcpy(&(words[i]), chunk + (i * 4), sizeof(uint32_t));
		words[i] = (chunk[i] >> 24 & 0xff) | (chunk[i] >> 8 & 0xff00) |
			(chunk[i] << 8 & 0xff0000) | (chunk[i] << 24 & 0xff000000);
	}
	while (i < 64)
	{
		s0 = ((right(words[i - 15], 7)) ^
				(right(words[i - 15], 18)) ^ (words[i - 15] >> 3));
		s1 = ((right(words[i - 2], 17)) ^
				(right(words[i - 2], 19)) ^ (words[i - 2] >> 10));
		words[i] = words[i - 16] + s0 + words[i - 7] + s1;
		i++;
	}
	return (words);
}

static void			maj_env_sha256(t_sha256 *env, unsigned int h[8])
{
	h[0] = h[0] + env->a;
	h[1] = h[1] + env->b;
	h[2] = h[2] + env->c;
	h[3] = h[3] + env->d;
	h[4] = h[4] + env->e;
	h[5] = h[5] + env->f;
	h[6] = h[6] + env->g;
	h[7] = h[7] + env->h;
	env->a = h[0];
	env->b = h[1];
	env->c = h[2];
	env->d = h[3];
	env->e = h[4];
	env->f = h[5];
	env->g = h[6];
	env->h = h[7];
}

void				store_variables(t_sha256 *env, uint32_t tmp, uint32_t tmp0)
{
	env->h = env->g;
	env->g = env->f;
	env->f = env->e;
	env->e = env->d + tmp0;
	env->d = env->c;
	env->c = env->b;
	env->b = env->a;
	env->a = tmp0 + tmp;
}

void				sha256_process_hash(t_sha256 *env, uint32_t *chunk,
		unsigned int h[8], size_t curr_block)
{
	int			i;
	uint32_t	*words;
	uint32_t	tmp;
	uint32_t	tmp0;
	uint32_t	maj;

	i = -1;
	while (++i < 16)
		ft_memcpy(&(chunk[i]), env->filled_input + curr_block + (i * 4),
				sizeof(uint32_t));
	i = -1;
	words = create_words(chunk);
	while (++i < 64)
	{
		tmp = (right(env->e, 6) ^ right(env->e, 11) ^ right(env->e, 25));
		tmp0 = (env->h + tmp + ((env->e & env->f) ^ ((~env->e) & env->g)) +
				g_sha256_r[i] + words[i]);
		tmp = (right(env->a, 2) ^ right(env->a, 13) ^ right(env->a, 22));
		maj = ((env->a & env->b) ^ (env->a & env->c) ^ (env->b & env->c));
		tmp = (tmp + maj);
		store_variables(env, tmp, tmp0);
	}
	maj_env_sha256(env, h);
}
