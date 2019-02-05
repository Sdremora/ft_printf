/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 12:54:47 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 13:26:02 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_simple(int fd, t_escape *escape)
{
	int len;
	int i1;
	int i2;

	len = 0;
	if (escape->str_simple != NULL)
	{
		i1 = ft_str_indexof(escape->str_simple, '{');
		i2 = (i1 >= 0) ? ft_str_indexof(escape->str_simple + i1, '}') : -1;
		if (i1 >= 0 && i2 >= 0)
		{
			i2 = 0;
			while (i2 >= 0)
				i2 = pf_found_text_colors(escape, i1);
			i2 = 0;
			while (i2 >= 0)
				i2 = pf_found_bg_colors(escape, i1);
			i2 = 0;
			while (i2 >= 0)
				i2 = pf_found_property(escape, i1);
		}
		len = ft_strlen(escape->str_simple);
		write(fd, escape->str_simple, len);
	}
	return (len);
}

static int	print_body(int fd, t_escape *escape)
{
	int len;

	len = 0;
	if (escape->prefix_len > 0)
	{
		len += escape->prefix_len;
		write(fd, escape->prefix, escape->prefix_len);
	}
	write(fd, escape->str, escape->str_len);
	len += escape->str_len;
	if (escape->postfix_len > 0)
	{
		len += escape->postfix_len;
		write(fd, escape->postfix, escape->postfix_len);
	}
	return (len);
}

int			escape_print(int fd, t_escape *escape)
{
	int			count;

	if (g_status >= 0 || g_status == E_BAD_ESCAPE)
	{
		count = print_simple(fd, escape);
		if (g_status >= 0)
			count += print_body(fd, escape);
	}
	else
		count = -1;
	free(escape->str_simple);
	free(escape->str);
	free(escape->prefix);
	free(escape->postfix);
	return (count);
}

/*
**	Печатает окончание управляющей строки
**	При "%10.10sTyc" -> выведет Tyc
*/

int			pf_print_end(int fd, t_escape *escape, \
				const char **format, int *offset)
{
	int	len;

	escape_initial(escape);
	escape->str_simple = ft_strnew(*offset);
	if (escape->str_simple != NULL)
		ft_strncat(escape->str_simple, *format, *offset);
	else
		g_status = E_NO_MEM;
	len = escape_print(fd, escape);
	*format += *offset;
	*offset = 0;
	return (len);
}
