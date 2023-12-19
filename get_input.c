#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float get_float_input(char* prompt) {
    float input;
    char c;

    while (1) {
        printf("%s", prompt);
        if (scanf("%f", &input) == 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            return input;
        } else {
            printf("Entrada inválida. Tente novamente.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

int get_int_input(char* prompt) {
    int input;
    char buffer[100];  // Buffer para armazenar a entrada do usuário
    char c;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin)) {
            // Use sscanf para extrair um número inteiro do buffer
            if (sscanf(buffer, "%d", &input) == 1) {
                return input;
            } else {
                printf("Entrada inválida. Tente novamente.\n");
            }
        } else {
            printf("Erro na leitura. Tente novamente.\n");
        }

        // Limpa o buffer de entrada para evitar caracteres adicionais
        while ((c = getchar()) != '\n' && c != EOF);
    }
}


char get_char_input(char* prompt) {
    char input;
    char c;

    while (1) {
        printf("%s", prompt);
        if (scanf(" %c", &input) == 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            return input;
        } else {
            printf("Entrada inválida. Tente novamente.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

char* get_string_input(char* prompt) {
    static char buffer[100];
    printf("%s", prompt);

    if (fgets(buffer, sizeof(buffer), stdin)) {
        size_t len = strlen(buffer);

        // Remove o caractere de nova linha (\n) se presente
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        } else {
            // Limpa o buffer de entrada para evitar caracteres adicionais
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        return buffer;
    } else {
        printf("Entrada inválida. Tente novamente.\n");

        // Limpa o buffer de entrada
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return NULL;
    }
}

