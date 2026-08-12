#include "lexer/lexer.h"
#include "lexer/token.h"
#include <stdio.h>

int main(void) {
    var lexer = lexer_create("2 + 14 * 5");
    let result = lexer_lex(&lexer);
    let tokens = lexer.tokens;

    if (result != LEXER_SUCCESS) {
        let token = tokens.data[tokens.length - 1];
        switch (result) {
            case LEXER_INVALID_CHARACTER: printf(
                "error: invalid character '%.*s' at line %zu, column %zu\n",
                (int)token.length, token.value,
                token.line, token.column
            ); break;

            default: break;
        }

        return 1;
    }

    for (size_t i = 0; i < tokens.length; i++) {
        let token = tokens.data[i];
        printf("Token %zu, %u, %.*s\n", i, token.kind, (int)token.length, token.value);
    }
}
