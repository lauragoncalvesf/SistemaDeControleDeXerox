#include "pedido.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void obterData(char *data){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// Função para criar um novo pedido
Pedido* criarPedido(int numero, char nome[], char tipo[], int paginas, char status[]) {
    Pedido* p = (Pedido*) malloc(sizeof(Pedido));
    p->numero = numero;
    strcpy(p->nomeCliente, nome);
    strcpy(p->tipoSolicitante, tipo);
    p->quantidadePaginas = paginas;
    strcpy(p->status, status);  // Atribui o status

    obterData(p->dataCadastro);
    p->proximo = NULL;  // Inicialmente o próximo é NULL
    return p;
}

// Função para exibir um pedido
void exibirPedido(Pedido* p) {
    printf("Numero do Pedido: %d\n", p->numero);
    printf("Nome do Solicitante: %s\n", p->nomeCliente);
    printf("Tipo de Solicitante: %s\n", p->tipoSolicitante);
    printf("Quantidade de Páginas: %d\n", p->quantidadePaginas);
    printf("Data de Cadastro: %s\n", p->dataCadastro);
    printf("Status do Pedido: %s\n", p->status);
    printf("-----------------------------------\n");
}

// Função para listar todos os pedidos
void listarPedidos(Pedido* lista) {
    Pedido* atual = lista;
    if (atual == NULL) {
        printf("Nenhum pedido cadastrado.\n");
    }
    while (atual != NULL) {
        exibirPedido(atual);
        atual = atual->proximo;
    }
}

// Função para buscar um pedido por número
Pedido* buscarPedidoPorNumero(Pedido* lista, int numero) {
    Pedido* atual = lista;
    while (atual != NULL) {
        if (atual->numero == numero) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

// Função para buscar um pedido por nome
Pedido* buscarPedidoPorNome(Pedido* lista, char nome[]) {
    Pedido* atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->nomeCliente, nome) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

// Função para atualizar os números dos pedidos na lista
void atualizarNumerosPedidos(Pedido* lista) {
    int contador = 1; // Começa a contagem do número 1
    Pedido* atual = lista;

    while (atual != NULL) {
        atual->numero = contador; // Atribui o número atual
        contador++; // Incrementa o contador para o próximo pedido
        atual = atual->proximo; // Move para o próximo pedido
    }
}


// Função para excluir um pedido
void excluirPedido(Pedido** lista, int numero) {
    Pedido* atual = *lista;
    Pedido* anterior = NULL;

    while (atual != NULL && atual->numero != numero) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Pedido de número %d não encontrado.\n", numero);
        return;
    }

    if (anterior == NULL) { // O primeiro da lista deve ser removido
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Pedido de número %d excluído com sucesso.\n", numero);
    atualizarNumerosPedidos(*lista);
}


// Função para editar um pedido
void editarPedido(Pedido* p) {
    printf("Editando o pedido %d\n", p->numero);
    printf("Novo status do pedido (pendente, concluido, cancelado): ");
    scanf(" %[^\n]%*c", p->status);
    printf("Quantidade de páginas: ");
    scanf("%d", &p->quantidadePaginas);
    printf("Pedido editado com sucesso.\n");
}

// Função para consultar pedidos por status
void consultarPorStatus(Pedido* lista, char status[]) {
    Pedido* atual = lista;
    int encontrados = 0;
    while (atual != NULL) {
        if (strcmp(atual->status, status) == 0) {
            exibirPedido(atual);
            encontrados++;
        }
        atual = atual->proximo;
    }
    if (encontrados == 0) {
        printf("Nenhum pedido com o status '%s' foi encontrado.\n", status);
    }
}

// Função para calcular o total de cópias e o valor arrecadado
void calcularTotalCopiasEValor(Pedido* lista, float precoPorCopia) {
    Pedido* atual = lista;
    int totalCopias = 0;
    float valorArrecadado = 0.0;

    while (atual != NULL) {
        totalCopias += atual->quantidadePaginas;
        valorArrecadado += atual->quantidadePaginas * precoPorCopia;
        atual = atual->proximo;
    }

    printf("Total de cópias: %d\n", totalCopias);
    printf("Valor arrecadado: R$ %.2f\n", valorArrecadado);
}

// Função para inserir um pedido na lista encadeada
void inserirPedidoNaLista(Pedido** lista, Pedido* novoPedido) {
    if (*lista == NULL) {
        *lista = novoPedido;  // Se a lista estiver vazia, o novo pedido é o primeiro
    } else {
        Pedido* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;  // Percorre até o final da lista
        }
        atual->proximo = novoPedido;  // Insere o novo pedido no final
    }
}

// Função para salvar a lista de pedidos no arquivo
void salvarListaNoArquivo(Pedido* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");  // Abre o arquivo no modo de escrita (substitui o conteúdo anterior)
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Pedido* atual = lista;
    while (atual != NULL) {
        fprintf(arquivo, "Numero do Pedido: %d\n", atual->numero);
        fprintf(arquivo, "Nome do Solicitante: %s\n", atual->nomeCliente);
        fprintf(arquivo, "Tipo de Solicitante: %s\n", atual->tipoSolicitante);
        fprintf(arquivo, "Quantidade de Páginas: %d\n", atual->quantidadePaginas);
        fprintf(arquivo, "Data de Cadastro: %s\n", atual->dataCadastro);
        fprintf(arquivo, "Status do Pedido: %s\n", atual->status);
        fprintf(arquivo, "-----------------------------------\n");
        atual = atual->proximo;
    }

    fclose(arquivo);
}

// Função para liberar a memória da lista de pedidos
void liberarMemoria(Pedido* lista) {
    Pedido* atual = lista;
    while (atual != NULL) {
        Pedido* proximo = atual->proximo;
        free(atual);  // Libera o nó atual
        atual = proximo;  // Avança para o próximo
    }
    printf("Memória liberada com sucesso!\n");
}
void carregarPedidosDoArquivo(Pedido** lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo. Criando um novo arquivo.\n");
        return; // Se o arquivo não existir, não faz nada
    }

    Pedido* novoPedido;
    while (!feof(arquivo)) {
        novoPedido = (Pedido*) malloc(sizeof(Pedido));
        if (fscanf(arquivo, "Numero do Pedido: %d\n", &novoPedido->numero) != 1) {
            free(novoPedido);
            break; // Para caso não conseguir ler o número, sai do loop
        }
        fscanf(arquivo, "Nome do Solicitante: %[^\n]\n", novoPedido->nomeCliente);
        fscanf(arquivo, "Tipo de Solicitante: %[^\n]\n", novoPedido->tipoSolicitante);
        fscanf(arquivo, "Quantidade de Páginas: %d\n", &novoPedido->quantidadePaginas);
        fscanf(arquivo, "Data de Cadastro: %[^\n]\n", novoPedido->dataCadastro);
        fscanf(arquivo, "Status do Pedido: %[^\n]\n", novoPedido->status);
        fscanf(arquivo, "-----------------------------------\n"); // Ignora a linha separadora

        // Insere o pedido na lista
        novoPedido->proximo = NULL; // Inicializa o próximo como NULL
        inserirPedidoNaLista(lista, novoPedido);
    }

    fclose(arquivo);
}