/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 11:50:29 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 09:26:02 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int g_status;

static void	spec_switch(t_escape *escape, va_list *ap)
{
	char sp;

	sp = escape->specifier;
	if (sp == 's' || sp == 'S')
		pf_format_s(escape, ap);
	else if (sp == 'd' || sp == 'D' || sp == 'i')
		pf_format_di(escape, ap);
	else if (sp == 'u' || sp == 'U' || sp == 'o' || sp == 'O' \
			|| sp == 'x' || sp == 'X')
		pf_format_oux(escape, ap, sp);
	else if (sp == '%')
		pf_format_c_char(escape, '%');
	else if (sp == 'c' || sp == 'C')
		pf_format_c_ap(escape, ap);
	else if (sp == 'p')
		pf_format_p(escape, ap);
	else if (sp == 'f' || sp == 'F')
		pf_format_f(escape, ap);
	else if (sp == ERROR_SPECIFIER && escape->error_char != '\0')
		pf_format_c_char(escape, escape->error_char);
}

/*
**	выкидывает: E_NO_MEM
**	пробрасывает : E_BAD_ESCAPE и E_NO_MEM
*/

static int	escape_handle(const char **format, int *offset, \
							t_escape *escape, va_list *ap)
{
	if (*offset > 0)
	{
		escape->str_simple = ft_strsub(*format, 0, *offset);
		if (escape->str_simple == NULL)
			return (set_status(E_NO_MEM));
		*format += *offset;
		*offset = 0;
	}
	parse_escape(escape, format, ap);
	if (g_status < 0)
		return (ERROR);
	spec_switch(escape, ap);
	if (g_status < 0)
		return (ERROR);
	return (TRUE);
}

static int	inner_printf(int fd, const char *format, va_list *ap)
{
	t_escape	escape;
	int			offset;
	int			count;

	offset = 0;
	count = 0;
	while (*format != '\0' && !g_status)
	{
		if (*(format + offset) == '\0')
			count += pf_print_end(fd, &escape, &format, &offset);
		else if (*(format + offset) == '%')
		{
			escape_initial(&escape);
			escape_handle(&format, &offset, &escape, ap);
			count += escape_print(fd, &escape);
			if (g_status == E_NO_MEM || g_status == E_CONVERT_UTF8)
				return (ERROR);
		}
		else
			offset++;
	}
	return (count);
}

int			ft_fprintf(int fd, const char *format, ...)
{
	va_list		ap;
	int			count;

	g_status = 0;
	if (fd < 0)
		return (ERROR);
	va_start(ap, format);
	count = inner_printf(fd, format, &ap);
	va_end(ap);
	return (count);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	int			count;

	g_status = 0;
	va_start(ap, format);
	count = inner_printf(1, format, &ap);
	va_end(ap);
	return (count);
}
