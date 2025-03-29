/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:28:11 by iasonov           #+#    #+#             */
/*   Updated: 2025/03/29 17:24:15 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	debug(char *input, t_list *list, t_ast_node *ast_tree, int ast_flag)
// {
// 	if (DEBUG_STATUS && !ast_flag)
// 		display_tokens(list);
// 	else if (DEBUG_STATUS && ast_flag)
// 	{
// 		display_ast(ast_tree, 0);
// 		write(STDOUT_FILENO, "Entered: ", 9);
// 		write(STDOUT_FILENO, input, ft_strlen(input));
// 		write(STDOUT_FILENO, "\n", 1);
// 	}
// 	return ;
// }

char	*read_input(t_shell_state *shell_state)
{
	char	*input;
	int		i;

	input = readline("minishell$> ");
	if (input == NULL)
	{
		free_envp(*(shell_state->envp));
		rl_clear_history();
		write(STDOUT_FILENO, "exit\n", 5);
		exit(SUCCESS);
	}
	i = 0;
	while (input[i] != '\0')
	{
		if (ft_strchr(" \t\n", input[i++]) == NULL)
		{
			add_history(input);
			break ;
		}
	}
	return (env_expander(input, shell_state));
}

int	main_loop(t_envp *envp)
{
	char			*input;
	t_list			*token_list;
	t_ast_node		*ast_tree;
	t_shell_state	shell_state;

	shell_state.last_exit_code = 0;
	shell_state.envp = envp;
	while (1)
	{
		input = read_input(&shell_state);
		token_list = lexer(input);
		free(input);
		if (token_list)
		{
			ast_tree = parser(token_list, shell_state);
			shell_state.first_node = ast_tree;
			exec_tree(ast_tree, &shell_state);
			if (ast_tree)
				free_ast_tree(ast_tree);
		}
	}
}

int	main(void)
{
	t_envp	envp;

	if (init_signals() == FAILURE)
		return (EXIT_FAILURE);
	rl_startup_hook = &readline_startup_hook;
	rl_event_hook = &readline_event_hook;
	envp = NULL;
	if (setup_envp(&envp) == FAILURE)
		return (EXIT_FAILURE);
	main_loop(&envp);
	free_envp(envp);
	rl_clear_history();
	return (0);
}
