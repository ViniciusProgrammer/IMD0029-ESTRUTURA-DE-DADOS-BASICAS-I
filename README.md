# Projeto: Gerenciador de Concursos da Mega-Sena com Tabela de Dispersão

Este projeto implementa um sistema para gerenciar concursos de loteria utilizando uma tabela hash para armazenar e recuperar dados. Os concursos incluem informações como número do concurso, data do sorteio e números sorteados. Além disso, o sistema oferece funcionalidades de inserção, busca, remoção e exibição dos concursos, além de permitir a análise estatística dos números sorteados.

## Estrutura de Pastas

O projeto segue a seguinte organização de diretórios:

```bash
src:      Contém os arquivos-fonte (.c) do projeto.
include:  Contém os arquivos de cabeçalho (.h) do projeto.
obj:      Diretório onde os arquivos-objeto (.o) são armazenados.
bin:      Diretório onde o executável final é gerado.
```

## Funcionalidades

### Módulo `concurso.h`

Este módulo define as funções principais para gerenciar os concursos de loteria.

- `Node* criarConcurso(int numero_concurso, const char* data, int numeros[6])`: Cria um novo concurso.
- `void inserirConcurso(HashTable* tabela, int numero_concurso, const char* data, int numeros[6])`: Insere um novo concurso na tabela hash.
- `Node* buscarConcurso(HashTable* tabela, int numero_concurso)`: Busca um concurso na tabela hash pelo seu número.
- `void removerConcurso(HashTable* tabela, int numero_concurso)`: Remove um concurso da tabela hash.
- `void visualizarConcursos(HashTable* tabela)`: Exibe todos os concursos armazenados.
- `void carregarConcursosDeArquivo(HashTable* tabela, const char* filename, const char* formato)`: Carrega concursos de um arquivo CSV ou TSV.
- `void apresentarEstatisticas(HashTable* tabela, int numero, int ano)`: Apresenta estatísticas sobre os concursos, incluindo frequências de números sorteados e quantidade de concursos por ano.

### Módulo `estatisticas.h`

Este módulo contém funções para análise estatística dos números sorteados nos concursos.

- `void quantidadeSorteiosNumero(HashTable* tabela, int numero)`: Conta quantas vezes um número foi sorteado.
- `void dezNumerosMaisSorteados(HashTable* tabela)`: Exibe os 10 números mais sorteados.
- `void dezNumerosMenosSorteados(HashTable* tabela)`: Exibe os 10 números menos sorteados.
- `void quantidadeConcursosAno(HashTable* tabela, int ano)`: Conta quantos concursos ocorreram em um determinado ano.

### Módulo `hashtable.h`

Este módulo define a estrutura da tabela hash usada para armazenar os concursos.

- `HashTable* criarHashTable(int tamanho_inicial)`: Cria uma tabela hash com tamanho inicial especificado.
- `void redimensionarHashTable(HashTable* tabela)`: Redimensiona a tabela hash quando a carga atinge um limite predefinido.
- `void destruirHashTable(HashTable* tabela)`: Libera a memória alocada para a tabela hash.
- `int hash(int key)`: Função de hash simples baseada na chave numérica do concurso.

## Entrada e Saída de Dados

O sistema permite a inserção de concursos manualmente via terminal ou através de arquivos formatados como CSV ou TSV. O formato do arquivo deve ser especificado ao carregar os dados.

Ao executar o programa, um menu interativo é apresentado com as seguintes opções:

- **Inserir Concurso**: Permite inserir manualmente um concurso com seu número, data e números sorteados.
- **Buscar Concurso**: Busca um concurso específico pelo número.
- **Remover Concurso**: Remove um concurso pelo número.
- **Visualizar Todos os Concursos**: Exibe todos os concursos armazenados.
- **Carregar Concursos**: Carrega concursos a partir de um arquivo CSV ou TSV.
- **Estatísticas**: Apresenta estatísticas sobre os números sorteados e a quantidade de concursos por ano.
- **Sair**: Encerra o programa e libera a memória alocada.

## Compilação

O projeto é compilado usando um Makefile. A estrutura básica do Makefile permite a compilação incremental e a organização dos arquivos de saída em diretórios apropriados.

### Comandos para compilar o projeto:

- `make`: Compila o projeto.
- `make clean`: Para limpar os arquivos-objeto e o executável gerado.
- `./bin/app`: Executa o programa.
