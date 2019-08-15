/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:14:18 by abassibe          #+#    #+#             */
/*   Updated: 2019/08/15 17:14:19 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
#define FT_SSL_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../includes/libft.h"

typedef struct s_sha256
{
    unsigned char *newMessage;
    size_t newMesageLen;
    int blockCount;
} t_sha256;

typedef struct s_md5
{
    unsigned char *newMessage;
    size_t newMesageLen;
    int blockCount;
} t_md5;

typedef struct s_ssl
{
    unsigned char *message;
    unsigned char *digest;
    size_t messageLen;
    t_md5 md5;
    t_sha256 sha256;
} t_ssl;

#endif