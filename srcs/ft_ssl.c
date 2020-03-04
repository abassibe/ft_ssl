/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <qumaujea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 02:26:08 by abassibe          #+#    #+#             */
/*   Updated: 2020/03/04 05:53:27 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static int	hash_next_arg(t_ssl *ssl, t_hash_algo hash_fun, char **av,
		uint32_t *arg_index)
{
	t_command	*command;

	if (!av[*arg_index + 1])
		return (ft_printf("%s: option requires an argument -- s\n", av[1]));
	*arg_index += 1;
	if (!(command = ft_memalloc(sizeof(t_command))))
		exit_error("Malloc error");
	command->target = ft_strdup(av[*arg_index]);
	ssl->opt_s = 1;
	process_hash(ssl, command, hash_fun);
	ssl->opt_s = 0;
	return (1);
}

static int	hash_current_arg(t_ssl *ssl, t_hash_algo hash_fun, char *arg,
		uint32_t string_index)
{
	char		*to_hash;
	uint32_t	i;
	t_command	*command;

	i = 0;
	while (arg[string_index + i])
		i++;
	if (!(to_hash = ft_memalloc(sizeof(char) * (i + 1))))
		exit_error("Malloc error");
	i = 0;
	while (arg[string_index + i])
	{
		to_hash[i] = arg[string_index + i];
		i++;
	}
	if (!(command = ft_memalloc(sizeof(t_command))))
		exit_error("Malloc error");
	command->target = to_hash;
	ssl->opt_s = 1;
	process_hash(ssl, command, hash_fun);
	ssl->opt_s = 0;
	return (1);
}

int			handle_option(t_ssl *ssl, char **av, uint32_t *arg_index, int i)
{
	if (av[*arg_index][i] == 'q')
	{
		ssl->opt_q = 1;
		if (!av[*arg_index][i + 1])
		{
			if (!av[*arg_index + 1])
				return (read_from_stdin(av[1], 2));
			return (1);
		}
	}
	else if (av[*arg_index][i] == 'r')
	{
		ssl->opt_r = 1;
		if (!av[*arg_index][i + 1])
		{
			if (!av[*arg_index + 1])
				return (read_from_stdin(av[1], 2));
			return (1);
		}
	}
	return (-1);
}

int			process_argument(t_ssl *ssl, t_hash_algo hash_fun, char **av, \
		uint32_t *arg_index)
{
	int		i;

	if (av[*arg_index][0] == '-')
	{
		i = 0;
		while (av[*arg_index][++i])
		{
			if (av[*arg_index][i] == 's')
			{
				return (av[*arg_index][i + 1] ? \
						hash_current_arg(ssl, hash_fun, av[*arg_index], i + 1) :
						hash_next_arg(ssl, hash_fun, av, arg_index));
			}
			if (av[*arg_index][i] == 'p')
				return (read_from_stdin(av[1], 1));
			else if (av[*arg_index][i] == 'q' || av[*arg_index][i] == 'r')
				if (handle_option(ssl, av, arg_index, i) != -1)
					return (0);
		}
		*arg_index += 1;
	}
	return (FILE_MODE);
}

int			main(int ac, char **av)
{
	t_ssl		*ssl;
	t_hash_algo	hash_function;
	uint32_t	i;

	if (ac == 1)
		display_usage();
	if (ac == 2)
		return (read_from_stdin(av[1], 2));
	if (!(ssl = ft_memalloc(sizeof(t_ssl))))
		exit_error("An error occured on malloc, exiting...");
	hash_function = select_hash_algo(av[1]);
	i = 1;
	while (av[++i])
		if (process_argument(ssl, hash_function, av, &i) == FILE_MODE)
			return (process_files(ssl, hash_function, av, i));
	return (0);
}
