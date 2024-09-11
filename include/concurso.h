#ifndef CONCURSO_H
#define CONCURSO_H

#include "hashtable.h"
#include "estatisticas.h"

Node* criarConcurso(int numero_concurso, const char* data, int numeros[6]);
void inserirConcurso(HashTable* tabela, int numero_concurso, const char* data, int numeros[6]);
Node* buscarConcurso(HashTable* tabela, int numero_concurso);
void removerConcurso(HashTable* tabela, int numero_concurso);
void visualizarConcursos(HashTable* tabela);
void carregarConcursosDeArquivo(HashTable* tabela, const char* filename, const char* formato);
void apresentarEstatisticas(HashTable* tabela, int numero, int ano);

#endif
