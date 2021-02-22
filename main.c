/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 01:35:22 by tjung             #+#    #+#             */
/*   Updated: 2021/02/18 21:01:12 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		print_error(int e, char *msg)
{
	printf("%s", msg);
	return (e);
}

int		check_save_opt(char *s)
{
	char	*opt;
	int		i;

	opt = "--save";
	i = 0;
	while (s[i] != '\0')
	{
		if (opt[i] != s[i])
			return (-1);
		i++;
	}
	if (i != 6)
		return (-1);
	return (1);
}

int		check_file_name(char *s, char *extension)
{
	int		i;
	int		j;

	i = 0;
	j = 4;
	while (s[i] != '\0')
		i++;
	if (i > 4)
	{
		while (j)
		{
			if (extension[4 - j] != s[i - j])
				return (-1);
			j--;
		}
		return (1);
	}
	return (-1);
}

int		main(int ac, char **av)
{
	int		bmp;

	bmp = 0;
	if (ac > 1 && ac < 4)
	{
		if (ac == 3)
		{
			if ((bmp = check_save_opt(av[2])) == -1)
				return (print_error(0, "Error\nInvalid parameter(main)\n"));
		}
		if (check_file_name(av[1], ".cub") == -1)
			return (print_error(0, "Error\nInvalid parameter(main)\n"));
		start_cub3d(av[1], bmp);
		return (0);
	}
	return (print_error(0, "Error\nInvalid parameter(main)\n"));
}
