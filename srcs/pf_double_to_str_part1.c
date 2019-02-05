/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_to_str_part1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:08:57 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/03 15:42:51 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_double_to_str.h"

static char		*parse_double(double num)
{
	char	*bits;
	int		expon;
	t_bnum	*mantissa;
	char	*result;

	bits = ft_get_bits(&num, sizeof(num));
	if (bits == NULL)
		return (NULL);
	ft_str_reverse(bits);
	result = pf_check_boards(bits, 'f');
	if (result == NULL)
	{
		expon = pf_get_exponent(bits, 1, DBL_EXP_LEN) - DBL_EXP_OFFSET;
		mantissa = pf_get_mantissa(bits, DBL_EXP_LEN + 1, expon);
		if (mantissa == NULL)
			return (NULL);
		result = pf_bnum_getstr(mantissa);
		pf_bnum_free(mantissa);
	}
	free(bits);
	return (result);
}

static char		*parse_long_double(long double num)
{
	char	*bits;
	int		expon;
	t_bnum	*mantissa;
	char	*result;

	bits = ft_get_bits(&num, sizeof(num) - 6);
	if (bits == NULL)
		return (NULL);
	ft_str_reverse(bits);
	result = pf_check_boards(bits, 'l');
	if (result == NULL)
	{
		expon = pf_get_exponent(bits, 1, LDBL_EXP_LEN) - LDBL_EXP_OFFSET;
		mantissa = pf_get_mantissa(bits, LDBL_EXP_LEN + 2, expon);
		result = pf_bnum_getstr(mantissa);
		pf_bnum_free(mantissa);
	}
	free(bits);
	return (result);
}

/*
**	l -> double
**	L -> long double
*/

char			*pf_double_to_str(char *sp, ...)
{
	va_list		args;
	char		*result;

	va_start(args, sp);
	if (*sp != 'L')
		result = parse_double(va_arg(args, double));
	else
		result = parse_long_double(va_arg(args, long double));
	va_end(args);
	return (result);
}
