/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <qumaujea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 02:34:57 by abassibe          #+#    #+#             */
/*   Updated: 2020/03/04 03:57:03 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static void		*next_command(t_command **command)
{
	if (!((*command)->next = ft_memalloc(sizeof(t_command))))
		exit_error("An error occured on malloc, exiting...");
	return ((*command)->next);
}

static void		set_algo_options(char *options, t_ssl **ssl, int *flag)
{
	int		i;

	i = 0;
	while (options[i])
	{
		if (options[i] == 's')
			*flag = 1;
		else if (options[i] == 'q')
			(*ssl)->opt_q = 1;
		else if (options[i] == 'p')
			(*ssl)->opt_p = 1;
		else if (options[i] == 'r')
		{
			if (!(*ssl)->opt_q)
				(*ssl)->opt_r = 1;
		}
		else if (options[i] != '-')
		{
			ft_putstr("md5: illegal option -- ");
			write(1, &options[i], 1);
			exit_error("\nusage: md5 [-pqr] [-s string] [files ...]\n");
		}
		i++;
	}
}

static void		parse_input(char **args, t_ssl *ssl, int index, t_command *tmp)
{
	if (ssl->opt_p)
		tmp->target = get_input_from_stdin();
	while (args[index])
	{
		if (tmp && tmp->target)
			tmp = next_command(&tmp);
		if ((args[index][0] && args[index][0] == '-') &&
				(args[index][1] && args[index][1] == 's'))
		{
			index++;
			if (!args[index])
			{
				tmp->target = "";
				return ;
			}
		}
		tmp->target = ft_strdup(args[index]);
		index++;
	}
}

void			parse_options(char **args, t_ssl *ssl)
{
	int		i;
	int		s_flag;

	i = 2;
	s_flag = 0;
	while (args[i] && args[i][0] == '-')
	{
		set_algo_options(args[i], &ssl, &s_flag);
		if (s_flag)
			break ;
		i++;
	}
	if (!(ssl->commands = ft_memalloc(sizeof(t_command))))
		exit_error("An error occured on malloc, exiting...");
	parse_input(args, ssl, i, ssl->commands);
}
