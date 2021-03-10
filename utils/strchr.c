/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 21:42:01 by tjung             #+#    #+#             */
/*   Updated: 2021/03/10 20:52:37 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		s_len;
	char	tmp;

	s_len = (int)ft_strlen(s);
	tmp = (char)c;
	if (tmp == '\0')
		return ((char *)s + s_len);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == tmp)
			break ;
		i++;
	}
	if (s[i] != '\0')
		return ((char *)s + i);
	return (NULL);
}
