#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estrutura de clientes.

struct cliente {
  char nome[100];
  char cpf[15];
  char endereco[100];
};

// Estrutura de filmes.

struct filme {
  char titulo[100];
  char genero[100];
  int ano;
};

// Estrutura de locações.

struct locacao {
  char cliente[100];
  char titulo[100];
  char data[11];
};

// Funções para cadastrar dados.

// Função para cadastrar um novo cliente.
void cadastrarCliente() {

  struct cliente cadastrar;
  char opcao;
  FILE *arquivo;

  system("clear");
  printf("Por favor, cadastre o cliente no sistema.\n\n");

  do {
    printf("Digite o nome: ");
    scanf("%99[^\n]%*c", cadastrar.nome);
    printf("\nDigite o CPF: ");
    scanf("%14[^\n]%*c", cadastrar.cpf);
    printf("\nDigite o endereço: ");
    scanf("%99[^\n]%*c", cadastrar.endereco);

    arquivo = fopen("dados-de-clientes.txt", "a+");
    fprintf(arquivo, "%s %s %s\n", cadastrar.nome, cadastrar.cpf, cadastrar.endereco);
    fclose(arquivo);

    printf("\nDeseja cadastrar outro cliente?\nSIM [S] ou NÃO [N] \n: ");
    scanf("%c%*c", &opcao);
    opcao = toupper(opcao);

  } while (opcao == 'S');
}

// Função para cadastrar um novo filme.
void cadastrarFilme() {

  struct filme cadastrar;
  char opcao;
  FILE *arquivo;

  system("clear");
  printf("Por favor, cadastre o filme no sistema.\n\n");

  do {
    printf("Digite o título do filme: ");
    scanf("%99[^\n]%*c", cadastrar.titulo);
    printf("\nDigite o gênero do filme: ");
    scanf("%99[^\n]%*c", cadastrar.genero);
    printf("\nDigite o ano de lançamento do filme: ");
    scanf("%d%*c", &cadastrar.ano);

    arquivo = fopen("dados-de-filmes.txt", "a+");
    fprintf(arquivo, "%s %s %d\n", cadastrar.titulo, cadastrar.genero, cadastrar.ano);
    fclose(arquivo);

    printf("\nDeseja cadastrar outro filme?\nSIM [S] ou NÃO [N] \n: ");
    scanf("%c%*c", &opcao);
    opcao = toupper(opcao);

  } while (opcao == 'S');
}

// Função para cadastrar uma nova locação.
void cadastrarLocacao() {

  struct locacao cadastrar;
  char opcao;
  FILE *arquivo;

  system("clear");
  printf("Por favor, cadastre a locação do filme no sistema.\n\n");

  do {
    printf("Digite o nome do titular da locação: ");
    scanf("%99[^\n]%*c", cadastrar.cliente);
    printf("\nDigite o título do filme locado: ");
    scanf("%99[^\n]%*c", cadastrar.titulo);
    printf("\nDigite a data da locação: ");
    scanf("%10[^\n]%*c", cadastrar.data);

    arquivo = fopen("dados-de-locacoes.txt", "a+");
    fprintf(arquivo, "%s %s %s\n", cadastrar.cliente, cadastrar.titulo, cadastrar.data);
    fclose(arquivo);

    printf("\nDeseja Cadastrar outra locação?\nSIM [S] ou NÃO [N] \n: ");
    scanf("%c%*c", &opcao);
    opcao = toupper(opcao);

  } while (opcao == 'S');
}

// Funções para listar dados.

// Função para listar clientes cadastrados.
void listarClientes() {

  struct cliente listar;
  FILE *arquivo = fopen("dados-de-clientes.txt", "r");

  system("clear");
  printf("Clientes cadastrados no sistema.\n\n");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo!\nTente novamente...\n");
    return;
  }

  while (fscanf(arquivo, "%s %s %s\n", listar.nome, listar.cpf, listar.endereco) != EOF) {
    printf("Nome: %s, CPF: %s, Endereço: %s\n\n", listar.nome, listar.cpf, listar.endereco);
  }

  fclose(arquivo);
}

// Função para listar filmes cadastrados.
void listarFilmes() {

  struct filme listar;
  FILE *arquivo = fopen("dados-de-filmes.txt", "r");

  system("clear");
  printf("Filmes cadastrados no sistema.\n\n");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo!\nTente novamente...\n");
    return;
  }

  while (fscanf(arquivo, "%s %s %d", listar.titulo, listar.genero, &listar.ano) != EOF) {
    printf("Título: %s, Gênero: %s, Ano: %d\n\n", listar.titulo, listar.genero, listar.ano);
  }

  fclose(arquivo);
}

// Função para listar locações cadastradas.
void listarLocacoes() {

  struct locacao listar;
  FILE *arquivo = fopen("dados-de-locacoes.txt", "r");

  system("clear");
  printf("Locações cadastradas no sistema.\n\n");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo!\nTente novamente...\n");
    return;
  }

  while (fscanf(arquivo, "%s %s %s", listar.cliente, listar.titulo, listar.data) != EOF) {
    printf("Nome do cliente: %s, Título do filme: %s, Data de locação: %s\n\n", listar.cliente, listar.titulo, listar.data);
  }

  fclose(arquivo);
}

// Funções para excluir dados.

