#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct Node {
    int idConcurso;
    char data[11];
    int numeros[6];
    struct Node* next;
} Node;

typedef struct {
    Node** tabela;
    int tamanho;
    int num_elementos;
} HashTable;

HashTable* criarHashTable(int tamanho_inicial);
void redimensionarHashTable(HashTable* tabela);
void destruirHashTable(HashTable* tabela);
int hash(int key);

#endif
