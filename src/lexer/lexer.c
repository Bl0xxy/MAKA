#include <ctype.h>

#include "lexer/lexer.h"
#include "lexer/token.h"
#include "util/array.h"

struct lexer lexer_create(const char *nonnull source) {
    return (struct lexer) {
        .source = source,
        .tokens = {0},

        .result = LEXER_SUCCESS,

        .current = *source,
        .position = 0,
        .column = 1,
        .line = 1
    };
}

void lexer_advance(struct lexer *nonnull self) {
    switch (self->current) {
        case '\0':  return;

        case '\n':  self->line++;
                    self->column = 1;
                    break;
        
        default:    self->column++;
                    break;
    }

    self->position++;
    self->current = self->source[self->position];
}

struct token lexer_next(struct lexer *nonnull self) {
    while (isspace(self->current))
        lexer_advance(self);

    let nonnull start = &self->source[self->position];

    struct token token = {
        .value = start,
        .length = 0,
        .kind = TOKEN_EOF,
        .line = self->line,
        .column = self->column
    };

    if (self->current == '\0')
        return token;

    if (isdigit(self->current)) {
        while (isdigit(self->current))
            lexer_advance(self);
        
        token.length = &self->source[self->position] - start;
        token.kind = TOKEN_NUMBER;
        return token;
    }

    switch (self->current) {
        case '+':
            lexer_advance(self);
            token.length = 1;
            token.kind = TOKEN_PLUS;
            break;

        case '-':
            lexer_advance(self);
            token.length = 1;
            token.kind = TOKEN_MINUS;
            break;

        case '*':
            lexer_advance(self);
            token.length = 1;
            token.kind = TOKEN_STAR;
            break;

        case '/':
            lexer_advance(self);
            token.length = 1;
            token.kind = TOKEN_SLASH;
            break;

        default:
            lexer_advance(self);
            self->result = LEXER_INVALID_CHARACTER;
            token.length = 1;
            break;
    }

    return token;
}

enum lexer_result lexer_lex(struct lexer *nonnull self) {
    while (true) {
        let token = lexer_next(self);
        array_push(&self->tokens, token);

        if (self->result != LEXER_SUCCESS)
            return self->result;

        if (token.kind == TOKEN_EOF)
            return LEXER_SUCCESS;
    }

    return LEXER_SUCCESS;
}
