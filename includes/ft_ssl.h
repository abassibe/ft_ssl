/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <qumaujea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 05:50:07 by abassibe          #+#    #+#             */
/*   Updated: 2020/03/04 05:42:54 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define FILE_MODE 101

static unsigned int			g_md5_h[8] =
{
	0x67452301,
	0xEFCDAB89,
	0x98BADCFE,
	0x10325476};

static unsigned int			g_md5_r[64] =
{
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

static unsigned int			g_sha256_h[8] =
{
	0x6a09e667,
	0xbb67ae85,
	0x3c6ef372,
	0xa54ff53a,
	0x510e527f,
	0x9b05688c,
	0x1f83d9ab,
	0x5be0cd19};

static unsigned int			g_sha256_r[64] =
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

typedef struct s_md5		t_md5;
typedef struct s_sha256		t_sha256;
typedef struct s_command	t_command;
typedef struct s_ssl		t_ssl;
typedef void				(*t_hash_algo)(t_ssl *ssl, t_command *command,
		unsigned char *input);

struct						s_md5
{
	uint32_t				a;
	uint32_t				b;
	uint32_t				c;
	uint32_t				d;
	uint32_t				f;
	uint32_t				g;
	uint32_t				*sub_block;
	size_t					input_len;
	size_t					filled_input_len;
	unsigned char			*filled_input;
};

struct						s_sha256
{
	uint32_t				a;
	uint32_t				b;
	uint32_t				c;
	uint32_t				d;
	uint32_t				e;
	uint32_t				f;
	uint32_t				g;
	uint32_t				h;
	uint32_t				*sub_block;
	size_t					input_len;
	size_t					filled_input_len;
	unsigned char			*filled_input;
};

struct						s_command
{
	char					*target;
	t_command				*next;
};

struct						s_ssl
{
	t_md5					*md5;
	t_sha256				*sha256;
	t_command				*commands;
	int						opt_q;
	int						opt_p;
	int						opt_r;
	int						opt_s;
	size_t					file_size;
};

void						md5(t_ssl *ssl, t_command *command,
		unsigned char *input);
unsigned char				*complet_input(char *input, int input_len);
void						hash_main_loop(t_md5 **env, uint32_t *word,
		unsigned int *k);
void						maj_env(t_md5 **env, unsigned int *h,
		unsigned char *buffer, int curr_block);
void						sha256(t_ssl *ssl, t_command *command,
		unsigned char *input);
void						sha256_process_hash(t_sha256 *env, uint32_t *chunk,
		unsigned int h[8], size_t curr_block);
int							set_command_options(char *options,
		t_command **command, int index);
void						get_target_from_console(t_command **command);
void						parse_options(char **args, t_ssl *ssl);
char						*get_input_from_file(int fd, size_t *size);
char						*get_input_from_stdin(void);
int							read_from_stdin(char *algo, int p_mode);
unsigned int				f0(unsigned int b, unsigned int c, unsigned int d);
unsigned int				f1(unsigned int b, unsigned int c, unsigned int d);
unsigned int				f2(unsigned int b, unsigned int c, unsigned int d);
unsigned int				f3(unsigned int b, unsigned int c, unsigned int d);
unsigned char				*ft_ustrnew(size_t size);
unsigned char				*ft_ustrcpy(unsigned char *dst, unsigned char *src);
void						exit_error(char *str);
char						*get_input_from_stdin();
void						invalid_hash_algo(void);
t_hash_algo					select_hash_algo(char *arg);
void						display_hash_md5(t_ssl *ssl, unsigned int *hash,
		t_command *command);
void						display_hash_sha256(t_ssl *ssl, unsigned int *hash,
		t_command *command);
char						*ft_itoa_base_unsigned(unsigned long long value,
		int base, int maj);
int							ft_strfind(char *str, char find);
unsigned char				*ft_ustrnew(size_t size);
void						process_hash(t_ssl *ssl, t_command *command,
		t_hash_algo hash_function);
int							process_files(t_ssl *ssl, t_hash_algo hash_function,
		char **av, uint32_t arg_index);
void						invalid_hash_algo(void);
void						display_usage(void);

#endif
