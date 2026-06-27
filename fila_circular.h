#ifndef FILA_CIRCULAR_H
#define FILA_CIRCULAR_H

#define MAX_NOME 50
#define TAM_FILA 6

struct Document {
    int id;
    char nome[MAX_NOME];
    int paginas;
    char prioridade; // A = urgente, B = media, C = normal
};

struct Fila {
    struct Document* dados[TAM_FILA];
    int inicio; //cabeca da fila
    int fim; //cauda da fila
};

// Funções utilitárias
int gerar_id();
struct Document* criar_documento(char* nome, int paginas, char prioridade);

// Operações da Fila
void inicializar_fila(struct Fila* f);
int esta_cheia(struct Fila *f);
int esta_vazia(struct Fila *f);
void inserir(struct Document* dado, struct Fila* f);
struct Document* remover(struct Fila* f);
struct Document* espiar(struct Fila* f);

#endif