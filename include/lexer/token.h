#pragma once

#include <stddef.h>

enum token_kind {
    // values & data
    TOKEN_NUMBER,
    TOKEN_STRING,
    
    TOKEN_IDENTIFIER,

    // keywords
    TOKEN_USE,

    // symbols
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    
    // misc.
    TOKEN_EOF
};

struct token {
    const char *nonnull value; // slice of lexer source
    size_t length;

    enum token_kind kind;
    size_t line;
    size_t column;
};
