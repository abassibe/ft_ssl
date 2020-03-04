/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.backup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <qumaujea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 02:26:08 by abassibe          #+#    #+#             */
/*   Updated: 2020/03/03 03:56:45 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static void	display_usage(void)
{
	exit_error("usage: ft_ssl command [command opts] [command arg]");
}

void		invalid_hash_algo(void)
{
	ft_putstr("Standard commands:\n\n");
	ft_putstr("Message Digest commands:\n");
	ft_putstr("md5\nsha256\n\n");
	ft_putstr("Cipher commands:\n");
}

static void	process_hash(t_ssl *ssl, t_command *command,
		t_hash_algo hash_function)
{
	unsigned char	*input;
	int				fd;

	input = NULL;
	if (command->opt_s || ssl->opt_p)
	{
		ssl->opt_p = 0;
		command->opt_s = 1;
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

int			main(int ac, char **av)
{
	t_ssl		*ssl;
	t_command	*current;
	t_hash_algo	hash_function;

	if (ac == 1)
		display_usage();
	if (ac == 2)
		return (read_from_stdin(av[1]));
	if (!(ssl = ft_memalloc(sizeof(t_ssl))))
		exit_error("An error occured on malloc, exiting...");
	hash_function = select_hash_algo(av[1]);
	parse_options(av, ssl);
	current = ssl->commands;
	while (current)
	{
		process_hash(ssl, current, hash_function);
		current = current->next;
	}
	return (0);
}
