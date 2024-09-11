#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "concurso.h"
#include "hashtable.h"

void menuInicial() {
    printf("1- Inserir Concurso\n");
    printf("2- Buscar Concurso\n");
    printf("3- Remover Concurso\n");
    printf("4- Visualizar Todos os Concursos\n");
    printf("5- Carregar Concursos\n");
    printf("6- Estatisticas\n");
    printf("7- Sair\n");
    printf("Escolha uma opcao: ");
}

void limparTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

char* toUpperCase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

int main(int argc, char *argv[]){

    int op;
    HashTable* tabela = criarHashTable(10);

    do {
        menuInicial();
        scanf("%d", &op);

        limparTerminal();
        switch (op) {
            case 1: {
                int numero_concurso, numeros[6];
                char data[11];
                printf("---Numero do Concurso: ");
                scanf("%d", &numero_concurso);
                printf("Data do Sorteio (dd-mm-yyyy): ");
                scanf("%s", data);
                printf("Digite os 6 numeros sorteados: ");
                for (int i = 0; i < 6; i++) {
                    scanf("%d", &numeros[i]);
                }
                limparTerminal();
                inserirConcurso(tabela, numero_concurso, data, numeros);
                break;
            }
            case 2: {
                int numero_concurso;
                printf("Numero do Concurso para Buscar: ");
                scanf("%d", &numero_concurso);
                Node* concurso = buscarConcurso(tabela, numero_concurso);
                
                limparTerminal();
                if (concurso) {
                    printf("-------------------------------------------------------------\n");
                    printf("Concurso: %d, Data: %s, Numeros: %d, %d, %d, %d, %d, %d\n",
                        concurso->idConcurso, concurso->data, concurso->numeros[0], concurso->numeros[1],
                        concurso->numeros[2], concurso->numeros[3], concurso->numeros[4], concurso->numeros[5]);
                    printf("-------------------------------------------------------------\n\n");
                } else {
                    printf("---Concurso nao encontrado!---\n\n");
                }
                break;
            }
            case 3: {
                int numero_concurso;
                printf("Numero do Concurso para Remover: ");
                scanf("%d", &numero_concurso);
                limparTerminal();
                removerConcurso(tabela, numero_concurso);
                break;
            }
            case 4:
                limparTerminal();
                visualizarConcursos(tabela);
                break;
            case 5: {
                char nomeArquivo[100], formato[4];
                printf("Nome do arquivo: ");
                scanf("%s", nomeArquivo);
                printf("Formato do arquivo (CSV ou TSV): ");
                scanf("%s", formato);
                limparTerminal();
                carregarConcursosDeArquivo(tabela, nomeArquivo, toUpperCase(formato));
                break;
            }
            case 6:{
                int numero, ano;
                printf("Quantidade de repeticoes do numero? ");
                scanf("%d", &numero);
                printf("Quantidade de concursos em qual ano? ");
                scanf("%d", &ano);
                limparTerminal();
                apresentarEstatisticas(tabela, numero, ano);
                break;
            }
            case 7:
                printf("---Saindo...\n");
                destruirHashTable(tabela);
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(op != 7);

    return 0;
}