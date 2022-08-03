/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:40:50 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/08/03 14:41:25 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* This function counts the number of words in the string to split. */

static int	ft_wdcount(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

/* This function returns the index of the first character of the "indexth" 
word. */

static int	ft_indexwd(char const *s, char c, int index)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c && index >= 0)
		{
			ret = i;
			index--;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	if (index < 0)
		return (ret);
	return (-1);
}

/* This function is a strdup of the word that starts at index start. */

static char	*ft_strdupwd(char const *s, char c, int start)
{
	int		i;
	int		j;
	int		len;
	char	*word;

	i = start;
	len = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i++] != c)
			len++;
		word = malloc(sizeof(char) * (len + 1));
		if (!word)
			return (NULL);
		while (j < len)
			word[j++] = s[start++];
		word[j] = '\0';
		return (word);
	}
	return (NULL);
}

static char	**ft_freesplit(char **strs, t_data *data)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
		free(strs[i++]);
	free(strs);
	error_mng("Malloc error", 0, data);
	return (NULL);
}

char	**ft_split(char const *s, char c, t_data *data)
{
	int		i;
	int		n;
	char	**strs;

	if (!s)
		return (NULL);
	i = 0;
	n = ft_wdcount(s, c);
	strs = malloc(sizeof(char *) * (n + 1));
	if (!strs)
		error_mng("Malloc error", 0, data);
	while (i < n)
	{
		strs[i] = ft_strdupwd(s, c, ft_indexwd(s, c, i));
		if (!strs[i])
			return (ft_freesplit(strs, data));
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
