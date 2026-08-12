#include "lexer/lexer.h"

struct lexer lexer_create(const char *nonnull source) {
    return (struct lexer) {
        .source = source,
        .tokens = {0},
        .current = *source,
        .position = 0,
        .column = 0,
        .line = 0
    };
}

void lexer_advance(struct lexer *nonnull self) {
    switch (self->current) {
        case '\0':  return;

        case '\n':  self->line++;
                    self->column = 0;
                    break;
        
        default:    self->column++;
                    break;
    }

    self->position++;
    self->current = self->source[self->position];
}

enum lexer_result lexer_lex(struct lexer *nonnull self) {
    return LEXER_SUCCESS;
}
