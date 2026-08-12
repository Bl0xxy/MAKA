#pragma once

#include <stddef.h>

enum token_kind {
    TOKEN_NUMBER,
    TOKEN_STRING,

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    
    TOKEN_EOF
};

struct token {
    const char *nonnull value; // slice of lexer source
    size_t length;

    enum token_kind kind;
    size_t line;
    size_t column;
};
