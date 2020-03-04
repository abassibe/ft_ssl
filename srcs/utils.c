/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <qumaujea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 02:26:08 by abassibe          #+#    #+#             */
/*   Updated: 2020/03/04 05:54:40 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	display_usage(void)
{
	exit_error("usage: ft_ssl command [command opts] [command arg]");
}

void	invalid_hash_algo(void)
{
	ft_putstr("Standard commands:\n\n");
	ft_putstr("Message Digest commands:\n");
	ft_putstr("md5\nsha256\n\n");
	ft_putstr("Cipher commands:\n");
}

int		process_files(t_ssl *ssl, t_hash_algo hash_fun, char **av,
		uint32_t arg_index)
{
	t_command		*command;
	int				fd;
	unsigned char	*input;

	while (av[arg_index])
	{
		if (!(command = ft_memalloc(sizeof(t_command))))
			exit_error("Malloc error");
		command->target = ft_strdup(av[arg_index]);
		if ((fd = open(command->target, O_RDONLY)) < 1)
			ft_printf("ft_ssl: %s: %s: No such file or directory.\n", av[1],
					command->target);
		else
		{
			input = (unsigned char *)get_input_from_file(fd, &ssl->file_size);
			hash_fun(ssl, command, input);
			if (input)
				free(input);
		}
		arg_index++;
	}
	return (0);
}

void	process_hash(t_ssl *ssl, t_command *command,
		t_hash_algo hash_function)
{
	unsigned char	*input;
	int				fd;

	input = NULL;
	if (ssl->opt_p || ssl->opt_s)
	{
		hash_function(ssl, command, (unsigned char *)command->target);
	}
	else
	{
		if ((fd = open(command->target, O_RDONLY)) < 1)
		{
			write(1, command->target, ft_strlen(command->target));
			write(1, " : No such file or directory.\n", 30);
		}
		else
		{
			input = (unsigned char *)get_input_from_file(fd, &ssl->file_size);
			hash_function(ssl, command, input);
			if (input)
				free(input);
		}
	}
}
