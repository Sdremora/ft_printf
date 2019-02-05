/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 11:52:39 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/04 18:15:06 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "ft_double_to_str.h"
# include "ft_colors.h"

# define TRUE 1
# define FALSE 0
# define ESCAPE_FLAGS "-+ #0"
# define ESCAPE_SPECIFIERS "dDioOuUxXfFcCsSp%"
# define ERROR_SPECIFIER 'Q'
# define ESCAPE_LEN_SP "lLhzjt"
# define ERROR -1
# define E_NO_MEM -2
# define E_BAD_ESCAPE -3
# define E_CONVERT_UTF8 -4

extern int g_status;

/*
**	LSP_L	-> l
**	LSP_LL	-> ll
**	LSP_UL	-> L
**	LSP_Z	-> z
**	LSP_J	-> j
**	LSP_T	-> t
**	LSP_H	-> h
**	LSP_HH	-> hh
**	LSP_DEF	-> default value and for count flags. It always must be last line.
*/

typedef enum	e_len_sp
{
	LSP_L,
	LSP_LL,
	LSP_UL,
	LSP_Z,
	LSP_J,
	LSP_T,
	LSP_H,
	LSP_HH,
	LSP_DEF
}				t_len_sp;

/*
**	F_MINUS	-> '-'
**	F_PLUS	-> '+'
**	F_WHTSP	-> ' '
**	F_HASH	-> '#'
**	F_ZERO	-> '0'
**	F_DEF	->	default value and for count flags.
**				It always must be the last line.
**
**	ESCAPE_FLAGS must be in the same order.
*/

typedef enum	e_flags_sp
{
	F_MINUS,
	F_PLUS,
	F_WHITESPACE,
	F_HASH,
	F_ZERO,
	F_DEF
}				t_flags_sp;

typedef struct	s_escape
{
	char		flags[F_DEF + 1];
	int			width;
	int			precision;
	t_len_sp	len_sp;
	char		specifier;
	char		*str_simple;
	char		*str;
	char		*str_utf8;
	char		*prefix;
	char		*postfix;
	int			str_len;
	int			prefix_len;
	int			postfix_len;
	char		error_char;
}				t_escape;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

int				ft_printf(const char *format, ...);
int				ft_fprintf(int fd, const char *format, ...);

size_t			ft_strlen(const char *s);
void			ft_bzero(void *s, size_t n);
int				ft_isdigit(int c);
char			*ft_strncpy(char *dest, const char *src, size_t n);
int				ft_atoi(const char *str);
void			*ft_memcpy(void *dst, const void *src, size_t n);
char			*ft_strdup(const char *s);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
void			*ft_free(int count_param, ...);
int				ft_str_put(char *str, size_t index, char chr);
void			ft_str_reverse(char *str);
char			*ft_get_bits(void *data, int data_bytes_count);
int				ft_str_indexof(const char *str, int c);
int				ft_str_n_indexof(const char *str, int n, int c);
int				ft_str_last_indexof(const char *str, int c);
int				ft_str_last_n_indexof(const char *str, int n, int c);
int				ft_str_indexof_str(const char *haystack, const char *needle);

int				set_status(int status);
int				escape_initial(t_escape *escape);
void			ft_str_chrset(char *line, int c, int start, int end);
void			ft_str_swap(char *str, int pos1, int pos2);
void			ft_str_toupper(char *str);

void			pf_format_di(t_escape *escape, va_list *ap);
void			pf_switch_flags_di(t_escape *escape, int sign);

void			pf_format_s(t_escape *escape, va_list *ap);
void			pf_check_precision(t_escape *escape);

void			pf_format_oux(t_escape *escape, va_list *ap, char sp);
void			pf_switch_flags_oux(t_escape *escape);

void			pf_format_c_ap(t_escape *escape, va_list *ap);
void			pf_format_c_char(t_escape *escape, char c);
void			format_char(t_escape *escape);

void			pf_format_p(t_escape *escape, va_list *ap);

t_escape		*parse_escape(t_escape *escape, \
							const char **format, va_list *ap);
int				pf_parse_flags(const char *format, t_escape *escape);
int				pf_parse_precision(const char *format, \
							t_escape *escape, va_list *ap);
int				pf_parse_width(const char *format, \
							t_escape *escape, va_list *ap);

char			*ft_itoa_unsize_base(size_t dec_num, int base);

int				escape_print(int id, t_escape *escape);
int				pf_print_end(int id, t_escape *escape, \
							const char **format, int *offset);

int				ft_wchar_get_utf8_size(unsigned int wchar);
int				ft_wchar_to_utf8(unsigned int wchar, char *buf);
int				ft_wchar_get_utf8_strlen(wchar_t *w_str);
int				ft_wchar_str_to_utf8(wchar_t *w_str, char **str);

void			pf_format_f(t_escape *escape, va_list *ap);
void			pf_check_precision_f(t_escape *escape);
void			pf_switch_flags_f(t_escape *escape, int sign);

int				pf_found_text_colors(t_escape *escape, int i);
int				pf_found_bg_colors(t_escape *escape, int i);
int				pf_found_property(t_escape *escape, int i);
#endif
