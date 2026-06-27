#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>
#include "fila_circular.h"
#include "triagem.h"

int main() {
    srand(time(NULL));

    struct Fila fila_alta, fila_media, fila_baixa;
    inicializar_fila(&fila_alta);
    inicializar_fila(&fila_media);
    inicializar_fila(&fila_baixa);

    // Criando e Triando a massa de teste
    struct Document* doc1 = criar_documento("relatorio_financeiro.pdf", 3, 'B');
    struct Document* doc2 = criar_documento("tcc_final.docx", 4, 'C');
    struct Document* doc3 = criar_documento("passaporte_urgente.pdf", 2, 'A');

    triagem(&fila_alta, &fila_media, &fila_baixa, doc1);
    triagem(&fila_alta, &fila_media, &fila_baixa, doc2);
    triagem(&fila_alta, &fila_media, &fila_baixa, doc3);

    printf("--- INICIANDO PROCESSAMENTO DA IMPRESSORA ---\n\n");
    int ciclo = 1;

    while (!esta_vazia(&fila_alta) || !esta_vazia(&fila_media) || !esta_vazia(&fila_baixa)) {
        printf("[Ciclo %02d] ", ciclo++);
        struct Fila* fila_atual = NULL;
        char* rank_nome = "";

        if (!esta_vazia(&fila_alta)) {
            fila_atual = &fila_alta;
            rank_nome = "ALTA";
        } else if (!esta_vazia(&fila_media)) {
            fila_atual = &fila_media;
            rank_nome = "MEDIA";
        } else if (!esta_vazia(&fila_baixa)) {
            fila_atual = &fila_baixa;
            rank_nome = "BAIXA";
        }

        if (fila_atual != NULL) {
            struct Document* doc_em_impressao = espiar(fila_atual);
            printf("Fila: %s | ID: %d | '%s' | Paginas restantes: %d\n", 
                   rank_nome, doc_em_impressao->id, doc_em_impressao->nome, doc_em_impressao->paginas);

            doc_em_impressao->paginas--;

            if (doc_em_impressao->paginas == 0) {
                printf("  >> [CONCLUIDO] '%s' impresso com sucesso.\n", doc_em_impressao->nome);
                struct Document* removido = remover(fila_atual); 
                free(removido); 
            }
        }
        //sleep(1);
        Sleep(1000); //caso esteja em um ambiente windows 
    }

    printf("\n[Fim] Todas as filas processadas!\n");
    return 0;
}