/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 15:54:44 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/04 18:08:51 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>
#include "ft_printf.h"
#include <fcntl.h>


int		main(void)
{
	char	*str;
	double num;
	long double num3;
	int 	num2;

	ft_printf("123{black}4567%%{def}%%\n");
	ft_printf("123{red}4567%%{def}%%\n");
	ft_printf("123{cyan}4567%%{def}%%\n");
	ft_printf("123{{cyan}4567%%{def}%%\n");
	ft_printf("raz{{cyan}dva{def}\n");
	ft_printf("12{red}красный{yellow}желтый{gray}серый{def}\n");
	ft_printf("12{red}{BG_CYAN}красныйжелтый{def}серый{BG_DEF}\n");
	ft_printf("12{BLINK}opa migni opa{N_BLINK}\n");
	ft_printf("12{BOLD}opa opa{N_BOLD}\n");
	ft_printf("12{UNDERLINE}opa opa{N_UNDERLINE}\n");
	ft_printf("12{INVERSE}opa opa{N_INVERSE}\n");
	// num = 1.0 / 0.0;
	// str = ft_get_bits(&num, sizeof(num));
	// ft_str_reverse(str);
	// printf("%s\n", str);
	// num3 = 1.0 / 0.0;
	// str = ft_get_bits(&num3, sizeof(num3));
	// ft_str_reverse(str);
	// printf("%s\n", str);
	// num3 = 1.0 / 0.0;
	// str = ft_get_bits(&num3, sizeof(num3) - 6);
	// ft_str_reverse(str);
	// printf("%s\n", str);
	// num3 = NAN;
	// str = ft_get_bits(&num3, sizeof(num3) - 6);
	// ft_str_reverse(str);
	// printf("%s\n", str);
	// num = INFINITY;
	// str = ft_get_bits(&num, sizeof(num));
	// ft_str_reverse(str);
	// printf("inf before ->\t%s\n", str);
	// num3 = num;
	// str = ft_get_bits(&num3, sizeof(num3) - 6);
	// ft_str_reverse(str);
	// printf("inf after ->\t%s\n", str);
	// num = NAN;
	// str = ft_get_bits(&num, sizeof(num));
	// ft_str_reverse(str);
	// printf("nan before ->\t%s\n", str);
	// num3 = num;
	// str = ft_get_bits(&num3, sizeof(num3) - 6);
	// ft_str_reverse(str);
	// printf("nan after ->\t%s\n", str);
	return (0);
}