#include "lexer.h"
#include "minishell.h"

int is_operator(char c)
{
  return (c == '|' || c == '<' || c == '>');
}

int is_quote(char c)
{
  return (c == '\'' || c == '"');
}

int is_whitespace(char c)
{
  return (c == ' ' || c == '\t');
}

t_token_type get_char_type(char c)
{
    if (c == '|')
        return (TOKEN_PIPE);
    if (c == '\'')
        return (TOKEN_SINGLE_QUOTE);
    if (c == '"')
        return (TOKEN_DOUBLE_QUOTE);
    if (c == '>')
        return (TOKEN_REDIR_OUT);
    if (c == '<')
        return (TOKEN_REDIR_IN);
    if (c == ' ' || c == '\t')
        return (TOKEN_WHITESPACE);
    if (c == '\0')
        return (TOKEN_EOF);
    return (TOKEN_WORD);
}

t_token_type  get_operator_type(char *str, int *advanced)
{
  if (str[0] == '>' && str[1] == '>')
  {
    *advanced = 2;
    return (TOKEN_REDIR_APPEND);
  }
  if (str[0] == '<' && str[1] == '<')
  {
    *advanced = 2;
    return (TOKEN_REDIR_HEREDOC);
  }
  *advanced = 1;
  return (get_char_type(str[0])); 
}

char *extract_quoted_string(char *input, int *pos,
  char quote)
{
  int start;
  int  len;

  start = *pos + 1;
  len = 0;
  while (input[start + len] && input[start + len] != quote)
    len++;
  if (!input[start + len])
    return (NULL);
  *pos = start + len + 1;
  return (strndup(&input[start], len)); 
}

void  add_token(t_lexer *lexer, t_token *token)
{
  t_token *current;

  if (!lexer->token_list)
  {
    lexer->token_list = token;
    lexer->token_count++;
    return;
  }
  current = lexer->token_list;
  while (current->next)
    current = current->next;
  current->next = token;
  lexer->token_count++;
}

t_token *create_token()
{
  t_token *token;

  token = malloc(sizeof(t_token));
  if (!token)
    return (NULL);;
  token->type = TOKEN_NULL;
  token->value = NULL;
  token->next = NULL;
  return (token);
}

void  free_token(t_token *token)
{
  if (!token)
    return ;
  free(token->value);
  if (token->next)
    free(token->next);
  free(token);
}

size_t  count_tokens(char **tokens)
{
  size_t  len;
  len = 0;

  while(tokens[len] != NULL)
    len++;
  return (len);
}

t_lexer *lexer(char *input)
{
  t_lexer *lexer;
  t_token *token;
  int     i;
  int     w_start;
  int     advance;
  char    *unquoted;

  lexer = malloc(sizeof(t_lexer));
  if (!lexer)
    return (NULL);
  lexer->token_count = 0;
  lexer->token_list = NULL;
  i = 0;
  while (input[i])
  {
    while(input[i] && is_whitespace(input[i]))
      i++;
    if (!input[i])
      break ;
    token = create_token();
    if (!token)
      return (NULL);
    if (is_operator(input[i]))
    {
      advance = 0;
      token->type = get_operator_type(&input[i], &advance);
      token->value = strndup(&input[i], advance);
      i += advance;
    }
    else if (is_quote(input[i]))
    {
      unquoted = extract_quoted_string(input, &i, input[i]);
      token->type = TOKEN_WORD;
      token->value = unquoted;
      if (!token->value)
      {
        free_token(token);
        return (NULL);
      }
    }
    else
    {
      w_start = i;
      while (input[i] && !is_whitespace(input[i]) &&
        !is_operator(input[i]) && !is_quote(input[i]))
        i++;
      token->type = TOKEN_WORD;
      token->value = strndup(&input[w_start], i - w_start); 
    }
    add_token(lexer, token);
  }
  return (lexer);
}


/*********Debug*************************************/
void print_tokens(t_lexer *lexer)
{
    t_token *current = lexer->token_list;
    
    printf("Token count: %d\n", lexer->token_count);
    while (current)
    {
        printf("Type: %d, Value: '%s'\n", current->type, current->value);
        current = current->next;
    }
}

int main(void)
{
    char *test_commands[] = {
        "ls -l",
        "echo \"hello world\"",
        "cat < input.txt >> output.txt",
        "ls -l | grep test",
        NULL
    };
    
    for (int i = 0; test_commands[i]; i++)
    {
        printf("\nTesting: '%s'\n", test_commands[i]);
        t_lexer *lex = lexer(test_commands[i]);
        print_tokens(lex);
        // Add cleanup code
    }
    return (0);
}
