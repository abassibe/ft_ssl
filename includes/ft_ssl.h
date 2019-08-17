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
#include <math.h>
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
    size_t newMessageLen;
    int blockCount;
    uint32_t buffA;
    uint32_t buffB;
    uint32_t buffC;
    uint32_t buffD;
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t *r;
    uint32_t *k;
} t_md5;

typedef struct s_ssl
{
    unsigned char *message;
    unsigned char *digest;
    size_t messageLen;
    t_md5 md5;
    t_sha256 sha256;
    void (*algo)(struct s_ssl *);
    void (*option)(struct s_ssl *);
} t_ssl;

void md5FillString(t_ssl *ssl);
uint32_t md5F0(uint32_t b, uint32_t c, uint32_t d);
uint32_t md5F1(uint32_t b, uint32_t c, uint32_t d);
uint32_t md5F2(uint32_t b, uint32_t c, uint32_t d);
uint32_t md5F3(uint32_t b, uint32_t c, uint32_t d);

unsigned char *ft_ustrnew(size_t size);
unsigned char *ft_ustrcpy(unsigned char *dst, unsigned char *src);

#endif