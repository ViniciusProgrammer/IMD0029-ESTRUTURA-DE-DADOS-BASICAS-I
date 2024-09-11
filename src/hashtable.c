#include <stdio.h>
#include <stdlib.h>

#include "hashtable.h"
#include "concurso.h"

int hash(int key) {
    return key;
}

HashTable* criarHashTable(int tamanho_inicial) {
    HashTable* tabela = (HashTable*)malloc(sizeof(HashTable));
    if (!tabela) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    tabela->tabela = (Node**)calloc(tamanho_inicial, sizeof(Node*));
    if (!tabela->tabela) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    tabela->tamanho = tamanho_inicial;
    tabela->num_elementos = 0;
    return tabela;
}

void redimensionarHashTable(HashTable* tabela) {
    int novo_tamanho = tabela->tamanho * 2;
    Node** nova_tabela = (Node**)calloc(novo_tamanho, sizeof(Node*));

    for (int i = 0; i < tabela->tamanho; i++) {
        Node* atual = tabela->tabela[i];
        while (atual) {
            int novo_index = atual->idConcurso % novo_tamanho;
            Node* proximo = atual->next;

            atual->next = nova_tabela[novo_index];
            nova_tabela[novo_index] = atual;

            atual = proximo;
        }
    }

    free(tabela->tabela);
    tabela->tabela = nova_tabela;
    tabela->tamanho = novo_tamanho;
}

void destruirHashTable(HashTable* tabela) {
    for (int i = 0; i < tabela->tamanho; i++) {
        Node* atual = tabela->tabela[i];
        while (atual) {
            Node* temp = atual;
            atual = atual->next;
            free(temp);
        }
    }
    free(tabela->tabela);
    free(tabela);
}
