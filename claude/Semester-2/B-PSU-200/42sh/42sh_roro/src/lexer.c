/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Lexical analysis for 42sh shell
*/

#include "shell.h"

static int is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '&' || 
            c == ';' || c == '(' || c == ')' || c == '`');
}

static token_type_t get_token_type(char *str)
{
    if (strcmp(str, "|") == 0)
        return TOKEN_PIPE;
    if (strcmp(str, "<") == 0)
        return TOKEN_REDIRECT_IN;
    if (strcmp(str, ">") == 0)
        return TOKEN_REDIRECT_OUT;
    if (strcmp(str, ">>") == 0)
        return TOKEN_REDIRECT_APPEND;
    if (strcmp(str, "2>") == 0)
        return TOKEN_REDIRECT_ERR;
    if (strcmp(str, "&") == 0)
        return TOKEN_BACKGROUND;
    if (strcmp(str, ";") == 0)
        return TOKEN_SEMICOLON;
    if (strcmp(str, "&&") == 0)
        return TOKEN_AND;
    if (strcmp(str, "||") == 0)
        return TOKEN_OR;
    if (strcmp(str, "(") == 0)
        return TOKEN_LPAR;
    if (strcmp(str, ")") == 0)
        return TOKEN_RPAR;
    if (strcmp(str, "`") == 0)
        return TOKEN_BACKTICK;
    return TOKEN_WORD;
}

token_t *create_token(token_type_t type, char *value)
{
    token_t *token = malloc(sizeof(token_t));
    
    if (!token) {
        return NULL;
    }
    
    token->type = type;
    token->value = my_strdup(value);
    token->next = NULL;
    
    if (!token->value) {
        free(token);
        return NULL;
    }
    
    return token;
}

static char *extract_word(char **line)
{
    char *start = *line;
    char *word;
    int len = 0;
    int in_quotes = 0;
    char quote_char = 0;
    int word_start = 0;
    
    while (start[len]) {
        if (!in_quotes && (start[len] == '\'' || start[len] == '"')) {
            in_quotes = 1;
            quote_char = start[len];
            len++; // Skip opening quote
            continue;
        } else if (in_quotes && start[len] == quote_char) {
            in_quotes = 0;
            quote_char = 0;
            len++; // Skip closing quote
            break;
        } else if (!in_quotes && (start[len] == ' ' || start[len] == '\t' || 
                                 is_special_char(start[len]))) {
            break;
        }
        len++;
    }
    
    // Remove quotes from the result
    if (quote_char != 0 || (len > 0 && (start[0] == '\'' || start[0] == '"'))) {
        word_start = 1;
        len = len > 2 ? len - 2 : 0;
    }
    
    word = malloc(len + 1);
    if (!word) {
        return NULL;
    }
    
    strncpy(word, start + word_start, len);
    word[len] = '\0';
    
    *line += (quote_char != 0 ? len + 2 : len);
    return word;
}

static char *extract_operator(char **line)
{
    char *start = *line;
    char *op;
    int len = 1;
    
    // Check for double character operators
    if ((start[0] == '>' && start[1] == '>') ||
        (start[0] == '&' && start[1] == '&') ||
        (start[0] == '|' && start[1] == '|') ||
        (start[0] == '2' && start[1] == '>')) {
        len = 2;
    }
    
    op = malloc(len + 1);
    if (!op) {
        return NULL;
    }
    
    strncpy(op, start, len);
    op[len] = '\0';
    
    *line += len;
    return op;
}

token_t *tokenize(char *line)
{
    token_t *head = NULL;
    token_t *tail = NULL;
    char *current = line;
    
    while (*current) {
        // Skip whitespace
        while (*current == ' ' || *current == '\t') {
            current++;
        }
        
        if (*current == '\0') {
            break;
        }
        
        char *token_str;
        token_t *token;
        
        if (is_special_char(*current)) {
            token_str = extract_operator(&current);
        } else {
            token_str = extract_word(&current);
        }
        
        if (!token_str) {
            free_tokens(head);
            return NULL;
        }
        
        token = create_token(get_token_type(token_str), token_str);
        free(token_str);
        
        if (!token) {
            free_tokens(head);
            return NULL;
        }
        
        if (!head) {
            head = tail = token;
        } else {
            tail->next = token;
            tail = token;
        }
    }
    
    // Add EOF token only if we have tokens
    if (head) {
        token_t *eof_token = create_token(TOKEN_EOF, "");
        if (!eof_token) {
            free_tokens(head);
            return NULL;
        }
        tail->next = eof_token;
    } else {
        // Empty line - create single EOF token
        head = create_token(TOKEN_EOF, "");
    }
    
    return head;
}

void free_tokens(token_t *tokens)
{
    while (tokens) {
        token_t *next = tokens->next;
        free(tokens->value);
        free(tokens);
        tokens = next;
    }
}