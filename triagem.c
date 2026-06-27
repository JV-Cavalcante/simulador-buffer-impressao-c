#include <stdio.h>
#include <stdlib.h>
#include "triagem.h"

void triagem(struct Fila* f_alta, struct Fila* f_media, struct Fila* f_baixa, struct Document* doc) {
    printf("[TRIAGEM] Processando arquivo: %s | Rank do arquivo %c\n", doc->nome, doc->prioridade);

    switch (doc->prioridade) {
        case 'A':
            if (!esta_cheia(f_alta)) {
                inserir(doc, f_alta);
                printf("  -> Sucesso: Inserido na Fila ALTA.\n");
            } else if (!esta_cheia(f_media)) {
                printf("  [AVISO] Fila ALTA cheia! Desviando para a Fila Média...\n");
                inserir(doc, f_media);
            } else {
                printf("  [ERRO CRITICO] Canais cheios. Arquivo '%s' rejeitado.\n", doc->nome);
                free(doc);
            }
            break;

        case 'B':
            if (!esta_cheia(f_media)) {
                inserir(doc, f_media);
                printf("  -> Sucesso: Inserido na Fila MEDIA.\n");
            } else if (!esta_cheia(f_baixa)) {
                printf("  [AVISO] Fila MEDIA cheia! Desviando para a Fila Baixa...\n");
                inserir(doc, f_baixa);
            } else {
                printf("  [ERRO] Buffer cheio. Arquivo '%s' rejeitado.\n", doc->nome);
                free(doc);
            }
            break;

        case 'C':
            if (!esta_cheia(f_baixa)) {
                inserir(doc, f_baixa);
                printf("  -> Sucesso: Inserido na Fila BAIXA.\n");
            } else {
                printf("  [ERRO] Fila BAIXA cheia! Arquivo '%s' rejeitado.\n", doc->nome);
                free(doc);
            }
            break;

        default:
            printf("  [ERRO] Prioridade '%c' invalida. Descartando.\n", doc->prioridade);
            free(doc);
            break;
    }
    printf("\n");
}