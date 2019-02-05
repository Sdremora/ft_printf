/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_to_str_part2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:08:57 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/03 16:52:49 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_double_to_str.h"

int				pf_get_exponent(char *bits, int start, int len)
{
	int	exponent;
	int	i;
	int	n;
	int	mult;

	exponent = 0;
	i = start + len - 1;
	n = 0;
	mult = 0;
	while (i >= start)
	{
		if (n == 0)
			mult = 1;
		else
			mult *= 2;
		if (bits[i] == '1')
			exponent += mult;
		n++;
		i--;
	}
	return (exponent);
}

static void		mantissa_mult_expon(t_bnum *mantissa, int expon)
{
	if (expon > 0)
	{
		while (expon-- > 0)
			pf_bnum_2multdiv(mantissa, '*');
	}
	else
	{
		while (expon++ < 0)
			pf_bnum_2multdiv(mantissa, '/');
	}
}

t_bnum			*pf_get_mantissa(char *bits, int start, int expon)
{
	t_bnum	*mantissa;
	t_bnum	*num;
	int		i;
	int		end;

	mantissa = pf_bnum_ini(1);
	num = pf_bnum_ini(1);
	if (!mantissa || !num)
		return (NULL);
	i = start;
	end = ft_str_last_indexof(bits + start, '1') + start;
	while (i <= end)
	{
		pf_bnum_2multdiv(num, '/');
		if (bits[i] == '1')
			pf_bnum_plus_bnum(mantissa, num);
		i++;
	}
	pf_bnum_free(num);
	mantissa_mult_expon(mantissa, expon);
	return (mantissa);
}

char			*pf_check_boards(char *bits, char type)
{
	int		exp_len;
	int		flag_exp;
	int		flag_mant;

	exp_len = (type == 'f') ? DBL_EXP_LEN : LDBL_EXP_LEN + 1;
	if (ft_str_indexof(bits + 1, '1') < 0)
		return (ft_strdup("0.0"));
	flag_exp = ft_str_n_indexof(bits + 1, exp_len, '0');
	flag_mant = ft_str_indexof(bits + exp_len + 1, '1');
	if (flag_exp < 0 && flag_mant < 0)
		return (ft_strdup("inf"));
	flag_mant = ft_str_indexof(bits + exp_len + 2, '1');
	if (flag_exp < 0 && flag_mant < 0)
		return (ft_strdup("nan"));
	return (NULL);
}