// Função para excluir um cliente.
void excluirCliente() {
  char nomeParaExcluir[100];

  system("clear");
  printf("Digite o nome do cliente a ser excluido: ");
  scanf("%99[^\n]%*c", nomeParaExcluir);

  FILE *arquivoEntrada = fopen("dados-de-clientes.txt", "r");
  FILE *arquivoTemporario = fopen("temporario1.txt", "w");

  if (arquivoEntrada == NULL || arquivoTemporario == NULL) {
    printf("Erro ao abrir os arquivos.\nTente novamente...\n");
    return;
  }

  struct cliente excluir;
  int encontrado = 0;

  while (fscanf(arquivoEntrada, "%s %s %s\n", excluir.nome, excluir.cpf, excluir.endereco) != EOF) {
      if (strcmp(excluir.nome, nomeParaExcluir) != 0) {
        fprintf(arquivoTemporario, "%s %s %s\n", excluir.nome, excluir.cpf, excluir.endereco);
      } else {
          encontrado = 1;
      }
  }
        
  fclose(arquivoEntrada);
  fclose(arquivoTemporario);

  if (encontrado) {
    remove("dados-de-clientes.txt");
    rename("temporario1.txt", "dados-de-clientes.txt");
    printf("Cliente excluído com sucesso!\n\n");
   } else {
      remove("temporario1.txt");
      printf("Cliente não encontrado!\nTente novamente...\n");
   }
}

// Função para excluir um filme.
void excluirFilme() {
  char nomeParaExcluir[100];

  system("clear");
  printf("Digite  o título do filme a ser excluido: ");
  scanf("%99[^\n]%*c", nomeParaExcluir);

  FILE *arquivoEntrada = fopen("dados-de-filmes.txt", "r");
  FILE *arquivoTemporario = fopen("temporario2.txt", "w");

  if (arquivoEntrada == NULL || arquivoTemporario == NULL) {
    printf("Erro ao abrir os arquivos.\nTente novamente...\n");
    return;
  }

  struct filme excluir;
  int encontrado = 0;

  while (fscanf(arquivoEntrada, "%s %s %d\n", excluir.titulo, excluir.genero, &excluir.ano) != EOF) {
      if (strcmp(excluir.titulo, nomeParaExcluir) != 0) {
        fprintf(arquivoTemporario, "%s %s %d\n", excluir.titulo, excluir.genero, excluir.ano);
      } else {
          encontrado = 1;
      }
  }
        
  fclose(arquivoEntrada);
  fclose(arquivoTemporario);

  if (encontrado) {
    remove("dados-de-filmes.txt");
    rename("temporario2.txt", "dados-de-filmes.txt");
    printf("Filme excluído com sucesso!\n\n");
   } else {
      remove("temporario2.txt");
      printf("Filme não encontrado!\nTente novamente....\n");
   }
}

// Função para excluir uma locação.
void excluirLocacao() {
  char nomeParaExcluir[100];

  system("clear");
  printf("Digite o nome do titular da Locação: ");
  scanf("%99[^\n]%*c", nomeParaExcluir);

  FILE *arquivoEntrada = fopen("dados-de-locacoes.txt", "r");
  FILE *arquivoTemporario = fopen("temporario3.txt", "w");

  if (arquivoEntrada == NULL || arquivoTemporario == NULL) {
    printf("Erro ao abrir os arquivos.\nTente novamente...\n");
    return;
  }

  struct locacao excluir;
  int encontrado = 0;

  while (fscanf(arquivoEntrada, "%s %s %s\n", excluir.cliente, excluir.titulo, excluir.data) != EOF) {
      if (strcmp(excluir.cliente, nomeParaExcluir) != 0) {
        fprintf(arquivoTemporario, "%s %s %s\n", excluir.cliente, excluir.titulo, excluir.data);
      } else {
          encontrado = 1;
      }
  }
        
  fclose(arquivoEntrada);
  fclose(arquivoTemporario);

  if (encontrado) {
    remove("dados-de-locacoes.txt");
    rename("temporario3.txt", "dados-de-locacoes.txt");
    printf("Locação excluída com sucesso!\n\n");
   } else {
      remove("temporario3.txt");
      printf("Titular da locação não encontrado!\nTente novamente...\n");
   }
}

// Função principal.
void main () {
  int opcao;
  system("clear");

  do {
    printf("Bem vindo ao Loca Facil - Sistema de Locadora de Filmes.\n");
    printf("Por favor, escolha uma das opções abaixo\n\n");
    printf("1 - Cadastrar novo cliente\n");
    printf("2 - Cadastrar novo filme\n");
    printf("3 - Cadastrar nova locação\n\n");
    printf("4 - Listar clientes cadastrados\n");
    printf("5 - Listar filmes cadastrados\n");
    printf("6 - Listar locações cadastradas\n\n");
    printf("7 - Excluir cliente\n");
    printf("8 - Excluir filme\n");
    printf("9 - Excluir locação\n\n");
    printf("0 - Sair do sistema\n\n");
    printf(": ");
    scanf("%d%*c", &opcao);

    switch (opcao) {
      case 1:
        cadastrarCliente();
        break;
      case 2:
        cadastrarFilme();
        break;
      case 3:
        cadastrarLocacao();
        break;
      case 4:
        listarClientes();
        break;
      case 5:
        listarFilmes();
        break;
      case 6:
        listarLocacoes();
        break;
      case 7:
        excluirCliente();
        break;
      case 8:
        excluirFilme();
        break;
      case 9:
        excluirLocacao();
        break;
      case 0:
        char confirmacao;

        system("clear");
        printf("Confirme para sair.\n\nNÃO [N] ou SIM [S]\n: ");
        scanf("%c%*c", &confirmacao);
        confirmacao = toupper(confirmacao);

        if (confirmacao == 'S') {
          system("clear");
          exit (0);
        } 

        default:
          system("clear");
          printf("Opção inválida. Tente novamente!\n\n");
          break;
      } 
  } while (1);
}
