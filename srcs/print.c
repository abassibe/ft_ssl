/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <qumaujea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 03:38:43 by abassibe          #+#    #+#             */
/*   Updated: 2020/03/04 05:54:03 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static void		start_format_by_options(t_ssl *ssl, t_command *command,
		char algo)
{
	if (ssl->opt_p == 2)
		return ;
	if (!ssl->opt_q && !ssl->opt_r)
	{
		if (ssl->opt_p)
			ft_printf("%s", command->target);
		else if (ssl->opt_s)
		{
			if (!algo)
				ft_printf("%s", "MD5 (\"");
			else
				ft_printf("%s", "SHA256 (\"");
			ft_printf("%s%s", command->target, "\") = ");
		}
		else
		{
			if (!algo)
				ft_printf("%s", "MD5 (");
			else
				ft_printf("%s", "SHA256 (");
			ft_printf("%s%s", command->target, ") = ");
		}
	}
}

static void		end_format_by_options(t_ssl *ssl, t_command *command)
{
	if (ssl->opt_r && !ssl->opt_q)
	{
		if (ssl->opt_s)
			ft_printf("%s", " \"");
		else
			ft_printf("%s", " ");
		ft_printf("%s", command->target);
		if (ssl->opt_s)
			ft_printf("%s", "\"");
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
		ft_printf("%c", '0');
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
		ft_printf("%s", curr_hash);
		free(curr_hash);
		i++;
	}
	end_format_by_options(ssl, command);
	ft_printf("%s", "\n");
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
			ft_printf("%c", '0');
			len++;
		}
		ft_printf("%s", curr_hash);
		free(curr_hash);
		i++;
	}
	end_format_by_options(ssl, command);
	ft_printf("%s", "\n");
}
