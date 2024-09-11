#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

#define MAX_NUMEROS 60

typedef struct {
    int numero;
    int quantidade;
} Frequencia;

static int compararFrequencia(const void* a, const void* b) {
    return ((Frequencia*)a)->quantidade - ((Frequencia*)b)->quantidade;
}

void quantidadeSorteiosNumero(HashTable* tabela, int numero) {
    int count = 0;
    for (int i = 0; i < tabela->tamanho; i++) {
        Node* atual = tabela->tabela[i];
        while (atual) {
            for (int j = 0; j < 6; j++) {
                if (atual->numeros[j] == numero) {
                    count++;
                    break;
                }
            }
            atual = atual->next;
        }
    }
    printf("Quantidade de sorteios do numero %d: %d\n", numero, count);
}

void dezNumerosMaisSorteados(HashTable* tabela) {
    Frequencia frequencias[MAX_NUMEROS] = {0};
    int maxNumero = 0;

    for (int i = 0; i < tabela->tamanho; i++) {
        Node* atual = tabela->tabela[i];
        while (atual) {
            for (int j = 0; j < 6; j++) {
                int numero = atual->numeros[j];
                if (numero > maxNumero) maxNumero = numero;
                frequencias[numero].numero = numero;
                frequencias[numero].quantidade++;
            }
            atual = atual->next;
        }
    }

    qsort(frequencias, maxNumero + 1, sizeof(Frequencia), compararFrequencia);

    printf("Dez numeros mais sorteados:\n");
    for (int i = maxNumero; i >= 0 && maxNumero - i < 10; i--) {
        if (frequencias[i].quantidade > 0) {
            printf("Numero %d: %d veze(s)\n", frequencias[i].numero, frequencias[i].quantidade);
        }
    }
    printf("---------------------\n");
}

void dezNumerosMenosSorteados(HashTable* tabela) {
    Frequencia frequencias[MAX_NUMEROS] = {0};
    int maxNumero = 0;

    for (int i = 0; i < tabela->tamanho; i++) {
        Node* atual = tabela->tabela[i];
        while (atual) {
            for (int j = 0; j < 6; j++) {
                int numero = atual->numeros[j];
                if (numero > maxNumero) maxNumero = numero;
                frequencias[numero].numero = numero;
                frequencias[numero].quantidade++;
            }
            atual = atual->next;
        }
    }

    qsort(frequencias, maxNumero + 1, sizeof(Frequencia), compararFrequencia);

    printf("Dez numeros menos sorteados:\n");
    int contagem = 0;
    for (int i = 0; i < maxNumero + 1 && contagem < 10; i++) {
        if (frequencias[i].quantidade > 0) {
            printf("Numero %d: %d veze(s)\n", frequencias[i].numero, frequencias[i].quantidade);
            contagem++;
        }
    }
    printf("---------------------\n");
}

void quantidadeConcursosAno(HashTable* tabela, int ano) {
    int contagem = 0;
    for (int i = 0; i < tabela->tamanho; i++) {
        Node* atual = tabela->tabela[i];
        while (atual) {
            int anoConcerto = atoi(atual->data + 6); // Extrai o ano da data
            if (anoConcerto == ano) {
                contagem++;
            }
            atual = atual->next;
        }
    }
    printf("Total de concursos realizados no ano %d: %d\n\n", ano, contagem);
}
