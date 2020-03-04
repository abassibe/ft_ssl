/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <qumaujea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 02:26:08 by abassibe          #+#    #+#             */
/*   Updated: 2020/03/04 04:18:51 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

char	*get_input_from_file(int fd, size_t *size)
{
	char	buffer[90000];
	char	*input;
	size_t	file_size;
	int		ret;

	input = NULL;
	file_size = 0;
	ret = 0;
	while ((ret = read(fd, buffer, 90000)) > 0)
		file_size += ret;
	if (ret == -1)
		exit_error("Error while reading, exiting...");
	lseek(fd, 0, SEEK_SET);
	if (!(input = (char *)ft_memalloc(sizeof(char) * (file_size + 1))))
		return (NULL);
	if ((*size = read(fd, input, file_size)) < 0)
		exit_error("Error while reading, exiting...");
	return (input);
}

char	*get_input_from_stdin(void)
{
	char	buffer[500];
	char	*input;
	char	*tmp;
	int		ret;
	int		i;

	input = NULL;
	i = 0;
	ft_bzero(buffer, 500);
	while ((ret = read(0, &buffer, 500)) > 0)
	{
		if (!(tmp = ft_memalloc(ft_strlen(buffer) + ft_strlen(input) + 1)))
			exit_error("An error occured on malloc, exiting...");
		ft_memcpy(tmp, input, ft_strlen(input));
		ft_memcpy(tmp + ft_strlen(input), buffer, ret);
		if (input)
			free(input);
		input = ft_strdup(tmp);
		ft_bzero(buffer, ft_strlen(buffer));
		if (tmp)
			free(tmp);
	}
	if (input)
		input[ft_strlen(input)] = '\0';
	return (input);
}

int		read_from_stdin(char *algo, int p_mode)
{
	unsigned char	*input;
	t_command		*command;
	t_hash_algo		hash_function;
	t_ssl			*ssl;

	input = NULL;
	if (!(ssl = ft_memalloc(sizeof(t_ssl))))
		exit_error("An error occured on malloc, exiting...");
	if (!(command = ft_memalloc(sizeof(t_command))))
		exit_error("An error occured on malloc, exiting...");
	hash_function = select_hash_algo(algo);
	input = (unsigned char *)get_input_from_stdin();
	if (!input)
		input = (unsigned char *)ft_strdup("");
	command->target = ft_strdup((char *)input);
	ssl->opt_p = p_mode;
	hash_function(ssl, command, input);
	if (input)
		free(input);
	return (0);
}
