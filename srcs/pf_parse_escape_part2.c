/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_escape_part2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:29:09 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 09:53:14 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_star_width(t_escape *escape, va_list *ap)
{
	int num;

	num = va_arg(*ap, int);
	if (num < 0)
	{
		escape->flags[F_MINUS] = '-';
		num = -num;
	}
	escape->width = num;
}

int			pf_parse_width(const char *format, t_escape *escape, va_list *ap)
{
	int		offset;
	char	temp[21];

	if (g_status || *format == '0' || (*format != '*' && !ft_isdigit(*format)))
		return (0);
	if (*format == '*')
	{
		parse_star_width(escape, ap);
		offset = 1;
	}
	else
	{
		offset = 0;
		ft_bzero(temp, 21);
		while (ft_isdigit(*(format + offset)))
			offset++;
		if (offset > 20)
			ft_strncpy(temp, format, 20);
		else
			ft_strncpy(temp, format, offset);
		escape->width = ft_atoi(temp);
	}
	return (offset);
}

int			pf_parse_precision(const char *format, \
				t_escape *escape, va_list *ap)
{
	int		offset;
	char	temp[21];

	if (g_status || *format != '.')
		return (0);
	offset = 1;
	if (*(format + offset) == '*')
	{
		escape->precision = va_arg(*ap, int);
		offset = 2;
	}
	else
	{
		ft_bzero(temp, 21);
		while (ft_isdigit(*(format + offset)))
			offset++;
		if (offset > 20)
			ft_strncpy(temp, format + 1, 20);
		else
			ft_strncpy(temp, format + 1, offset);
		escape->precision = ft_atoi(temp);
	}
	return (offset);
}

int			pf_parse_flags(const char *format, t_escape *escape)
{
	int		offset;
	int		n;

	offset = 0;
	while (*(format + offset) != '\0' && \
			(n = ft_str_indexof(ESCAPE_FLAGS, *(format + offset))) >= 0)
	{
		escape->flags[n] = *(format + offset);
		offset++;
	}
	return (offset);
}
