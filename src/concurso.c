#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "concurso.h"
#include "hashtable.h"
#include "estatisticas.h"

#define MAX_LINHA 100

Node* criarConcurso(int numero_concurso, const char* data, int numeros[6]) {
    Node* novoConcurso = (Node*)malloc(sizeof(Node));
    if (!novoConcurso) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }

    novoConcurso->idConcurso = numero_concurso;
    strncpy(novoConcurso->data, data, 11);
    memcpy(novoConcurso->numeros, numeros, 6 * sizeof(int));
    novoConcurso->next = NULL;

    return novoConcurso;
}

void inserirConcurso(HashTable* tabela, int numero_concurso, const char* data, int numeros[6]) {
    if (tabela->num_elementos >= tabela->tamanho * 0.75) {
        redimensionarHashTable(tabela);
    }

    int index = hash(numero_concurso) % tabela->tamanho;

    Node* atual = tabela->tabela[index];
    while (atual) {
        if (atual->idConcurso == numero_concurso) {
            printf("Concurso ja existe!\n");
            return;
        }
        atual = atual->next;
    }

    Node* novoConcurso = criarConcurso(numero_concurso, data, numeros);
    novoConcurso->next = tabela->tabela[index];
    tabela->tabela[index] = novoConcurso;
    tabela->num_elementos++;

    printf("---Concurso inserido com sucesso!---\n\n");
}

Node* buscarConcurso(HashTable* tabela, int numero_concurso) {
    int index = hash(numero_concurso) % tabela->tamanho;

    Node* atual = tabela->tabela[index];
    while (atual) {
        if (atual->idConcurso == numero_concurso) {
            return atual;
        }
        atual = atual->next;
    }

    return NULL;
}

void removerConcurso(HashTable* tabela, int numero_concurso) {
    int index = hash(numero_concurso) % tabela->tamanho;
    Node* atual = tabela->tabela[index];
    Node* anterior = NULL;

    while (atual) {
        if (atual->idConcurso == numero_concurso) {
            if (anterior) {
                anterior->next = atual->next;
            } else {
                tabela->tabela[index] = atual->next;
            }
            free(atual);
            tabela->num_elementos--;
            printf("---Concurso removido com sucesso!---\n\n");
            return;
        }
        anterior = atual;
        atual = atual->next;
    }

    printf("---Concurso nao encontrado!---\n\n");
}

void visualizarConcursos(HashTable* tabela) {
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < tabela->tamanho; i++) {
        Node* atual = tabela->tabela[i];
        while (atual) {
            printf("Concurso: %d, Data: %s, Numeros: %d, %d, %d, %d, %d, %d\n",
                atual->idConcurso, atual->data, atual->numeros[0], atual->numeros[1],
                atual->numeros[2], atual->numeros[3], atual->numeros[4], atual->numeros[5]);
            printf("-------------------------------------------------------------\n");
            atual = atual->next;
        }
    }
}

void carregarConcursosDeArquivo(HashTable* tabela, const char* nomeArq, const char* formato) {
    FILE* file = fopen(nomeArq, "r");
    if (!file) {
        printf("---Erro ao abrir o arquivo!---\n\n");
        return;
    }

    char linha[MAX_LINHA];
    char formatoLeitura[50];

    if (strcmp(formato, "CSV") == 0) {
        strcpy(formatoLeitura, "%d,%10[^,],%d,%d,%d,%d,%d,%d");
    } else if (strcmp(formato, "TSV") == 0) {
        strcpy(formatoLeitura, "%d\t%10[^\t]\t%d\t%d\t%d\t%d\t%d\t%d");
    } else {
        printf("---Formato desconhecido!---\n\n");
        fclose(file);
        return;
    }

    while (fgets(linha, sizeof(linha), file)) {
        int numero_concurso;
        int numeros[6];
        char data[11];

        if (sscanf(linha, formatoLeitura, &numero_concurso, data, &numeros[0], &numeros[1], &numeros[2], &numeros[3], &numeros[4], &numeros[5]) == 8) {
            inserirConcurso(tabela, numero_concurso, data, numeros);
        } else {
            printf("Erro ao processar a linha: %s\n", linha);
        }
    }

    fclose(file);
    printf("---Concursos carregados com sucesso!---\n\n");
}


void apresentarEstatisticas(HashTable* tabela, int numero, int ano) {
    printf("---Estatisticas:\n");

    quantidadeSorteiosNumero(tabela, numero);
    dezNumerosMaisSorteados(tabela);
    dezNumerosMenosSorteados(tabela);
    quantidadeConcursosAno(tabela, ano);
}

