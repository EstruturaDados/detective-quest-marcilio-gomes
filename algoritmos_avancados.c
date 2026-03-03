#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================= ÁRVORE DE SALAS =================

typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
    char pista[50]; // pista encontrada na sala (se houver)
} Sala;

Sala* criarSala(char nome[], char pista[]) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// ================= BST DE PISTAS =================

typedef struct NoPista {
    char pista[50];
    struct NoPista *esq;
    struct NoPista *dir;
} NoPista;

NoPista* criarNoPista(char pista[]) {
    NoPista *novo = (NoPista*) malloc(sizeof(NoPista));
    strcpy(novo->pista, pista);
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

NoPista* inserir(NoPista *raiz, char pista[]) {
    if (raiz == NULL)
        return criarNoPista(pista);

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esq = inserir(raiz->esq, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->dir = inserir(raiz->dir, pista);

    return raiz;
}

void emOrdem(NoPista *raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("- %s\n", raiz->pista);
        emOrdem(raiz->dir);
    }
}

int buscar(NoPista *raiz, char pista[]) {
    if (raiz == NULL)
        return 0;

    int cmp = strcmp(pista, raiz->pista);

    if (cmp == 0)
        return 1;
    else if (cmp < 0)
        return buscar(raiz->esq, pista);
    else
        return buscar(raiz->dir, pista);
}

// ================= EXPLORAÇÃO =================

void explorar(Sala *atual, NoPista **raizPistas) {
    char opcao;

    while (atual != NULL) {

        printf("\nVoce esta em: %s\n", atual->nome);

        // Se houver pista
        if (strlen(atual->pista) > 0) {
            printf("Voce encontrou uma pista: %s\n", atual->pista);

            if (!buscar(*raizPistas, atual->pista)) {
                *raizPistas = inserir(*raizPistas, atual->pista);
            }
        }

        printf("\nEscolha:\n");
        if (atual->esquerda) printf("e -> Esquerda\n");
        if (atual->direita) printf("d -> Direita\n");
        printf("p -> Ver pistas coletadas\n");
        printf("s -> Sair\n");
        printf("Opcao: ");

        scanf(" %c", &opcao);

        if (opcao == 'e' && atual->esquerda)
            atual = atual->esquerda;
        else if (opcao == 'd' && atual->direita)
            atual = atual->direita;
        else if (opcao == 'p') {
            printf("\n=== PISTAS EM ORDEM ALFABETICA ===\n");
            emOrdem(*raizPistas);
        }
        else if (opcao == 's')
            break;
        else
            printf("Opcao invalida!\n");
    }
}

// ================= MAIN =================

int main() {

    // Árvore da mansão
    Sala *hall = criarSala("Hall de Entrada", "");

    hall->esquerda = criarSala("Biblioteca", "Livro Rasgado");
    hall->direita = criarSala("Sala de Jantar", "");

    hall->esquerda->esquerda = criarSala("Sala Secreta", "Chave Antiga");
    hall->esquerda->direita = criarSala("Escritorio", "Carta Misteriosa");

    hall->direita->esquerda = criarSala("Cozinha", "Faca Ensanguentada");
    hall->direita->direita = criarSala("Jardim", "");

    NoPista *raizPistas = NULL;

    explorar(hall, &raizPistas);

    return 0;
}