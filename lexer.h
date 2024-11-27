typedef enum e_token_type {
    TOKEN_WORD,         // Regular words/commands
    TOKEN_PIPE,         // |
    TOKEN_REDIR_IN,     // <
    TOKEN_REDIR_OUT,    // >
    TOKEN_REDIR_APPEND, // >>
    TOKEN_REDIR_HEREDOC,// <<
    TOKEN_SINGLE_QUOTE, // '
    TOKEN_DOUBLE_QUOTE, // "
    TOKEN_WHITESPACE,   // Space, tab, etc.
    TOKEN_EOF,          // End of input
    TOKEN_ERROR,        // For error handling
    TOKEN_NULL,
}   t_token_type;

typedef struct s_token {
  t_token_type      type;
  char            *value;
  struct  s_token *next;
}              t_token;

typedef  struct s_lexer {
  t_token  *token_list;
  int   token_count;
}               t_lexer;



#define MAX_TOKENS 100