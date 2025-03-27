/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:28:11 by iasonov           #+#    #+#             */
/*   Updated: 2025/03/27 13:17:49 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_sig_status;

int	readline_hook(void)
{
	if (g_sig_status == SIGINT)
	{
		g_sig_status = 0;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return (SUCCESS);
}

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

	g_sig_status = 0;
	input = readline("minishell$> ");
	if (input == NULL)
	{
		free_envp(*envp);
		rl_clear_history();
		write(STDOUT_FILENO, "exit\n", 5);
		exit(SUCCESS);
	}
	add_history(input);
	return (input);
}

int	main_loop(t_envp *envp)
{
	char			*input;
	t_list			*token_list;
	t_ast_node		*ast_tree;
	t_shell_state	shell_state;
	int				last_exit_code;

	last_exit_code = 0;
	shell_state.last_exit_code = &last_exit_code;
	shell_state.envp = envp;
	ast_tree = NULL;
	while (1)
	{
		input = read_input(envp);
		token_list = lexer(input);
		debug(input, token_list, ast_tree, 0);
		if (token_list)
		{
			ast_tree = parser(token_list, shell_state);
			debug(input, token_list, ast_tree, 1);
			exec_tree(ast_tree, &shell_state);
			if (ast_tree)
				free_ast_tree(ast_tree);
		}
		free(input);
	}
}

int	main(int argc, char **argv, char **envp_orig)
{
	t_envp		envp;

	(void)argc;
	(void)argv;
	init_signals();
	rl_event_hook = &readline_hook;
	envp = NULL;
	if (setup_envp(&envp, envp_orig) == FAILURE)
	{
		free_envp(envp);
		return (EXIT_FAILURE);
	}
	main_loop(&envp);
	free_envp(envp);
	rl_clear_history();
	return (0);
}
