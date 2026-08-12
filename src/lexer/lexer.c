#include <ctype.h>

#include "lexer/lexer.h"
#include "lexer/token.h"
#include "util/array.h"

static const struct {
    const char *nonnull name;
    enum token_kind kind;
} keywords[] = {
    { "use", TOKEN_USE }
};

constexpr auto keywords_len = sizeof(keywords) / sizeof(*keywords);

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

static struct token lexer_build_token(const struct lexer *nonnull self, size_t length, enum token_kind kind) {
    return (struct token) {
        .value = &self->source[self->position],
        .length = length,
        .kind = kind,
        .line = self->line,
        .column = self->column
    };
}

struct token lexer_next(struct lexer *nonnull self) {
    while (isspace(self->current))
        lexer_advance(self);

    struct token token = lexer_build_token(self, 0, TOKEN_EOF);

    // null handling
    if (self->current == '\0')
        return token;

    // number handling
    if (isdigit(self->current)) {
        while (isdigit(self->current))
            lexer_advance(self);
        
        token.length = &self->source[self->position] - token.value;
        token.kind = TOKEN_NUMBER;
        return token;
    }

    // identifier/keyword handling
    // if (isalpha(self->current)) {
    //     while (isalnum(self->current))
    //         lexer_advance(self);

    //     token.length = &self->source[self->position] - token.value;
        
    // }

    switch (self->current) {
        // string handling
        case '"':
            lexer_advance(self);
            token = lexer_build_token(self, 0, TOKEN_STRING);

            while (self->current != '"' && self->current != '\0')
                lexer_advance(self);

            if (self->current == '\0') {
                self->result = LEXER_UNTERMINATED_STRING;
                return token;
            }

            token.length = &self->source[self->position] - token.value;
            lexer_advance(self);
            break;

        // symbol handling
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
