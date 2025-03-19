/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:28:11 by iasonov           #+#    #+#             */
/*   Updated: 2025/03/19 16:06:55 by aevstign         ###   ########.fr       */
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

<<<<<<< Updated upstream
sig_atomic_t	g_sig_status;

int	readline_hook(void)
{
	if (g_sig_status == SIGINT || g_sig_status == SIGQUIT)
	{
		g_sig_status = 0;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return (SUCCESS);
=======
void	free_token_callback(void *token)
{
	t_token *t;

	t = (t_token *)token;
	if (t)
	{
		free(t->value);
		free(t);
	}
}

void	free_command_args(char **args)
{
	int i;

	i = 0;
	if (args)
	{
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
}

void	free_ast_tree(t_ast_node *node)
{
	if (!node)
		return ;
	free_command_args(node->args);
	if (node->redir.heredoc_delim)
		free(node->redir.heredoc_delim);
	if (node->redir.infile)
		free(node->redir.infile);
	if (node->redir.outfile)
		free(node->redir.outfile);
	free_ast_tree(node->left);
	free_ast_tree(node->right);
	free(node);
>>>>>>> Stashed changes
}

int	main_loop(t_envp *envp)
{
	int			exit_status;
	char		*input;
	t_list		*token_list;
	t_ast_node	*ast_tree;

	exit_status = 0;
	while (1)
	{
		ast_tree = NULL;
		input = read_input(envp);
		token_list = lexer(input);
		free(input);
		debug(input, token_list, ast_tree, 0);
		ast_tree = parser(token_list, *envp);
		ft_lstclear(&token_list, free_token_callback);
		debug(input, token_list, ast_tree, 1);
		exec_tree(ast_tree, envp, &exit_status);
		free_ast_tree(ast_tree);
	}
}

int	main(int argc, char **argv, char **envp_orig)
{
	t_envp		envp;

	(void)argc;
	(void)argv;
	init_signals();
	rl_event_hook = &readline_hook;
	if (setup_envp(&envp, envp_orig) == FAILURE)
		return (EXIT_FAILURE);
	main_loop(&envp);
	return (0);
}
