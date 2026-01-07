
#include <stdio.h>
#include <stddef.h>

typedef struct {
    unsigned short value;
} token;

/*
  Gera um token a partir de dois caracteres.
  Retorna 1 se o par for repetido (aa, bb, etc),
  retorna 0 caso contrário.
 */

int tokenize_pair(char a, char b, token *out)
{
    if (a == b) {
        out->value = ((unsigned short)a << 8) | (unsigned short)b;
        return 1;
    }
    return 0;
}

int main(void)
{
    const char str[] = "Soommetthiingg";
    size_t str_size = sizeof(str) - 1;

    for (size_t i = 0; i + 1 < str_size; i++)
    {
        token t;

        if (tokenize_pair(str[i], str[i + 1], &t)) {
            printf("repeat pair: %c%c -> token %u\n",
                   str[i], str[i + 1], t.value);
        }
    }

    return 0;
}


