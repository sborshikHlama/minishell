/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:28:11 by iasonov           #+#    #+#             */
/*   Updated: 2025/03/14 12:32:53 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	debug(char *input, t_list *list, t_ast_node *ast_tree, int ast_flag)
{
	if (DEBUG_STATUS && !ast_flag)
		display_tokens(list);
	else if (DEBUG_STATUS && ast_flag)
	{
		display_ast(ast_tree, 0);
		write(STDOUT_FILENO, "Entered: ", 9);
		write(STDOUT_FILENO, input, ft_strlen(input));
		write(STDOUT_FILENO, "\n", 1);
	}
	return ;
}

char	*read_input(t_envp *envp)
{
	char	*input;

	input = readline("minishell$> ");
	if (input == NULL)
	{
		free_envp(*envp);
		write(STDOUT_FILENO, "exit\n", 5);
		return (NULL);
	}
	add_history(input);
	return (input);
}

int	main_loop(t_envp *envp)
{
	char		*input;
	t_list		*token_list;
	t_ast_node	*ast_tree;

	ast_tree = NULL;
	while (1)
	{
		input = read_input(envp);
		token_list = lexer(input);
		debug(input, token_list, ast_tree, 0);
		ast_tree = parser(token_list, *envp);
		debug(input, token_list, ast_tree, 1);
		exec_tree(ast_tree, envp);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp_orig)
{
	t_envp		envp;

	(void)argc;
	(void)argv;
	if (setup_envp(&envp, envp_orig) == FAILURE)
		return (EXIT_FAILURE);
	main_loop(&envp);
	return (0);
}
