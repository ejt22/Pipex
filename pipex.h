/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:16:24 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/08/01 15:53:10 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		fd1;
	int		fd2;
	int		pipe[2];
	pid_t	pid1;
	pid_t	pid2;
	char	**cmd1;
	char	**cmd2;
	char	**path_cmd1;
	char	**path_cmd2;
}	t_data;

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2, t_data *data);
char	**ft_split(char const *s, char c, t_data *data);
void	free_strs(char *strs[]);
void	free_struct(t_data *data);
void	error_mng(char *type, int is_perror, t_data *data);
char	**find_path(char *cmd[], char *envp[], t_data *data);
char	*access_path(char *path_cmd[], t_data *data);

#endif
