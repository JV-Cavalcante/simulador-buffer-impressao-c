#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fila_circular.h"

int gerar_id() {
    #define MAX_ID 200
    #define MIN_ID 10
    return (rand() % (MAX_ID - MIN_ID + 1)) + MIN_ID;
}

struct Document* criar_documento(char* nome, int paginas, char prioridade) {
    struct Document* novo = (struct Document*)malloc(sizeof(struct Document));
    if (novo == NULL) return NULL;
    novo->id = gerar_id();
    strcpy(novo->nome, nome);
    novo->paginas = paginas;
    novo->prioridade = prioridade;
    return novo;
}

void inicializar_fila(struct Fila* f) {
    f->inicio = 0;
    f->fim = 0;
}

int esta_cheia(struct Fila *f) {
    return (f->fim + 1) % TAM_FILA == f->inicio;
}

int esta_vazia(struct Fila *f) {
    return f->fim == f->inicio;
}

void inserir(struct Document* dado, struct Fila* f) {
    if (esta_cheia(f)) {
        printf("Buffer cheio, nao e possivel inserir novos elementos.\n");
        return;
    }
    f->dados[f->fim] = dado;
    f->fim = (f->fim + 1) % TAM_FILA;
}

struct Document* remover(struct Fila* f) {
    if (esta_vazia(f)) return NULL;
    struct Document* dado_removido = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    return dado_removido;
}

struct Document* espiar(struct Fila* f) {
    if (esta_vazia(f)) return NULL;
    return f->dados[f->inicio];
}