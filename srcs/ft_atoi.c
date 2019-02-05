/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 14:16:08 by sdremora          #+#    #+#             */
/*   Updated: 2019/01/17 18:09:12 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define LONG_MAX 9223372036854775807

int		ft_atoi(const char *str)
{
	unsigned long int	res;
	int					is_negative;

	is_negative = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			is_negative = -1;
		str++;
	}
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (((res == LONG_MAX / 10 && (*str - '0') > 7) || \
			res > LONG_MAX / 10) && is_negative == 1)
			return (-1);
		else if (((res == LONG_MAX / 10 && (*str - '0') > 8) || \
			res > LONG_MAX / 10) && is_negative == -1)
			return (0);
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * is_negative);
}
