/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 03:38:43 by abassibe          #+#    #+#             */
/*   Updated: 2019/11/17 05:19:18 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static void		start_format_by_options(t_ssl *ssl, t_command *command,
		char algo)
{
	if (!ssl->opt_q && !ssl->opt_r)
	{
		if (command->opt_s || ssl->opt_p)
		{
			ssl->opt_p = 0;
			if (!algo)
				ft_putstr("MD5(\"");
			else
				ft_putstr("SHA256(\"");
		}
		else
		{
			if (!algo)
				ft_putstr("MD5(");
			else
				ft_putstr("SHA256(");
		}
		ft_putstr(command->target);
		if (command->opt_s || ssl->opt_p)
			ft_putstr("\")= ");
		else
			ft_putstr(")= ");
	}
}

static void		end_format_by_options(t_ssl *ssl, t_command *command)
{
	if (ssl->opt_r && !ssl->opt_q)
	{
		if (command->opt_s || ssl->opt_p)
			ft_putstr(" \"");
		else
			ft_putstr(" ");
		ft_putstr(command->target);
		if (command->opt_s || ssl->opt_p)
			ft_putstr("\"");
	}
}

static uint32_t	convert_as_little_endian(uint32_t n)
{
	char	*tmp;
	int		len;

	tmp = ft_itoa_base_unsigned(((n >> 24) | ((n & 0xff0000) >> 8)
				| ((n & 0xff00) << 8) | (n << 24)), 16, 0);
	len = ft_strlen(tmp);
	if (tmp)
		free(tmp);
	while (len < 8)
	{
		write(1, "0", 1);
		len++;
	}
	return ((n >> 24) | ((n & 0xff0000) >> 8)
			| ((n & 0xff00) << 8) | (n << 24));
}

void			display_hash_md5(t_ssl *ssl, unsigned int *hash,
		t_command *command)
{
	char	*curr_hash;
	int		i;

	i = 0;
	start_format_by_options(ssl, command, 0);
	while (i < 4)
	{
		curr_hash = ft_itoa_base_unsigned(convert_as_little_endian(hash[i]),
				16, 0);
		ft_putstr(curr_hash);
		free(curr_hash);
		i++;
	}
	end_format_by_options(ssl, command);
	ft_putstr("\n");
}

void			display_hash_sha256(t_ssl *ssl, unsigned int *h,
		t_command *command)
{
	char	*curr_hash;
	int		i;
	int		len;

	i = 0;
	start_format_by_options(ssl, command, 1);
	while (i < 8)
	{
		curr_hash = ft_itoa_base_unsigned(h[i], 16, 0);
		len = ft_strlen(curr_hash);
		while (len < 8)
		{
			write(1, "0", 1);
			len++;
		}
		ft_putstr(curr_hash);
		free(curr_hash);
		i++;
	}
	end_format_by_options(ssl, command);
	ft_putstr("\n");
}
