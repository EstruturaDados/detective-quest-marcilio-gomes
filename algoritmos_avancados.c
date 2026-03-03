#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 13
#define MAX 50

// ===================== BST =====================

typedef struct No {
    char pista[MAX];
    struct No *esq, *dir;
} No;

No* criarNo(char *pista) {
    No* novo = (No*) malloc(sizeof(No));
    strcpy(novo->pista, pista);
    novo->esq = novo->dir = NULL;
    return novo;
}

No* inserirBST(No* raiz, char *pista) {
    if (raiz == NULL)
        return criarNo(pista);

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esq = inserirBST(raiz->esq, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->dir = inserirBST(raiz->dir, pista);

    return raiz;
}

int buscarBST(No* raiz, char *pista) {
    if (raiz == NULL)
        return 0;

    if (strcmp(pista, raiz->pista) == 0)
        return 1;

    if (strcmp(pista, raiz->pista) < 0)
        return buscarBST(raiz->esq, pista);

    return buscarBST(raiz->dir, pista);
}

void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("- %s\n", raiz->pista);
        emOrdem(raiz->dir);
    }
}

void liberarBST(No* raiz) {
    if (raiz != NULL) {
        liberarBST(raiz->esq);
        liberarBST(raiz->dir);
        free(raiz);
    }
}

// ===================== HASH =====================

typedef struct Item {
    char pista[MAX];
    char suspeito[MAX];
    struct Item *prox;
} Item;

Item* tabela[TAM];

int funcaoHash(char *pista) {
    int soma = 0;
    for (int i = 0; pista[i] != '\0'; i++)
        soma += pista[i];
    return soma % TAM;
}

void inserirNaHash(char *pista, char *suspeito, No* raiz) {

    if (!buscarBST(raiz, pista)) {
        printf("❌ Pista nao existe na BST!\n");
        return;
    }

    int indice = funcaoHash(pista);

    Item* novo = (Item*) malloc(sizeof(Item));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);

    novo->prox = tabela[indice];
    tabela[indice] = novo;

    printf("✅ Associacao realizada com sucesso!\n");
}

void mostrarAssociacoes() {
    printf("\n=== PISTAS E SUSPEITOS ===\n");

    for (int i = 0; i < TAM; i++) {
        Item* atual = tabela[i];
        while (atual != NULL) {
            printf("Pista: %s -> Suspeito: %s\n",
                   atual->pista,
                   atual->suspeito);
            atual = atual->prox;
        }
    }
}

void suspeitoMaisCitado() {

    char suspeitos[100][MAX];
    int contagem[100];
    int total = 0;

    for (int i = 0; i < TAM; i++) {
        Item* atual = tabela[i];
        while (atual != NULL) {

            int encontrado = 0;

            for (int j = 0; j < total; j++) {
                if (strcmp(suspeitos[j], atual->suspeito) == 0) {
                    contagem[j]++;
                    encontrado = 1;
                    break;
                }
            }

            if (!encontrado) {
                strcpy(suspeitos[total], atual->suspeito);
                contagem[total] = 1;
                total++;
            }

            atual = atual->prox;
        }
    }

    if (total == 0) {
        printf("\nNenhum suspeito registrado.\n");
        return;
    }

    int maior = contagem[0];
    int indice = 0;

    for (int i = 1; i < total; i++) {
        if (contagem[i] > maior) {
            maior = contagem[i];
            indice = i;
        }
    }

    printf("\n🔎 Suspeito mais citado: %s (%d pistas)\n",
           suspeitos[indice], maior);
}

void liberarHash() {
    for (int i = 0; i < TAM; i++) {
        Item* atual = tabela[i];
        while (atual != NULL) {
            Item* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
}

// ===================== MENU =====================

int main() {

    No* raiz = NULL;

    for (int i = 0; i < TAM; i++)
        tabela[i] = NULL;

    int opcao;
    char pista[MAX];
    char suspeito[MAX];

    do {

        printf("\n===== MENU =====\n");
        printf("1 - Inserir pista\n");
        printf("2 - Listar pistas (ordem alfabetica)\n");
        printf("3 - Associar pista a suspeito\n");
        printf("4 - Mostrar associacoes\n");
        printf("5 - Mostrar suspeito mais citado\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {

            case 1:
                printf("Digite o nome da pista: ");
                fgets(pista, MAX, stdin);
                pista[strcspn(pista, "\n")] = 0;
                raiz = inserirBST(raiz, pista);
                printf("✅ Pista inserida!\n");
                break;

            case 2:
                printf("\n=== PISTAS EM ORDEM ===\n");
                emOrdem(raiz);
                break;

            case 3:
                printf("Digite a pista: ");
                fgets(pista, MAX, stdin);
                pista[strcspn(pista, "\n")] = 0;

                printf("Digite o suspeito: ");
                fgets(suspeito, MAX, stdin);
                suspeito[strcspn(suspeito, "\n")] = 0;

                inserirNaHash(pista, suspeito, raiz);
                break;

            case 4:
                mostrarAssociacoes();
                break;

            case 5:
                suspeitoMaisCitado();
                break;

            case 0:
                printf("Encerrando investigacao...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    liberarBST(raiz);
    liberarHash();

    return 0;
}