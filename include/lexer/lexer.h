#pragma once

#include <stddef.h>
#include "util/array.h"

struct lexer {
    const char *nonnull source;
    array(const struct token) tokens;
    char current;
    size_t position;
    size_t column;
    size_t line;
};

enum [[nodiscard]] lexer_result {
    LEXER_SUCCESS,
    LEXER_INVALID_CHARACTER,
    LEXER_INVALID_NUMBER,
    LEXER_UNTERMINATED_STRING
};

struct lexer lexer_create(const char *nonnull source);
void lexer_advance(struct lexer *nonnull self);
struct token lexer_next(struct lexer *nonnull self);
enum lexer_result lexer_lex(struct lexer *nonnull self);

