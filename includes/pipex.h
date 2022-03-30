/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:53:21 by mlecherb          #+#    #+#             */
/*   Updated: 2022/03/30 16:31:01 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "functions.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>

# define ERROR_NUMBER_ARGS "Error: pipex takes 4 arguments"
# define ERROR_INIT_PIPEX "Error: malloc 'pipex'"
# define ERROR_OPEN_FILE_READ "Error: open file for reading"
# define ERROR_OPEN_FILE_WRITE "Error: open file for writing"
# define ERROR_SPLIT_CMD "Error: malloc in parsing command"
# define ERROR_NO_PATHS_IN_ENVP "Error: no PATH in envp"
# define ERROR_PARSING_PATHS "Error: malloc in parsing"
# define ERROR_SEARCH_PATH_CMD "Error: malloc in search path"
# define ERROR_NO_PATH_CMD "No path for command"
# define ERROR_PIPE "Error: create pipe"
# define ERROR_FORK "Error: create child-process"
# define ERROR_DUP2 "Error: dup2"
# define ERROR_CLOSE_FD "Error: close fd"
# define ERROR_EXECVE "Error: execve"
# define ERROR_WAIT_CHILD1 "Error: waitpid child1"
# define ERROR_WAIT_CHILD2 "Error: waitpid child2"

typedef struct s_pipex
{
	int		end[2];
	char	**argv;
	char	**envp;
	int		infile;
	int		outfile;
	char	**cmd1;
	char	**cmd2;
	char	**paths;
	char	*path1;
	char	*path2;
	pid_t	child1;
	pid_t	child2;
}			t_pipex;

void	parsing_data(t_pipex *pipex, char **argv, char **envp);

t_pipex	*init_pipex(void);
void	free_pipex(t_pipex *pipex);
void	free_array(char **array);
void	end_program(char *mess, t_pipex *pipex, int code);

size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);

#endif