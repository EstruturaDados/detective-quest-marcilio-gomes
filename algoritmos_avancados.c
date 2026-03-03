#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó (sala)
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Cria uma nova sala dinamicamente
Sala* criarSala(char nome[]) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Exploração interativa
void explorarSalas(Sala *atual) {
    char opcao;

    while (atual != NULL) {

        printf("\nVoce esta em: %s\n", atual->nome);

        // Se for folha, fim do caminho
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Fim do caminho! Sala final encontrada.\n");
            break;
        }

        printf("Escolha um caminho:\n");
        if (atual->esquerda != NULL)
            printf("e -> Ir para a esquerda\n");
        if (atual->direita != NULL)
            printf("d -> Ir para a direita\n");
        printf("s -> Sair\n");
        printf("Opcao: ");

        scanf(" %c", &opcao);

        if (opcao == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        }
        else if (opcao == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        }
        else if (opcao == 's') {
            printf("Exploracao encerrada.\n");
            break;
        }
        else {
            printf("Opcao invalida ou caminho inexistente!\n");
        }
    }
}

int main() {

    // ===== Montagem da Mansão (estática) =====

    Sala *hall = criarSala("Hall de Entrada");

    hall->esquerda = criarSala("Biblioteca");
    hall->direita = criarSala("Sala de Jantar");

    hall->esquerda->esquerda = criarSala("Sala Secreta");
    hall->esquerda->direita = criarSala("Escritorio Antigo");

    hall->direita->esquerda = criarSala("Cozinha");
    hall->direita->direita = criarSala("Jardim Interno");

    // ===== Início da exploração =====
    explorarSalas(hall);

    return 0;
}