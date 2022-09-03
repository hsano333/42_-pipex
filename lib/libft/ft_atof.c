/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 06:47:29 by hsano             #+#    #+#             */
/*   Updated: 2022/09/01 21:15:51 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_common.h"
#define NUMBER_LONG  1000000000000000000

static double	calc(long len, char *dot_point)
{
	double	tmp_double;
	size_t	power;
	double	tmp_power;
	size_t	tmp;

	power = 1;
	tmp = 0;
	tmp_double = 0;
	while (len-- && power < NUMBER_LONG)
	{
		power *= 10;
		tmp += (*(dot_point++) - '0') * NUMBER_LONG / power;
	}
	tmp_double = 0;
	tmp_power = NUMBER_LONG / 10;
	while (len > 0 && len--)
	{
		tmp_double += ((double)(*(dot_point++) - '0')) \
			* ((double)(tmp_power / (double)power));
		tmp_power /= 10;
	}
	return ((double)(tmp + tmp_double) / (double)NUMBER_LONG);
}

static char	*check_invalid_word(const char *str, int *error)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
			return ((char *)(&(str[i])));
		else if (!(ft_isdigit(str[i]) || str[i] == '-' || str[i] == '+'))
		{
			*error = true;
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

double	ft_atod(const char *str, int *error)
{
	long	len;
	char	*dot_point;
	double	result;
	long	tmp;
	int		minus_flag;

	tmp = ft_atol(str, error);
	if (*error == true)
		return (0.0);
	dot_point = check_invalid_word(str, error);
	if (dot_point == NULL)
		return ((float)tmp);
	minus_flag = false;
	if (tmp < 0 || (tmp == 0 && (dot_point - str >= 2) \
				&& *(dot_point - 2) == '-'))
		minus_flag = true;
	dot_point++;
	len = get_digit_len(dot_point, 0);
	if (len == 0)
		return ((double)tmp);
	result = (double)(calc(len, dot_point));
	if (minus_flag)
		return (0 - result + (double)tmp);
	return (result + (double)tmp);
}

float	ft_atof(const char *str, int *error)
{
	return ((float)ft_atod(str, error));
}
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <math.h>
//int main(int argc,char **argv)
//{
//	char *s1;
//	//int len;
//	//int	result;
//	int	error;
//	long	l_test = 10;
//	double	d_test = 0.12345;
//
//	//result = 0;
//	printf("LONGMAX=%ld\n",LONG_MAX);
//	printf("LLONGMAX=%lld\n",LLONG_MAX);
//	printf("ULLONGMAX=%lld\n",ULLONG_MAX);
//	printf("INTMAX=%d\n",INT_MAX);
//	printf("10 = :%.30lf, \n", (double)l_test + d_test);
//	if (argc == 2)
//	{
//		s1 = argv[1];
//		//s1 = "\t\v\f\r\n \f-06050";
//		//len = atoi(s1);
//		//result = ft_atoi(s1,&error);
//		printf("input:%s\n",s1);
//		printf("my atol:%.30lf, error=%d\n", ft_atof(s1,&error),error);
//		printf("my atod:%.30lf, error=%d\n", ft_atod(s1,&error),error);
//		printf("error=%d\n",error);
//		//printf("nanf test=%lf\n", nan(s1));
//		//printf("nanf test=%lf\n", nanf(s1));
//		//printf("my atof:%lf, error=%d\n", ft_atof(s1,&error),error);
//		//printf("test:%d\n",len);
//	}
//
//	return (0);
//}
