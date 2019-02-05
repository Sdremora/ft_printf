/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_escape_part1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 10:40:12 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 09:52:59 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pf_parse_specifier(const char *format, t_escape *escape)
{
	int	offset;

	offset = 0;
	if (*format != '\0' && ft_str_indexof(ESCAPE_SPECIFIERS, *format) >= 0)
	{
		escape->specifier = *format;
		offset++;
	}
	return (offset);
}

/*
**	Если в управляющей последовательности стоит несколько спецификаторов
**	длины. Будет учтен только один, тот у которого меньшее
**	присваиваемое значение. Эти значения подоброны подбором.
*/

static int	pf_set_length_spec(t_escape *escape, t_len_sp len_sp)
{
	int		offset;

	if (escape->len_sp > len_sp)
		escape->len_sp = len_sp;
	if (len_sp == LSP_LL || len_sp == LSP_HH)
		offset = 2;
	else
		offset = 1;
	return (offset);
}

static int	pf_parse_length(const char *format, t_escape *escape)
{
	int		offset;

	if (g_status)
		return (0);
	offset = 0;
	if (*format == 'l' && *(format + 1) != 'l')
		offset = pf_set_length_spec(escape, LSP_L);
	else if (*format == 'l' && *(format + 1) == 'l')
		offset = pf_set_length_spec(escape, LSP_LL);
	else if (*format == 'L')
		offset = pf_set_length_spec(escape, LSP_UL);
	else if (*format == 'z')
		offset = pf_set_length_spec(escape, LSP_Z);
	else if (*format == 'j')
		offset = pf_set_length_spec(escape, LSP_J);
	else if (*format == 't')
		offset = pf_set_length_spec(escape, LSP_T);
	else if (*format == 'h' && *(format + 1) != 'h')
		offset = pf_set_length_spec(escape, LSP_H);
	else if (*format == 'h' && *(format + 1) == 'h')
		offset = pf_set_length_spec(escape, LSP_HH);
	return (offset);
}

/*
**	Находит случай, когда в последовательность попадает символ
**	с которым не работает ни один из парсеров или когда дошли до конца строки,
**	но спецификатор не был найден.
**	если это левый символ, то он будет обработан, как чар со всеми флагами
**	если \0 то последовательность игнорируется
*/

static void	pf_found_bad_chr(t_escape *escape, const char *format, \
						int *offset, int offset_temp)
{
	if (*offset == offset_temp)
	{
		escape->specifier = ERROR_SPECIFIER;
		if (*(format + *offset) != '\0')
		{
			escape->specifier = ERROR_SPECIFIER;
			escape->error_char = *(format + *offset);
			escape->str_len = 1;
			(*offset)++;
		}
		else
		{
			g_status = E_BAD_ESCAPE;
		}
	}
}

t_escape	*parse_escape(t_escape *escape, const char **format, va_list *ap)
{
	int			offset;
	int			offset_temp;

	(*format)++;
	offset = 0;
	offset_temp = offset;
	while (!g_status && escape->specifier == '\0')
	{
		offset += pf_parse_flags(*format + offset, escape);
		offset += pf_parse_width(*format + offset, escape, ap);
		offset += pf_parse_precision(*format + offset, escape, ap);
		offset += pf_parse_length(*format + offset, escape);
		offset += pf_parse_specifier(*format + offset, escape);
		pf_found_bad_chr(escape, *format, &offset, offset_temp);
		offset_temp = offset;
	}
	*format += offset;
	return (escape);
}
