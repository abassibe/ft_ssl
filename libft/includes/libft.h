/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <qumaujea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:16:00 by qumaujea          #+#    #+#             */
/*   Updated: 2020/02/13 02:34:49 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

void			ft_putendl(char *str);
void			ft_putstr(char *str);
void			exit_error(char *str);
int				ft_strfind(char *str, char find);
int				ft_strcmp(char *s1, char *s2);
char			*ft_itoa_base_unsigned(unsigned long long value,
		int base, int maj);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memalloc(size_t size);
size_t			ft_strlen(char *s);
char			*ft_strcpy(char *dst, char *src);
char			*ft_strnew(size_t size);
char			*ft_strdup(char *s1);
unsigned char	*ft_ustrnew(size_t size);
unsigned char	*ft_ustrcpy(unsigned char *dst, unsigned char *src);

#endif
